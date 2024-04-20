
#include <ArduinoJson.h>
#include <String.h>

#include <SPI.h>
#include <Wire.h>
#include <WiFi.h>

#include <HTTPClient.h>
#include <WebServer.h>

#include "tftlcd.h"
#include "getInfo.h"
#include "net.h"
#include "task.h"
#include "common.h"
#include "PreferencesUtil.h"


// ********************* 全局变量块
// 设置wifi接入信息(请根据您的WiFi信息进行修改)

int currentPage = 0;

// *********************  全局变量块 结束 ****************


hw_timer_t * timer = NULL;
void IRAM_ATTR onTimer() {            //中断函数
  updataTime();
}

void setup() {

  // 定时器初始化
  timer = timerBegin(0, 80, true);                //初始化
  timerAttachInterrupt(timer, &onTimer, true);    //调用中断函数
  timerAlarmWrite(timer, 1000000, true);        //timerBegin的参数二 80位80MHZ，这里为1000000  意思为1秒
  timerAlarmEnable(timer);                //定时器使能

  // 串口初始化
  Serial.begin(9600);
  // tftlcd初始化
  tftInit();
  // 配网
  // 提前写入固定的wifi信息
  setInfoBeforeApWifi();
  getWiFiCity();
  Serial.print("ssid:");
  Serial.println(ssid);
  Serial.print("pass:");
  Serial.println(pass);
  Serial.print("city:");
  Serial.println(city);
  if(ssid.length() == 0 || pass.length() == 0 || city.length() == 0 ){
    wifiConfigBySoftAP();
  }
  else{
    Serial.print("ssid");
    Serial.println(ssid);
    Serial.print("pass");
    Serial.println(pass);
    connectWIFI(ssid, pass, 10);
  }

  if(WiFi.status() == WL_CONNECTED){
    currentPage = 2;
    getTimeFromNTPClient();
    getWeatherFromXinzhi(city, &weatherCode,&temperature);
    // displayData(0,0);
    // displayTime(0,40);
    startRunner();
    draw_weather_photo(240-50-20,20,weatherCode);
  }

}

void loop() {
  if(currentPage == 0){
    doClient();
  }
  else{
    executeRunner();
    // tft.fillRect(0, 0, 240, 180, TFT_WHITE);
    // displayData(0,0);
    // displayTime(0,40);
    // displayWeather(0,80);
        // executeRunner();
    // updataTime();
    // draw_temperature_and_humidity(0, 230, temperature, 75);
    // draw_time(0, 80, hh, mm);
    // draw_date(0, 80+80, year, month, day);
    // draw_city_name(0,0,"西安");
    // drawSpacemanGif(240-70,320-90,400);
    // displayTimeCLK(0,0);
    // Serial.println("executeRunner");
  }
  

}




