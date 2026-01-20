/*
  ==============================================================================

    MuteDistortion.h
    Created: 23 May 2022 5:10:13pm
    Author:  Athanasios Gotsopoulos

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
class MuteDistortion
{
public:

    float gain = 10;
    float volume = 0.1;
    float bias = 0.0;
    
    int  mode = 1;
    
    MuteDistortion(){};
    ~MuteDistortion(){};
    
    void setTanh(){mode=1;}
    void setSoftClip(){mode=2;};
    void setHardClip(){mode=3;};
    
    int getMode(){return mode;};
    
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
            if (mode == 1)
            {
                buffer[sample] = tanh(buffer[sample]*gain+bias)*volume;
            }
            else if (mode==2)
            {
                float x = buffer[sample]*gain+bias;
                float out = (x/abs(x))*(1-exp(-(x*x)/abs(x)));
                buffer[sample] = out*volume;
            }
            else if (mode==3)
            {
                float out = buffer[sample]*gain+bias;
                if (out>1)
                {
                    out=1;
                }
                if (out<-1)
                {
                    out = -1;
                }
                buffer[sample] = out*volume;
            }
        } 
    };
private:
    
};
