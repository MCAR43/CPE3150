#include <reg51.h>
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



void main(void)
{
	//P0M1 = 0;//Set ports 0, 1, and 2 into bi-mode - comment out until it's ready for the simon2
	//P0M2 = 0;
	//P1M1 = 0;
	//P1M2 = 0;
	//P2M0 = 0;
	//P2M1 = 0;
	
	
}//End main


