# README

## 说明

该项目是一个桌面小时钟，有查看时间、天气等功能。

## 项目结构

### arduinoPart

该文件夹的main中存放运行在单片机上的程序，其他为测试样例程序

#### main中的函数

###### getTimeFromNTPClient

功能：从NTP服务器获取时间，用来校验时间

传入参数：city，获取天气的城市,int *WeatherCode,int *Temperature}

###### getWeatherFromXinzhi

功能：从心知天气api获取天气参数，目前只能获取天气和温度

传入参数：city，获取天气的城市

传出参数：WeatherCode：天气对应的代码

​					Temperature：温度值（°C）

###### getTime

功能：从ds1302获取时间

###### setTime

功能：设置ds1302的时间

###### displayTime

###### displayData

###### displayWeather
