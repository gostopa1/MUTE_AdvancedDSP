#pragma once

#include <JuceHeader.h>
class MuteTanh
{
public:
    float gain = 10;
    float volume = 0.1;
    float bias = 0.0;
    
    MuteTanh(){};
    ~MuteTanh(){};
    
    float getGain(){return gain;};
    void setGain(float newGain){gain=newGain;};
    
    float getVolume(){return volume;};
    void setVolume(float newVolume){volume=newVolume;};
    
    float getBias(){return bias;};
    void setBias(float newBias){bias=newBias;};
    
    void prepare(double sampleRate, int samplesPerBlock)
    {
    };
    void process(float * buffer, int numSamples)
    {
        for (int sample=0;sample<numSamples;++sample)
        {
            buffer[sample] = tanh(buffer[sample]*gain+bias)*volume;
        } 
    };
private:
    
};