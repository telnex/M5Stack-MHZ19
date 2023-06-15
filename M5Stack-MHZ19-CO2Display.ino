/****************************************************************************************/
/* CO2 level analyzer                                                                   */
/* Version: 1.0                                                                         */
/* Date: 15.06.2023                                                                     */
/****************************************************************************************/
#include <M5Stack.h>
#include "src/MHZ/MHZ.h"
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>


MHZ co2(&Serial2, 0, MHZ19B);

/* Constants & Variables */
String VER = "1.0.0";
byte MENU = 0;
bool Speaker = true;
bool network = false;
int backlight = 255;
String img_path= "";
String address = "";

/* Network connection */
const char *ssid = "WIFI";
const char *password = "PASS_WIFI";
String host = "SITE";					
String key = "API";					// indicate if necessary


WiFiMulti WiFiMulti;
HTTPClient http;


/****************************************************************************************/
/* Init routine                                                                         */
/****************************************************************************************/
void setup() {
  M5.begin();
  M5.Power.begin();
  WiFiMulti.addAP(ssid, password);
  M5.Lcd.setTextColor(ORANGE, BLACK);
  M5.Lcd.setTextSize(2);
  M5.Lcd.drawJpgFile(SD, "/wifi.jpg");
  char cnt[6];
  for(int i=1; i<5; i++) {
    M5.Lcd.setCursor(273,160);
    sprintf(cnt,"%d", i);
    M5.Lcd.print(cnt);
    if (WiFiMulti.run() == WL_CONNECTED) {
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());
      network = true;
      break;
    }
    delay(1500);
  }
  M5.Lcd.setCursor(273,160);
  if (!network) {
    Serial.println("Not connect to Internet!");
    M5.Lcd.print("OFF");
  } else {
    M5.Lcd.print("ON");
  }
  
  delay(1500);
  Serial.begin(115200);
  delay(100);
  Serial2.begin(9600);

  // enable debug to get addition information
  co2.setDebug(false);

  M5.Lcd.drawJpgFile(SD, "/prepare.jpg");
  int i = 3*60;
  char str[6];
  while (co2.isPreHeating()) {
    M5.Lcd.setCursor(273,160);
    sprintf(str,"%3d", i);
    M5.Lcd.print(str);
    delay(1000);
    i--;
    if(M5.BtnC.isPressed())
      break;  // Skip preheat
    M5.update();
  }
}


/****************************************************************************************/
/* Main routine                                                                         */
/****************************************************************************************/
void loop() {
  M5.update(); 
  if (M5.BtnA.isPressed()) {
    MENU = 1;
  }
  if (MENU == 1) {
    String image = "/set-inf-1.jpg";
    M5.Lcd.setTextColor(DARKGREY, WHITE);
    if (M5.BtnB.isPressed()) {
      if (Speaker) Speaker = false;
      else Speaker = true;
    }
    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(172,55);
    if (Speaker) M5.Lcd.print("ON ");
    else M5.Lcd.print("OFF");
    if(image != img_path){
      M5.Lcd.drawJpgFile(SD, image.c_str());
      img_path = image;
    }
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(74,135);
    if (network) M5.Lcd.print(WiFi.localIP());
    else M5.Lcd.print("NO CONNECT");
    M5.Lcd.setCursor(74,160);
    uint16_t Bat_Level = M5.Power.getBatteryLevel();  // docs: "Get battery capacity"
    bool CONTROL = M5.Power.canControl();
    bool Charg = M5.Power.isCharging();
    if (CONTROL) {
      if (Charg) {
        if (M5.Power.isChargeFull()) {
          M5.Lcd.print("100%");
        } else
          M5.Lcd.print("CHARGING");
      } else {
        M5.Lcd.print(String(Bat_Level) + "%");
      }
    }
    M5.Lcd.setCursor(74,185);
    M5.Lcd.print(VER);
    if (M5.BtnC.isPressed()) {
      MENU = 0;
    }
  }
  else {
    get_data();
    if (M5.BtnC.wasPressed()){
      if (backlight==255) {
        backlight = 5;
      } else {
        backlight = 255;
      }
      M5.Lcd.setBrightness(backlight);
    } 
  }
  delay(1000);
}


/****************************************************************************************/
/* УРОВЕНЬ СО2                                                                          */
/* Получение данных от модуля                                                           */
/****************************************************************************************/
void get_data(void){
  int co2_ppm = co2.readCO2UART();
  
  if (co2_ppm > 0) {
    String new_image = "";
    if(co2_ppm <= 1000){
      new_image = "/co2-low.jpg";     // 0 - 1000
    }else if(co2_ppm <= 2000){    
      new_image = "/co2-mid1.jpg";    // 1000 - 2000
    }else if(co2_ppm <= 3000){   
      new_image = "/co2-mid2.jpg";    // 2000 - 3000
    }else if(co2_ppm <= 4000){
      new_image = "/co2-high1.jpg";   // 3000 - 4000
      BEEP();
    } else {
      new_image = "/co2-high2.jpg";   // 4000 -
      BEEP();
    } 

    if(new_image != img_path){
      M5.Lcd.drawJpgFile(SD, new_image.c_str());
      img_path = new_image;
    }

    char ppm[6];
    sprintf(ppm,"%5d", co2_ppm);
    
    M5.Lcd.setTextColor(BLACK,WHITE);
    M5.Lcd.setTextSize(4);
    M5.Lcd.setCursor(70,185);
    M5.Lcd.print(ppm);
    if (network) {
      address = String("https://") + host + "/esphome?key=" + key + "&co2="+ co2_ppm;
      http.begin(address);
      int httpCode = http.GET();
      if (httpCode < 0) {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      } else {
        Serial.printf("Server CODE: %d\n", httpCode); 
      }    
      http.end();
    }
  }

  // int temperature = co2.getLastTemperature();
  // if (temperature > 0) {
  //   // Serial.print(", Temperature: ");
  //   // Serial.println(temperature);
  // }
}


/****************************************************************************************/
/* ЗВУКОВОЙ СИГНАЛ                                                                      */
/* Звуковое уведомление при высоком уровение СО2                                        */
/****************************************************************************************/
void BEEP(void) {
  if (Speaker) {
    M5.Speaker.beep();
    delay(400);
    M5.Speaker.mute();
  }
}

