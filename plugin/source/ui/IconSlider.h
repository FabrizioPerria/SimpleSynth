#pragma once

#include "JuceHeader.h"
#include "utils/SVGData.h"

// class HighlightedSlider : public juce::Slider
// {
//   public:
// 	void paint(juce::Graphics &g) override
// 	{
// 		g.fillAll(juce::Colours::yellow.withAlpha(0.5f)); // fill with semi-transparent yellow
// 		juce::Slider::paint(g);							  // call the base class paint method
// 	}
// };

// class HighlightedImage : public juce::DrawableButton
// {
//   public:
// 	HighlightedImage(juce::String name, juce::DrawableButton::ButtonStyle style) : juce::DrawableButton(name, style)
// 	{
// 	}

// 	void paint(juce::Graphics &g) override
// 	{
// 		g.fillAll(juce::Colours::blue.withAlpha(0.5f)); // fill with semi-transparent yellow
// 		juce::DrawableButton::paint(g);
// 	}
// };

class IconSlider : public juce::Component
{
  public:
	IconSlider(juce::AudioProcessorValueTreeState &apvts, const juce::String &parameterID, SVGData svg);

	void resized() override;
	void setSliderStyle(juce::Slider::SliderStyle style);

  private:
	juce::Slider slider;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment;
	juce::DrawableButton icon;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IconSlider)
};
