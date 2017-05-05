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

sbit speaker = P1 ^ 7;//Speaker / buzzer

#define DIFFICULTY_ONE = 20;
#define DIFFICULTY_TWO = 40; //arbitrary test numbers, change these later
#define DIFFICULTY_THREE = 60;


void delay();
void getTone();
void missTone();
void sendData(char score);
void setLED(unsigned char row, unsigned char col); //Sets the specified LED (sets it to 0)
void clearLED(unsigned char row, unsigned char col); //Clears the specified LED (sets it to 1)
unsigned char getHole(unsigned char row, unsigned char col); //Gets the current value for the button
unsigned char wait(int difficulty, unsigned char row, unsigned char col); //Will return 1 if the button is pressed on time
unsigned char swapBytes(int); //no idea
void setPorts(void); //Making sure the LED's work on the simon-board by setting them into bi-directional mode
void clearAll(); //Clears all LED's on the board, could prove useful
void setAll(); //Sets all LED's on the board
unsigned char setDifficulty();

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
	setPorts(); //has to be called after these variables are declared
	setLED(0, 0); //Difficulty One
    setLED(0, 1); //Difficulty Two
    setLED(0, 2); //Difficulty Three
	uart_init();
    
    while (1) {
      
	  do { //Main Menu Loop
        //Should probably do this all in a function to keep our Main clean, fuck it, i'll do that
        if (!getHole(0, 0)) {
          difficulty = 20;
		  menu = 1;
        } else if (!getHole(0, 1)) {
          difficulty = 40;
		  menu = 1;
        } else if (!getHole(0, 2)) {
          difficulty = 60;
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
			sendData(score);
			getTone();
			score++;
			//Send Score to Serial
		}
		else {
			//Light up ohe LED on breabdoard
			missTone();
			missTone();
			missTone();
		}
		clearLED(row, col);
		delay();
		delay();

		

	  }while(!gameOver);	  
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
}

/*int swapBytes(int x)
{
    return ((x & 0x00FF)<< 8 | (x & 0xFF00)>>8 );
}*/


/*void clearAll() {
  for (unsigned char i = 0; i < 3; i++) {
    for (unsigned char k = 0; k < 3; k++) {
      clearLED(i, k);
    }
  }
}

void setAll() {
  for (unsigned char i = 0; i < 3; i++) {
    for (unsigned char k = 0; k < 3; k++) {
      setLED(i, k);
    }
  }
}*/


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
	EA = 0;
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
	EA = 0;
	ET0 = 0;

	return;
}
void sendData(char score) {
unsigned char i = 0;
char temp = 0;
char sc[10] = "Score :";

/*while(sc[i] != '\0'){
	uart_transmit(sc[i]);
	i++;
}*/

i = 0;
temp = score+0x30;
uart_transmit(temp);
uart_transmit('\r');
uart_transmit('\n');


}














