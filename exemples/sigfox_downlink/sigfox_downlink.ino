// ---------------------------------------------------------------------
// This file is a example for use the library armapi with
// ARM NANO (NANO_LP with sigfox) on arduino board.
//
// This software send periodically 'Hello Sigfox' to Sigfox network
// and get the message from sigfox to on/off the led.
// The first byte is user to switch on/off the led.
// - If the byte is 0 the led is switch to off.
// - If the byte is different of 0 the led is switch to on.
//
// Created date: 13.02.2016
// ---------------------------------------------------------------------

/***********************************************************************

 Copyright (c) 2016 ATIM


 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:


 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.


 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.

***********************************************************************/

// ---------------------------------------------------------------------
// Include
// ---------------------------------------------------------------------
#include <arm.h>

// ---------------------------------------------------------------------
// Define
// ---------------------------------------------------------------------
#define LED 13

// ---------------------------------------------------------------------
// Global variables
// ---------------------------------------------------------------------
//Instance of  the class Arm
Arm myArm;
//The message to send at sigfox
uint8_t msg[] = "Hello Sigfox";
//Buffer for data sigfox downlink
uint8_t data[8] = {0};

// ---------------------------------------------------------------------
// Implemented functions
// ---------------------------------------------------------------------

void setup()
{
	//Init Led for chow error
	pinMode(LED, OUTPUT);
	digitalWrite(LED, LOW);
	
	//Init Arm and set LED to on if error
	if (myArm.Init(&Serial) != ARM_ERR_NONE)
		digitalWrite(LED, HIGH);
	
	//Set Sigfox mode in uplink
	myArm.SetMode(ARM_MODE_SFX);
	myArm.SfxEnableDownlink(true);
	myArm.UpdateConfig();
}

void loop()
{
	unsigned int i;
	
	//Send the message to sigfox
	myArm.Send(msg, sizeof(msg)-1);
	
	//Wait (60s of timeout) and receive the data from sigfox
	myArm.Receive(data, sizeof(data), 60000);
	
	if(data[i])
		digitalWrite(LED, HIGH);
	else
		digitalWrite(LED, LOW);
	
	//Wait 360min
	for(i=0; i<360; i++)
		delay(60000);
}
