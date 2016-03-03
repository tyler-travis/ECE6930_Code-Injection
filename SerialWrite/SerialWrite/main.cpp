//------------------------------------------------------------------------------------
//
//	Code: PC to uController
//	Authors: Justin Cox & Tyler Travis
//	Date: 2/24/2016
//
//------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <Windows.h>
#include "Serial.h"


void readUart(void);

//------------------------------------------------------------------------------------
//	FUNCTION MAIN
//------------------------------------------------------------------------------------

CSerial serial;


int main(){

	//*************************
	//	SERIAL
	//*************************
	int port = 4; 
	int baudRate = 115200; 
	int dispType = 0;

	int nBytesSent = 0;

	const int SIZE = 41;

	unsigned char attack[SIZE] = {0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61,
						  0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61,
						  0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61,
						  0x62,0x62,0x62,0x62,0x62,0x62,0xab,0x65,0x00,0x01, 
						  '\r'};

	//-----------------------------------
	//		SERIAL CODE
	//-----------------------------------
	if (!serial.Open(port, baudRate)){
		printf("Error opening COM port! \n");
		return 0;
	}

	//-----------------------------------
	//	WRITE DATA
	//-----------------------------------
	
	nBytesSent = serial.SendData(attack, SIZE);

	//-----------------------------------
	//	READ DATA
	//-----------------------------------
	
	//Read Data Printed to gets()
	readUart();

	//Read Data from printf()
	readUart();

	serial.Close();

	return 0;
}

void readUart(void){

	int nBytesRead = 0;
	int curT = 0; 
	int oldT = 0;
	char readBuffer[1];
	
	while(readBuffer[0] != '\n')
	{
		curT = GetTickCount();

		if (curT - oldT > 5)
		{
			nBytesRead = serial.ReadData(readBuffer, sizeof(readBuffer));
	
			if (nBytesRead > 0)
			{

				for(int i = 0; i < nBytesRead; i++){
					printf("%c", readBuffer[i]);
				}

			}

			oldT = curT;
		}

	}

}