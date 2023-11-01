#pragma once

#include "JuceHeader.h"

class LabeledSlider : public juce::Component
{
  public:
	LabeledSlider(juce::AudioProcessorValueTreeState &apvts, const juce::String &parameterID, const juce::String &name);

	void resized() override;

  private:
	juce::Slider slider;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment;
	juce::Label label;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LabeledSlider)
};