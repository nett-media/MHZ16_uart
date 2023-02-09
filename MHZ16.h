#pragma once

#include <Arduino.h>

void initMhz16();
void initMhz16(int _rx_pin, int _tx_pin);
int getCo2PPM();

static const int REQUEST_CNT = 8;
static const int RESPONSE_CNT = 9;
