#ifndef ADC_H_
#define ADC_H_
#define ACSR            *((volatile unsigned char*)(0x28))
#define ADMUX           *((volatile unsigned char*)(0x27))
#define ADCSRA          *((volatile unsigned char*)(0x26))
#define ADCH            *((volatile unsigned char*)(0x25))
#define ADCL            *((volatile unsigned char*)(0x24))   
void adc_init();
#endif