#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

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
	juce::ComboBox waveType;
	std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> waveTypeAttachment;

	juce::Slider attackSlider;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attackAttachment;
	juce::Slider decaySlider;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> decayAttachment;
	juce::Slider sustainSlider;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sustainAttachment;
	juce::Slider releaseSlider;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> releaseAttachment;

	juce::Slider gainSlider;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;

	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.
	AudioPluginAudioProcessor &processorRef;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPluginAudioProcessorEditor)
};
