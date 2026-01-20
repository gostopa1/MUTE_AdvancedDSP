/*
 ==============================================================================
 
 MuteRandomSignal.h
 Created: 15 Mar 2021 12:11:37am
 Author:  Athanasios Gotsopoulos
 
 ==============================================================================
 */

#pragma once
#include <JuceHeader.h>

class MuteRandomSignal
{
public:
    float volume=1.0;
    float minVal=-1;
    float maxVal=1;
    MuteRandomSignal()
    {
        srand(time(NULL));
    };
    ~MuteRandomSignal(){};
    void prepare(double sampleRate, int samplesPerBlock){};
    
    void setMin(float in)
    {
        minVal=in;
    };
    void setMax(float in)
    {
        maxVal=in;
    }

    void process(float * buffer, int numSamples)
    {
        for (int sample=0;sample<numSamples; ++sample)
        {
            float temp=((rand()/float(RAND_MAX))*(maxVal-minVal))+minVal;
            buffer[sample]=volume*temp;
        }
    }
    
private:
};
