#ifndef _ANN_H_
#define _ANN_H_
#include <math.h>
#include "stdlib.h"
#include "stdio.h"
#include "ANN_Config.h"
/******************************************************************
*-------------------- APIs
******************************************************************/
void initializing_Hidden_weights_randomly();
void start_training();
void get_weights();
void get_prediction(unsigned int in_for_predict[InputNodes],unsigned char* buffer);
#endif