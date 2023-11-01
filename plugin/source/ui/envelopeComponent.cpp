#include "ui/EnvelopeComponent.h"

EnvelopeComponent::EnvelopeComponent(juce::AudioProcessorValueTreeState &apvts)
	: attackSlider(apvts, "ATTACK", "A"), decaySlider(apvts, "DECAY", "D"), sustainSlider(apvts, "SUSTAIN", "S"),
	  releaseSlider(apvts, "RELEASE", "R")
{
	addAndMakeVisible(attackSlider);
	addAndMakeVisible(decaySlider);
	addAndMakeVisible(sustainSlider);
	addAndMakeVisible(releaseSlider);

	setText("ADSR");
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
