#ifndef __NET_H
#define __NET_H

#include "common.h"
#include <HTTPClient.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>

#define NTP3 "ntp5.ntsc.ac.cn"
#define NTP2 "ntp5.ict.ac.cn"
#define NTP1 "ntp5.aliyun.com"

void wifiConfigBySoftAP(void);
void doClient(void);
void connectWIFI(String ssid,String password,int outTimes);

extern String ssid;
extern String pass;
extern String city;
extern int currentPage;



#endif