#pragma once

#include "JuceHeader.h"
#include "ui/IconSlider.h"
#include "ui/OscillatorPickerComponent.h"
#include "ui/GainComponent.h"
#include "ui/LabeledSlider.h"

class OscillatorComponent : public juce::GroupComponent
{
  public:
	OscillatorComponent(juce::AudioProcessorValueTreeState &apvts, juce::String pickerId, juce::String gainId,
						juce::String lfoFrequencyId, juce::String lfoDepthId, juce::String name);
	~OscillatorComponent() override;

	void resized() override;

  private:
	OscillatorPickerComponent oscillatorPicker;
	IconSlider lfoFrequency;
	IconSlider lfoDepth;
	IconSlider gain;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscillatorComponent)
};
