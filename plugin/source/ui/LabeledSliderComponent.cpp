#include "ui/LabeledSliderComponent.h"

LabeledSliderComponent::LabeledSliderComponent(juce::AudioProcessorValueTreeState &apvts,
											   const juce::String &parameterID, const juce::String &name)
{
	attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, parameterID, slider);
	label.setText(name, juce::dontSendNotification);
	/* label.setFont(10.0f); */
	label.setJustificationType(juce::Justification::centred);
	addAndMakeVisible(label);
	setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
	slider.setTextBoxStyle(juce::Slider::NoTextBox, true, 50, 20);
	slider.onValueChange = [this]{ updateTooltip(); };
	addAndMakeVisible(slider);
	updateTooltip();
}

void LabeledSliderComponent::resized()
{
	juce::FlexBox fb;

	fb.flexDirection = slider.getSliderStyle() == Slider::SliderStyle::LinearHorizontal
						   ? juce::FlexBox::Direction::row
						   : juce::FlexBox::Direction::column;

	fb.items.add(juce::FlexItem(label).withFlex(0.1f));
	fb.items.add(juce::FlexItem(slider).withFlex(1.0f));

	fb.performLayout(getLocalBounds());
}

void LabeledSliderComponent::setSliderStyle(juce::Slider::SliderStyle style)
{
	slider.setSliderStyle(style);
}

void LabeledSliderComponent::updateTooltip()
{
	slider.setTooltip(std::to_string(( int ) slider.getValue()));
}