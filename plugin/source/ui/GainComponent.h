#pragma once

#include "JuceHeader.h"
#include "ui/IconSliderComponent.h"

class GainComponent : public juce::GroupComponent
{
  public:
	GainComponent(juce::AudioProcessorValueTreeState &apvts, juce::String parameterId);
	~GainComponent() override;

	void resized() override;

  private:
	IconSliderComponent gainSlider;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GainComponent)
};
