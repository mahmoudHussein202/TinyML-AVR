#include "ANN.h"
/******************************************************************
* ------- Training Data 
******************************************************************/
const unsigned char Input[PatternCount][InputNodes] = {
  {1},{2},{3},{4},{5},
  {11},{12},{13},{14},{15},
  {21},{22},{23},{24},{25},
  {31},{32},{33},{34},{35},
}; 
const unsigned char Target[PatternCount][OutputNodes] = {
  {0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},
  {1,1,0,0},{1,1,0,0},{1,1,0,0},{1,1,0,0},{1,1,0,0},
  {1,1,0,0},{1,1,0,0},{1,1,0,0},{1,1,0,0},{1,1,0,0},
  {1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1},
};
/******************************************************************
*-------------------- Variables ------------------------
******************************************************************/
int i, j, p, q, r;
int ReportEvery100 = 0;
int RandomizedIndex[PatternCount];
long  TrainingCycle;
float Rando;
float Error;
float Accum;
float Hidden[HiddenNodes];
float Output[OutputNodes];
float HiddenWeights[InputNodes+1][HiddenNodes];
float OutputWeights[HiddenNodes+1][OutputNodes];
float HiddenDelta[HiddenNodes];
float OutputDelta[OutputNodes];
float ChangeHiddenWeights[InputNodes+1][HiddenNodes];
float ChangeOutputWeights[HiddenNodes+1][OutputNodes];
void initializing_Hidden_weights_randomly()
{
    for( int p = 0 ; p < PatternCount ; p++ ) 
    {    
        RandomizedIndex[p] = p ;
    }
    /******************************************************************
    * Initialize HiddenWeights and ChangeHiddenWeights 
    ******************************************************************/
    for( i = 0 ; i < HiddenNodes ; i++ ) 
    {    
        for( j = 0 ; j <= InputNodes ; j++ ) 
        { 
            ChangeHiddenWeights[j][i] = 0.0 ;
            Rando = (float)(rand())/1000000;
            HiddenWeights[j][i] = 2.0 * ( Rando - 0.5 ) * InitialWeightMax ;
        }
    }
    /******************************************************************
    * Initialize OutputWeights and ChangeOutputWeights
    ******************************************************************/
    for( i = 0 ; i < OutputNodes ; i ++ ) 
    {    
        for( j = 0 ; j <= HiddenNodes ; j++ ) 
        {
        ChangeOutputWeights[j][i] = 0.0 ;          
        Rando = (float)(rand())/1000000;          
        OutputWeights[j][i] = 2.0 * ( Rando - 0.5 ) * InitialWeightMax ;
        }
    }
}

