//A7_Client.cpp

#include "A7Client.h"

#define A7Client_ENABLE_DEBUG
#define A7Client_ENABLE_RESP_DEBUG

SoftwareSerial* serialA7 = NULL;

A7Client::A7Client(uint8_t rx, uint8_t tx, uint32_t baudRate){
	serialA7 = new SoftwareSerial(rx, tx);
	serialA7->begin(baudRate);
}

bool A7Client::init(){
	
}





int A7Client::connect(IPAddress ip, uint16_t port){
	char host[16] = {0};
	snprintf(host, 15, "%d.%d.%d.%d", ip[3], ip[2], ip[1], ip[0]);
	return connect(host, port);
	}

int A7Client::connect(const char *host, uint16_t port){

		return true;

}

void A7Client::A7_DEBUG(char *msg){
	#ifdef A7Client_ENABLE_DEBUG
	Serial.print(F("Debug: "));
	Serial.println(msg);	
	#endif
}

size_t A7Client::write(uint8_t b){	
	return write(&b, 1);
}

size_t A7Client::write(char *buf){
	if (buf == NULL) return 0;
    return write((const uint8_t *)buf, strlen(buf));
}

size_t A7Client::write(const uint8_t *buf, size_t size){

	
		serialA7->write(buf, size);
	
		
			return size;
				
	
}

size_t A7Client::writeSerial(uint8_t b){	//send command directly thorugh serial
	return writeSerial(&b, 1);
}

size_t A7Client::writeSerial(char *buf){
	if (buf == NULL) return 0;
    return writeSerial((const uint8_t *)buf, strlen(buf));
}

size_t A7Client::writeSerial(const uint8_t *buf, size_t size){
	return serialA7->write(buf, size);	
}


int A7Client::available(){
	return serialA7->available();
}

int A7Client::read(){
	return serialA7->read();
}

int A7Client::read(uint8_t *buf, size_t size){
	return size;
}


void A7Client::flush(){
	serialA7->flush();
}

int A7Client::peek(){
	serialA7->peek();
}

void A7Client::stop(){

	
}

uint8_t A7Client::connected(){

		return 1;		

	
}

A7Client::operator bool(){
	return (connected()==1);
	
}