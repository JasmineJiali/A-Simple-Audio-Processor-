/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef COMPRESSOR_H_INCLUDED
#define COMPRESSOR_H_INCLUDED

#include "../plugins.h"

#include "UParam.h"
#include "PeakLevelDetector.h"
#include "GainDynamics.h"

#define dB(x) 20.0 * ((x) > 0.00001 ? log10(x) : -5.0)
#define dB2mag(x) pow(10.0, (x) / 20.0)

//==============================================================================
/**
*/
class CompressorAudiorocessor  : public AudioProcessor
{
public:
    //==============================================================================
    CompressorAudiorocessor();
    ~CompressorAudiorocessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    int getNumParameters() override;
    float getParameter (int index) override;
    void setParameter (int index, float newValue) override;
    float getParameterDefaultValue (int index) override; // Not included in default Juce template

    const String getParameterName (int index) override;
    const String getParameterText (int index) override;

    const String getInputChannelName (int channelIndex) const override;
    const String getOutputChannelName (int channelIndex) const override;
    bool isInputChannelStereoPair (int index) const override;
    bool isOutputChannelStereoPair (int index) const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool silenceInProducesSilenceOut() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    enum Parameters {
        threshold,
        ratio,
        attack,
        release,
        totalNumParams
    };
    
    UParam userParams[totalNumParams];

    const float DEFAULT_THRESHOLD   = 0.f;
    const float DEFAULT_RATIO       = 1.f;
    const float DEFAULT_ATTACK      = 0.020f;    // seconds
    const float DEFAULT_RELEASE     = 0.500f;   // seconds
    
private:
    const float DEFAULT_VST_THRESHOLD   = 1.0f;
    const float DEFAULT_VST_RATIO       = 0.0f;
    const float DEFAULT_VST_ATTACK      = 0.2f;
    const float DEFAULT_VST_RELEASE     = 0.5f;
    
    float fs, thresholdDb, aRatio, attackTime, releaseTime;
    
    // Peak Level Detectors
    ScopedPointer<PeakLevelDetector> leftLevelDetector, rightLevelDetector;
    float peakOutL, peakOutR, peakSum, peakSumDb;
    
    // Gain Dynamics
    ScopedPointer<GainDynamics> gainDymanics;
    
    // Gains
    float gain, gainDb;
    
    void setThresh();
    void setRatio();
    void setAttack();
    void setRelease();
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompressorAudiorocessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
