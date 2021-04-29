// ***********************************************************
// this is .c file
//Project:   ALU
// Author:   Apoorva Jinde
// ***********************************************************

#include<reg51.h>
#include<string.h>

//Define Macros
#define Error  13    // Any value other than 0 to 9 is good here

//Function declarations
void cct_init(void);
void delay(int);
void lcdinit(void);
void writecmd(int);
void writedata(char);
void writeline(char[]);
void ReturnHome(void);
char READ_SWITCHES(void);
char get_key(void);
int get_num(char);
char get_func(char);
void DispError(int);
void disp_num(int);
void desrip();

//*******************
//Pin description
/*
P2 is data bus
P3.7 is RS
P3.6 is E
P1.0 to P1.3 are keypad row outputs
P1.4 to P1.7 are keypad column inputs
*/
//********************
// Define Pins
//********************
sbit RowA = P1^0;     //RowA
sbit RowB = P1^1;     //RowB
sbit RowC = P1^2;     //RowC
sbit RowD = P1^3;     //RowD

sbit C1   = P1^4;     //Column1
sbit C2   = P1^5;     //Column2
sbit C3   = P1^6;     //Column3
sbit C4   = P1^7;     //Column4

sbit E    = P3^6;     //E pin for LCD
sbit RS   = P3^7;     //RS pin for LCD

