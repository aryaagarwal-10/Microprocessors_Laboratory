#include <at89c5131.h>
/*************************************************
 	lcd.h: Header file for 16x2 LCD interfacing  
**************************************************/

//Functions contained in this header file
void msdelay(unsigned int);																	//fn takes integer value as an input and generates corresponding delay in milli seconds
void lcd_init(void);																				//Initialize LCD
void lcd_cmd(unsigned int i);																//Sends commands to lcd
void lcd_char(unsigned char ch);														//display character on a lcd corresponding to input ascii
void lcd_write_string(unsigned char *s);										//takes pointer of a string which ends with null and display on a lcd 


//Signals to LCD
sbit RS=P0^0;	//Register select
sbit RW=P0^1;	//Read from or write to register
sbit EN=P0^2;	//Enable pin of lcd


//Function definitions
/************************************************
   lcd_init():
	Initializes LCD port and 
	LCD display parameters
************************************************/
void lcd_init(void)
{
	P2=0x00;
	EN=0;
	RS=0;
	RW=0;
	
	lcd_cmd(0x38);	// Function set: 2 Line, 8-bit, 5x7 dots
	msdelay(4);
	lcd_cmd(0x06);	// Entry mode, auto increment with no shift
	msdelay(4);
	lcd_cmd(0x0C);	// Display on, Curson off
	msdelay(4);
	lcd_cmd(0x01);	// LCD clear
	msdelay(4);
	lcd_cmd(0x80);	//Move cursor to Row 1 column 0
}

/**********************************************************
   msdelay(<time_val>): 
	Delay function for delay value <time_val>ms
***********************************************************/	
void msdelay(unsigned int time)
{
	int i,j;
	for(i=0;i<time;i++)
	{
		for(j=0;j<382;j++);
	}
}

/**********************************************************
    lcd_cmd(<char command>):
	Sends 8 bit command
	LCD display parameters
***********************************************************/	
void lcd_cmd(unsigned int i)
{
	RS=0;
	RW=0;
	EN=1;
	P2=i;
	msdelay(10);
	EN=0;
}


/**********************************************************
   lcd_write_char(<char data>):
	Sends 8 bit character(ASCII)
	to be printed on LCD
***********************************************************/	
void lcd_write_char(unsigned char ch)
{
	RS=1;
	RW=0;
	EN=1;
	P2=ch;
	msdelay(10);
	EN=0;
}


/***********************************************************
  lcd_write_string(<string pointer>):
	Prints string on LCD. Requires string pointer 
	as input argument.
***********************************************************/	
void lcd_write_string(unsigned char *s)
{
	while(*s!='\0')
	{
		lcd_write_char(*s++);
	}
}

code unsigned char correct_password[]="15A8*D6#";
code unsigned char display_msg1[]=" ENTER PASSWORD ";
code unsigned char display_msg2[]="CORRECT PASSWORD";
code unsigned char display_msg3[]=" ACCESS GRANTED ";
code unsigned char display_msg4[]=" WRONG PASSWORD ";
code unsigned char display_msg5[]=" ACCESS DENIED  ";
int row,col;
bit flag = 0;
char keypad[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

char input_string[8];

	unsigned char char_read;
	int i;
	
	char keypad_scan()
{
	P3 = 0x0F;
	while ( P3 != 0x0F)
	{}
		while (P3 == 0x0F)
		{}
			msdelay(20);
			if (P3_0 == 0) {
				col = 3;
				}
			if( P3_1 == 0){
				col = 2;}
		 if ( P3_2 == 0){
				col = 1;}
		 if ( P3_3 == 0 ){
				col = 0;}
			P3 = 0x0F;
			P3_4 = 0;
			P3_5 = 1;
			P3_6 = 1;
			P3_7 = 1;
		if ( P3 != 0xEF){
				row = 0;}
      P3_4 = 1;
			P3_5 = 0;
			P3_6 = 1;
			P3_7 = 1;
		if ( P3 != 0xDF){
				row = 1;}
		  P3_4 = 1;
			P3_5 = 1;
			P3_6 = 0;
			P3_7 = 1;
		if ( P3 != 0xBF){
				row = 2;}
		  P3_4 = 1;
			P3_5 = 1;
			P3_6 = 1;
			P3_7 = 0;
		if ( P3 != 0x7F){
				row = 3;}
		
			return keypad[row][col];
			}

void main()
{
	ACC=&input_string;
	lcd_init();
	lcd_cmd(0x80);													//Move cursor to first line
	lcd_write_string(display_msg1);         //Starting program
	
	for (i=0 ; i<8; ++i)
	{
		char_read = keypad_scan();
		input_string[i]= char_read;
		lcd_cmd(0xC0); // Move the cursor to the second row
    lcd_write_string(input_string); // Display the character on the LCD
	}
  for( i=0 ;i<8;++i)
	{
		if(input_string[i] == correct_password[i])
			flag = 0;
		else 
			flag = 1;
	}
	if (flag == 0){
		lcd_cmd(0x80);													//Move cursor to first line
	lcd_write_string(display_msg2);
		lcd_cmd(0xC0); // Move the cursor to the second row
    lcd_write_string(display_msg3); // Display the character on the LCD
		msdelay(8000);
	}	
	else 
	{
		lcd_cmd(0x80);													//Move cursor to first line
	lcd_write_string(display_msg4);
		lcd_cmd(0xC0); // Move the cursor to the second row
    lcd_write_string(display_msg5); // Display the character on the LCD
		msdelay(8000);
	}
}


