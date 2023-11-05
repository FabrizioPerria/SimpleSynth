#pragma once

#include "JuceHeader.h"
#include "ui/IconSliderComponent.h"
#include "ui/FilterPickerComponent.h"
#include "ui/EnvelopeComponent.h"

class FilterComponent : public juce::GroupComponent
{
  public:
	FilterComponent(juce::AudioProcessorValueTreeState &apvts, juce::String filterId, juce::String cutoffId,
					juce::String resonanceId, juce::String name);
	void resized() override;

  private:
	FilterPickerComponent filterType;
	IconSliderComponent cutoff;
	IconSliderComponent resonance;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FilterComponent)
};
