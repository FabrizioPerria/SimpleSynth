#pragma once

#include "JuceHeader.h"
#include "ui/IconSliderComponent.h"
#include "ui/FilterPickerComponent.h"

class FilterComponent : public juce::Component
{
  public:
	FilterComponent(juce::AudioProcessorValueTreeState &apvts, juce::String filterId, juce::String cutoffId,
					juce::String resonanceId);
	void resized() override;

  private:
	FilterPickerComponent filterType;
	IconSliderComponent cutoff;
	IconSliderComponent resonance;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FilterComponent)
};
