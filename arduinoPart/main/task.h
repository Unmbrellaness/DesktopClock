#ifndef __TASK_H
#define __TASK_H

#include "tftlcd.h"
#include "getInfo.h"
#include "net.h"


void startTimerQueryWeather();
void startTimerQueryTime();

void startRunner();
void executeRunner();

#endif