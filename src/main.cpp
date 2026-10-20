#include <Arduino.h>
#include <Pixy2.h>
#include <BLESerial.h>
#include <motor.h>

BLESerial SerialBT;
Pixy2 pixy;

// Spårar signatur 1 om inget annat angivs
int signatureBitmask = 1;
String color = "Blank";

// globala variabler
int x_center = 316 / 2; // centrum på x axeln i pixy kameran
int y_center = 208 / 2; // centrum på y
int x_actual;
int y_actual;
int x_error;
int y_error;

void setup()
{
  // Startar upp pixy
  Serial.begin(115200);
  SPI.begin(6, 2, 7, 10);
  pixy.init();
  Serial.println("Pixy2 startad...\n");

  // Startar up Bluetooth
  SerialBT.begin("Pixy2_ESP32");
  Serial.println("Bluetooth väntar på anslutning...\n");
  delay(1000);
  setupMotors(); // initierar motor fuktionen
  SerialBT.println("System ready! Choose number \n(1)Blue \n(2)Red \n(3)Green \n(4)Yellow");
}

void loop()
{
  // Läs in siffra från Bluetooth
  if (SerialBT.available()) //
  {
    // spar in siffran i variabeln c
    char c = SerialBT.read();

    // checkar om siffran är en inläst färg
    if (c >= '1' && c <= '4')
    {
      // Omvandla bitmask till en färg för utskrift med hjälp av en bitmask
      if (c == '1')
        signatureBitmask = 1, color = "Blue";
      if (c == '2')
        signatureBitmask = 2, color = "Red";
      if (c == '3')
        signatureBitmask = 4, color = "Green";
      if (c == '4')
        signatureBitmask = 8, color = "Yellow";

      SerialBT.print(">>> Swapped tracking to color: ");
      SerialBT.println(color);
    }
  }

  // Läser in objekt från pixy kameran
  pixy.ccc.getBlocks(false, signatureBitmask);

  // Om block upptäcks, beräkna fel och styr roboten
  if (pixy.ccc.numBlocks)
  {
    Serial.print("Detected ");
    Serial.println(pixy.ccc.numBlocks);

    x_actual = pixy.ccc.blocks[0].m_x; // Objektets x position
    y_actual = pixy.ccc.blocks[0].m_y; // Objektets y position

    x_error = x_actual - x_center; // Beräknar hur mycket roboten ska svänga5
    y_error = y_actual - y_center; // Beräknar hur mycket roboten ska åka framåt/bakåt

    if (y_error > 80)
    {
      // åker Bakåt
      TurnRobot("backward");
      Serial.println("Robot åker bakåt");
    }
    else if (x_error > 50)
    { // robot svänger höger
      TurnRobot("right");
      Serial.println("Robot svänger höger");
    }
    else if (x_error < -50)
    { // robot svänger vänster
      TurnRobot("left");
      Serial.println("Robot svänger vänster");
    }
    else if (y_error < 40)
    { // åker framåt
      TurnRobot("forward");
      Serial.println("Robot åker framåt");
    }
    else
    {
      //robot stannar
      TurnRobot("stop");
      Serial.println(">>> Inga block upptäckta, robot stannar");
    }
  }
  else
  {
    TurnRobot("stop");
    Serial.println(">>> Inga block upptäckta, robot stannar");
  }
  // Delay
  delay(70);
}