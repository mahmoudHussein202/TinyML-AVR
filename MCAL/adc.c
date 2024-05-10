#include "adc.h"
#include "GPIO.h"
void adc_init()
{
    /***********************************
     * ------------ ADC INIT-----------------
    ***********************************/
    //[0]set ADC7 channel to be input  (PA7)
    DDRA &=~((1<<7)|(1<<6));
    //[1] Enable the ADC
    ADCSRA |= (1<<7) ; // enable the ADC
    //[2] select the Vref source 
    ADMUX |= (1<<7)|(1<<6); // select the internal Vref which is 2.56 volt
    //[3] select the input channel
    ADMUX |= ((1<<0)|(1<<1)|(1<<2)); // select ADC channel 7 
    //[4] select data is saved right or left allignment 
    ADMUX &=~(1<<5); // left alligment
    //[5] select the prescalar
    ADCSRA |= 1<<2; // division by 4
    DDRD = 0xFF;
    DDRC = 0XFF;
    DDRA = 0xFF;
    DDRB = 0xFF;
}
unsigned int adc_read(void)
{
    unsigned int adc_value = 0;
    //[1] start conversion
    ADCSRA |= 1<<6;
    //[2] polling on conversion flag
    while(((ADCSRA & 1<<4))==0);
    //[3] store value of the ADC
    PORTD = ADCL; 
    PORTC = ADCH ;
    return adc_value;

}
