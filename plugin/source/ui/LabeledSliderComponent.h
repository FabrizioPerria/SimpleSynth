#pragma once

#include "JuceHeader.h"

class LabeledSliderComponent : public juce::Component
{
  public:
	LabeledSliderComponent(juce::AudioProcessorValueTreeState &apvts, const juce::String &parameterID, const juce::String &name);

	void resized() override;
	void setSliderStyle(juce::Slider::SliderStyle style);

  private:
	juce::Slider slider;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment;
	juce::Label label;

	void updateTooltip();

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LabeledSliderComponent)
};
