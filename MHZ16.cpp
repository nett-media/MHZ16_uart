#include <Arduino.h>
#include <MHZ16.h>

#define WAIT_READ_TIMES	100
#define WAIT_READ_DELAY	10

const int serialNr = 1; //choose Serial UART 0,1 or 2
const int co2_rx_pin = 39;	//Serial rx pin no
const int co2_tx_pin = 32;	//Serial tx pin no
HardwareSerial co2serial(serialNr);

uint8_t getppm[REQUEST_CNT]			= {0xff, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00};


void initMhz16() {
	co2serial.begin(9600, SERIAL_8N1, co2_rx_pin, co2_tx_pin);
}

void initMhz16(int _rx_pin, int _tx_pin) {
	co2serial.begin(9600, SERIAL_8N1, _rx_pin, _tx_pin);
}

uint8_t MHZ16_checksum( uint8_t com[] ) {
	uint8_t sum = 0x00;
	for ( int i = 1; i < REQUEST_CNT; i++) {
		sum += com[i];
	}
	sum = 0xff - sum + 0x01;
	return sum;
}

/*
void writeCommand(uint8_t cmd[]) {
	writeCommand(cmd,NULL);
}
*/
void writeCommand(uint8_t cmd[], uint8_t* response) {

    co2serial.write(cmd, REQUEST_CNT);
	co2serial.write(MHZ16_checksum(cmd));
	co2serial.flush();
	
	if (response != NULL) {
		int i = 0;
		while(co2serial.available() <= 0) {
			if( ++i > WAIT_READ_TIMES ) {
				Serial.println("error: can't get MH-Z16 response.");
				return;
			}
			yield();
			delay(WAIT_READ_DELAY);
		}
		co2serial.readBytes(response, RESPONSE_CNT);
	}
}

int getSerialData() {
	uint8_t buf[RESPONSE_CNT];
	for( int i=0; i<RESPONSE_CNT; i++){
		buf[i]=0x0;
	}

	writeCommand(getppm, buf);
	int co2 = 0, co2temp = 0, co2status =  0;

	// parse
	if (buf[0] == 0xff && buf[1] == 0x86 && MHZ16_checksum(buf) == buf[RESPONSE_CNT-1]) {
		co2 = buf[2] * 256 + buf[3];
	} else {
		co2 = co2temp = co2status = -1;
	}
	return co2;
}	

int getCo2PPM() {
	return getSerialData();
}