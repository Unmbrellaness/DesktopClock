#include <Preferences.h>
#include "net.h"

Preferences prefs; // 声明Preferences对象

// 读取Wifi账号、密码和城市名称
void getWiFiCity(){
  prefs.begin("clock");
  ssid = prefs.getString("ssid", "");
  pass = prefs.getString("pass", "");
  city = prefs.getString("city", "");
  prefs.end();
}

// 写入Wifi账号、密码和城市名称
void setWiFiCity(String ssid,String pass,String city){
  prefs.begin("clock");
  prefs.putString("ssid", ssid);
  prefs.putString("pass", pass);
  prefs.putString("city", city);
  prefs.end();
}

// 清除Wifi账号、密码和城市名称
void clearWiFiCity(){
  prefs.begin("clock");
  prefs.remove("ssid");
  prefs.remove("pass");
  prefs.remove("city");
  prefs.remove("backColor");
  prefs.end();
}

// 测试用，在读取NVS之前，先写入自己的Wifi信息，免得每次浪费时间再配网
void setInfoBeforeApWifi(){
  prefs.begin("clock");
  prefs.putString("ssid", "HUAWEI Phone");
  prefs.putString("pass", "15713121521");
  prefs.putString("city", "xian");
  prefs.end();
}