// ***********************************************************
// Main program
//
int main(void)
{
   char key;                     //key char for keeping record of pressed key
   int num1 = 0;                 //First number
   char func = '+';              //Function to be performed among two numbers
   int num2 = 0;                 //Second number
   int op=0;
   char opc=' ';
   cct_init();                   //Make input and output pins as required
   lcdinit();                    //Initilize LCD
   desrip();// shows the option
   while(1)
   {
     desrip();
     opc=get_key();
     writecmd(0x01);
     writedata(opc);
     writedata(')');
     op=get_num(opc);
     if(op!=Error)
     {
     if(op==1)
     //get numb1
     {
    key = get_key();
	 writedata(key);            //Echo the key pressed to LCD
	 num1 = get_num(key);       //Get int number from char value, it checks for wrong input as well

	 if(num1!=Error)            //if correct input then proceed, num1==Error means wrong input
	 {
		 key = get_key();
		 writedata(key);                  //Echo the key pressed to LCD
		 func = get_func(key);            //it checks for wrong fun
		 if(func!='e')                    //if correct input then proceed, func=='e' means wrong input
		 {
			 //get numb2
			 key = get_key();
			 writedata(key);              //Echo the key pressed to LCD
			 num2 = get_num(key);         //Get int number from char value, it checks for wrong input as well

			 if(num2!=Error)              //if correct input then proceed, num2==Error means wrong input
			 {
				 //get equal sign
				 key = get_key();
				 writedata(key);          //Echo the key pressed to LCD

				 if(key == '=')           //if = is pressed then proceed
				 {
					 switch(func)         //switch on function
					 {
					 case '+': disp_num(num1+num2); break;

					 case '-': disp_num(num1-num2); break;

					 case 'x': disp_num(num1*num2); break;

					 case '/': if(num2==0)
					            DispError(0);
					            else
					          disp_num(num1/num2);
					          break;
					 }
				 }
				 else				      //key other then = here means error wrong input
				 {
					 if(key == 'C')       //if clear screen is pressed then clear screen and reset
					 {
					    writecmd(0x01);   //Clear Screen
						desrip();
					 }
					 else
					 {
					 	DispError(0); 	  //Display wrong input error
						desrip();
					 }
				 }
			 }
		 }
     }
   }
   else if(op==2)
   {
    key = get_key();

    writedata(key);            //Echo the key pressed to LCD
	 num1 = get_num(key);       //Get int number from char value, it checks for wrong input as well

	 if(num1!=Error)            //if correct input then proceed, num1==Error means wrong input
	 {//get function
		 key = get_key();
		  switch(key)         //switch on function
					 {
					 case '+': writedata('|'); break;
					 case '-': writedata('^'); break;
					 case 'x': writedata('&'); break;
					 case '/': writedata('~');
					 writedata('^'); break;

					 }

		 func = get_func(key);            //it checks for wrong func

		 if(func!='e')                    //if correct input then proceed, func=='e' means wrong input
		 {
			 //get numb2
			 key = get_key();
			 writedata(key);              //Echo the key pressed to LCD
			 num2 = get_num(key);         //Get int number from char value, it checks for wrong input as well

			 if(num2!=Error)              //if correct input then proceed, num2==Error means wrong input
			 {
				 //get equal sign
				 key = get_key();
				 writedata(key);          //Echo the key pressed to LCD

				 if(key == '=')           //if = is pressed then proceed
				 {
					 switch(func)         //switch on function
					 {
					 case '+': disp_num(num1|num2); break;
					 case '-': disp_num(num1^num2); break;
					 case 'x': disp_num(num1&num2); break;
					 case '/': disp_num(~(num1^num2));
					     break;
					 }
				 }
				 else				      //key other then = here means error wrong input
				 {
					 if(key == 'C')       //if clear screen is pressed then clear screen and reset
					 {
					    writecmd(0x01);   //Clear Screen
						desrip();
					 }
					 else
					 {
					 	DispError(0); 	  //Display wrong input error
						desrip();
					 }
				 }
			 }
		 }
     }
   }
    else if(op==3)
     //get numb1
     {
    key = get_key();

	 writedata(key);            //Echo the key pressed to LCD
	 num1 = get_num(key);       //Get int number from char value, it checks for wrong input as well

	 if(num1!=Error)            //if correct input then proceed, num1==Error means wrong input
	 {
		 //get function
		 key = get_key();
		 switch(key)         //switch on function
					 {
					 case '+': writedata('I'); break;
					 case '-': writedata('D'); break;
					 case 'x': writedata('~'); break;
					 case '/': DispError(1);break;
					 }                //Echo the key pressed to LCD
		 func = get_func(key);            //it checks for wrong func

		 if(func!='e')                    //if correct input then proceed, func=='e' means wrong input
		 {
			//get equal sign
				 key = get_key();
				 writedata(key);          //Echo the key pressed to LCD

				 if(key == '=')           //if = is pressed then proceed
				 {
					 switch(func)         //switch on function
					 {
					 case '+': disp_num(num1+1); break;
					 case '-': disp_num(num1-1); break;
					 case 'x': disp_num(~num1);break;
					 case '/': DispError(1);break;
					 }
				 }
				 else				      //key other then = here means error wrong input
				 {
					 if(key == 'C')       //if clear screen is pressed then clear screen and reset
					 {
					    writecmd(0x01);   //Clear Screen
						desrip();
					 }
					 else
					 {
					 	DispError(0); 	  //Display wrong input error
						desrip();
					 }
				 }

		 }
     }
   }
      else if(op==4)
   {
    key = get_key();

    writedata(key);            //Echo the key pressed to LCD
	 num1 = get_num(key);       //Get int number from char value, it checks for wrong input as well

	 if(num1!=Error)            //if correct input then proceed, num1==Error means wrong input
	 {//get function
		 key = get_key();
		  switch(key)         //switch on function
					 {
					 case '+': writedata('<'); writedata('<');break;
					 case '-': writedata('>'); writedata('>');break;
					 case 'x': DispError(1);break;
					 case '/': DispError(1);break;
					 }

		 func = get_func(key);            //it checks for wrong func

		 if(func!='e')                    //if correct input then proceed, func=='e' means wrong input
		 {
			 //get numb2
			 key = get_key();
			 writedata(key);              //Echo the key pressed to LCD
			 num2 = get_num(key);         //Get int number from char value, it checks for wrong input as well

			 if(num2!=Error)              //if correct input then proceed, num2==Error means wrong input
			 {
				 //get equal sign
				 key = get_key();
				 writedata(key);          //Echo the key pressed to LCD

				 if(key == '=')           //if = is pressed then proceed
				 {
					 switch(func)         //switch on function
					 {
					 case '+': disp_num(num1<<num2); break;
					 case '-': disp_num(num1>>num2); break;
					 case 'x': DispError(1);break;
					 case '/': DispError(1);break;
					 }
				 }
				 else				      //key other then = here means error wrong input
				 {
					 if(key == 'C')       //if clear screen is pressed then clear screen and reset
					 {
					    writecmd(0x01);   //Clear Screen
						desrip();
					 }
					 else
					 {
					 	DispError(0); 	  //Display wrong input error
						desrip();
					 }
				 }
			 }
		 }
     }
   }
   else
    DispError(0);
   }

}

}
void desrip()
{
   writecmd(0x95);
   writedata('a');                                 //write
   writedata('r');                                 //write
   writedata('i');                                 //write
   writedata('t');                                 //write
   writedata('-');                                 //write
   writedata('1');                                 //write
   writedata(',');                                 //write
   writedata('l');                                 //write
   writedata('o');                                 //write
   writedata('g');                                 //write
   writedata('i');                                 //write
   writedata('c');
   writedata('-');                                 //write
   writedata('2');                                 //write
   writedata(',');                                 //write
   writedata('b');
   writedata('i');                                 //write
   writedata('t');                                  //write

   writecmd(0xd8);

   writedata('o');                                 //write
   writedata('p');                                 //write
   writedata('-');                                 //write
   writedata('3');
   writedata(',');                                 //write
   writedata('s');                                 //write
   writedata('h');                                 //write
   writedata('i');                                 //write
   writedata('f');                                 //write
   writedata('t');                                 //write
   writedata('-');                                 //write
   writedata('4');
                                   //write
   writecmd(0x80);
}

void cct_init(void)
{
	P0 = 0x00;   //not used
	P1 = 0xf0;   //used for generating outputs and taking inputs from Keypad
	P2 = 0x00;   //used as data port for LCD
	P3 = 0x00;   //used for RS and E
}

void delay(int a)
{
   int i;
   for(i=0;i<a;i++);   //null statement
}

void writedata(char t)
{
   RS = 1;             // This is data
   P2 = t;             //Data transfer
   E  = 1;             // => E = 1
   delay(150);
   E  = 0;             // => E = 0
   delay(150);
}


