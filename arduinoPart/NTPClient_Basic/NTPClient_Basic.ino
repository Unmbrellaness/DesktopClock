
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

################ define块
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

################# define块 结束

################# 全局变量块
const char *ssid     = "308E";
const char *password = "308308308";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP,"europe.pool.ntp.org",60*60*8);
################# 全局变量块 结束


void setup(){
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
  oledInit();
  timeClient.begin();
}


void loop() {
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

  Serial.println(Time);
  display.clearDisplay();
  display.setTextSize(1); //选择字号
  display.setTextColor(WHITE);  //字体颜色
  display.setCursor(0,0);
  display.print(Week[weekNum]);

  display.setCursor(0,16);
  // display.print(EpochTime);
  display.print(currentYear);
  display.print("-");
  display.print(currentMonth);
  display.print("-");
  display.print(currentDay);

  display.setCursor(0,32);
  display.print(Time);

  display.display();

  delay(500);
}

void oledInit(){
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
}
