/*
  ==============================================================================

    MuteSplit.h
    Created: 15 Mar 2021 12:11:17am
    Author:  Athanasios Gotsopoulos

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class MuteSplit
{
    public:
    std::vector<float> bufferCopy;
    float * bufferPtr = nullptr;

    MuteSplit(){};
    ~MuteSplit(){};
    void prepare(double sampleRate, int samplesPerBlock)
    {
        bufferCopy.resize(sampleRate, samplesPerBlock);
    };
    void process(float * buffer, int numSamples)
    {
        memcpy(&bufferCopy[0], buffer, sizeof(float)*numSamples);
    };
    float * getPtr()
    {   bufferPtr = &bufferCopy[0];
        return bufferPtr;
    }
private:
    
};

