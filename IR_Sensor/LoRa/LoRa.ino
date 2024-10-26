String lora_band = "865000000";
String lora_networkid = "5";
String lora_address = "2";
String lora_RX_address = "1";

String incomingString;

const int ledPin = 2;

void setup()
{ 

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);

  delay(1500);
  digitalWrite(ledPin, LOW);

  Serial.begin(115200);
  Serial.println("AT+BAND=" + lora_band);
  delay(500);
  Serial.println("AT+NETWORKID=" + lora_networkid);
  delay(500);
  Serial.println("AT+ADDRESS=" + lora_address);
  delay(1000);
}

void loop()
{ 
  if(Serial.available())
  {
    incomingString = Serial.readString();

    if(incomingString.indexOf("ON") >0)
    {
      digitalWrite(ledPin, HIGH);
      delay(1000);
    }

    if(incomingString.indexOf("OF") >0)
    {
      digitalWrite(ledPin, LOW);
    }
  }
}