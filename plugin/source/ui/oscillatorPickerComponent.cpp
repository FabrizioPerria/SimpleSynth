#include "ui/OscillatorPickerComponent.h"
#include "utils/OscillatorType.h"

OscillatorPickerComponent::OscillatorPickerComponent(juce::AudioProcessorValueTreeState &apvts,
													 const juce::String &parameterID)
{
	for (auto waveType : OscillatorType::toArray())
	{
		auto svgData = OscillatorType::getSVG(waveType);
		radioButton.addButton(svgData.svg, svgData.size, OscillatorType::toString(waveType));
	}

	addAndMakeVisible(radioButton);
	attachment = std::make_unique<RadioButtonAttachment>(apvts, parameterID, radioButton);
}

OscillatorPickerComponent::~OscillatorPickerComponent()
{
}

void OscillatorPickerComponent::resized()
{
	juce::FlexBox fb;

	fb.items.add(FlexItem(radioButton).withFlex(1.0f).withMaxHeight(50));
	fb.performLayout(getLocalBounds().reduced(10));
}
