#pragma once
#include "LinkwitzRiley.h"
#include "MuteMix.h"
#include "MuteTanh.h"
#include "MuteGain.h"
class MultibandDistortion

/*

// Example of a multiband processors. It splits the signal into three bands (<100Hz, 100Hz-10kHz, >10kHz) 
// and applies different processing to each band before recombining them.
// The processing is just an example and can be changed to anything else (e.g. different distortion types, filters, etc.). 
// Note that the gain of the middle band is set to 0 (i.e. it is muted) just to show how you can have different processing in each band, 
// but you can change that as well.

input
  |
buffer
  |   
crossover (lr1) ------------------------------------
  |                                                 |       
  |                                                 |       
buffer <10khz                               high_buffer1 >10kHz
  |                                                 |
crossover (lr2) -------------                       |
  |                          |                      |                 
  |                  high_buffer2 >100Hz (<10kHz)   |                 
distortion (dist1)           |                  gain = 0 (i.e. mute)
  |                          |                      |                 
  |                          |                      |
mix1--------------------------                      |
  |                                                 |
  |                                                 |
mix2-------------------------------------------------
  |
buffer
  |
output

*/

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
        dist1.setGain(300.0); // Set the gain of the distortion to 300 (very high!)
        gain1.prepare(sampleRate, samplesPerBlock);
        gain1.setGain(0.0f); // Setting the gain of the gain processor to 0 (i.e. muting it)
        gain2.prepare(sampleRate, samplesPerBlock);
        lr1.prepare(sampleRate, samplesPerBlock);
        lr2.prepare(sampleRate, samplesPerBlock);
        lr1.setCutoff(10000.0); // Setting the crossover frequency of lr1 to 10k
        lr2.setCutoff(100.0);// Setting the crossover frequency of lr2 to 100 Hz
        high_buffer1 = lr1.getHighBuffer(); // Get pointer to the >10kHz band buffer
        high_buffer2 = lr2.getHighBuffer(); // Get pointer to the 100Hz-10kHz band buffer
        mix1.prepare(sampleRate, samplesPerBlock);
        mix2.prepare(sampleRate, samplesPerBlock);
    }
    void process(float * buffer, int numSamples)
    {
        lr1.process(buffer,numSamples); // Split the buffer into <10k and >10k (the latter is in high_buffer1)
        lr2.process(buffer,numSamples); // Split the <10k buffer into <100Hz (in buffer) and 100Hz-10k (in high_buffer2)
        
        dist1.process(buffer,numSamples); // Distort the buffer (it now contains anything <100Hz)
        
        gain1.process(high_buffer1,numSamples); // Set gain to the >10k content

        mix1.process(buffer, high_buffer2, numSamples);
        mix2.process(buffer, high_buffer1, numSamples);
    }
    
private:
};
