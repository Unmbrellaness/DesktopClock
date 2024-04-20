#ifndef __TFTUTIL_H
#define __TFTUTIL_H

#include <TFT_eSPI.h>
#include <SPI.h>
#include "common.h"
#include "getInfo.h"
#include "PreferencesUtil.h"

extern TFT_eSPI tft;
extern TFT_eSprite clk;

void tftInit();
// void drawSpacemanGif(int x, int y,int delaytime);
void showImage(int32_t x, int32_t y, int32_t w, int32_t h, const uint16_t *data);//函数声明
// void displayTime(int x,int y);
// void displayData(int x,int y);
// void displayWeather(int x,int y);

// void drawSpacemanGif(int x, int y,int delaytime);
void draw_weather_photo(int x,int y,int weather_num);
void draw_temperature_and_humidity(int x,int y,int temperature_num,int humidity_num);
void draw_date(int x,int y,int year,int month,int day);
void draw_time(int x,int y,int hour,int min);
void draw_city_name(int x,int y,String city_name);
void showImage(int32_t x, int32_t y, int32_t w, int32_t h, const uint16_t *data);//函数声明

#endif