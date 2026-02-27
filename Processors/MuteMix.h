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
    void process_multiple(float * buffer1, float ** buffers, int numBuffers, int numSamples, bool include_input=true)
    {
        for (int sample=0;sample<numSamples;++sample)
        {
            if (!include_input)
            {
              buffer1[sample]=0.0f;
            }
            
            for (int i=0; i<numBuffers; ++i)
            {
                buffer1[sample] += buffers[i][sample];
            }
        }

    };
    void process_multiples(float ** buffers1, float ** buffers2, int numBuffers, int numSamples)
    {
        for (int sample=0;sample<numSamples;++sample)
        {
            for (int i=0; i<numBuffers; ++i)
            {
                buffers1[i][sample] += buffers2[i][sample];
            }
        }
    };
private:
    
};
