#pragma once

#include "JuceHeader.h"
#include "ui/IconSliderComponent.h"

class ReverbComponent : public juce::GroupComponent
{
  public:
	ReverbComponent(juce::AudioProcessorValueTreeState &apvts, juce::String wetdryId, juce::String widthId,
					juce::String dampingId, juce::String roomSizeId, juce::String name);
	void resized() override;

  private:
	IconSliderComponent wetdrySlider;
	IconSliderComponent widthSlider;
	IconSliderComponent dampingSlider;
	IconSliderComponent roomSizeSlider;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ReverbComponent)
};
