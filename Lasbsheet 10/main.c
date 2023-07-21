/**********************************************************
EE337: ADC IC MCP3008 interfacing with pt-51
(1) Complete spi_init() function from spi.h 

***********************************************************/

#include <at89c5131.h>
#include "lcd.h"																				//Driver for interfacing lcd 
#include "mcp3008.h" //Driver for interfacing ADC ic MCP3008
#include "serial.c"		

char adc_ip_data_ascii[6]={0,0,0,0,0,'\0'};							//string array for saving ascii of input sample
code unsigned char display_msg1[]="Volt.: ";						//Display msg on 1st line of lcd
code unsigned char display_msg2[]=" mV";								//Display msg on 2nd line of lcd



void main(void)
{.................
	int j=0;
	unsigned int adc_data=0;

	
	spi_init();																					
	adc_init();
  lcd_init();
	uart_init();
	
	while(1)
	{
	 	unsigned int x;
	
		x = adc(4);																					//Read analog value from 0th channel of ADC Ic MCP3008
		adc_data = (unsigned int) (x*3.2258); 							//Converting received 10 bits value to milli volt (3.3*1000*i/p /1023)
		
		lcd_cmd(0x80);																			//Move cursor to first line
		lcd_write_string(display_msg1);											//Display "Volt: " on first line of lcd
		
		int_to_string(adc_data,adc_ip_data_ascii);					//Converting integer to string of ascii
		
		lcd_write_string(adc_ip_data_ascii);								//Print analog sampled input on lcd
		lcd_write_string(display_msg2);											//Display "XXXXX mV"
		transmit_string(adc_ip_data_ascii);
		transmit_string("\r\n");
												

	}
}

