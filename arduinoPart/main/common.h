#ifndef __COMMON_H
#define __COMMON_H

#include <Arduino.h>
#include "img/yuhangyuan/yuhangyuan0_black.h"
#include "img/yuhangyuan/yuhangyuan1_black.h"
#include "img/yuhangyuan/yuhangyuan2_black.h"
#include "img/yuhangyuan/yuhangyuan3_black.h"
#include "img/yuhangyuan/yuhangyuan4_black.h"
#include "img/yuhangyuan/yuhangyuan5_black.h"
#include "img/yuhangyuan/yuhangyuan6_black.h"
#include "img/yuhangyuan/yuhangyuan7_black.h"
#include "img/yuhangyuan/yuhangyuan8_black.h"
#include "img/yuhangyuan/yuhangyuan9_black.h"
#include "img/yuhangyuan/yuhangyuan0.h"
#include "img/yuhangyuan/yuhangyuan1.h"
#include "img/yuhangyuan/yuhangyuan2.h"
#include "img/yuhangyuan/yuhangyuan3.h"
#include "img/yuhangyuan/yuhangyuan4.h"
#include "img/yuhangyuan/yuhangyuan5.h"
#include "img/yuhangyuan/yuhangyuan6.h"
#include "img/yuhangyuan/yuhangyuan7.h"
#include "img/yuhangyuan/yuhangyuan8.h"
#include "img/yuhangyuan/yuhangyuan9.h"
#include "img/wea/xue.h"
#include "img/wea/lei.h"
#include "img/wea/shachen.h"
#include "img/wea/wu.h"
#include "img/wea/bingbao.h"
#include "img/wea/yun.h"
#include "img/wea/yu.h"
#include "img/wea/yin.h"
#include "img/wea/qing.h"
#include "img/wea/xue_black.h"
#include "img/wea/lei_black.h"
#include "img/wea/shachen_black.h"
#include "img/wea/wu_black.h"
#include "img/wea/bingbao_black.h"
#include "img/wea/yun_black.h"
#include "img/wea/yu_black.h"
#include "img/wea/yin_black.h"
#include "img/wea/qing_black.h"
#include "img/temperature_photo.h"
#include "img/humidity.h"
#include "img/temperature_black.h"
#include "img/humidity_black.h"
// #include "img/QRcode.h"
#include "font/clock_num_big_64.h"
#include "font/clock_timer_hour_52.h"
#include "font/clock_num_mid_35.h"
#include "font/clock_num_50.h"
#include "font/clock_heiti_24.h"
#include "font/clock_city_24.h"
#include "font/clock_tips_28.h"
#include "font/clock_timer_24.h"
#include "font/clock_future_weather_20.h"
#include "font/clock_other_title_35.h"
#include "font/clock_title_45.h"
#include "font/zh_front_20.h"
#include "font/ITCBLKAD72.h"
#include "font/STHUPO40.h"

#include<string.h>
using namespace std;

#define NTP3 "ntp5.ntsc.ac.cn"
#define NTP2 "ntp5.ict.ac.cn"
#define NTP1 "ntp5.aliyun.com"
#define BACK_BLACK 0
#define BACK_WHITE 1
#define D4 12  // 开发板D4灯
#define BUTTON 8 // 按钮引脚


// int ss=0,mm=0,hh=0,yyear=2024,mmonth=1,dday=1;

// 配置WiFi的网页代码
const String ROOT_HTML_PAGE1 PROGMEM = R"rawliteral(
  <!DOCTYPE html><html lang='zh'>
