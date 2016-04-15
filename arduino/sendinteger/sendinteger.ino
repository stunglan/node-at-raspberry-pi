/*

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */
 /*
  Hack.lenotta.com
  Modified code of Getting Started RF24 Library
  It will switch a relay on if receive a message with text 1, 
  turn it off otherwise.
  Edo
 */

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
int relay = 3;
int i = 0;
unsigned long message = 3;

//
// Hardware conf
//

// Set up nRF24L01 radio on SPI bus plus pins 9 & 10 

RF24 radio(9,10);

//
// Topology
//

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

void setup(void)
{
  //
  // Print preamble
  //

  
  Serial.begin(57600);
  printf_begin();
  //Serial.println("**************V1 Send Sensor Data***********");
  
  radio.begin();
  //radio.setPALevel(RF24_PA_LOW);
  radio.setChannel(0x1);
  radio.setPALevel(RF24_PA_MAX);
  radio.setRetries(15,15);
  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1,pipes[0]);
  //radio.enableDynamicPayloads();
  //radio.setAutoAck(true);
  radio.printDetails();
  radio.stopListening();
  //radio.powerUp();


  //
  // Setup and configure rf radio
  //

 

}

void loop(void)
{
  message++;
  message = message % 1000;

  radio.write(&message, sizeof(unsigned long));
  printf("Temperature sent:  %lu\n",message);
 
  // pause a second
  radio.powerDown();
  delay(5000);
  radio.powerUp();

}
