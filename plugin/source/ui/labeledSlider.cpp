#include "ui/LabeledSlider.h"

LabeledSlider::LabeledSlider(juce::AudioProcessorValueTreeState &apvts, const juce::String &parameterID,
							 const juce::String &name)
{
	attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, parameterID, slider);
	label.setText(name, juce::dontSendNotification);
	label.setJustificationType(juce::Justification::centred);
	addAndMakeVisible(label);
	slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
	slider.setTextBoxStyle(juce::Slider::NoTextBox, true, 50, 20);
	addAndMakeVisible(slider);
}

void LabeledSlider::resized()
{
	juce::FlexBox fb;

	fb.flexDirection = slider.getSliderStyle() == Slider::SliderStyle::LinearVertical ? juce::FlexBox::Direction::column
																					  : juce::FlexBox::Direction::row;

	fb.items.add(juce::FlexItem(label).withFlex(0.1f));
	fb.items.add(juce::FlexItem(slider).withFlex(1.0f));

	fb.performLayout(getLocalBounds());
}

void LabeledSlider::setSliderOrientation(juce::Slider::SliderStyle style)
{
	slider.setSliderStyle(style);
}
