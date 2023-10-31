#include "oscillatorPickerComponent.h"
#include "BinaryData.h"

void OscillatorPickerComponent::setupButton(juce::DrawableButton &button, const char *svg, size_t size)
{
	auto buttonImage = juce::Drawable::createFromImageData(svg, size);
	auto buttonImageSelected = juce::Drawable::createFromImageData(svg, size);
	buttonImage->replaceColour(juce::Colours::black, juce::Colours::cyan);
	buttonImageSelected->replaceColour(juce::Colours::black, juce::Colours::red);
	button.setImages(buttonImage.get(), nullptr, nullptr, nullptr, buttonImageSelected.get());
	button.setClickingTogglesState(true);
	button.setRadioGroupId(1);
	button.addListener(this);
	addAndMakeVisible(button);
	button.setBounds(0, 0, 100, 100);
}

OscillatorPickerComponent::OscillatorPickerComponent()
	: sineButton("Sine", juce::DrawableButton::ButtonStyle::ImageOnButtonBackground),
	  squareButton("Square", juce::DrawableButton::ButtonStyle::ImageOnButtonBackground),
	  sawButton("Saw", juce::DrawableButton::ButtonStyle::ImageOnButtonBackground)
{
	setupButton(sineButton, BinaryData::sine_svg, BinaryData::sine_svgSize);
	setupButton(squareButton, BinaryData::square_svg, BinaryData::square_svgSize);
	setupButton(sawButton, BinaryData::sawtooth_svg, BinaryData::sawtooth_svgSize);
}

OscillatorPickerComponent::~OscillatorPickerComponent()
{
}

void OscillatorPickerComponent::resized()
{
	juce::FlexBox flexBox;
	flexBox.flexDirection = juce::FlexBox::Direction::row;

	flexBox.items.add(juce::FlexItem(sineButton).withFlex(1));
	flexBox.items.add(juce::FlexItem(squareButton).withFlex(1));
	flexBox.items.add(juce::FlexItem(sawButton).withFlex(1));

	flexBox.performLayout(getLocalBounds().withHeight(getHeight() / 10).withWidth(getWidth() / 3).reduced(10));
}

void OscillatorPickerComponent::buttonClicked(juce::Button *button)
{
	if (button == &sineButton)
	{
		/* oscillatorType = OscillatorType::sine; */
	}
	else if (button == &squareButton)
	{
		/* oscillatorType = OscillatorType::square; */
	}
	else if (button == &sawButton)
	{
		/* oscillatorType = OscillatorType::saw; */
	}
}
