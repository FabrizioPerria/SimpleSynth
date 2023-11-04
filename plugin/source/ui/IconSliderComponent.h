#pragma once

#include "JuceHeader.h"
#include "utils/SVGData.h"

typedef juce::FlexBox::Direction IconSliderDirection;

class IconSliderComponent : public juce::Component
{
  public:
	IconSliderComponent(juce::AudioProcessorValueTreeState &apvts, const juce::String &parameterID, SVGData svg,
						IconSliderDirection direction = IconSliderDirection::row);

	void resized() override;
	void setSliderStyle(juce::Slider::SliderStyle style);

  private:
	juce::Slider slider;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment;
	juce::DrawableButton icon;
	IconSliderDirection direction;

	void updateTooltip();

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IconSliderComponent)
};
