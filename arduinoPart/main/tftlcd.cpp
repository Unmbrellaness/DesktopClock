
#include "tftlcd.h"


#define TFT_GREY 0x5AEB
#define PI_BUF_SIZE 128

TFT_eSPI tft = TFT_eSPI(); 
TFT_eSprite clk = TFT_eSprite(&tft);

// 初始化tft
void tftInit(){
  tft.init();
  tft.setRotation(0);
  tft.setSwapBytes(true);

    // test
  tft.fillScreen(TFT_BLACK);
  delay(500);
  tft.fillScreen(TFT_RED);
  delay(500);
  // tft.fillScreen(TFT_GREEN);
  // delay(500);
  // tft.fillScreen(TFT_BLUE);
  // delay(500);
  // tft.fillScreen(TFT_BLACK);
  // delay(500);
  tft.fillScreen(TFT_WHITE);
  delay(500);
}


// //在屏幕上显示时间
// void displayTime(int x,int y){
//   tft.setTextSize(3); // 设置文本大小
//   tft.setTextColor(TFT_RED); // 设置文本颜色  
//   tft.setCursor(x, y); // 设置光标位置  
//   tft.print(hh);
//   tft.print(":");
//   tft.print(mm);
//   // tft.print(":");
//   // tft.print(ss);
  
// }

// //在屏幕上显示日期
// void displayData(int x,int y){
//   tft.setTextSize(3); // 设置文本大小
//   tft.setTextColor(TFT_RED); // 设置文本颜色  
//   tft.setCursor(x, y); // 设置光标位置  
//   tft.print(year);
//   tft.print("-");
//   tft.print(month);
//   tft.print("-");
//   tft.print(day);
// }

// //在屏幕上显示天气
// void displayWeather(int x,int y){
//   tft.setTextSize(3); // 设置文本大小
//   tft.setTextColor(TFT_RED); // 设置文本颜色  
//   tft.setCursor(x, y); // 设置光标位置 
//   tft.print("temp:"); 
//   tft.print(temperature);
//   tft.print("°C");
//   tft.setCursor(x, y+40); // 设置光标位置 
//   tft.print("wCode:");
//   tft.print(weatherCode);
// }

// 绘制太空机器人动图
void drawSpacemanGif(int x, int y,int delaytime){
  int w = 70;
  delaytime = 30;
  // put your main code here, to run repeatedly:
  tft.pushImage(x, y, w, w,yuhangyuan0);delay(delaytime);
  tft.pushImage(x, y, w, w,yuhangyuan1);delay(delaytime);
  tft.pushImage(x, y, w, w,yuhangyuan2);delay(delaytime);
  tft.pushImage(x, y, w, w,yuhangyuan3);delay(delaytime);
  tft.pushImage(x, y, w, w,yuhangyuan4);delay(delaytime);
  tft.pushImage(x, y, w, w,yuhangyuan5);delay(delaytime);
  tft.pushImage(x, y, w, w,yuhangyuan6);delay(delaytime);
  tft.pushImage(x, y, w, w,yuhangyuan7);delay(delaytime);
  tft.pushImage(x, y, w, w,yuhangyuan8);delay(delaytime);
  tft.pushImage(x, y, w, w,yuhangyuan9);delay(delaytime);
}

// 绘制天气图标
void draw_weather_photo(int x,int y,int weather_code){
  int w = 50;
  if(weather_code >= 0 && weather_code <= 1){
    // 晴
    tft.pushImage(x, y, w, w, qing);
  }
  else if(weather_code == 9){
    // 阴天
    tft.pushImage(x, y, w, w, yin);
  }
    else if(weather_code == 10 ||(weather_code >=13 && weather_code<=19)){
      // 雨
    tft.pushImage(x, y, w, w, yu);    
  }
    else if(weather_code >=4 && weather_code<=8){
      // 云
    tft.pushImage(x, y, w, w, yun);    
  }
    else if(weather_code == 12){
      // 冰雹
    tft.pushImage(x, y, w, w, bingbao);    
  }
    else if(weather_code >=30 && weather_code<=31){
      // 雾
    tft.pushImage(x, y, w, w, wu);    
  }
    else if(weather_code >=26 && weather_code<=29){
      // 沙尘
    tft.pushImage(x, y, w, w, shachen);    
  }
    else if(weather_code == 11){
      // 雷
    tft.pushImage(x, y, w, w, lei);    
  }
      else if(weather_code >=20 && weather_code<=25){
      // 雪
    tft.pushImage(x, y, w, w, xue);    
  }
  
}

