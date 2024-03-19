/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Description: Source file for the ATmega32 ADC driver
 *
 * Author: MARCO
 *
 *******************************************************************************/

#include "avr/io.h" /* To use the ADC Registers */
#include "adc.h"
#include "common_macros.h" /* To use the macros like SET_BIT */


void ADC_init(const ADC_ConfigType * Config_Ptr)
{

	/* ADMUX Register Bits Description:
	* REFS1:0 =  input based on the choose of the user
    * ADLAR   = 0 right adjusted
    * MUX4:0  = 00000 to choose channel 0 as initialization
    */
	 ADMUX = (ADMUX & 0x3F) | ((Config_Ptr->ref_volt)<<6);

	/* ADCSRA Register Bits Description:
	 * Bit 7 – ADEN = 1 to Enable ADC
	 * Bit 3 – ADIE = 0 for ADC Interrupt DISanable
	 * ADATE   = 0 Disable Auto Trigger
	 *ADPS2:0 = input based on the choose of the user
   	 */

	ADCSRA = ADCSRA | (1<<ADEN);
	ADCSRA = (ADCSRA& 0xF8 ) | (Config_Ptr->prescaler);
}


uint16 ADC_readChannel(uint8 ch_num)
{
	/* Choose the correct channel by setting the channel number in MUX4:0 bits */
	ADMUX = ( ADMUX & 0xE0 ) | (ch_num & 0x07);
	/* Start conversion write '1' to ADSC */
	SET_BIT(ADCSRA,ADSC);
	/* Wait for conversion to complete, ADIF becomes '1' */
	while(BIT_IS_CLEAR(ADCSRA,ADIF));
	 /* Clear ADIF by write '1' to it */
	SET_BIT(ADCSRA,ADIF);
	/* Read the digital value from the data register */
	return ADC;
}
