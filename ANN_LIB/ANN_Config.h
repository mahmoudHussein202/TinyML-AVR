#ifndef _ANN_CONFIG_H_
#define _ANN_CONFIG_H_
/******************************************************************
*-------- Network Setup
******************************************************************/
#define PatternCount    20
#define InputNodes      1 
#define HiddenNodes     8
#define OutputNodes     4
#define Trainng_Cycles  30000000
/******************************************************************
*-------- Network Configuration - customized per network 
******************************************************************/
#define LearningRate        0.0001
#define Momentum            0.9
#define InitialWeightMax    0.5
#define Success             0.0001
#endif