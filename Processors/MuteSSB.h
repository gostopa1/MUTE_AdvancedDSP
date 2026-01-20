/*

 Frequency shifting using Weaver technique:
 
http://www.cim.mcgill.ca/~clark/nordmodularbook/nm_spectrum_shift.html

*/


#pragma once

#include <JuceHeader.h>
#include "MuteSplit.h"
#include "MuteLowPass.h"
#include "MuteMultiply.h"
#include "MuteSine.h"
#include "MuteCosine.h"
#include "MuteMix.h"

class MuteSSB
{
public:
    
    float F1 = 440.0;
    float F2 = 880.0;
    float LPF = 440.0;
    MuteSplit MuteSplit1, MuteSplit2,MuteSplit3, MuteSplit4, MuteSplit5, MuteSplit6;
    MuteSine MuteSine1, MuteSine2;
    MuteCosine MuteCosine1, MuteCosine2;
    MuteLowPass MuteLowPass1, MuteLowPass2;
    MuteMultiply MuteMultiply1, MuteMultiply2, MuteMultiply3, MuteMultiply4;
    MuteMix MuteMix1;
    
    MuteSSB(){};
    ~MuteSSB(){};
    
    void setF1(float newF1)
    {
    F1=newF1;
    LPF=F1;
        MuteLowPass1.setFreq(LPF);
        MuteLowPass1.setFreq(LPF);
        
        MuteSine1.setFreq(F1);
        MuteCosine1.setFreq(F1);
    }
    
    void setF2(float newF2)
    {
        F2=newF2;
        MuteSine2.setFreq(F2);
        MuteCosine2.setFreq(F2);
    }
    
    float getF1(){return F1;};
    float getF2(){return F2;};
    
    void prepare(double sampleRate, int samplesPerBlock)
    {
        MuteSplit1.prepare(sampleRate, samplesPerBlock);
        MuteSplit2.prepare(sampleRate, samplesPerBlock);
        MuteSplit3.prepare(sampleRate, samplesPerBlock);
        MuteSplit4.prepare(sampleRate, samplesPerBlock);
        MuteSplit5.prepare(sampleRate, samplesPerBlock);
        MuteSplit6.prepare(sampleRate, samplesPerBlock);
        
        MuteSine1.prepare(sampleRate, samplesPerBlock);
        MuteSine2.prepare(sampleRate, samplesPerBlock);
        MuteCosine1.prepare(sampleRate, samplesPerBlock);
        MuteCosine2.prepare(sampleRate, samplesPerBlock);
        MuteMultiply1.prepare(sampleRate, samplesPerBlock);
        MuteMultiply2.prepare(sampleRate, samplesPerBlock);
        MuteMultiply3.prepare(sampleRate, samplesPerBlock);
        MuteMultiply4.prepare(sampleRate, samplesPerBlock);
        
        MuteLowPass1.prepare(sampleRate, samplesPerBlock);
        MuteLowPass2.prepare(sampleRate, samplesPerBlock);
        
        LPF=F1;
        MuteLowPass1.setFreq(LPF);
        MuteLowPass1.setFreq(LPF);
        
        MuteSine1.setFreq(F1);
        MuteCosine1.setFreq(F1);
        
        MuteSine2.setFreq(F2);
        MuteCosine2.setFreq(F2);
        
        
    };
    void process(float * buffer, int numSamples)
    {
        MuteSplit1.process(buffer,numSamples);
        float * buffers1 = MuteSplit1.getPtr();
        
        MuteSplit2.process(buffer,numSamples);
        float * bufferc1 = MuteSplit2.getPtr();
        
        MuteSplit3.process(buffer,numSamples);
        float * bufferUpper1 = MuteSplit3.getPtr();
        
        MuteSplit4.process(buffer,numSamples);
        float * bufferLower1 = MuteSplit4.getPtr();
        
        MuteSplit5.process(buffer,numSamples);
        float * buffers2 = MuteSplit5.getPtr();
        
        MuteSplit6.process(buffer,numSamples);
        float * bufferc2 = MuteSplit6.getPtr();
        
        MuteSine1.process(buffers1,numSamples);
        MuteCosine1.process(bufferc1,numSamples);
        
        MuteSine2.process(buffers2,numSamples);
        MuteCosine2.process(bufferc2,numSamples);
        
        MuteMultiply1.process(bufferUpper1,buffers1,numSamples);
        MuteMultiply2.process(bufferLower1,bufferc1,numSamples);
        
        MuteLowPass1.process(bufferUpper1,numSamples);
        MuteLowPass2.process(bufferLower1,numSamples);
        
        MuteMultiply3.process(bufferUpper1,buffers2,numSamples);
        MuteMultiply4.process(bufferLower1,bufferc2,numSamples);
        
        MuteMix1.process(bufferUpper1, bufferLower1, numSamples);
        
        //memcpy(buffer, bufferUpper1, sizeof(float)*numSamples);
        
        for (int sample=0;sample<numSamples;++sample)
        {
            //buffer[sample] = tanh(buffer[sample]*gain+bias)*volume;
            buffer[sample] = bufferUpper1[sample];
        }
        
    };
    
    void processWithMod(float * buffer, float * bufferMod, int numSamples)
    {
        MuteSplit1.process(buffer,numSamples);
        float * buffers1 = MuteSplit1.getPtr();
        
        MuteSplit2.process(buffer,numSamples);
        float * bufferc1 = MuteSplit2.getPtr();
        
        MuteSplit3.process(buffer,numSamples);
        float * bufferUpper1 = MuteSplit3.getPtr();
        
        MuteSplit4.process(buffer,numSamples);
        float * bufferLower1 = MuteSplit4.getPtr();
        
        MuteSplit5.process(buffer,numSamples);
        float * buffers2 = MuteSplit5.getPtr();
        
        MuteSplit6.process(buffer,numSamples);
        float * bufferc2 = MuteSplit6.getPtr();
        
        MuteSine1.processWithMod(buffers1,bufferMod,numSamples);
        MuteCosine1.processWithMod(bufferc1,bufferMod,numSamples);
        
        MuteSine2.process(buffers2,numSamples);
        MuteCosine2.process(bufferc2,numSamples);
        
        MuteMultiply1.process(bufferUpper1,buffers1,numSamples);
        MuteMultiply2.process(bufferLower1,bufferc1,numSamples);
        
        MuteLowPass1.processWithMod(bufferUpper1,bufferMod,numSamples);
        MuteLowPass2.processWithMod(bufferLower1,bufferMod,numSamples);
        
        MuteMultiply3.process(bufferUpper1,buffers2,numSamples);
        MuteMultiply4.process(bufferLower1,bufferc2,numSamples);
        
        MuteMix1.process(bufferUpper1, bufferLower1, numSamples);
        
        //memcpy(buffer, bufferUpper1, sizeof(float)*numSamples);
        
        for (int sample=0;sample<numSamples;++sample)
        {
            //buffer[sample] = tanh(buffer[sample]*gain+bias)*volume;
            buffer[sample] = bufferUpper1[sample];
        }
        
    };
private:
    
};
