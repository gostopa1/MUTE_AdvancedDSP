#include "MuteSplit.h"
#include "MuteMix.h"
#include "SchroederAllpass.h"
#include "LP1.h"
//#include "z.h"
#include "z_mod.h"
#include "MuteGain.h"

class UrsaMajorSpaceStation
{
public:
    
    z_mod z1,z2,z3,z4,z5,z6,z7,z8,z9,z10,z11,z12,z13,z14,z15,z16;
    z_mod do1, do2, do3, do4;

    LP1 lp1;
    MuteSplit s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15, s16;
    MuteSplit out1, out2, out3, out4;
    MuteSplit feedback, dry_split;
    MuteMix mix1, mix_out, mix_feedback, mix_dry;
    MuteGain gain_feedback;

    float early_reflections=0.7;
    UrsaMajorSpaceStation(){}
    ~UrsaMajorSpaceStation(){}
    float * path1=nullptr;
    float * path2=nullptr;
    float * path3=nullptr;
    float * path4=nullptr;
    float * path5=nullptr;
    float * path6=nullptr;
    float * path7=nullptr;
    float * path8=nullptr;
    float * path9=nullptr;
    float * path10=nullptr;
    float * path11=nullptr;
    float * path12=nullptr;
    float * path13=nullptr;
    float * path14=nullptr;
    float * path15=nullptr;
    float * path16=nullptr;

    float * out_path1=nullptr;
    float * out_path2=nullptr;
    float * out_path3=nullptr;
    float * out_path4=nullptr;

    float * temp=nullptr;

    float * input1=nullptr;
    float * input2=nullptr;
    float * feedback_path=nullptr;
    float * dry_path=nullptr;

    void prepare(double sampleRate, int samplesPerBlock)
    {
        dry_split.prepare(sampleRate, samplesPerBlock);
        dry_path = dry_split.getPtr();

        float multiplier=1.0;
        sampleRate=sampleRate*multiplier;
        z1.prepare(sampleRate, samplesPerBlock);
        z1.setDelaySamples(int(47.0*sampleRate/1000.0));
        z2.prepare(sampleRate, samplesPerBlock);
        z2.setDelaySamples(int(158.0*sampleRate/1000.0));
        z3.prepare(sampleRate, samplesPerBlock);
        z3.setDelaySamples(int(200.0*sampleRate/1000.0));
        z4.prepare(sampleRate, samplesPerBlock);
        z4.setDelaySamples(int(233.0*sampleRate/1000.0));
        z5.prepare(sampleRate, samplesPerBlock);
        z5.setDelaySamples(int(120.0*sampleRate/1000.0));
        z6.prepare(sampleRate, samplesPerBlock);
        z6.setDelaySamples(int(169.0*sampleRate/1000.0));
        z7.prepare(sampleRate, samplesPerBlock);
        z7.setDelaySamples(int(209.0*sampleRate/1000.0));
        z8.prepare(sampleRate, samplesPerBlock);
        z8.setDelaySamples(int(240.0*sampleRate/1000.0));
        z9.prepare(sampleRate, samplesPerBlock);
        z9.setDelaySamples(int(134.0*sampleRate/1000.0));
        z10.prepare(sampleRate, samplesPerBlock);
        z10.setDelaySamples(int(180.0*sampleRate/1000.0));
        z11.prepare(sampleRate, samplesPerBlock);   
        z11.setDelaySamples(int(217.0*sampleRate/1000.0));    
        z12.prepare(sampleRate, samplesPerBlock);
        z12.setDelaySamples(int(244.0*sampleRate/1000.0));
        z13.prepare(sampleRate, samplesPerBlock);
        z13.setDelaySamples(int(146.0*sampleRate/1000.0));
        z14.prepare(sampleRate, samplesPerBlock);
        z14.setDelaySamples(int(190*sampleRate/1000.0));
        z15.prepare(sampleRate, samplesPerBlock);
        z15.setDelaySamples(int(225.0*sampleRate/1000.0));
        z16.prepare(sampleRate, samplesPerBlock);
        z16.setDelaySamples(int(247.0*sampleRate/1000.0));
        
        do1.prepare(sampleRate, samplesPerBlock);
        do1.setDelaySamples(int(early_reflections*175.0*sampleRate/1000.0));
        do2.prepare(sampleRate, samplesPerBlock);
        do2.setDelaySamples(int(early_reflections*60.0*sampleRate/1000.0));
        do3.prepare(sampleRate, samplesPerBlock);
        do3.setDelaySamples(int(early_reflections*90.0*sampleRate/1000.0));
        do4.prepare(sampleRate, samplesPerBlock);
        do4.setDelaySamples(int(early_reflections*137.0*sampleRate/1000.0));
        
        lp1.prepare(sampleRate, samplesPerBlock);
        lp1.setCutoffHz(6000.0f);

        s1.prepare(sampleRate, samplesPerBlock);
        s2.prepare(sampleRate, samplesPerBlock);
        s3.prepare(sampleRate, samplesPerBlock);
        s4.prepare(sampleRate, samplesPerBlock);
        s5.prepare(sampleRate, samplesPerBlock);
        s6.prepare(sampleRate, samplesPerBlock);
        s7.prepare(sampleRate, samplesPerBlock);
        s8.prepare(sampleRate, samplesPerBlock);
        s9.prepare(sampleRate, samplesPerBlock);
        s10.prepare(sampleRate, samplesPerBlock);
        s11.prepare(sampleRate, samplesPerBlock);
        s12.prepare(sampleRate, samplesPerBlock);
        s13.prepare(sampleRate, samplesPerBlock);
        s14.prepare(sampleRate, samplesPerBlock);
        s15.prepare(sampleRate, samplesPerBlock);
        s16.prepare(sampleRate, samplesPerBlock);
        path1 = s1.getPtr();
        path2 = s2.getPtr();
        path3 = s3.getPtr();
        path4 = s4.getPtr();
        path5 = s5.getPtr();
        path6 = s6.getPtr();
        path7 = s7.getPtr();
        path8 = s8.getPtr();
        path9 = s9.getPtr();
        path10 = s10.getPtr();
        path11 = s11.getPtr();
        path12 = s12.getPtr();
        path13 = s13.getPtr();
        path14 = s14.getPtr();
        path15 = s15.getPtr();
        path16 = s16.getPtr();

        feedback.prepare(sampleRate, samplesPerBlock);
        feedback_path = feedback.getPtr();

        out1.prepare(sampleRate, samplesPerBlock);
        out2.prepare(sampleRate, samplesPerBlock);
        out3.prepare(sampleRate, samplesPerBlock);
        out4.prepare(sampleRate, samplesPerBlock);
        out_path1 = out1.getPtr();
        out_path2 = out2.getPtr();
        out_path3 = out3.getPtr();
        out_path4 = out4.getPtr();

        mix1.prepare(sampleRate, samplesPerBlock);
        mix_out.prepare(sampleRate, samplesPerBlock);
        mix_feedback.prepare(sampleRate, samplesPerBlock);
        gain_feedback.prepare(sampleRate, samplesPerBlock);
        gain_feedback.setGain(0.7/16.0);
        sampleRate=sampleRate/multiplier; // compensate for initial oversampling

    }

