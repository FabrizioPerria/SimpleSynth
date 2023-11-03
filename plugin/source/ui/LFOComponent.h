#pragma once

#include "JuceHeader.h"
#include "ui/IconSliderComponent.h"

class LFOComponent : public juce::Component
{
  public:
	LFOComponent(juce::AudioProcessorValueTreeState &apvts, juce::String frequencyId, juce::String depthId);
	void resized() override;

  private:
	IconSliderComponent frequency;
	IconSliderComponent depth;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LFOComponent)
};