// 绘制城市文字
void draw_city_name(int x,int y,String city_name){
  clk.createSprite(160,50);
  clk.loadFont(STHUPO40);
  clk.fillSprite(TFT_YELLOW);
  
  clk.drawString(city_name,0,10);
  clk.pushSprite(x,y); // 布局坐标
  clk.unloadFont();
  clk.deleteSprite();
}

// 绘制温度
void draw_temperature_and_humidity(int x,int y,int temperature_num,int humidity_num){
  int w = 40;
  // 绘制温湿度图标
  tft.pushImage(x, y, w, w, temperature_photo);
  tft.pushImage(x, y+50, w, w, humidity);

  int penColor = 0x0000;
  int totalLen = 63;

  int humidityLen = (humidity_num / 100.0) * totalLen;
  uint16_t temperatureLen = 30;
  
  uint16_t humidityColor = TFT_BLUE;
  uint16_t temperatureColor;

  //计算温度要显示的长度以及要显示的颜色
  if(temperature_num >= 40){ // 超过40度，红色高温预警
    temperatureLen = totalLen;
    temperatureColor = TFT_RED;
  }else if(temperature_num >= 35){ // 超过37度，橙色高温预警
    temperatureLen = totalLen - (40 - temperature_num);
    temperatureColor = 0xFC60;
  }else if(temperature_num > 0 && temperature_num < 35){
    temperatureLen = totalLen - (40 - temperature_num);
    temperatureColor = 0x2C3E;
  }else if(temperature_num <= 0){
    temperatureLen = totalLen - (40 - temperature_num);
    if(temperatureLen < 0){
      temperatureLen = 0;
    }
    temperatureColor = TFT_DARKGREY;
  }

// 绘制温度图
  clk.setColorDepth(8);
  clk.createSprite(65, 9); // 创建布局大小 宽x高
  clk.fillSprite(TFT_WHITE);
  clk.drawRoundRect(0,0,65,9,2,penColor); // 画进度条外边(x方向,y方向,长度,高度,圆角,颜色)
  clk.drawRoundRect(1,0,63,9,2,penColor); // 画进度条外边(x方向,y方向,长度,高度,圆角,颜色)
  clk.drawFastHLine(1,1,61,penColor);
  clk.drawFastHLine(1,7,61,penColor);
  clk.fillRoundRect(1,2,temperatureLen,5,2,temperatureColor);// 进度条填充(x方向,y方向,长度,高度,圆角,颜色)
  clk.pushSprite(x+w+10,y+20); // 布局坐标
  clk.deleteSprite();

// 绘制湿度图
  clk.setColorDepth(8);
  clk.createSprite(65, 9); // 创建布局大小 宽x高
  clk.fillSprite(TFT_WHITE);
  clk.drawRoundRect(0,0,65,9,2,penColor); // 画进度条外边(x方向,y方向,长度,高度,圆角,颜色)
  clk.drawRoundRect(1,0,63,9,2,penColor); // 画进度条外边(x方向,y方向,长度,高度,圆角,颜色)
  clk.drawFastHLine(1,1,61,penColor);
  clk.drawFastHLine(1,7,61,penColor);
  clk.fillRoundRect(1,2,humidityLen,5,2,humidityColor);// 进度条填充(x方向,y方向,长度,高度,圆角,颜色)
  clk.pushSprite(x+w+10,y+20+40); // 布局坐标
  clk.deleteSprite();


  clk.setColorDepth(8);
  clk.createSprite(60, 90); 
  clk.fillSprite(TFT_WHITE);
  clk.loadFont(clock_heiti_24);
  // tft.fillSprite(TFT_WHITE);
  // 这里需要修改，先把原来的温度覆盖，再换新的
  clk.setTextColor(temperatureColor);
  // tft.drawNumber(temperature,x+100,y+25);
  clk.drawString(String(temperature_num)+"℃",0,12);

  clk.setTextColor(humidityColor);
  // tft.drawNumber(humidity_num,x+100,y+25+40);
  clk.drawString(String(humidity_num)+"%",0,55);
  clk.unloadFont();
  clk.pushSprite(x+120,y); // 布局坐标
  clk.deleteSprite();

}