    void process(float* buffer, int numSamples)
    {   
        dry_split.process(buffer,numSamples);
        
        mix1.process(buffer, feedback_path,numSamples);

        s1.process(buffer,numSamples);
        s2.process(buffer,numSamples);
        s3.process(buffer,numSamples);
        s4.process(buffer,numSamples);
        s5.process(buffer,numSamples);
        s6.process(buffer,numSamples);
        s7.process(buffer,numSamples);
        s8.process(buffer,numSamples);
        s9.process(buffer,numSamples);
        s10.process(buffer,numSamples);
        s11.process(buffer,numSamples);
        s12.process(buffer,numSamples);
        s13.process(buffer,numSamples);
        s14.process(buffer,numSamples);
        s15.process(buffer,numSamples);
        s16.process(buffer,numSamples);

        z1.process(path1,numSamples);
        z2.process(path2,numSamples);
        z3.process(path3,numSamples);
        z4.process(path4,numSamples);
        z5.process(path5,numSamples);
        z6.process(path6,numSamples);
        z7.process(path7,numSamples);
        z8.process(path8,numSamples);
        z9.process(path9,numSamples);
        z10.process(path10,numSamples);
        z11.process(path11,numSamples);
        z12.process(path12,numSamples);
        z13.process(path13,numSamples);
        z14.process(path14,numSamples);
        z15.process(path15,numSamples);
        z16.process(path16,numSamples);

        empty_buffer(feedback_path,numSamples);
        mix_feedback.process(feedback_path, path1, numSamples);
        mix_feedback.process(feedback_path, path2, numSamples);
        mix_feedback.process(feedback_path, path3, numSamples);
        mix_feedback.process(feedback_path, path4, numSamples);
        mix_feedback.process(feedback_path, path5, numSamples);
        mix_feedback.process(feedback_path, path6, numSamples);
        mix_feedback.process(feedback_path, path7, numSamples);
        mix_feedback.process(feedback_path, path8, numSamples);
        mix_feedback.process(feedback_path, path9, numSamples);
        mix_feedback.process(feedback_path, path10, numSamples);
        mix_feedback.process(feedback_path, path11, numSamples);
        mix_feedback.process(feedback_path, path12, numSamples);
        mix_feedback.process(feedback_path, path13, numSamples);
        mix_feedback.process(feedback_path, path14, numSamples);
        mix_feedback.process(feedback_path, path15, numSamples);
        mix_feedback.process(feedback_path, path16, numSamples);
        lp1.process(feedback_path,numSamples);
        gain_feedback.process(feedback_path,numSamples);
        
        out1.process(buffer,numSamples);
        out2.process(buffer,numSamples);
        out3.process(buffer,numSamples);
        out4.process(buffer,numSamples);
        do1.process(out_path1,numSamples);
        do2.process(out_path2,numSamples);
        do3.process(out_path3,numSamples);
        do4.process(out_path4,numSamples);

        empty_buffer(buffer,numSamples);
        mix_out.process(buffer, out_path1,numSamples);
        mix_out.process(buffer, out_path2,numSamples);
        mix_out.process(buffer, out_path3,numSamples);
        mix_out.process(buffer, out_path4,numSamples);
        //mix_dry.process(buffer, dry_path,numSamples);
        
    }

    void empty_buffer(float * buffer, int numSamples)
    {
        for (int i = 0; i < numSamples; i++)
        {
            buffer[i] = 0.0f;
        }
    }
    void setDecay(float newDecay)
    {
        gain_feedback.setGain(newDecay/8.0); // Because of the 16 parallel delay lines, we need to divide the decay by 16 to get the correct overall decay time for the reverb.
    }
    void setLowpass(float newCutoff)
    {
        lp1.setCutoffHz(newCutoff);
    }
private:
   
};
