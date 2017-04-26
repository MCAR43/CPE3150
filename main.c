#include "reg932.h"
#include <stdlib.h>
sbit mole0_0 = P2^4;//LEDs
sbit mole0_1 = P0^5;
sbit mole0_2 = P2^7;
sbit mole1_0 = P0^6;
sbit mole1_1 = P1^6;
sbit mole1_2 = P0^4;
sbit mole2_0 = P2^5;
sbit mole2_1 = P0^7;
sbit mole2_2 = P2^6;

sbit hole0_0 = P2^0;//Buttons
sbit hole0_1 = P0^1;
sbit hole0_2 = P2^3;
sbit hole1_0 = P0^2;
sbit hole1_1 = P1^4;
sbit hole1_2 = P0^0;
sbit hole2_0 = P2^1;
sbit hole2_1 = P0^3;
sbit hole2_2 = P2^2;

/*int swapBytes(int x)
{
    return ((x & 0x00FF)<< 8 | (x & 0xFF00)>>8 );
}*/

void setLED(unsigned char row, unsigned char col)
{
	switch(row)
	{
		case 0:
		{
			switch(col)
			{
				case 0:
					mole0_0 = 0;
					break;
				case 1:
					mole0_1 = 0;
					break;
				case 2:
					mole0_2 = 0;
					break;
			}//end switch col
		}//end case 0
			break;
		case 1:
		{
			switch(col)
			{
				case 0:
					mole1_0 = 0;
					break;
				case 1:
					mole1_1 = 0;
					break;
				case 2:
					mole1_2 = 0;
					break;
			}//end switch col
		}//end case 1
			break;
		case 2:
		{
			switch(col)
			{
				case 0:
					mole2_0 = 0;
					break;
				case 1:
					mole2_1 = 0;
					break;
				case 2:
					mole2_2 = 0;
					break;
			}//end switch col
		}//end case 2
			break;
	}	//end case switch
}

void clearLED(unsigned char row, unsigned char col)
{
	switch(row)
	{
		case 0:
		{
			switch(col)
			{
				case 0:
					mole0_0 = 1;
					break;
				case 1:
					mole0_1 = 1;
					break;
				case 2:
					mole0_2 = 1;
					break;
			}//end switch col
		}//end case 0
			break;
		case 1:
		{
			switch(col)
			{
				case 0:
					mole1_0 = 1;
					break;
				case 1:
					mole1_1 = 1;
					break;
				case 2:
					mole1_2 = 1;
					break;
			}//end switch col
		}//end case 1
			break;
		case 2:
		{
			switch(col)
			{
				case 0:
					mole2_0 = 1;
					break;
				case 1:
					mole2_1 = 1;
					break;
				case 2:
					mole2_2 = 1;
					break;
			}//end switch col
		}//end case 2
			break;
	}	//end case switch
}

unsigned char getHole(unsigned char row, unsigned col)//Gets the value for the button
{
	switch(row)
	{
		case 0:
		{
			switch(col)
			{
				case 0:
					return((unsigned char)hole0_0);
					break;
				case 1:
					return((unsigned char)hole0_1);
					break;
				case 2:
					return((unsigned char)hole0_2);
					break;
			}//end switch col
		}//end case 0
			break;
		case 1:
		{
			switch(col)
			{
				case 0:
					return((unsigned char)hole1_0);
					break;
				case 1:
					return((unsigned char)hole1_1);
					break;
				case 2:
					return((unsigned char)hole1_2);
					break;
			}//end switch col
		}//end case 1
			break;
		case 2:
		{
			switch(col)
			{
				case 0:
					return((unsigned char)hole2_0);
					break;
				case 1:
					return((unsigned char)hole2_1);
					break;
				case 2:
					return((unsigned char)hole2_2);
					break;
			}//end switch col
		}//end case 2
			break;
	}	//end case switch
}

unsigned char wait(int difficulty, unsigned char row, unsigned char col)//Boolean is not a default type in C. Will return 1 if button is pressed on time
{
	
	unsigned int index;
	TMOD = 0x01;
	TH0 = 0;
	TL0 = 0;//These delays must be observable by humans, so difficulty will be number of loops
	TR0 = 1;
	
	for(index = 0; index < difficulty; index++)
	{
		while(!TF0)//wait for the max time
		{
			if(getHole(row, col)	== 0)//buttons are low if pressed, getHole will generate some overhead
			{
				TR0 = 0;//Stop timer
				TF0 = 0;//Reset overflow
				return 1;//Return 1 is presses
			}//end if
		}//end while
	}//end for, difficulty 
	return 0;//button was never pressed
}//end wait function

void setPorts(void)
{
	P0M1 = 0x00;//Set ports 0, 1, and 2 into bi-mode - comment out until it's ready for the simon2
	P0M2 = 0x00;
	P1M1 = 0x00;
	P1M2 = 0x00;
	P2M1 = 0x00;
	P2M2 = 0x00;
}


void main(void)
{
	unsigned int difficulty = 860;//using the max demay for a timer, this is the number of loops that we will wait for at max time
	unsigned char test = 0;
	setPorts();//has to be called after these variables are declared
	//Example
	setLED(1, 1);
 	test = wait(difficulty, 1, 1); //This will wait for about a second before returning, if pressed the function will return 1 right as it's pressed
	//if not pressed it will wait the full timer
	if(test)
	{
		clearLED(1, 1);
	}



	
	while(1);
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}//End main


