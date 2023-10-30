#pragma once

#include "JuceHeader.h"

class EnvelopeComponent : public juce::Component
{
  public:
	EnvelopeComponent(juce::AudioProcessorValueTreeState &apvts);
	~EnvelopeComponent() override;

	void paint(juce::Graphics &g) override;
	void resized() override;

  private:
	juce::Slider attackSlider;
	juce::Slider decaySlider;
	juce::Slider sustainSlider;
	juce::Slider releaseSlider;

	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attackAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> decayAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sustainAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> releaseAttachment;

	void setupSlider(juce::Slider &slider);

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EnvelopeComponent)
};
