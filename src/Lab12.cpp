/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/Rich/CTD2023/Lab12/src/Lab12.ino"
// libraries
#include "MQTT.h"
#include "oled-wing-adafruit.h"

void setup();
void loop();
void resetDisplay();
#line 5 "c:/Users/Rich/CTD2023/Lab12/src/Lab12.ino"
#define LEDPIN D7

SYSTEM_THREAD(ENABLED);

void callback(char *topic, byte *payload, unsigned int length);

// display Class
OledWingAdafruit display;
MQTT client("lab.thewcl.com", 1883, callback);

void setup()
{
  // startup OLED, Serial
  Serial.begin(9600);
  display.setup();
  display.clearDisplay();
  display.display();

  pinMode(LEDPIN, OUTPUT);
  // digitalWrite(LEDPIN, HIGH);
  // delay(1500);
  // digitalWrite(LEDPIN, LOW);

  client.subscribe("testtopic/CoolTopic1");
  client.subscribe("testtopic/CoolTopic1");
}
void loop()
{
  if (client.isConnected())
  {
    client.loop();
  }
  else
  {
    client.connect(System.deviceID());
    client.subscribe("testtopic/CoolTopic1");
    client.subscribe("testtopic/CpolTopic1");
    Serial.println("DIDN'T WORK");
  }
  // run display and blynk continuously
  display.loop();
  // Serial.println("Worked");
  // client.publish("testtopic/EpicTopic1", "Hello, everyone!");
  // delay(1000);

  if (display.pressedA())
  {
    client.publish("testtopic/CoolTopic1", "Pressed A");
  }
  if (display.pressedB())
  {
    client.publish("testtopic/CoolTopic1", "Pressed B");
  }
  if (display.pressedC())
  {
    client.publish("testtopic/CoolTopic1", "Pressed C");
  }
}
void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.println("callback");
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;
  Serial.printf("%s", p);
  Serial.println();

  if (String(p).equals("1"))
  {
    Serial.println("HIGH");
    digitalWrite(LEDPIN, HIGH);
  }
  else if (String(p).equals("0"))
  {
    Serial.println("LOW");
    digitalWrite(LEDPIN, LOW);
  }
  else if (String(p).equals("Pressed A"))
  {
    resetDisplay();
    display.println("Pressed A button");
    display.display();
  }
  else if (String(p).equals("Pressed B"))
  {
    resetDisplay();
    display.println("Pressed B button");
    display.display();
  }
  else if (String(p).equals("Pressed C"))
  {
    resetDisplay();
    display.println("Pressed C button");
    display.display();
  }
  else
  {
    Serial.println(p);
  }
}
// client.subscribe("inTopic/message");  //in setup and by client.connect in loop if
// client.publish("iotBennett", "Message");
void resetDisplay()
{
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.display();
}