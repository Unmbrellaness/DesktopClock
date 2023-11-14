#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <ArduinoJson.h>
#include <string.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


// *********************  define块
// 测试HTTP请求用的URL。注意网址前面必须添加"http://"
#define URL_WEATHER "https://api.seniverse.com/v3/weather/now.json?key=S1Ol8f-mnMEd88U89&location=xian&language=zh-Hans&unit=c"
// 完整格式：https://api.seniverse.com/v3/weather/now.json?key=S1Ol8f-mnMEd88U89&location=xian&language=zh-Hans&unit=c

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_MOSI   5  //DI   ------ D1
#define OLED_CLK    4  //D0  ------- D2
#define OLED_DC    14  //DC  ------- D5
#define OLED_CS    12  //CS  ------- D6
#define OLED_RESET 13  //RES -------D7
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
// *********************  define块 结束




// ********************* 全局变量块
// 设置wifi接入信息(请根据您的WiFi信息进行修改)
char *ssid     = "308E";
char *password = "308308308";

// WiFiUDP ntpUDP;
// NTPClient timeClient(ntpUDP,"europe.pool.ntp.org",60*60*8);
// *********************  全局变量块 结束
 


void setup() {
  // 串口初始化
  Serial.begin(9600);
  // 自动连接wifi
  connectWIFI(ssid,password);
  // oled初始化
  oledInit();
  // 获取时间
  // getTime();
}

void loop() {
  // getTime();
  // delay(500);
}

//连接wifi
void connectWIFI(char* ssid,char* password){
  //设置ESP8266工作模式为无线终端模式
  WiFi.mode(WIFI_STA);
 
  //开始连接wifi
  WiFi.begin(ssid, password);
 
  //等待WiFi连接,连接成功打印IP
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi Connected!");
}

//获取从网络获取时间，代码不太合理，以后要改
/*
void getTime(){
  HTTPClient httpClient;
  httpClient.begin(URL_TIME); 
  String timeJson;

  const size_t capacity_time = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(7) + 170;
  DynamicJsonDocument doc(capacity_time);
  String Time;
  String Week;

  int httpCode = httpClient.GET();
  Serial.print("Send GET request to URL: ");
  Serial.println(URL_TIME);

  if (httpCode == HTTP_CODE_OK) {
  // 使用getString函数获取服务器响应体内容，存入responsePayload
    timeJson = httpClient.getString();
    // Serial.println("获取到：");
    // Serial.println(timeJson);
    //解析Json
    deserializeJson(doc, timeJson);
    Time = doc["result"]["datetime_1"].as<String>();
    Week = doc["result"]["week_4"].as<String>();

    display.clearDisplay();
    display.setTextSize(2); //选择字号
    display.setTextColor(WHITE);  //字体颜色
    display.setCursor(0,0);
    display.print(Week);
    display.setCursor(0,32);
    display.print(Time);
    display.display();
    // delay(2000);
  } 
  else {//未获取，返回错误code
    Serial.println("Server Respose Code:");
    Serial.println(httpCode);

    display.clearDisplay();
    display.setTextSize(2); //选择字号
    display.setTextColor(WHITE);  //字体颜色
    display.setCursor(0,0);
    display.print("ERROR!!!");
    display.display();
  }

  Serial.println(Time);
  Serial.println(Week);



  httpClient.end();
}
*/

//从NTP服务器获取时间，用来校准日期，未完成
void getTimeFromNTPClient(){
  WiFiUDP ntpUDP;
  NTPClient timeClient(ntpUDP,"europe.pool.ntp.org",60*60*8);
  timeClient.begin();
  timeClient.update();
  String Week[7] = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
  String Time = timeClient.getFormattedTime();
  int weekNum = timeClient.getDay();
  int EpochTime = timeClient.getEpochTime();
  
  struct tm *ptm = gmtime((time_t *)&EpochTime);
  int currentYear = ptm->tm_year + 1900;
  int currentDay = ptm->tm_mday;
  int currentMonth = ptm->tm_mon + 1;

  Serial.print(currentYear);
  Serial.print("年");
  Serial.print(currentMonth);
  Serial.print("月");
  Serial.print(currentDay);
  Serial.println("日");


}


//获取从心知天气api获取天气信息
void getWeather(char* city,int *WeatherCode,int *Temperature){

  // //获取传入的城市的天气数据
  // char* url_weather1 = "https://api.seniverse.com/v3/weather/now.json?key=S1Ol8f-mnMEd88U89&location=" 
  // char* url_weather2 = "&language=zh-Hans&unit=c" 
  // strcat(url_weather1, city);
  // strcat(url_weather1, url_weather2)
  // Serial.println(url_weather1);

  HTTPClient httpClient;
  httpClient.begin(URL_WEATHER);
  String weatherJson;

  const size_t capacity_weather = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 2*JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(6) + 210;
  
  DynamicJsonDocument doc(capacity_weather);

  int weatherCode;
  int temperature;

  int httpCode = httpClient.GET();
  Serial.print("Send GET request to URL: ");
  Serial.println(URL_WEATHER);

  if (httpCode == HTTP_CODE_OK) {
  // 使用getString函数获取服务器响应体内容，存入responsePayload
    weatherJson = httpClient.getString();
    // Serial.println("获取到：");
    Serial.println(weatherJson);
    //解析Json
    deserializeJson(doc, weatherJson);
    weatherCode = doc["result"]["now"]["code"];
    temperature = doc["result"]["now"]["temperature"];
    //获取字符串： doc["result"]["week_4"].as<String>();
  } 
  else {//未获取，返回错误code
    Serial.println("Server Respose Code:");
    Serial.println(httpCode);
  }

  Serial.println(weatherCode);
  Serial.println(temperature);

  *WeatherCode = weatherCode;
  *Temperature = temperature;

  httpClient.end();
}

//oled初始化
void oledInit(){
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
}




