#ifndef __GETINFO_H
#define __GETINFO_H

#include <WiFiUdp.h>
#include <NTPClient.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>
#include "tftlcd.h"
#include "common.h"

// 测试HTTP请求用的URL。注意网址前面必须添加"http://"
// 天气接口
const String nowURL = "https://api.seniverse.com/v3/weather/now.json?key=S1Ol8f-mnMEd88U89&location=xian&language=zh-Hans&unit=c";  //查询实况天气的接口地址
#define URL_WEATHER "http://api.seniverse.com/v3/weather/now.json?key=S1Ol8f-mnMEd88U89&location=xian&language=zh-Hans&unit=c"
// 完整格式：https://api.seniverse.com/v3/weather/now.json?key=S1Ol8f-mnMEd88U89&location=xian&language=zh-Hans&unit=c

extern int hh,mm,ss;
extern int year,day,month;
extern uint32_t targetTime;
extern int weatherCode;
extern int temperature;

void getTimeFromNTPClient();
void getWeatherFromXinzhi(String city,int *WeatherCode,int *Temperature);
void updataTime();

#endif