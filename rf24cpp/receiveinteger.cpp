#include <string>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <RF24/RF24.h>
#include <unistd.h> 

using namespace std;
;

RF24 radio(RPI_V2_GPIO_P1_22, RPI_V2_GPIO_P1_24, BCM2835_SPI_SPEED_8MHZ);

const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

// hack to avoid SEG FAULT, issue #46 on RF24 github https://github.com/TMRh20/RF24.git
unsigned long  got_message;

void setup(void){
	//Prepare the radio module
	printf("\nPreparing interface\n");
	radio.begin();
	radio.setRetries( 15, 15);
	radio.setChannel(0x1);
	radio.setPALevel(RF24_PA_MAX);
	//radio.setPALevel(RF24_PA_LOW);

    //radio.enableDynamicPayloads();
    //radio.setAutoAck(true);
	radio.printDetails();
	radio.openWritingPipe(pipes[0]);
	radio.openReadingPipe(1,pipes[1]);
    radio.powerUp();
	//	radio.startListening();

}

unsigned long getMessage() {

    printf("get message\n");
	radio.startListening();
	//Let's take the time while we listen

    bool timeout = false;
    unsigned long started_waiting_at = millis();
	while ( ! radio.available() && ! timeout ) {
		//printf("%d", radio.available());
		if (millis() - started_waiting_at > 10000 ){
			timeout = true;
		}
	}

 	if( timeout ){
		//If we waited too long the transmission failed
		printf("Oh gosh, it's not giving me any response...\n\r");
		return 100;
	}else{
		//If we received the message in time, let's read it and print it
		radio.read( &got_message, sizeof(unsigned long) );
		printf("Yay! Got this response %lu.\n\r",got_message);
		return got_message;
	}
    radio.stopListening();

}  

int main( int argc, char ** argv){

	setup();
	unsigned long message = 0;

    while (message != 100)	{
        message = getMessage();
        printf("Message : %lu...\n",message);
    }

	
}