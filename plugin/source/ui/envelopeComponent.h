#pragma once

#include "JuceHeader.h"
#include "ui/LabeledSlider.h"

class EnvelopeComponent : public juce::GroupComponent
{
  public:
	EnvelopeComponent(juce::AudioProcessorValueTreeState &apvts);
	~EnvelopeComponent() override;

	void resized() override;

  private:
	LabeledSlider attackSlider;
	LabeledSlider decaySlider;
	LabeledSlider sustainSlider;
	LabeledSlider releaseSlider;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EnvelopeComponent)
};
