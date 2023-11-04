#include "ui/EnvelopeComponent.h"
#include "BinaryData.h"
#include "utils/SVGData.h"

EnvelopeComponent::EnvelopeComponent(juce::AudioProcessorValueTreeState &apvts, juce::String attackId,
									 juce::String decayId, juce::String sustainId, juce::String releaseId,
									 juce::String name)
	: attackSlider(apvts, attackId, SVGData{BinaryData::a_svg, BinaryData::a_svgSize}, IconSliderDirection::column),
	  decaySlider(apvts, decayId, SVGData{BinaryData::d_svg, BinaryData::d_svgSize}, IconSliderDirection::column),
	  sustainSlider(apvts, sustainId, SVGData{BinaryData::s_svg, BinaryData::s_svgSize}, IconSliderDirection::column),
	  releaseSlider(apvts, releaseId, SVGData{BinaryData::r_svg, BinaryData::r_svgSize}, IconSliderDirection::column)
{
	attackSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
	addAndMakeVisible(attackSlider);
	decaySlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
	addAndMakeVisible(decaySlider);
	sustainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
	addAndMakeVisible(sustainSlider);
	releaseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
	addAndMakeVisible(releaseSlider);

	setText(name);
}

EnvelopeComponent::~EnvelopeComponent()
{
}

void EnvelopeComponent::resized()
{
	juce::FlexBox fb;

	fb.flexDirection = juce::FlexBox::Direction::row;

	fb.items.add(FlexItem(attackSlider).withFlex(1.0f).withMargin(10));
	fb.items.add(FlexItem(decaySlider).withFlex(1.0f).withMargin(10));
	fb.items.add(FlexItem(sustainSlider).withFlex(1.0f).withMargin(10));
	fb.items.add(FlexItem(releaseSlider).withFlex(1.0f).withMargin(10));

	fb.performLayout(getLocalBounds().reduced(10));
}
