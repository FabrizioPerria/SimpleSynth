#include "ui/IconSliderComponent.h"
#include "utils/SVGData.h"

IconSliderComponent::IconSliderComponent(juce::AudioProcessorValueTreeState &apvts, const juce::String &parameterID,
										 SVGData svg)
	: attachment(std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, parameterID, slider)),
	  icon("Icon", juce::DrawableButton::ButtonStyle::ImageFitted)
{
	setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
	slider.setTextBoxStyle(juce::Slider::NoTextBox, true, 50, 20);
	slider.onValueChange = [this]() { updateTooltip(); };
	addAndMakeVisible(slider);
	updateTooltip();

	std::unique_ptr<juce::Drawable> drawable(juce::Drawable::createFromImageData(svg.svg, svg.size));
	drawable->replaceColour(juce::Colours::black, juce::Colours::cyan);
	icon.setImages(drawable.get());
	icon.setClickingTogglesState(false);
	icon.setToggleState(false, juce::dontSendNotification);
	addAndMakeVisible(icon);
}

void IconSliderComponent::resized()
{
	juce::FlexBox fb;
	fb.flexDirection = juce::FlexBox::Direction::row;

	fb.items.add(juce::FlexItem(icon).withFlex(0.15f));
	fb.items.add(juce::FlexItem(slider).withFlex(1.0f));

	fb.performLayout(getLocalBounds().reduced(10));
}

void IconSliderComponent::setSliderStyle(juce::Slider::SliderStyle style)
{
	slider.setSliderStyle(style);
}

void IconSliderComponent::updateTooltip()
{
	slider.setTooltip(std::to_string(( int ) slider.getValue()));
}