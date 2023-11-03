#include "ui/LFOComponent.h"
#include "BinaryData.h"
#include "utils/SVGData.h"

LFOComponent::LFOComponent(juce::AudioProcessorValueTreeState &apvts, juce::String frequencyId, juce::String depthId)
	: frequency(apvts, frequencyId, SVGData{BinaryData::lfoFreq_svg, BinaryData::lfoFreq_svgSize}),
	  depth(apvts, depthId, SVGData{BinaryData::lfoDepth_svg, BinaryData::lfoDepth_svgSize})
{
	frequency.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
	depth.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
	addAndMakeVisible(frequency);
	addAndMakeVisible(depth);
}

void LFOComponent::resized()
{
	juce::FlexBox fb;

	fb.flexDirection = juce::FlexBox::Direction::column;

	fb.items.add(FlexItem(frequency).withFlex(1.0f));
	fb.items.add(FlexItem(depth).withFlex(1.0f));

	fb.performLayout(getLocalBounds());
}
