#include "ANN_LIB\ANN_Config.h"
#include "MCAL\adc.h"
#include "MCAL\GPIO.h"
#include "math.h"
int main()
{
    adc_init();
    /******************************************************************
    * Compute hidden layer activations
    ******************************************************************/
    float Accum;
    float Hidden[HiddenNodes];
    float Output[OutputNodes];
    float HiddenWeights[InputNodes+1][HiddenNodes] = 
    {{-0.154372,  -0.160183,  -0.165150,  -0.157838,  -0.183739,  -0.155643,  -0.164032,  -0.729726}
    ,{2.802584,  3.194871,  3.442663,  3.056557,  4.204031,  2.905981,  3.389803,  5.219613}};
    float OutputWeights[HiddenNodes+1][OutputNodes] =
    {
        {-1.063731,  -1.060815,  -3.012644,  -2.980829},
        {-0.854669,  -0.855398,  -3.165397,  -3.164078},
        {-0.739446,  -0.731554,  -3.267387,  -3.284709},
        {-0.936973,  -0.929029,  -3.104111,  -3.111800},
        {-0.370540,  -0.388609,  -3.612271,  -3.617539},
        {-1.005264,  -1.020881,  -3.054394,  -3.032644},
        {-0.766953,  -0.755215,  -3.243413,  -3.261636},
        {-5.422549,  -5.421462,  -1.171225,  -1.168148},
        {7.291582,  7.295068,  5.135379,  5.136407},
    };

    while(1)
    {
        //[1] start conversion
        ADCSRA |= 1<<6;
        //[2] polling on conversion flag
        while(((ADCSRA & 1<<4))==0);
        //[3] store value of the ADC
        PORTD = ADCL; 
        PORTC = ADCH ;
        /******************************************************************
        * Compute hidden layer activations
        ******************************************************************/
        int a[1] =  {PORTD};
        float acc_test= 0 ;
        for( int i = 0 ; i < HiddenNodes ; i++ ) {    
        Accum = HiddenWeights[InputNodes][i] ;
        for( int j = 0 ; j < InputNodes ; j++ ) {
            Accum += a[j] * HiddenWeights[j][i] ;
        }
        Hidden[i] = 1.0/(1.0 + exp(-Accum)) ;
        }
        /******************************************************************
        * Compute output layer activations and calculate errors
        ******************************************************************/
        for( int i = 0 ; i < OutputNodes ; i++ ) {    
        Accum = OutputWeights[HiddenNodes][i] ;
        for( int j = 0 ; j < HiddenNodes ; j++ ) {
            Accum += Hidden[j] * OutputWeights[j][i] ;
        }
        Output[i] = 1.0/(1.0 + exp(-Accum)) ; 
        }
        /*******************************************************************/
        /********************** PORT B OUTPUT RESULT ***********************/
        
        for( int i = 0 ; i < OutputNodes ; i++ ) 
        {       
            if(Output[i]>0.5)
            {
                PORTB|=1<<i;
            }
            else
            {
                PORTB&=~(1<<i);
            }
        }
    }
}