#include "MuteSplit.h"
#include "MuteMix.h"
#include "SchroederAllpass.h"
#include "LP1.h"
#include "z_mod.h"
#include "MuteGain.h"

class Greisinger
{
public:
    SchroederAllpass ap1, ap2, ap3, ap4;
    
    SchroederAllpass apm1_1, apm2_1;
    SchroederAllpass ap1_1, ap2_1;
    MuteGain gain_1_1, gain_2_1;
    MuteGain output_gain;
    MuteGain empty_gain;
    z_mod d1_1, d2_1, d1_2, d2_2;
    z_mod do1, do2, do3, do4, do5, do6, do7;
    LP1 lp1, lp2;

    MuteSplit dry_split1; 
    MuteSplit s1, s2; 
    MuteSplit si1, si2; 
    MuteSplit ds1, ds2, ds3, ds4, ds5, ds6, ds7;
    MuteMix mix1, mix2;
    Greisinger(){}
    ~Greisinger(){}
    float * path1=nullptr;
    float * path2=nullptr;
    float * temp=nullptr;

    float * input1=nullptr;
    float * input2=nullptr;

    void prepare(double sampleRate, int samplesPerBlock)
    {
        float ap_gain=0.9;
        ap1.prepare(sampleRate, samplesPerBlock);
        ap1.setDelay(int(4.8*sampleRate/1000.0));
        ap1.setGain(ap_gain);
        ap2.prepare(sampleRate, samplesPerBlock);
        ap2.setDelay(int(3.6*sampleRate/1000.0));
        ap2.setGain(ap_gain);
        ap3.prepare(sampleRate, samplesPerBlock);
        ap3.setDelay(int(13.0*sampleRate/1000.0));
        ap3.setGain(ap_gain);
        ap4.prepare(sampleRate, samplesPerBlock);
        ap4.setDelay(int(9.3*sampleRate/1000.0));  
        ap4.setGain(ap_gain);

        apm1_1.prepare(sampleRate, samplesPerBlock);
        apm1_1.setDelay(int(31.0*sampleRate/1000.0));
        apm1_1.setGain(ap_gain);
        apm2_1.prepare(sampleRate, samplesPerBlock);
        apm2_1.setDelay(int(23.0*sampleRate/1000.0));
        apm2_1.setGain(ap_gain);
        ap1_1.prepare(sampleRate, samplesPerBlock);
        ap1_1.setDelay(int(89.0*sampleRate/1000.0));
        ap1_1.setGain(ap_gain);
        ap2_1.prepare(sampleRate, samplesPerBlock);
        ap2_1.setDelay(int(60.0*sampleRate/1000.0));
        ap2_1.setGain(ap_gain);
        
        d1_1.prepare(sampleRate, samplesPerBlock);
        d1_1.setDelaySamples(int(142.0*sampleRate/1000.0));
        d1_2.prepare(sampleRate, samplesPerBlock);
        d1_2.setDelaySamples(int(106.0*sampleRate/1000.0));
        
        d2_1.prepare(sampleRate, samplesPerBlock);
        d2_1.setDelaySamples(int(150.0*sampleRate/1000.0));
        d2_2.prepare(sampleRate, samplesPerBlock);
        d2_2.setDelaySamples(int(125.0*sampleRate/1000.0));

        lp1.prepare(sampleRate, samplesPerBlock);
        float cutoff = 6000;
        lp1.setCutoffHz(cutoff);
        lp2.prepare(sampleRate, samplesPerBlock);
        lp2.setCutoffHz(cutoff);
        float decay=1;
        gain_1_1.prepare(sampleRate, samplesPerBlock);
        gain_1_1.setGain(decay);
        gain_2_1.prepare(sampleRate, samplesPerBlock);
        gain_2_1.setGain(decay);

        do1.prepare(sampleRate, samplesPerBlock);
        do2.prepare(sampleRate, samplesPerBlock);
        do3.prepare(sampleRate, samplesPerBlock);
        do4.prepare(sampleRate, samplesPerBlock);
        do5.prepare(sampleRate, samplesPerBlock);
        do6.prepare(sampleRate, samplesPerBlock);
        do7.prepare(sampleRate, samplesPerBlock);
        do1.setDelaySamples(int(9.0*sampleRate/1000.0));
        do2.setDelaySamples(int(99.0*sampleRate/1000.0));
        do3.setDelaySamples(int(64.0*sampleRate/1000.0 ));
        do4.setDelaySamples(int(67.0*sampleRate/1000.0));
        do5.setDelaySamples(int(67.0*sampleRate/1000.0));
        do6.setDelaySamples(int(60.0*sampleRate/1000.0));
        do7.setDelaySamples(int(67.0*sampleRate/1000.0));
        
        dry_split1.prepare(sampleRate, samplesPerBlock);

        output_gain.prepare(sampleRate, samplesPerBlock);
        output_gain.setGain(0.05);
        empty_gain.prepare(sampleRate, samplesPerBlock);
        empty_gain.setGain(0.05);

        s1.prepare(sampleRate, samplesPerBlock);
        s2.prepare(sampleRate, samplesPerBlock);
        si1.prepare(sampleRate, samplesPerBlock);
        si2.prepare(sampleRate, samplesPerBlock);
        ds1.prepare(sampleRate, samplesPerBlock);
        ds2.prepare(sampleRate, samplesPerBlock);
        ds3.prepare(sampleRate, samplesPerBlock);
        ds4.prepare(sampleRate, samplesPerBlock);
        ds5.prepare(sampleRate, samplesPerBlock);
        ds6.prepare(sampleRate, samplesPerBlock);
        ds7.prepare(sampleRate, samplesPerBlock);
        mix1.prepare(sampleRate, samplesPerBlock);
        mix2.prepare(sampleRate, samplesPerBlock);

        path1 = s1.getPtr();
        path2 = s2.getPtr();
    }

