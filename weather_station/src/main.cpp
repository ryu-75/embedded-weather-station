#include "main.hpp"

Adafruit_BMP085 bmp;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 0, 60000);
Adafruit_SSD1306 oled(nombreDePixelsEnLargeur, nombreDePixelsEnHauteur, &Wire, brocheResetOLED);

time_t  rawTime;
struct tm *timeinfo;

const char* ssid = "Freebox-61C6B4";
const char* password = "compromisi&3-puera-subdetur-posthumis4";

string  get_temp(float temperature) {
  oled.setCursor(5, 16);
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  return std::to_string(temperature) + " C";
}

string get_pressure(int pressure) {
  oled.setCursor(5, 28);
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  return std::to_string(pressure) + " hPa";
}

string get_relative_humidity(double humidity) {
  oled.setCursor(5, 28);
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  return std::to_string(humidity) + " %";
}

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }

  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
  
  if (!oled.begin(SSD1306_SWITCHCAPVCC, adresseI2CecranOLED)) {
    Serial.println("Initialization failed");
    while (1);
  }

  if (!bmp.begin()) {
    Serial.println("Could not found a valid BMP sensor, check wiring!");
    while (1);
  }

  timeClient.begin();
  pinMode(LED_BUILTIN, OUTPUT);
}

int frame = 0;
unsigned long currentTime = 0;
unsigned long previousTime = 0;

void loop() {
  currentTime = millis();
  
  if ((currentTime - previousTime) >= FRAME_DELAY) {
    float temperature = bmp.readTemperature();
    int pressure = bmp.readSealevelPressure() / 100;
    
    timeClient.update();
    previousTime = currentTime;
    frame++;
    setTime();
    BitmapType type = setBitmapEnum(pressure);
    const byte* const bitmap = setBitmap(type, frame);
    if (!temperature) {
      Serial.println("Could not read temperature from BMP");
      light_error();
      return ;
    }
    if (!pressure) {
      Serial.println("Could not read pressure from BMP");
      light_error();
      return ;
    }

    sendData(temperature, pressure);

    oled.clearDisplay();
    oled.println(get_temp(temperature).c_str());
    oled.println(get_pressure(pressure).c_str());
    displayTime();
    oled.drawBitmap(80, 12, bitmap, FRAME_WIDTH, FRAME_HEIGHT, 1);
    oled.display();
  } 
}

void  sendData(float temperature, int pressure) {
  if (WiFi.status() == WL_CONNECTED) {  
    WiFiClient  wifiClient;
    HTTPClient  http;

    http.begin(wifiClient, "http://192.168.1.30:3000/weather");
    http.addHeader("content-type", "application/json");
    http.addHeader("Accept", "application/json");
    
    String  data = "{\"temperature\": " + String(temperature, 2) + ", \"pressure\": " + String(pressure) + "}" ;
    
    Serial.print("Data to send: ");
    Serial.println(data);
    
    int httpResponseCode = http.POST(data);
    
    if (httpResponseCode > 0) {
      String  response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.println("Error on sending POST");
      Serial.println(httpResponseCode);
    }
    http.end();
  }
}

void  setTime() {
  rawTime = timeClient.getEpochTime();

  int offset = 7200;

  rawTime += offset;
  timeinfo = localtime(&rawTime);
}

void  displayTime() {
  // Set text parameters
  oled.setCursor(5, 5);
  oled.setTextSize(1);
  oled.setTextColor(WHITE);

  // Display time
  oled.print(timeinfo->tm_hour);
  oled.print(":");
  if (timeinfo->tm_min < 10)
    oled.print("0");
  oled.print(timeinfo->tm_min);
  oled.print(":");
  if (timeinfo->tm_sec < 10)
    oled.print("0");
  oled.println(timeinfo->tm_sec);
}

void  light_error() {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(2000);
}