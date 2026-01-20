/*
  ==============================================================================

    MuteMultiply.h
    Created: 15 Mar 2021 12:11:25am
    Author:  Athanasios Gotsopoulos

  ==============================================================================
*/

#pragma once
class MuteAdd
{
public:
  
    float amount = 1.0f;
    MuteAdd(){};
    ~MuteAdd(){};
    
    void setAmount(float newAmount){amount = newAmount;};
    float getAmount(){return amount;};
    
    void prepare(double sampleRate, int samplesPerBlock)
    {
    };
    void process(float * buffer1, int numSamples)
    {
        for (int sample=0;sample<numSamples;++sample)
        {
            buffer1[sample]=buffer1[sample]+amount;
        }

    };
private:
    
};
