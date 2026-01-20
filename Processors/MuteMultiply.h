/*
  ==============================================================================

    MuteMultiply.h
    Created: 15 Mar 2021 12:11:25am
    Author:  Athanasios Gotsopoulos

  ==============================================================================
*/

#pragma once
class MuteMultiply
{
public:
  
    MuteMultiply(){};
    ~MuteMultiply(){};
    void prepare(double sampleRate, int samplesPerBlock)
    {
    };
    void process(float * buffer1, float * buffer2, int numSamples)
    {
        for (int sample=0;sample<numSamples;++sample)
        {
            buffer1[sample]=buffer1[sample]*buffer2[sample];
        }

    };
private:
    
};
