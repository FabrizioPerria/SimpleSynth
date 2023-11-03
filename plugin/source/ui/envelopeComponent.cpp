#include "ui/EnvelopeComponent.h"

EnvelopeComponent::EnvelopeComponent(juce::AudioProcessorValueTreeState &apvts, juce::String attackId,
									 juce::String decayId, juce::String sustainId, juce::String releaseId,
									 juce::String name)
	: attackSlider(apvts, attackId, "A"), decaySlider(apvts, decayId, "D"), sustainSlider(apvts, sustainId, "S"),
	  releaseSlider(apvts, releaseId, "R")
{
	addAndMakeVisible(attackSlider);
	addAndMakeVisible(decaySlider);
	addAndMakeVisible(sustainSlider);
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
