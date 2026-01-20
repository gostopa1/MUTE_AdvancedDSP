#pragma once

#include <JuceHeader.h>
class MuteCubicSoftClipper
{
public:
    float gain = 10;
    float volume = 0.1;
    float bias = 0.0;
    
    MuteCubicSoftClipper(){};
    ~MuteCubicSoftClipper(){};
    
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
        float xbias = 0;
        for (int sample=0;sample<numSamples;++sample)
        {
            xbias = gain*buffer[sample] + bias;
            if (xbias<=-1)
            {
                buffer[sample] = -2.0/3.0;
            }
            else if (xbias>=1)
            {
                buffer[sample] = 2.0/3.0;
            }
            else
            {
                buffer[sample] = xbias - (xbias*xbias*xbias)/3.0;
            }
        } 
    };
private:
    
};