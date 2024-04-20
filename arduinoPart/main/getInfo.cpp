
#include "getInfo.h"


int hh=0,mm=0,ss=0;
int year=2024,day=1,month=1;
uint32_t targetTime=0;
int weatherCode=0;
int temperature=0;

void getTimeFromNTPClient();
void getWeatherFromXinzhi(String city,int *WeatherCode,int *Temperature);
void updataTime();

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

  int tm_Hour = timeClient.getHours();
  int tm_Minute = timeClient.getMinutes();
  int tm_Second = timeClient.getSeconds();

  Serial.print("ntp校准时间:");
  Serial.print(currentYear);
  Serial.print("年");
  Serial.print(currentMonth);
  Serial.print("月");
  Serial.print(currentDay);
  Serial.print("日 ");
  Serial.print(tm_Hour);
  Serial.print(":");
  Serial.print(tm_Minute);
  Serial.print(":");
  Serial.println(tm_Second);

  hh=tm_Hour;
  mm=tm_Minute;
  ss=tm_Second;
  year=currentYear;
  day=currentDay;
  month=currentMonth;

}


void updataTime(){
  // if(targetTime < millis())
  //   // Set next update for 1 second later
  //   targetTime = millis() + 1000;
  ss++;              // Advance second
  if (ss > 59){    // Check for roll-over
    ss = 0;          // Reset seconds to zero
    mm++;            // Advance minute
    if(mm > 59){   // Check for roll-over
      mm = 0;
      hh++;          // Advance hour
      if(hh > 23){ // Check for 24hr roll-over (could roll-over on 13)
        hh = 0;      // 0 for 24 hour clock, set to 1 for 12 hour clock
        day++;
        if(day>31&&((month == 1)||(month == 3)||(month == 5)||(month == 7)||(month == 8)||(month == 10)||(month == 12))){
          day = 1;
          month++;
          if(month>12){
            year++;
          }
        }
        else if(day>28&&(month == 2)){
          day = 1;
          month++;
          if(month>12){
            year++;
          }
        }
        else if(day>30){
          day = 1;
          month++;
          if(month>12){
            year++;
          }
        }
      }
    }
  }
}

//获取从心知天气api获取天气信息
void getWeatherFromXinzhi(String city,int *WeatherCode,int *Temperature){

  HTTPClient httpClient;
  httpClient.begin(nowURL);
  String weatherJson;

  const size_t capacity_weather = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 2*JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(6) + 210;
  
  DynamicJsonDocument doc(capacity_weather);

  int weatherCode;
  int temperature;
  // String weatherCode;
  // String temperature;

  int httpCode = httpClient.GET();
  Serial.print("Send GET request to URL: ");
  Serial.println(nowURL);

  if (httpCode == HTTP_CODE_OK) {
  // 使用getString函数获取服务器响应体内容，存入responsePayload
    weatherJson = httpClient.getString();
    // Serial.println("获取到：");
    Serial.println(weatherJson);
    //解析Json
    deserializeJson(doc, weatherJson);
    // weatherCode = doc["result"][0]["now"]["code"].as<String>();
    // temperature = doc["result"][0]["now"]["temperature"].as<String>();
    //获取字符串： doc["result"]["week_4"].as<String>();
    JsonObject results_0 = doc["results"][0];
    const char* results_0_location_name = results_0["location"]["name"]; // "Beijing"
    const char* results_0_location_country = results_0["location"]["country"]; // "CN"
    
    JsonObject results_0_now = results_0["now"];
    const char* results_0_now_text = results_0_now["text"]; // "Clear"
    const char* results_0_now_code = results_0_now["code"]; // "1"
    const char* results_0_now_temperature = results_0_now["temperature"]; // "3"
    
    const char* results_0_last_update = results_0["last_update"]; // "2020-03-01T20:10:00+08:00"  
  
    String location_name_String = results_0["location"]["name"].as<String>();
    int now_code_int = results_0_now["code"].as<int>();
    int now_temperature_int = results_0_now["temperature"].as<int>();
  
    Serial.println(now_code_int);
    Serial.println(now_temperature_int);
    weatherCode = now_code_int;
    temperature = now_temperature_int;
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


// // 查询实况天气
// void getNowWeather(){
//   bool cityLegal = true; // 记录城市字符串是否合法
//   String url = "https://api.seniverse.com/v3/weather/now.json?key=S1Ol8f-mnMEd88U89&location=beijing&language=zh-Hans&unit=c";
//   //创建 HTTPClient 对象
//   HTTPClient httpClient;
//   //连接持续3s
//   httpClient.setConnectTimeout(3000);
//   httpClient.begin(url);
//   //启动连接并发送HTTP请求
//   int httpCode = httpClient.GET();
//   Serial.println("正在获取天气数据");
//   //如果服务器响应OK则从服务器获取响应体信息并通过串口输出
//   if (httpCode == HTTP_CODE_OK) {
//     Serial.println("获取成功");
//     String str = httpClient.getString();
//     Serial.println(str);
//     if(str.indexOf("city不存在") > 0 || str.indexOf("errcode") > 0){ // 城市名称不合法
//       cityLegal = false;
//     }else{
//       StaticJsonDocument<512> doc;

//       DeserializationError error = deserializeJson(doc, str);

//       if (error) {
//         Serial.print("deserializeJson() failed: ");
//         Serial.println(error.c_str());
//         return;
//       }

//       JsonObject results_0 = doc["results"][0];

//       JsonObject results_0_location = results_0["location"];
//       const char* results_0_location_id = results_0_location["id"]; // "WX4FBXXFKE4F"
//       const char* results_0_location_name = results_0_location["name"]; // "北京"
//       const char* results_0_location_country = results_0_location["country"]; // "CN"
//       const char* results_0_location_path = results_0_location["path"]; // "北京,北京,中国"
//       const char* results_0_location_timezone = results_0_location["timezone"]; // "Asia/Shanghai"
//       const char* results_0_location_timezone_offset = results_0_location["timezone_offset"]; // "+08:00"

//       JsonObject results_0_now = results_0["now"];
//       const char* results_0_now_text = results_0_now["text"]; // "多云"
//       const char* results_0_now_code = results_0_now["code"]; // "4"
//       const char* results_0_now_temperature = results_0_now["temperature"]; // "2"

//       const char* results_0_last_update = results_0["last_update"]; // "2024-02-27T19:22:22+08:00"

//       Serial.println(results_0_location_id);
//       Serial.println(results_0_location_name);
//       Serial.println(results_0_location_country);
//       Serial.println(results_0_location_path);
//       Serial.println(results_0_location_timezone);
//       Serial.println(results_0_location_timezone_offset);
//       Serial.println(results_0_now_text);
//       Serial.println(results_0_now_code);
//       Serial.println(results_0_now_temperature);
//       Serial.println(results_0_last_update);
//     }    
//   } else {
//     Serial.print("请求实况天气错误：");
//     Serial.println(httpCode);
//   }
//   //关闭与服务器连接
//   httpClient.end();
// }

