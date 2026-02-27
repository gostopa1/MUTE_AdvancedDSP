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
    int N=1;
    
    // std::vector<float> bufferCopy;
    std::vector<std::vector<float>> bufferCopy;
    std::vector<float *> bufferCopyPtrs;
    // float * bufferPtr = nullptr;

    MuteSplit()
    {
        bufferCopy.resize(N);
        bufferCopyPtrs.resize(N);
    };
    MuteSplit(int newN)
    {
        N=newN;
        bufferCopy.resize(N);
        bufferCopyPtrs.resize(N);
    };
    ~MuteSplit(){};
    void prepare(double sampleRate, int samplesPerBlock)
    {
        for (int i=0; i<N; ++i)
        {
            bufferCopy[i].resize(samplesPerBlock, 0.0f);
        }
    };
    void process(float * buffer, int numSamples)
    {
        for (int i=0; i<N; ++i)
        {
            memcpy(&bufferCopy[i][0], buffer, sizeof(float)*numSamples);
        }
    };

    void process_multiples(float ** buffers1, float ** buffers2, int numBuffers, int numSamples)
    {
        for (int i=0; i<numBuffers; ++i)
        {
            memcpy(buffers1[i], buffers2[i], sizeof(float)*numSamples);
        }
    };

    float * getPtr(int index=0)
    {   
        bufferCopyPtrs[index] = &bufferCopy[index][0];
        return bufferCopyPtrs[index];
    }
    float ** getPtrs()
    {
        for (int i=0; i<N; ++i)
        {
            bufferCopyPtrs[i] = &bufferCopy[i][0];

        }
        
        return bufferCopyPtrs.data();
    }
private:
    
};

