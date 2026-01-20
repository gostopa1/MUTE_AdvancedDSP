/*
  ==============================================================================

    MuteDCFilter.h
    Created: 20 Apr 2022 10:27:11pm
    Author:  Athanasios Gotsopoulos

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
class MuteDCFilter
{
public:
    
    float tempOut = 0.0f;
    float prevIn = 0.0f;
    MuteDCFilter(){};
    ~MuteDCFilter(){};
    
    void prepare(double sampleRate, int samplesPerBlock)
    {
    };
    void process(float * buffer, int numSamples)
    {
        for (int sample=0;sample<numSamples;++sample)
        {
            // From Reaper DC filter
            // otm1=0.999*otm1 + spl0 - itm1; itm1=spl0; spl0=otm1;
            tempOut = 0.999*tempOut + buffer[sample] - prevIn;
            prevIn = buffer[sample];
            buffer[sample] = tempOut;
        } 
    };
private:
    
};
