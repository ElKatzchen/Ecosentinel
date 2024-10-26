#include <Wire.h>
#include "TSL2561.h"

String lora_band = "865000000";
String lora_networkid = "5";
String lora_address = "1";
String lora_RX_address = "2";

TSL2561 tsl(TSL2561_ADDR_FLOAT);
const int ledPin = 2;

void setup(void)
{
  tsl.begin();

  tsl.setGain(TSL2561_GAIN_16X);
  tsl.setTiming(TSL2561_INTEGRATIONTIME_13MS);
  //tsl.setTiming(TSL2561_INTEGRATIONTIME_101MS);
  //tsl.setTiming(TSL2561_INTEGRATIONTIME_402MS);

  pinMode(ledPin, OUTPUT);

  delay(1500);

  Serial.begin(115200);
  Serial.println("AT+BAND=" + lora_band);
  delay(500);
  Serial.println("AT+ADDRESS=" + lora_address);
  delay(500);
  Serial.println("AT+NETWORKID=" + lora_networkid);
  delay(1500);
}

void loop(void)
{
  //uint16_t x = tsl.getLuminosity(TSL2561_VISIBLE);     
  //uint16_t x = tsl.getLuminosity(TSL2561_FULLSPECTRUM);
  uint16_t x = tsl.getLuminosity(TSL2561_INFRARED);

  uint32_t lum = tsl.getFullLuminosity();
  uint16_t ir, full;
  ir = lum >> 16;
  full = lum & 0xFFFF;
  //Serial.print("IR: " + String(ir) + "\n");
  //Serial.print("Full: " + String(full) + "\n");
  //Serial.print("Visible: " + String(full - ir) + "\n");
  
  //Serial.print("Lux: " + String(tsl.calculateLux(full, ir)) + "\n");

  if (ir >= 100)
  {
    digitalWrite(ledPin, LOW);
    Serial.println("AT+SEND="+ lora_RX_address +",2,ON");
  }
  else
  {
    digitalWrite(ledPin, HIGH);
    Serial.println("AT+SEND="+ lora_RX_address +",2,OF");
  }

  delay(500);
}