void start_training()
{
    for( TrainingCycle = 1 ; TrainingCycle < Trainng_Cycles ; TrainingCycle++) 
    { 
        /******************************************************************
        * Randomize order of training patterns
        ******************************************************************/
        for( p = 0 ; p < PatternCount ; p++) 
        {
            while(!(q>=0 && q<=PatternCount-1))
            {
                q = (int)rand()%(PatternCount-0+1);
            }
            r = RandomizedIndex[p] ; 
            RandomizedIndex[p] = RandomizedIndex[q] ; 
            RandomizedIndex[q] = r ;
        }
        Error = 0.0 ;
        /******************************************************************
        * Cycle through each training pattern in the randomized order
        ******************************************************************/
        for( q = 0 ; q < PatternCount ; q++ ) 
        {    
            p = RandomizedIndex[q];
        }
        /******************************************************************
        * Compute hidden layer activations
        ******************************************************************/
        for( i = 0 ; i < HiddenNodes ; i++ ) 
        {    
            Accum = HiddenWeights[InputNodes][i] ;
            for( j = 0 ; j < InputNodes ; j++ ) 
            {
                //printf("%d %2f\n",Input[p][j],HiddenWeights[j][i]);
                Accum += Input[p][j] * HiddenWeights[j][i] ;
            }
            Hidden[i] = 1.0/(1.0 + exp(-Accum)) ;
        }
        /******************************************************************
        * Compute output layer activations and calculate errors
        ******************************************************************/
        for( i = 0 ; i < OutputNodes ; i++ ) 
        {    
            Accum = OutputWeights[HiddenNodes][i] ;
            for( j = 0 ; j < HiddenNodes ; j++ ) 
            {
                Accum += Hidden[j] * OutputWeights[j][i] ;
            }
            Output[i] = 1.0/(1.0 + exp(-Accum)) ;   
            OutputDelta[i] = (Target[p][i] - Output[i]) * Output[i] * (1.0 - Output[i]) ;   
            Error += 0.5 * (Target[p][i] - Output[i]) * (Target[p][i] - Output[i]) ;
        }
        //printf("error = %f \n",Error);  
        /******************************************************************
        * Backpropagate errors to hidden layer
        ******************************************************************/
        for( i = 0 ; i < HiddenNodes ; i++ ) 
        {    
            Accum = 0.0 ;
            for( j = 0 ; j < OutputNodes ; j++ ) 
            {
                Accum += OutputWeights[i][j] * OutputDelta[j] ;
            }
            HiddenDelta[i] = Accum * Hidden[i] * (1.0 - Hidden[i]) ;
        }
        /******************************************************************
        * Update Inner-->Hidden Weights
        ******************************************************************/
        for( i = 0 ; i < HiddenNodes ; i++ ) 
        {     
            ChangeHiddenWeights[InputNodes][i] = LearningRate * HiddenDelta[i] + Momentum * ChangeHiddenWeights[InputNodes][i] ;
            HiddenWeights[InputNodes][i] += ChangeHiddenWeights[InputNodes][i] ;
            for( j = 0 ; j < InputNodes ; j++ ) 
            { 
                ChangeHiddenWeights[j][i] = LearningRate * Input[p][j] * HiddenDelta[i] + Momentum * ChangeHiddenWeights[j][i];
                HiddenWeights[j][i] += ChangeHiddenWeights[j][i] ;
            }
        }
        /******************************************************************
        * Update Hidden-->Output Weights
        ******************************************************************/
        for( i = 0 ; i < OutputNodes ; i ++ ) 
        {    
            ChangeOutputWeights[HiddenNodes][i] = LearningRate * OutputDelta[i] + Momentum * ChangeOutputWeights[HiddenNodes][i] ;
            OutputWeights[HiddenNodes][i] += ChangeOutputWeights[HiddenNodes][i] ;
            for( j = 0 ; j < HiddenNodes ; j++ ) 
            {
                ChangeOutputWeights[j][i] = LearningRate * Hidden[j] * OutputDelta[i] + Momentum * ChangeOutputWeights[j][i] ;
                OutputWeights[j][i] += ChangeOutputWeights[j][i] ;
            }
        }
        ReportEvery100++;
        if(ReportEvery100 ==1000)
        {
            printf("error = %f \n",Error);
            ReportEvery100 = 0;
        }
        if(Error<= Success)
            break;
    }
    printf("trianing finished with an error = %f \n",Error);
}

void get_weights()
{
    printf("\n-----------------------HIDDEN WEIGHTS---------------------\n");

    for(int i = 0 ; i < (InputNodes+1) ;i++)
    {
        for (int j = 0 ; j < HiddenNodes; j++)
            printf("%f,  ",HiddenWeights[i][j]);

        printf("\n");
    }
        printf("\n-----------------------OUTPUT WEIGHTS---------------------\n");

    for(int i = 0 ; i < HiddenNodes+1 ;i++)
    {
        for (int j = 0 ; j < OutputNodes; j++)
            printf("%f,  ",OutputWeights[i][j]);

        printf("\n");
    }
}
void get_prediction(unsigned int in_for_predict[InputNodes],unsigned char out_buffer[OutputNodes])
{
    /******************************************************************
    * Compute hidden layer activations
    ******************************************************************/
    float acc_test= 0 ;
    /******************************************************************
    * Compute hidden layer activations
    ******************************************************************/
    for( i = 0 ; i < HiddenNodes ; i++ ) {    
    Accum = HiddenWeights[InputNodes][i] ;
    for( j = 0 ; j < InputNodes ; j++ ) {
        Accum += in_for_predict[j] * HiddenWeights[j][i] ;
    }
    Hidden[i] = 1.0/(1.0 + exp(-Accum)) ;
    }
    /******************************************************************
    * Compute output layer activations and calculate errors
    ******************************************************************/
    for( i = 0 ; i < OutputNodes ; i++ ) 
    {    
    Accum = OutputWeights[HiddenNodes][i] ;
    for( j = 0 ; j < HiddenNodes ; j++ ) 
    {
        Accum += Hidden[j] * OutputWeights[j][i] ;
    }
    Output[i] = 1.0/(1.0 + exp(-Accum)) ; 
    }
    printf("output : ");
    for( i = 0 ; i < OutputNodes ; i++ ) {       
    printf("%f",Output[i]);
    printf (" ");
    if (Output[i] > 0.5)
        out_buffer[i]=1;
    else
        out_buffer[i]=0;
    }
}
