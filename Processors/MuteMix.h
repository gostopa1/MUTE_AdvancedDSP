/*
  ==============================================================================

    MuteMultiply.h
    Created: 15 Mar 2021 12:11:25am
    Author:  Athanasios Gotsopoulos

  ==============================================================================
*/

#pragma once
class MuteMix
{
public:
  
    MuteMix(){};
    ~MuteMix(){};
    void prepare(double sampleRate, int samplesPerBlock)
    {
    };
    void process(float * buffer1, float * buffer2, int numSamples)
    {
        for (int sample=0;sample<numSamples;++sample)
        {
            buffer1[sample]=buffer1[sample]+buffer2[sample];
        }

    };
private:
    
};
