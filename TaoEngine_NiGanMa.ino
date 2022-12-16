#include <ArduinoJson.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
String json = "";
uint8_t level_one[8]= {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F}; // 12.5%
uint8_t level_two[8]= {0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x1F}; // 25%
uint8_t level_three[8]= {0x00,0x00,0x00,0x00,0x00,0x1F,0x1F,0x1F}; // 37.5%
uint8_t level_four[8]= {0x00,0x00,0x00,0x00,0x1F,0x1F,0x1F,0x1F}; // 50%
uint8_t level_five[8]= {0x00,0x00,0x00,0x1F,0x1F,0x1F,0x1F,0x1F}; // 62.5%
uint8_t level_six[8]= {0x00,0x00,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F}; // 75%
uint8_t level_seven[8]= {0x00,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F}; // 87.5%
uint8_t level_eight[8]= {0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F}; // 100%

void setup() {
  Serial.begin(115200);  //设串口
  lcd.init(); // 启动lcd
  lcd.backlight(); //开背光
}

void loop() {
  while(Serial.available() > 0){
    json += char(Serial.read());
    delay(2);
  }
  if(json.length() > 0){
      Serial.print(json);
      DynamicJsonDocument doc(1024);
      deserializeJson(doc, json);
      if(doc["mod"] == "1"){
        const char* mem_t = doc["mem_t"];
        const char* memory_p = doc["mem_p"];
        double memory = doc["mem"];
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Mem:");
        lcd.print(mem_t);
        lcd.setCursor(13,1);
        lcd.print(memory_p);
        
        }else if(doc["mod"] == "2"){
          const char* cpu_n = doc["cpu_n"];
          const char* cpu_u = doc["cpu_u"];
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("CPU:");
          lcd.print(cpu_n);
          lcd.setCursor(13,1);
          lcd.print(cpu_u);
        }
    }
    json = "";
}
