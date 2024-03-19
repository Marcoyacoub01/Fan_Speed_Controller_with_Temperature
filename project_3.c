/*
 * project_3.c
 *
 *  Created on: Feb 29, 2024
 *      Author: MARCO
 */


#include "adc.h"
#include "lm35_sensor.h"
#include "dcMotor.h"
#include "lcd.h"

uint8 temp = 0 ;

void display(void)
{
	temp = LM35_getTemperature();
			if (temp < 30)
			{
				LCD_displayStringRowColumn(0,10,"OFF");
				DcMotor_Rotate(STOP,0);

			}
			else if ((temp >= 30) && (temp < 60))
			{
				LCD_displayStringRowColumn(0,10,"ON ");
				DcMotor_Rotate(CW,25);

			}
			else if ((temp >= 60) && (temp < 90))
			{
				LCD_displayStringRowColumn(0,10,"ON ");
				DcMotor_Rotate(CW,50);
			}
			else if ((temp >= 90) && (temp < 120))
			{
				LCD_displayStringRowColumn(0,10,"ON ");
				DcMotor_Rotate(CW,75);
			}
			else if (temp > 120)
			{
				LCD_displayStringRowColumn(0,10,"ON ");
				DcMotor_Rotate(CW,100);
			}
			LCD_moveCursor(1,9);
			if (temp < 100)
			{
				LCD_intgerToString(temp);
				LCD_displayCharacter(' ');
			}
			else
			{
			LCD_intgerToString(temp);
			}


			LCD_displayCharacter('C');
}


int main (void)
{
	ADC_ConfigType adc_config =
	{
			INTERNAL,
			PRESCALER_8
	};

	ADC_init(&adc_config);
	DcMotor_Init();
	LCD_init();




	LCD_displayStringRowColumn(0,3,"FAN IS ");
	LCD_displayStringRowColumn(1,3,"TEMP = ");

	while(1)
	{
		display();
	}
}




