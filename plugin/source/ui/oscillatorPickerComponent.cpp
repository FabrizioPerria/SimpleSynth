#include "ui/OscillatorPickerComponent.h"
#include "BinaryData.h"

OscillatorPickerComponent::OscillatorPickerComponent(juce::AudioProcessorValueTreeState &apvts,
													 const juce::String &parameterID)
{
	radioButton.addButton(BinaryData::sine_svg, BinaryData::sine_svgSize, "SINE");
	radioButton.addButton(BinaryData::square_svg, BinaryData::square_svgSize, "SQUARE");
	radioButton.addButton(BinaryData::sawtooth_svg, BinaryData::sawtooth_svgSize, "SAW");
	addAndMakeVisible(radioButton);
	attachment = std::make_unique<RadioButtonAttachment>(apvts, parameterID, radioButton);
}

OscillatorPickerComponent::~OscillatorPickerComponent()
{
}

void OscillatorPickerComponent::resized()
{
	juce::FlexBox fb;

	fb.items.add(FlexItem(radioButton).withFlex(1.0f));
	fb.performLayout(getLocalBounds().reduced(10));
}