    void process(float* buffer, int numSamples)
    {
        dry_split1.process(buffer,numSamples);
        ap1.process(buffer,numSamples);
        ap2.process(buffer,numSamples);
        ap3.process(buffer,numSamples);
        ap4.process(buffer,numSamples);

        si1.process(buffer,numSamples);
        si2.process(buffer,numSamples);
        
        input1 = si1.getPtr();
        input2 = si2.getPtr();

        mix1.process(path1, buffer, numSamples);
        apm1_1.process(path1,numSamples);
        d1_1.process(path1,numSamples);
        ds1.process(path1,numSamples);
        ds2.process(path1,numSamples);
        lp1.process(path1,numSamples);
        ap1_1.process(path1,numSamples);
        ds3.process(path1,numSamples);
        d1_2.process(path1,numSamples);
        ds4.process(path1,numSamples);
        gain_1_1.process(path1,numSamples);

        
        mix2.process(path2, buffer, numSamples);
        apm2_1.process(path2,numSamples);
        d2_1.process(path2,numSamples);
        ds5.process(path2,numSamples);
        lp2.process(path2,numSamples);
        ap2_1.process(path2,numSamples);
        ds6.process(path2,numSamples);
        d2_2.process(path2,numSamples);
        ds7.process(path2,numSamples);
        gain_2_1.process(path2,numSamples);

        temp=path1;
        path1=path2;
        path2=temp;
        
        do1.process(ds1.getPtr(),numSamples);
        do2.process(ds2.getPtr(),numSamples);
        do3.process(ds3.getPtr(),numSamples);
        do4.process(ds4.getPtr(),numSamples);
        do5.process(ds5.getPtr(),numSamples);
        do6.process(ds6.getPtr(),numSamples);
        do7.process(ds7.getPtr(),numSamples);
        
        empty_gain.process(buffer,numSamples);
        mix1.process(buffer, ds1.getPtr(), numSamples);
        mix1.process(buffer, ds2.getPtr(), numSamples);
        mix1.process(buffer, ds3.getPtr(), numSamples);
        mix1.process(buffer, ds4.getPtr(), numSamples);
        mix2.process(buffer, ds5.getPtr(), numSamples);
        mix2.process(buffer, ds6.getPtr(), numSamples);
        mix2.process(buffer, ds7.getPtr(), numSamples);
        output_gain.process(buffer,numSamples);
        mix1.process(buffer, dry_split1.getPtr(), numSamples);
    }
    void empty(float * buffer, int numSamples)
    {
        for (int sample=0;sample<numSamples;++sample)
        {
            buffer[sample] = 0.0f;
        }
    }
    void setDecay(float newDecay)
    {
        gain_1_1.setGain(newDecay);
        gain_2_1.setGain(newDecay);
    }
    
    void setLowpass(float newCutoff)
    {
        lp1.setCutoffHz(newCutoff);
        lp2.setCutoffHz(newCutoff);    
    }
private:
   
};
