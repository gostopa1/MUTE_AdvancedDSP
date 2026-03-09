#pragma once
#include "LinkwitzRiley.h"
#include "MuteMix.h"
#include "MuteTanh.h"
#include "MuteGain.h"
class MultibandDistortion
{
public:
    LinkwitzRiley lr1, lr2;
    MuteMix mix1, mix2;
    MuteTanh dist1, dist2;
    MuteGain gain1, gain2;
    MultibandDistortion(){};
    ~MultibandDistortion(){};
    
    float * low_buffer1=nullptr;
    float * high_buffer1=nullptr;
    float * low_buffer2=nullptr;
    float * high_buffer2=nullptr;

    void prepare(double sampleRate, int samplesPerBlock)
    {
        dist1.prepare(sampleRate, samplesPerBlock);
        dist2.prepare(sampleRate, samplesPerBlock);

        gain1.prepare(sampleRate, samplesPerBlock);
        gain1.setGain(0.0f);
        gain2.prepare(sampleRate, samplesPerBlock);
        lr1.prepare(sampleRate, samplesPerBlock);
        lr2.prepare(sampleRate, samplesPerBlock);
        lr1.setCutoff(10000.0);
        lr2.setCutoff(100.0);
        high_buffer1 = lr1.getHighBuffer();
        high_buffer2 = lr2.getHighBuffer();
        mix1.prepare(sampleRate, samplesPerBlock);
        mix2.prepare(sampleRate, samplesPerBlock);
        

    }
    void process(float * buffer, int numSamples)
    {
        lr1.process(buffer,numSamples);
        lr2.process(buffer,numSamples);
        dist1.process(buffer,numSamples);
        
        gain1.process(high_buffer1,numSamples);

        mix1.process(buffer, high_buffer1, numSamples);
        mix2.process(buffer, high_buffer2, numSamples);

    }
    
private:
};
