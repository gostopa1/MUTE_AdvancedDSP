#pragma once

#include <vector>
#include <cmath>
#include <algorithm>

class LinkwitzRiley
{
public:
    LinkwitzRiley() = default;
    ~LinkwitzRiley() = default;

    void prepare(double sampleRate, int samplesPerBlock)
    {
        sr = (sampleRate > 0.0) ? sampleRate : 48000.0;
        maxBlock = std::max(1, samplesPerBlock);

        lowBuffer.assign((size_t)maxBlock, 0.0f);
        highBuffer.assign((size_t)maxBlock, 0.0f);

        reset();

        // Ensure coefficients exist even if user forgets to call setCutoff().
        setCutoff(cutoffHz);
    }

    // Set Linkwitz-Riley 4th order crossover frequency (Hz).
    void setCutoff(double hz)
    {
        cutoffHz = std::clamp(hz, 10.0, 0.499 * sr);

        // LR4 = cascade two identical 2nd-order Butterworth (Q = 1/sqrt(2))
        constexpr double Q = 0.7071067811865476; // 1/sqrt(2)
        lp1.setLowpass(sr, cutoffHz, Q);
        lp2.setLowpass(sr, cutoffHz, Q);
        hp1.setHighpass(sr, cutoffHz, Q);
        hp2.setHighpass(sr, cutoffHz, Q);
    }

    // Resets filter state.
    void reset()
    {
        lp1.reset(); lp2.reset();
        hp1.reset(); hp2.reset();
    }

    // Process mono buffer:
    // - Overwrites `buffer` with the LOW band
    // - Writes the HIGH band into an internal buffer accessible via getHighBuffer()
    void process(float* buffer, int numSamples)
    {
        if (!buffer || numSamples <= 0) return;

        if ((int)highBuffer.size() < numSamples)
            highBuffer.resize((size_t)numSamples);

        // (Optional) keep lowBuffer too (not required, but handy)
        if ((int)lowBuffer.size() < numSamples)
            lowBuffer.resize((size_t)numSamples);

        for (int i = 0; i < numSamples; ++i)
        {
            const float x = buffer[i];

            // Low band: LP -> LP
            float lo = lp1.process(x);
            lo = lp2.process(lo);

            // High band: HP -> HP
            float hi = hp1.process(x);
            hi = hp2.process(hi);

            lowBuffer[(size_t)i] = lo;
            highBuffer[(size_t)i] = hi;

            buffer[i] = lo; // in-place low output
        }
    }

    // High band output after process()
    float* getHighBuffer() { return highBuffer.data(); }
    // Low band (same as buffer output), provided for convenience
    float* getLowBuffer() { return lowBuffer.data(); }

private:
    struct Biquad
    {
        // Coefficients (Direct Form I/II normalized with a0=1)
        double b0 = 1.0, b1 = 0.0, b2 = 0.0;
        double a1 = 0.0, a2 = 0.0;

        // State (Direct Form II Transposed)
        double z1 = 0.0, z2 = 0.0;

        void reset() { z1 = z2 = 0.0; }

        float process(float x)
        {
            const double y = b0 * x + z1;
            z1 = b1 * x - a1 * y + z2;
            z2 = b2 * x - a2 * y;
            return (float)y;
        }

        // RBJ cookbook 2nd-order lowpass
        void setLowpass(double sampleRate, double freqHz, double Q)
        {
            const double w0 = 2.0 * M_PI * (freqHz / sampleRate);
            const double cosw0 = std::cos(w0);
            const double sinw0 = std::sin(w0);
            const double alpha = sinw0 / (2.0 * Q);

            double B0 = (1.0 - cosw0) * 0.5;
            double B1 = (1.0 - cosw0);
            double B2 = (1.0 - cosw0) * 0.5;
            double A0 = 1.0 + alpha;
            double A1 = -2.0 * cosw0;
            double A2 = 1.0 - alpha;

            // Normalize (a0 = 1)
            b0 = B0 / A0;
            b1 = B1 / A0;
            b2 = B2 / A0;
            a1 = A1 / A0;
            a2 = A2 / A0;
        }

        // RBJ cookbook 2nd-order highpass
        void setHighpass(double sampleRate, double freqHz, double Q)
        {
            const double w0 = 2.0 * M_PI * (freqHz / sampleRate);
            const double cosw0 = std::cos(w0);
            const double sinw0 = std::sin(w0);
            const double alpha = sinw0 / (2.0 * Q);

            double B0 = (1.0 + cosw0) * 0.5;
            double B1 = -(1.0 + cosw0);
            double B2 = (1.0 + cosw0) * 0.5;
            double A0 = 1.0 + alpha;
            double A1 = -2.0 * cosw0;
            double A2 = 1.0 - alpha;

            // Normalize (a0 = 1)
            b0 = B0 / A0;
            b1 = B1 / A0;
            b2 = B2 / A0;
            a1 = A1 / A0;
            a2 = A2 / A0;
        }
    };

private:
    double sr = 48000.0;
    int maxBlock = 0;
    double cutoffHz = 1000.0;

    // Two cascaded biquads per band => LR4
    Biquad lp1, lp2;
    Biquad hp1, hp2;

    std::vector<float> lowBuffer;
    std::vector<float> highBuffer;
};