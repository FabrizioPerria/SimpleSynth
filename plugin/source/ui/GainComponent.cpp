#include "GainComponent.h"
#include "BinaryData.h"
#include <string>

GainComponent::GainComponent(juce::AudioProcessorValueTreeState &apvts, juce::String parameterId)
	: gainSlider(apvts, parameterId, SVGData{BinaryData::volume_svg, BinaryData::volume_svgSize},
				 IconSliderDirection::column)
{
	setText("Gain");

	gainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
	addAndMakeVisible(gainSlider);
}

GainComponent::~GainComponent()
{
}

void GainComponent::resized()
{
	juce::FlexBox fb;

	fb.items.add(juce::FlexItem(gainSlider).withFlex(1.0f).withMargin(5));
	fb.performLayout(getLocalBounds().reduced(10));
}
