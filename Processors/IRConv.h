#pragma once
#include <JuceHeader.h>

class IRConv
{
public:
    IRConv() = default;
    ~IRConv() = default;

    void prepare (double sampleRate, int samplesPerBlock)
    {
        juce::dsp::ProcessSpec spec;
        spec.sampleRate       = sampleRate;
        spec.maximumBlockSize = (juce::uint32) samplesPerBlock;
        spec.numChannels      = 1; // mono

        convolution.reset();
        convolution.prepare (spec);

        prepared = true;
    }

    void reset()
    {
        convolution.reset();
    }

    // Do NOT call on audio thread (file I/O).
    bool loadIRFromWavFile (const juce::File& file,
                            bool normalise = true,
                            bool trim = true,
                            size_t expectedSize = 0) // 0 = keep original length
    {
        if (! file.existsAsFile())
            return false;

        convolution.loadImpulseResponse (file,
                                         juce::dsp::Convolution::Stereo::no,
                                         trim ? juce::dsp::Convolution::Trim::yes
                                              : juce::dsp::Convolution::Trim::no,
                                         expectedSize,
                                         normalise ? juce::dsp::Convolution::Normalise::yes
                                                   : juce::dsp::Convolution::Normalise::no);

        irLoaded = true;
        return true;
    }

    // Convenience overload so you can pass "C:/.../ir.wav" directly
    bool loadIRFromWavFile (const juce::String& fullPath,
                            bool normalise = true,
                            bool trim = true,
                            size_t expectedSize = 0)
    {
        return loadIRFromWavFile (juce::File { fullPath }, normalise, trim, expectedSize);
    }

    void process (float* buffer, int numSamples)
    {
        if (! prepared || ! irLoaded || buffer == nullptr || numSamples <= 0)
            return;

        float* channels[1] = { buffer };
        juce::dsp::AudioBlock<float> block (channels, 1, (size_t) numSamples);
        juce::dsp::ProcessContextReplacing<float> ctx (block);
        convolution.process (ctx);
    }

private:
    juce::dsp::Convolution convolution;
    bool prepared = false;
    bool irLoaded = false;
};
