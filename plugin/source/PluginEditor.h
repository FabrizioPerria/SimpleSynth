#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "ui/EnvelopeComponent.h"
#include "ui/OscillatorComponent.h"
#include "ui/GainComponent.h"
#include "ui/FilterComponent.h"
#include "ui/ReverbComponent.h"

//==============================================================================
class AudioPluginAudioProcessorEditor : public juce::AudioProcessorEditor
{
  public:
	explicit AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor &);
	~AudioPluginAudioProcessorEditor() override;

	//==============================================================================
	void paint(juce::Graphics &) override;
	void resized() override;

  private:
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.
	AudioPluginAudioProcessor &processorRef;

	OscillatorComponent oscillator0;
	OscillatorComponent oscillator1;
	OscillatorComponent oscillator2;
	EnvelopeComponent ampEnvelopeComponent;
	FilterComponent filterComponent;
	EnvelopeComponent modEnvelopeComponent;
	ReverbComponent reverbComponent;
	GainComponent gainComponent;

	std::unique_ptr<juce::TooltipWindow> tooltipWindow;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPluginAudioProcessorEditor)
};
