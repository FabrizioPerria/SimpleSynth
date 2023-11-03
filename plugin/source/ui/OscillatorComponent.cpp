#include "ui/OscillatorComponent.h"
#include "BinaryData.h"
#include "utils/SVGData.h"

OscillatorComponent::OscillatorComponent(juce::AudioProcessorValueTreeState &apvts, juce::String pickerId,
										 juce::String gainId, juce::String lfoFrequencyId, juce::String lfoDepthId,
										 juce::String filterPickerId, juce::String filterCutoffId,
										 juce::String filterResonanceId, juce::String name)
	: oscillatorPicker(apvts, pickerId),
	  gain(apvts, gainId, SVGData{BinaryData::volume_svg, BinaryData::volume_svgSize}),
	  lfo(apvts, lfoFrequencyId, lfoDepthId), filter(apvts, filterPickerId, filterCutoffId, filterResonanceId)
{
	gain.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
	addAndMakeVisible(oscillatorPicker);
	addAndMakeVisible(gain);
	addAndMakeVisible(lfo);
	addAndMakeVisible(filter);
	setText(name);
}

OscillatorComponent::~OscillatorComponent()
{
}

void OscillatorComponent::resized()
{
	juce::FlexBox fbSliders;
	fbSliders.flexDirection = juce::FlexBox::Direction::column;
	fbSliders.items.add(juce::FlexItem(gain).withFlex(1.0f));
	fbSliders.items.add(juce::FlexItem(lfo).withFlex(1.0f));

	juce::FlexBox fb;
	fb.flexDirection = juce::FlexBox::Direction::row;
	fb.items.add(juce::FlexItem(oscillatorPicker).withFlex(1.0f));
	fb.items.add(juce::FlexItem(fbSliders).withFlex(3.0f));
	fb.items.add(juce::FlexItem(filter).withFlex(3.0f));

	fb.performLayout(getLocalBounds().reduced(10));
}
