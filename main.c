#include "reg932.h"
#include "uart.h"
#include <stdlib.h>
sbit mole0_0 = P2 ^ 4; //LEDs
sbit mole0_1 = P0 ^ 5;
sbit mole0_2 = P2 ^ 7;
sbit mole1_0 = P0 ^ 6;
sbit mole1_1 = P1 ^ 6;
sbit mole1_2 = P0 ^ 4;
sbit mole2_0 = P2 ^ 5;
sbit mole2_1 = P0 ^ 7;
sbit mole2_2 = P2 ^ 6;

sbit hole0_0 = P2 ^ 0; //Buttons
sbit hole0_1 = P0 ^ 1;
sbit hole0_2 = P2 ^ 3;
sbit hole1_0 = P0 ^ 2;
sbit hole1_1 = P1 ^ 4;
sbit hole1_2 = P0 ^ 0;
sbit hole2_0 = P2 ^ 1;
sbit hole2_1 = P0 ^ 3;
sbit hole2_2 = P2 ^ 2;

sbit strike1 = P3 ^ 1;//Strike outs
sbit strike2 = P3 ^ 0;
sbit strike3 = P1 ^ 0;

sbit speaker = P1 ^ 7;//Speaker / buzzer


void delay();
void strikeOut(unsigned char s);
void getTone();
void missTone();
void endGame();
void sendData(char score);
void setLED(unsigned char row, unsigned char col); //Sets the specified LED (sets it to 0)
void clearLED(unsigned char row, unsigned char col); //Clears the specified LED (sets it to 1)
unsigned char getHole(unsigned char row, unsigned char col); //Gets the current value for the button
unsigned char wait(int difficulty, unsigned char row, unsigned char col); //Will return 1 if the button is pressed on time
void setPorts(void); //Making sure the LED's work on the simon-board by setting them into bi-directional mode
unsigned char userUnlock(); //Must unlock the simon board by pressing the 'Game' button 3 times
void buzz() interrupt 1 {

speaker = ~speaker;

}

void main(void) {

    unsigned int difficulty; //using the max demay for a timer, this is the number of loops that we will wait for at max time
    unsigned char test = 0;
    unsigned char menu = 0; //Var to decide if the game is over (main loop control var)
	unsigned char gameOver = 0;
	unsigned char row = 0;
	unsigned char col = 0;
	unsigned char score = 0;
	unsigned char result = 0;
	unsigned char i = 0;
	unsigned char strikes = 0;
	unsigned char passcode = 0;
	setPorts(); //has to be called after these variables are declared
	uart_init();

    passcode = userUnlock();
	if(passcode == 1){
    while (1) {

		setLED(0, 0); //Difficulty One
    	setLED(0, 1); //Difficulty Two
    	setLED(0, 2); //Difficulty Three
      
	  do { //Main Menu Loop
        //Should probably do this all in a function to keep our Main clean
        if (!getHole(0, 0)) {
          difficulty = 20;//Hard - Magic
		  menu = 1;
        } else if (!getHole(0, 1)) {
          difficulty = 40;//Medium - Magic
		  menu = 1;
        } else if (!getHole(0, 2)) {
          difficulty = 60;//Easy - Magic
		  menu = 1;
        }
      } while (!menu);
	  clearLED(0, 0);
	  clearLED(0, 1);
	  clearLED(0, 2);

	  //Game Loop
	  do {
		row = rand() % 3;
		col = rand() % 3;
		setLED(row, col);
		result = wait(difficulty, row, col);
		if(result) {
			score++;
			sendData(score);
			getTone();
			//Send Score to Serial
		}
		else {
			//Light up ohe LED on breabdoard
			strikes++;
			missTone();
			missTone();
			missTone();
			strikeOut(strikes);
			if(strikes == 3)
				gameOver = 1;
		}
		clearLED(row, col);
		delay();
		delay();

		

	  }while(!gameOver);

	  endGame();
	  menu = 0;
	  strikes = 0;
	  score = 0;
	  gameOver = 0;
 
    }
	}
  } //End main

void setLED(unsigned char row, unsigned char col) {
  switch (row) {
  	case 0:
    {
      switch (col) {
      case 0:
        mole0_0 = 0;
        break;
      case 1:
        mole0_1 = 0;
        break;
      case 2:
        mole0_2 = 0;
        break;
      } //end switch col
    } //end case 0
    break;
  case 1:
    {
      switch (col) {
      case 0:
        mole1_0 = 0;
        break;
      case 1:
        mole1_1 = 0;
        break;
      case 2:
        mole1_2 = 0;
        break;
      } //end switch col
    } //end case 1
    break;
  case 2:
    {
      switch (col) {
      case 0:
        mole2_0 = 0;
        break;
      case 1:
        mole2_1 = 0;
        break;
      case 2:
        mole2_2 = 0;
        break;
      } //end switch col
    } //end case 2
    break;
  } //end case switch
}

