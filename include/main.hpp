#ifndef MAIN_HPP 
#define MAIN_HPP

#include <Adafruit_BMP085.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Arduino.h>

#include <Ticker.h>

#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiUdp.h>
// C++ libraries
#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <bits/stdc++.h>
#include <cmath>

// OLED Screen
#define nombreDePixelsEnLargeur 128         // Taille de l'écran OLED, en pixel, au niveau de sa largeur
#define nombreDePixelsEnHauteur 64          // Taille de l'écran OLED, en pixel, au niveau de sa hauteur
#define brocheResetOLED         -1          // Reset de l'OLED partagé avec l'Arduino (d'où la valeur à -1, et non un numéro de pin)
#define adresseI2CecranOLED     0x3C        // Adresse de "mon" écran OLED sur le bus i2c (généralement égal à 0x3C ou 0x3D)

// Frame
#define FRAME_DELAY (64)
#define FRAME_WIDTH (48)
#define FRAME_HEIGHT (48)
#define FRAME_STORM_COUNT (sizeof(stormBitmap) / sizeof(stormBitmap[0]))
#define FRAME_SUNNY_COUNT (sizeof(sunnyBitmap) / sizeof(sunnyBitmap[0]))
#define FRAME_CLOUDY_COUNT (sizeof(cloudyBitmap) / sizeof(cloudyBitmap[0]))
#define FRAME_RAINY_COUNT (sizeof(rainyBitmap) / sizeof(rainyBitmap[0]))
#define FRAME_SUN_OVER_COUNT (sizeof(sunOvercast) / sizeof(sunOvercast[0]))
#define FRAME_NIGHT_OVER_COUNT (sizeof(nightOvercast) / sizeof(nightOvercast[0]))
#define FRAME_NIGHT_COUNT (sizeof(clearNight) / sizeof(clearNight[0]))

using std::string;

extern const byte   stormBitmap[][288];
extern const byte   sunnyBitmap[][288];
extern const byte   cloudyBitmap[][288];
extern const byte   rainyBitmap[][288];
extern const byte   sunOvercast[][288];
extern const byte   nightOvercast[][288];
extern const byte   clearNight[][288];

enum BitmapType {
    STORM,
    SUNNY,
    NIGHT,
    CLOUDY,
    RAINY,
    SUN_OVERCAST,
    NIGHT_OVERCAST
};

extern time_t  rawTime;
extern struct tm *timeinfo;

const byte* setBitmap(BitmapType bitmap, int frame);
BitmapType setBitmapEnum(int pressure);
void    setTime();
string  get_temp(float temperature);
string  get_pressure(int pressure);
void    displayTime();
void    light_error();
void  sendData(float temperature, int pressure);

#endif