void writecmd(int z)
{
   RS = 0;             // This is command
   P2 = z;             //Data transfer
   E  = 1;             // => E = 1
   delay(150);
   E  = 0;             // => E = 0
   delay(150);
}

void lcdinit(void)
{
  ///////////// Reset process from datasheet /////////
     delay(15000);
   writecmd(0x30);
     delay(4500);
   writecmd(0x30);
     delay(300);
   writecmd(0x30);
     delay(650);
  /////////////////////////////////////////////////////
   writecmd(0x38);    //function set
   writecmd(0x0c);    //display on,cursor off,blink off
   writecmd(0x01);    //clear display
   writecmd(0x06);    //entry mode, set increment
}

void ReturnHome(void)     /* Return to 0 cursor location */
{
   writecmd(0x02);
   delay(1500);
   desrip();
}

void writeline(char Line[])
{
   int i;
   for(i=0;i<strlen(Line);i++)
   {
      writedata(Line[i]);     /* Write Character */
   }

   ReturnHome();          /* Return to 0 cursor position */
}

char READ_SWITCHES(void)
{
	RowA = 0; RowB = 1; RowC = 1; RowD = 1; 	//Test Row A

	if (C1 == 0) { delay(10000); while (C1==0); return '7'; }
	if (C2 == 0) { delay(10000); while (C2==0); return '8'; }
	if (C3 == 0) { delay(10000); while (C3==0); return '9'; }
	if (C4 == 0) { delay(10000); while (C4==0); return '/'; }

	RowA = 1; RowB = 0; RowC = 1; RowD = 1; 	//Test Row B

	if (C1 == 0) { delay(10000); while (C1==0); return '4'; }
	if (C2 == 0) { delay(10000); while (C2==0); return '5'; }
	if (C3 == 0) { delay(10000); while (C3==0); return '6'; }
	if (C4 == 0) { delay(10000); while (C4==0); return 'x'; }

	RowA = 1; RowB = 1; RowC = 0; RowD = 1; 	//Test Row C

	if (C1 == 0) { delay(10000); while (C1==0); return '1'; }
	if (C2 == 0) { delay(10000); while (C2==0); return '2'; }
	if (C3 == 0) { delay(10000); while (C3==0); return '3'; }
	if (C4 == 0) { delay(10000); while (C4==0); return '-'; }

	RowA = 1; RowB = 1; RowC = 1; RowD = 0; 	//Test Row D

	if (C1 == 0) { delay(10000); while (C1==0); return 'C'; }
	if (C2 == 0) { delay(10000); while (C2==0); return '0'; }
	if (C3 == 0) { delay(10000); while (C3==0); return '='; }
	if (C4 == 0) { delay(10000); while (C4==0); return '+'; }

	return 'n';           	// Means no key has been pressed
}

char get_key(void)           //get key from user
{
	char key = 'n';              //assume no key pressed

	while(key=='n')              //wait untill a key is pressed
		key = READ_SWITCHES();   //scan the keys again and again

	return key;                  //when key pressed then return its value
}

int get_num(char ch)         //convert char into int
{
	switch(ch)
	{
		case '0': return 0; break;
		case '1': return 1; break;
		case '2': return 2; break;
		case '3': return 3; break;
		case '4': return 4; break;
		case '5': return 5; break;
		case '6': return 6; break;
		case '7': return 7; break;
		case '8': return 8; break;
		case '9': return 9; break;
		case 'C': writecmd(0x01); return Error; break;  //this is used as a clear screen and then reset by setting error
		default: DispError(0); return Error; break;     //it means wrong input
	}
}

char get_func(char chf)            //detects the errors in inputted function
{
	if(chf=='C')                   //if clear screen then clear the LCD and reset
	{
		writecmd(0x01);            //clear display
		desrip();
		return 'e';
	}

	if( chf!='+' && chf!='-' && chf!='x' && chf!='/' )  //if input is not from allowed funtions then show error
	{
		DispError(1);
		desrip();
		return 'e';
	}

	return chf;                        //function is correct so return the correct function
}


void DispError(int numb)           //displays differet error messages
{
	writecmd(0x01);                //clear display
	desrip();
	switch(numb)
	{
	case 0: 	writeline("Wrong Input");      break;
	case 1: 	writeline("Wrong Function");   break;
	default:    writeline("Wrong Input");      break;
	}
}

void disp_num(int numb)            //displays number on LCD
{
	unsigned char UnitDigit  = 0;  //It will contain unit digit of numb
	unsigned char TenthDigit = 0;  //It will contain 10th position digit of numb

	if(numb<0)
	{
		numb = -1*numb;  // Make number positive
		writedata('-');	 // Display a negative sign on LCD
	}

	TenthDigit = (numb/10);	          // Findout Tenth Digit

	if( TenthDigit != 0)	          // If it is zero, then don't display
		writedata(TenthDigit+0x30);	  // Make Char of TenthDigit and then display it on LCD

	UnitDigit = numb - TenthDigit*10;

	writedata(UnitDigit+0x30);	  // Make Char of UnitDigit and then display it on LCD
}

