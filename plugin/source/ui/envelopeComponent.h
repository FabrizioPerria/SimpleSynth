#pragma once

#include "JuceHeader.h"
#include "ui/LabeledSliderComponent.h"

class EnvelopeComponent : public juce::GroupComponent
{
  public:
	EnvelopeComponent(juce::AudioProcessorValueTreeState &apvts, juce::String attackId, juce::String decayId,
					  juce::String sustainId, juce::String releaseId, juce::String name);
	~EnvelopeComponent() override;

	void resized() override;

  private:
	LabeledSliderComponent attackSlider;
	LabeledSliderComponent decaySlider;
	LabeledSliderComponent sustainSlider;
	LabeledSliderComponent releaseSlider;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EnvelopeComponent)
};
