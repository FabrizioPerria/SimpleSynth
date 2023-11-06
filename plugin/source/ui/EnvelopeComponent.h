#pragma once

#include "JuceHeader.h"
#include "ui/IconSliderComponent.h"
#include "ui/LabeledSliderComponent.h"

class EnvelopeComponent : public juce::GroupComponent
{
  public:
	EnvelopeComponent(juce::AudioProcessorValueTreeState &apvts, juce::String attackId, juce::String decayId,
					  juce::String sustainId, juce::String releaseId, juce::String name);
	~EnvelopeComponent() override;

	void resized() override;

  private:
	IconSliderComponent attackSlider;
	IconSliderComponent decaySlider;
	IconSliderComponent sustainSlider;
	IconSliderComponent releaseSlider;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EnvelopeComponent)
};
