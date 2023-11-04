#include "ui/FilterPickerComponent.h"
#include "ui/RadioButtonComponent.h"
#include "utils/FilterType.h"

FilterPickerComponent::FilterPickerComponent(juce::AudioProcessorValueTreeState &apvts, juce::String parameterID)
	: radioButton(RadioButtonDirection::row)
{
	for (auto waveType : FilterType::toArray())
	{
		auto svgData = FilterType::getSVG(waveType);
		radioButton.addButton(svgData.svg, svgData.size, FilterType::toString(waveType));
	}

	addAndMakeVisible(radioButton);
	attachment = std::make_unique<RadioButtonAttachment>(apvts, parameterID, radioButton);
}

void FilterPickerComponent::resized()
{
	juce::FlexBox fb;

	fb.items.add(juce::FlexItem(radioButton).withFlex(1.0f));
	fb.performLayout(getLocalBounds().reduced(10));
}
