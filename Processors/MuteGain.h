#pragma once

#include <JuceHeader.h>
class MuteGain
{
public:
    float gain = 1;
    MuteGain(){};
    ~MuteGain(){};
    
    float getGain(){return gain;};
    void setGain(float newGain){gain=newGain;};
    
    void prepare(double sampleRate, int samplesPerBlock)
    {
    };
    void process(float * buffer, int numSamples)
    {
        for (int sample=0;sample<numSamples;++sample)
        {
            buffer[sample] = buffer[sample]*gain;
        } 
    };
private:
    
};