void draw_time(int x,int y,int hour,int min){
  String shour,smin;
  if(hour <10){
    shour = "0"+String(hour);
  }
  else{
    shour = String(hour);
  }
  if(min <10){
    smin = "0"+String(min);
  }
  else{
    smin = String(min);
  }
  clk.setColorDepth(8);
  clk.createSprite(240, 80);
  clk.setTextDatum(CC_DATUM);
  clk.loadFont(ITCBLKAD72);
  clk.fillSprite(TFT_GREEN);
  clk.setTextColor(TFT_RED);
  
  clk.drawString(shour+" : "+smin,120,40);
  clk.unloadFont();
  clk.pushSprite(x,y);
  clk.deleteSprite();
}

void draw_date(int x,int y,int year,int month,int day){
  clk.setColorDepth(8);
  clk.createSprite(200, 50);
  clk.setTextDatum(CC_DATUM);
  clk.loadFont(clock_num_mid_35);
  clk.fillSprite(TFT_YELLOW);
  clk.setTextColor(TFT_BLUE);
  
  clk.drawString(String(year)+" - "+String(month)+" - "+String(day),100,25);
  clk.unloadFont();
  clk.pushSprite(x,y);
  clk.deleteSprite();
}



void showImage(int32_t x, int32_t y, int32_t w, int32_t h, const uint16_t *data){
  int32_t dx = 0;
  int32_t dy = 0;
  int32_t dw = w;
  int32_t dh = h*2;
 
  if (x < 0) { dw += x; dx = -x; x = 0; }
  if (y < 0) { dh += y; dy = -y; y = 0; }
 
  if (dw < 1 || dh < 1) return;
 
  CS_L;
 
  data += dx + dy * w;
 
  uint16_t  buffer[PI_BUF_SIZE];
  uint16_t* pix_buffer = buffer;
  uint16_t  high,low;
 
  tft.setWindow(x, y, x + dw - 1, y + dh - 1);
 
  // Work out the number whole buffers to send
  uint16_t nb = (dw * dh) / (2 * PI_BUF_SIZE);
 
  // Fill and send "nb" buffers to TFT
  for (int32_t i = 0; i < nb; i++) {
    for (int32_t j = 0; j < PI_BUF_SIZE; j++) {
      high = pgm_read_word(&data[(i * 2 * PI_BUF_SIZE) + 2 * j + 1]);
      low = pgm_read_word(&data[(i * 2 * PI_BUF_SIZE) + 2 * j ]);
      pix_buffer[j] = (high<<8)+low;
    }
    tft.pushPixels(pix_buffer, PI_BUF_SIZE);
  }
 
  // Work out number of pixels not yet sent
  uint16_t np = (dw * dh) % (2 * PI_BUF_SIZE);
 
  // Send any partial buffer left over
  if (np) {
    for (int32_t i = 0; i < np; i++)
    {
      high = pgm_read_word(&data[(nb * 2 * PI_BUF_SIZE) + 2 * i + 1]);
      low = pgm_read_word(&data[(nb * 2 * PI_BUF_SIZE) + 2 * i ]);
      pix_buffer[i] = (high<<8)+low;
    }
    tft.pushPixels(pix_buffer, np);
  }
 
  CS_H;
}



