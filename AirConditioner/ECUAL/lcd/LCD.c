/*
 * CFile1.c
 *
 * Created: 4/1/2023 3:51:57 PM
 *  Author: atef
 */
#define  F_CPU  8000000
#include <util/delay.h>
#include "LCD_Interface.h"
#include "LCD_Cfg.h"

#if LCD_MODE==_8_BIT
static void LCD_WriteIns(u8 u8_a_ins)
{
	
	
    DIO_write(PORT_B,RS,LOW);
	DIO_WritePort(LCD_PORT,u8_a_ins);
	 DIO_write(PORT_B,EN,HIGH);
	_delay_ms(1);
	 DIO_write(PORT_B,EN,LOW);
	_delay_ms(1);
	
}

static void LCD_WriteData(u8 u8_a_data)
{
	
	    DIO_write(PORT_B,RS,HIGH);
	    DIO_WritePort(LCD_PORT,u8_a_data);
	    DIO_write(PORT_B,EN,HIGH);
	    _delay_ms(1);
	    DIO_write(PORT_B,EN,LOW);
	    _delay_ms(1);
}



void LCD_Init(void)
{
	_delay_ms(50);
	
	LCD_WriteIns(0x38);//5*7 2 lines
	LCD_WriteIns(0x0c);//0x0c,0x0e,0x0f cursor
	LCD_WriteIns(0x01);//clear screen
	_delay_ms(1);
	LCD_WriteIns(0x06);// increment DDRAM address, no shift
	
}

#elif LCD_MODE ==_4_BIT
static void LCD_WriteIns(u8 u8_a_ins)
{
	
	

	DIO_write(LCD_PORT,RS,LOW);
	
	DIO_write(LCD_PORT,D7,GET_BIT(u8_a_ins,7));
	DIO_write(LCD_PORT,D6,GET_BIT(u8_a_ins,6));
	DIO_write(LCD_PORT,D5,GET_BIT(u8_a_ins,5));
	DIO_write(LCD_PORT,D4,GET_BIT(u8_a_ins,4));
	 DIO_write(LCD_PORT,EN,HIGH);
	_delay_ms(1);
	 DIO_write(LCD_PORT,EN,LOW);
	_delay_ms(1);
	DIO_write(LCD_PORT,D7,GET_BIT(u8_a_ins,3));
	DIO_write(LCD_PORT,D6,GET_BIT(u8_a_ins,2));
	DIO_write(LCD_PORT,D5,GET_BIT(u8_a_ins,1));
	DIO_write(LCD_PORT,D4,GET_BIT(u8_a_ins,0));
	DIO_write(LCD_PORT,EN,HIGH);
	_delay_ms(1);
	DIO_write(LCD_PORT,EN,LOW);
	_delay_ms(1);
}

static void LCD_WriteData(u8 u8_a_data)
{
		DIO_write(LCD_PORT,RS,HIGH);
		
		DIO_write(LCD_PORT,D7,GET_BIT(u8_a_data,7));
		DIO_write(LCD_PORT,D6,GET_BIT(u8_a_data,6));
		DIO_write(LCD_PORT,D5,GET_BIT(u8_a_data,5));
		DIO_write(LCD_PORT,D4,GET_BIT(u8_a_data,4));
		DIO_write(LCD_PORT,EN,HIGH);
		_delay_ms(1);
		DIO_write(LCD_PORT,EN,LOW);
		_delay_ms(1);
		DIO_write(LCD_PORT,D7,GET_BIT(u8_a_data,3));
		DIO_write(LCD_PORT,D6,GET_BIT(u8_a_data,2));
		DIO_write(LCD_PORT,D5,GET_BIT(u8_a_data,1));
		DIO_write(LCD_PORT,D4,GET_BIT(u8_a_data,0));
		DIO_write(LCD_PORT,EN,HIGH);
		_delay_ms(1);
		DIO_write(LCD_PORT,EN,LOW);
		_delay_ms(1);
}



void LCD_Init(void)
{
	_delay_ms(50);
	LCD_WriteIns(0x02);
	LCD_WriteIns(0x28);//5*7 2 lines
	LCD_WriteIns(0x0c);//0x0c,0x0e,0x0f cursor
	LCD_WriteIns(0x01);//clear screen
	_delay_ms(1);
	LCD_WriteIns(0x06);// increment DDRAM address, no shift
	
}

#endif

//should be send address in ddram befor this function
void LCD_WriteChar(u8 u8_a_ch)
{
	LCD_WriteData(u8_a_ch);
}
void LCD_WriteString(u8 *u8_a_str)
{
	u8 i;
	for (i=0;u8_a_str[i];i++)
	{
		LCD_WriteChar(u8_a_str[i]);
	}
	
}
void LCD_SetCursor(u8 u8_a_line,u8 u8_a_cell)
{
	if (u8_a_line==0)
	{
		LCD_WriteIns(0x80|u8_a_cell);
	}
	else if (u8_a_line ==1)
	{
		LCD_WriteIns(0x80+0x40+u8_a_cell);
	}
	
}
void LCD_Clear(void)
{
	LCD_WriteIns(CLR_INS);
	_delay_ms(1);
}


void LCD_WriteNumber(i32 i32_a_num)
{
	u8 str[10],i=0,j;
	if (i32_a_num==0)
	{
		LCD_WriteChar('0');
		return;
	}
	if (i32_a_num<0)
	{
		i32_a_num=i32_a_num*(-1);
		LCD_WriteChar('-');
	}
	
	while(i32_a_num)
	{
		str[i]=i32_a_num%10 +'0';
		i++;
		i32_a_num=i32_a_num/10;
	}
	for (j=i;j>0;j--)
	{
		LCD_WriteChar(str[j-1]);
	}

}


void LCD_WriteBinary(u8 u8_a_num)
{
	i8 i;
	for (i=7;i>=0;i--)
	{
		LCD_WriteChar(GET_BIT(u8_a_num,i)+'0');
	}
	
}


void LCD_ClearLoc(u8 u8_a_line ,u8 u8_a_cell,u8 u8_a_num)
{
	u8 i;
	LCD_SetCursor(u8_a_line,u8_a_cell);
	for (i=0;i<u8_a_num;i++)
	{
		LCD_WriteChar(' ');
	}
	
}


void LCD_WriteNumber_3D(u16 num)
{
	//LCD_WriteChar(((num%100000)/10000)+'0');
	LCD_WriteChar(((num%10000)/1000)+'0');
	LCD_WriteChar(((num%1000)/100)+'0');
	LCD_WriteChar(((num%100)/10)+'0');
	LCD_WriteChar(((num%10)/1)+'0');
}


void LCD_CustomChar(u8 u8_a_loc,u8 *u8_a_pattern)
{
	LCD_WriteIns(0x40+u8_a_loc*8);
	for(u8 i=0;i<8;i++)
	{
		LCD_WriteData(u8_a_pattern[i]);
	}
	LCD_WriteIns(0x80);
}
 
 
 void LCD_PinsInit ()
 {
	 DIO_init(LCD_PORT,0,OUTPUT);
	 DIO_init(LCD_PORT,1,OUTPUT);
	 DIO_init(LCD_PORT,2,OUTPUT);
	 DIO_init(LCD_PORT,3,OUTPUT);
	 DIO_init(LCD_PORT,4,OUTPUT);
	 DIO_init(LCD_PORT,5,OUTPUT);
	 DIO_init(LCD_PORT,6,OUTPUT);
	 DIO_init(LCD_PORT,7,OUTPUT);
 }