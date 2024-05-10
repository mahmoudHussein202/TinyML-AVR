#include "ANN_LIB/ANN.h"
int main()
{
    /*--------- Initialization---------*/
    unsigned char result[OutputNodes] = {0};
    initializing_Hidden_weights_randomly();
    /*----------- Training ---------*/
    start_training();
    /*----------- Results ----------*/
    get_weights();
    /*-----------Small Test ---------*/
    unsigned int input_val[InputNodes]={7}; 
    get_prediction(input_val,result);
}