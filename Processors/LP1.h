#pragma once
#include <cmath>
#include <algorithm>

class LP1
{
public:
    LP1() = default;
    ~LP1() = default;
    void prepare(double sampleRate, int /*samplesPerBlock*/)
    {
        fs = (sampleRate > 0.0) ? sampleRate : 44100.0;
        reset();
        updateCoeff();
    }

    // Set cutoff in Hz (call whenever cutoff changes)
    void setCutoffHz(float newCutoffHz)
    {
        cutoffHz = std::max(0.0f, newCutoffHz);
        updateCoeff();
    }

    void process(float* buffer, int numSamples)
    {
        if (!buffer || numSamples <= 0) return;

        // One-pole LPF (in-place)
        float y = z1;
        const float aLocal = a;

        for (int n = 0; n < numSamples; ++n)
        {
            const float x = buffer[n];
            y = y + aLocal * (x - y);
            buffer[n] = y;
        }

        z1 = y;
    }

    void reset(float value = 0.0f)
    {
        z1 = value;
    }

private:
    void updateCoeff()
    {
        // Clamp cutoff to [0, Nyquist]
        const float nyquist = 0.5f * static_cast<float>(fs);
        const float fc = std::min(cutoffHz, nyquist);

        if (fc <= 0.0f)
        {
            a = 0.0f; // output holds at z1
            return;
        }

        const float x = -2.0f * static_cast<float>(M_PI) * fc / static_cast<float>(fs);
        a = 1.0f - std::exp(x); // stable 0..1
    }

    double fs { 44100.0 };
    float cutoffHz { 1000.0f };
    float a { 0.0f };   // smoothing coefficient
    float z1 { 0.0f };  // filter state (previous output)
};