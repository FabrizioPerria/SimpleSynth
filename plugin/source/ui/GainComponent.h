#pragma once

#include "JuceHeader.h"

class GainComponent : public juce::GroupComponent
{
  public:
	GainComponent(juce::AudioProcessorValueTreeState &apvts, juce::String parameterId);
	~GainComponent() override;

	void resized() override;

  private:
	juce::Slider gainSlider;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainSliderAttachment;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GainComponent)
};