void clearLED(unsigned char row, unsigned char col) {
  switch (row) {
  case 0:
    {
      switch (col) {
      case 0:
        mole0_0 = 1;
        break;
      case 1:
        mole0_1 = 1;
        break;
      case 2:
        mole0_2 = 1;
        break;
      } //end switch col
    } //end case 0
    break;
  case 1:
    {
      switch (col) {
      case 0:
        mole1_0 = 1;
        break;
      case 1:
        mole1_1 = 1;
        break;
      case 2:
        mole1_2 = 1;
        break;
      } //end switch col
    } //end case 1
    break;
  case 2:
    {
      switch (col) {
      case 0:
        mole2_0 = 1;
        break;
      case 1:
        mole2_1 = 1;
        break;
      case 2:
        mole2_2 = 1;
        break;
      } //end switch col
    } //end case 2
    break;
  } //end case switch
}

unsigned char getHole(unsigned char row, unsigned col) //Gets the value for the button
  {
    switch (row) {
    case 0:
      {
        switch (col) {
        case 0:
          return ((unsigned char) hole0_0);
          break;
        case 1:
          return ((unsigned char) hole0_1);
          break;
        case 2:
          return ((unsigned char) hole0_2);
          break;
        } //end switch col
      } //end case 0
      break;
    case 1:
      {
        switch (col) {
        case 0:
          return ((unsigned char) hole1_0);
          break;
        case 1:
          return ((unsigned char) hole1_1);
          break;
        case 2:
          return ((unsigned char) hole1_2);
          break;
        } //end switch col
      } //end case 1
      break;
    case 2:
      {
        switch (col) {
        case 0:
          return ((unsigned char) hole2_0);
          break;
        case 1:
          return ((unsigned char) hole2_1);
          break;
        case 2:
          return ((unsigned char) hole2_2);
          break;
        } //end switch col
      } //end case 2
      break;
    } //end case switch
  }

unsigned char wait(int difficulty, unsigned char row, unsigned char col) //Boolean is not a default type in C. Will return 1 if button is pressed on time
  {
    unsigned int index;
    TMOD = 0x01;
	

    for (index = 0; index < difficulty; index++) {
	  TH0 = 0x00;
      TL0 = 0x00; //These delays must be observable by humans, so difficulty will be number of loops
      TR0 = 1;
      while (!TF0) //wait for the max time
      {
        if (getHole(row, col) == 0) //buttons are low if pressed, getHole will generate some overhead
        {
          TR0 = 0; //Stop timer
          TF0 = 0; //Reset overflow
          return 1; //Return 1 is presses
        } //end if
      } //end while
	  TF0 = 0;
	  TR0 = 0;
    } //end for, difficulty 
    return 0; //button was never pressed			
  } //end wait function

void setPorts(void) {
  P0M1 = 0x00; //Set ports 0, 1, and 2 into bi-mode - comment out until it's ready for the simon2
  P0M2 = 0x00;
  P1M1 = 0x00;
  P1M2 = 0x00;
  P2M1 = 0x00;
  P2M2 = 0x00;
  P3M1 = 0x00;
}


void delay() {
	unsigned int i = 0;
	TMOD = 0x10;
	for(i = 0; i < 40; i++) {
		TH1 = 0xF0;
		TL1 = 0x00;
		TR1 = 1;
		while(TF1 == 0);
		TR1 = 0;
		TF1 = 0;	
	
		}
	
	return;
}


void getTone() {//C ^ 6, 1046 Hz, (1/1046) = 0.00096s = 960us, 960us/(1.085/6*) = 5309 *(This microcontroller is 6 times faster than the standard 8051)
	TMOD = 0x01;
	TH0 = 0xEB;
	TL0 = 0x42;
	EA = 1;
	ET0 = 1;
	TR0 = 1;
	delay();
	TR0 = 0;
	TF0 = 0;
	ET0 = 0;

	return;
}

void missTone() {//C ^ 6, 1046 Hz, (1/1046) = 0.00096s = 960us, 960us/(1.085/6*) = 5309 *(This microcontroller is 6 times faster than the standard 8051)
	TMOD = 0x01;
	TH0 = 0xFF;
	TL0 = 0xFF;
	EA = 1;
	ET0 = 1;
	TR0 = 1;
	delay();
	TR0 = 0;
	TF0 = 0;
	ET0 = 0;

	return;
}
void sendData(char score) {
unsigned char i = 0;
char temp = 0;
char sc[10] = "Score :";
//lower = score & 0x0F;
//upper = score & 0xF0;
//upper = (lower > 9) ? (upper+1) : (upper);
//upper = (upper % 10) + 0x30;
//lower = (lower % 10) + 0x30;
temp = ((score / 10) << 4) | (score % 10);

while(sc[i] != '\0'){
	uart_transmit(sc[i]);
	i++;
}

i = 0;
uart_transmit(((temp & 0xF0) >> 4) + 0x30);
uart_transmit((temp & 0x0F) + 0x30);
uart_transmit('\r');
uart_transmit('\n');


}

void strikeOut(unsigned char s) {

}

void endGame() {

	unsigned char i = 0;
	char sc[10] = "Game Over!";
	for(i = 0; i < 10; i++)
		uart_transmit(sc[i]);
	for(i = 0; i < 5; i++) {
		uart_transmit('\r');
		uart_transmit('\n');
	}
}

unsigned char userUnlock(){
  unsigned char numPresses = 0;
  while(numPresses < 3){
    if(!getHole(1,1)){
	  numPresses++;
	}
  }
  return 1;
}