<head>
    <meta charset='UTF-8'>
    <meta name='viewport' content='width=device-width, initial-scale=1.0'>
    <link href='favicon.ico' rel='shortcut icon'>
    <title>叁零捌时钟配置页面</title>
    <style type='text/css'>
        #titleDiv{
            margin-top: 20px;
            height: 10%;
            width: 100%;
            text-align: center;
            font-size: 2rem;
            font-weight: bold;
        }
        .titleOption{
            text-align: center;
            margin-top: 30px;
            height: 40px;
            background-color: dodgerblue; 
            position: relative;
            color: #ffffff;
            border-radius: 5px;
            line-height: 40px;
        }
        #selectDiv {
            margin-top: 20px;
            height: 40px;
            border-radius: 5px;
            box-shadow: 0 0 5px #ccc;
            position: relative;   
        }
        select {
            border: none;
            outline: none;
            width: 100%;
            height: 40px;
            line-height: 40px;
            appearance: none;
            -webkit-appearance: none;
            -moz-appearance: none;
            text-align: center;
            font-size: 1rem;
        }
        .passAndCity{
            border: none;
            margin-top: 20px;
            height: 40px;
            border-radius: 5px;
            box-shadow: 0 0 5px #ccc;
            font-size: 1rem;
            position: relative;
            text-align: center;
        }
        #sub{
            text-align: center;
            margin-top: 50px;
            height: 40px;
            background-color: dodgerblue; 
            position: relative;
            color: #ffffff;
            border-radius: 5px;
            line-height: 40px;
            cursor: pointer;
        }
        #tail{
            font-size: 0.9rem;
            margin-top: 5px;
            width: 100%;
            text-align: center;
            color: #757575;
        }
    </style>
</head>
<body>
    <div id='titleDiv'>308时钟</div>
    <div id='tail'>叁零捌实验室室&nbsp&nbsp&nbsp&nbsp出品</div>
    <form action='configwifi' method='post' id='form' accept-charset="UTF-8">
        <div class='titleOption commonWidth'>WiFi名称</div>
        <div id='selectDiv' class='commonWidth'>
            <select name='ssid' id='ssid'>
                <option value=''></option>
)rawliteral";
const String ROOT_HTML_PAGE2 PROGMEM = R"rawliteral(
  </select>
        </div>
        <div class='titleOption commonWidth'>WiFi密码</div>
        <input type='text' placeholder='请输入WiFi密码' name='pass' id='pass' class='passAndCity commonWidth'>
        <div class='titleOption commonWidth'>城市名称（ 无需"市区县", 例 : 江阴 ）</div>
        <input type='text' placeholder='请输入城市名称' name='city' id='city' class='passAndCity commonWidth'>
        <div id='sub' onclick='doSubmit()'>提交</div>
    </form>
    <script type='text/javascript'>
        function doSubmit(){
            var select = document.getElementById('ssid');
            var selectValue = select.options[select.selectedIndex].value;
            if(selectValue == ''){
                alert('请选择要连接的WiFi');
                return;
            }
            if(document.getElementById('pass').value == ''){
                alert('请输入该WiFi的密码');
                return;
            }
            if(document.getElementById('city').value == ''){
                alert('请输入城市名称');
                return;
            }
            document.getElementById('form').submit();
        }
        var nodes = document.getElementsByClassName('commonWidth');
        var node = document.getElementById('sub');
        var screenWidth = window.screen.width;
        function setWidth(width){
            nodes[0].setAttribute('style',width);
            nodes[1].setAttribute('style',width);
            nodes[2].setAttribute('style',width);
            nodes[3].setAttribute('style',width);
            nodes[4].setAttribute('style',width);
            nodes[5].setAttribute('style',width);
        }
        if(screenWidth > 1000){
            setWidth('width: 40%;left: 30%;');
            node.setAttribute('style','width: 14%;left: 43%;');
        }else if(screenWidth > 800 && screenWidth <= 1000){
            setWidth('width: 50%;left: 25%;');
            node.setAttribute('style','width: 16%;left: 42%;');
        }else if(screenWidth > 600 && screenWidth <= 800){
            setWidth('width: 60%;left: 20%;');
            node.setAttribute('style','width: 20%;left: 40%;');
        }else if(screenWidth > 400 && screenWidth <= 600){
            setWidth('width: 74%;left: 13%;');
            node.setAttribute('style','width: 26%;left: 37%;');
        }else{
            setWidth('width: 90%;left: 5%;');
            node.setAttribute('style','width: 40%;left: 30%;');
        }
    </script>
</body>
</html>
)rawliteral";         

#endif
