#pragma once

#include <JuceHeader.h>
#include "SynthVoice.h"
#include "data/EnvelopeData.h"
#include "data/FilterData.h"
#include "data/GainData.h"
#include "data/ReverbData.h"

//==============================================================================
class AudioPluginAudioProcessor : public juce::AudioProcessor
{
  public:
	//==============================================================================
	AudioPluginAudioProcessor();
	~AudioPluginAudioProcessor() override;

	//==============================================================================
	void prepareToPlay(double sampleRate, int samplesPerBlock) override;
	void releaseResources() override;

	bool isBusesLayoutSupported(const BusesLayout &layouts) const override;

	void processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &) override;
	using AudioProcessor::processBlock;

	//==============================================================================
	juce::AudioProcessorEditor *createEditor() override;
	bool hasEditor() const override;

	//==============================================================================
	const juce::String getName() const override;

	bool acceptsMidi() const override;
	bool producesMidi() const override;
	bool isMidiEffect() const override;
	double getTailLengthSeconds() const override;

	//==============================================================================
	int getNumPrograms() override;
	int getCurrentProgram() override;
	void setCurrentProgram(int index) override;
	const juce::String getProgramName(int index) override;
	void changeProgramName(int index, const juce::String &newName) override;

	//==============================================================================
	void getStateInformation(juce::MemoryBlock &destData) override;
	void setStateInformation(const void *data, int sizeInBytes) override;

	juce::AudioProcessorValueTreeState::ParameterLayout createParams();

	juce::AudioProcessorValueTreeState &getApvts();

  private:
	juce::Synthesiser synth;
	ReverbData reverb;
	GainData outputGain;
	juce::AudioProcessorValueTreeState apvts;

	void setupOscillator(SynthVoice *voice, const int voiceIndex);
	void setupEnvelope(SynthVoice *voice);
	void setupFilter(SynthVoice *voice);
	void setupModEnvelope(SynthVoice *voice);
	void setupReverb();
	void setupOutputGain();

	void setupOscillatorVoiceParameters(juce::AudioProcessorValueTreeState::ParameterLayout &paramLayout);
	void setupAmpEnvelopeParameters(juce::AudioProcessorValueTreeState::ParameterLayout &paramLayout);
	void setupFilterParameters(juce::AudioProcessorValueTreeState::ParameterLayout &paramLayout);
	void setupModEnvelopeParameters(juce::AudioProcessorValueTreeState::ParameterLayout &paramLayout);
	void setupReverbParameters(juce::AudioProcessorValueTreeState::ParameterLayout &paramLayout);
	void setupOutputGainParameters(juce::AudioProcessorValueTreeState::ParameterLayout &paramLayout);

	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPluginAudioProcessor)
};
