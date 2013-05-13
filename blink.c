
#include <msp430.h>
#include "time430.h"

#include "uart.h"
#include "i2c.h"

void delay(unsigned int ms)
{
while (ms--)
{
__delay_cycles(1000); // set for 16Mhz change it to 1000 for 1 Mhz
}
}

void ftoa(char buff[], float x)
{
 int y = x * 100;
 char polje[10];
 int i ;
 for(i = 0; y != 0; i++)
 {
  int num = y % 10;
  y -= num;
  y /= 10;

  switch(num){
  case 0: polje[i] = '0';
    break;
  case 1: polje[i] = '1';
    break;
  case 2: polje[i] = '2';
    break;
  case 3: polje[i] = '3';
    break;
  case 4: polje[i] = '4';
    break;
  case 5: polje[i] = '5';
    break;
  case 6: polje[i] = '6';
    break;
  case 7: polje[i] = '7';
    break;
  case 8: polje[i] = '8';
    break;
  case 9: polje[i] = '9';
    break;
  default: break;
  }
 }
 polje[i] = '\0';

 int z = i - 1;
 i = 0;

 for(; z > -1; z--)
 {
  if( z == 1)
  {

   buff[i] = '.';
   i++;
  }
  buff[i] = polje[z];
  i++;
 }
 buff[i] = '\0';
}

char buf[10];

int main(void) {
	WDTCTL = WDTPW | WDTHOLD;
	  TIME430_CALIBRATE_CLOCK();
	  P1DIR = 0xFF;
	  P1OUT = 0x01;


	  uartSetupPins();
	  uartInit(buf, 10);

	  i2cSetupPins();

	 int x = 0;
	  for (;;) {
	      if(x==0) {
	          x=1;
	          P1OUT |= BIT0;
	        }else{
	            x=0;
	            P1OUT &= ~BIT0;
	        }

	    char buffer[3];
	    i2cSetupRx(0x48);
	    i2cReceive(buffer, 2);
	    buffer[2]='\0';

	    int t = ((buffer[0] << 8) | (buffer[1])) >> 3;
	    float t2=t * 0.0625;
	    ftoa(buf, t2);
	    //itoa(t2, out, 10);
	   // sprintf(out, "%d", t2);

	    uartPrint(buf);
	    uartPrint("\n");


	    delay(1000);

	  }
	
	return 0;
}
