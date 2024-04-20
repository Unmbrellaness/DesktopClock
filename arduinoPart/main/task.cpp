
#include <TaskScheduler.h>
#include "task.h"


//声明任务执行函数
void tUpdataTimeCallback();
void tUpdataWeatherCallback();
void tCheckWifiCallback();
void tDrawTimeCallback();
// void tCalculateTimeCallback();
void tDrawDateCallback();

// void tDrawDataCallback();

 
Scheduler runner;
// 定义任务
Task tUpdataTime(1000 *60 *30, TASK_FOREVER, &tUpdataTimeCallback, &runner, true);//更新时间，每30min一次
Task tUpdataWeather(1000*60*30, TASK_FOREVER, &tUpdataWeatherCallback, &runner, true);//更新天气，每30min一次
//Task tCheckWifi(1000, TASK_FOREVER, &tCheckWifiCallback, &runner);//检查wifi
Task tDrawTime(100, TASK_FOREVER, &tDrawTimeCallback, &runner, true);//画时间，每0.1s画一次
Task tDrawDate(1000, TASK_FOREVER, &tDrawDateCallback, &runner, true);//画日期，每1s画一次
// Task tCalculateTime(50, TASK_FOREVER, &tCalculateTimeCallback, &runner, true);//更新时间，每0.1s一次

// 启动runner
void startRunner(){
  runner.startNow();
}
// 执行runner
void executeRunner(){
  runner.execute();
}

//////////////// 定时器相关区域//////////////////////////////////////////
// 定义定时器
hw_timer_t *timerQueryWeather = NULL;
hw_timer_t *timerQueryTime = NULL;
void IRAM_ATTR onTimerQueryWeather() {
  // 使能查询天气的多线程任务
  tUpdataWeather.enable();
} 
void IRAM_ATTR onTimerQueryTime() {
  // 使能查询天气的多线程任务
  tUpdataTime.enable();
} 
// 初始化定时器，让查询天气的多线程任务在一小时后再使能
void startTimerQueryWeather(){
  timerQueryWeather = timerBegin(0, 80, true);// 1us计数一次
  timerAttachInterrupt(timerQueryWeather, &onTimerQueryWeather, true); 
  timerAlarmWrite(timerQueryWeather, 60*60*1000000, false); // 执行完一次后就取消这个定时器 (3600000000)3600秒，即60分钟后使能
  timerAlarmEnable(timerQueryWeather); 
}

// 初始化定时器，让查询天气的多线程任务在一小时后再使能
void startTimerQueryTime(){
  timerQueryTime = timerBegin(0, 80, true);// 1us计数一次
  timerAttachInterrupt(timerQueryTime, &onTimerQueryTime, true); 
  timerAlarmWrite(timerQueryTime, 30*60*1000000, false);
  timerAlarmEnable(timerQueryTime); 
}



/////////// 多任务协程回调区域 ////////////////////////////////////////
// NTP对时
void tUpdataTimeCallback(){
  getTimeFromNTPClient();
}

// 检查Wifi状态,如果失败，重新连接
void tCheckWiFiCallback(){
  Serial.println("开始检查网络状态");
  // checkWiFiStatus();
}

void tUpdataWeatherCallback(){
  getWeatherFromXinzhi(city,&weatherCode,&temperature);
  draw_temperature_and_humidity(0, 230, temperature, 75);
  draw_city_name(0,0,"西安");
}

void tDrawTimeCallback(){
  draw_time(0, 80, hh, mm);
  // Serial.println("tDrawTimeCallback:");
  // Serial.println(hh);
  // Serial.println(":");
  // Serial.println(mm);
}

// void tCalculateTimeCallback(){
//   updataTime();
// }


void tDrawDateCallback(){
  draw_date(0, 80+80, year, month, day);
  // Serial.println("tDrawDateCallback:");
  // Serial.println(year);
  // Serial.println("-");
  // Serial.println(month);
  // Serial.println("-");
  // Serial.println(day);
}





