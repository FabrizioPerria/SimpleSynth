#pragma once

#include "JuceHeader.h"
#include "ui/IconSliderComponent.h"
#include "ui/OscillatorPickerComponent.h"
#include "ui/GainComponent.h"
#include "ui/LabeledSliderComponent.h"
#include "ui/LFOComponent.h"
#include "ui/FilterComponent.h"

class OscillatorComponent : public juce::GroupComponent
{
  public:
	OscillatorComponent(juce::AudioProcessorValueTreeState &apvts, juce::String pickerId, juce::String gainId,
						juce::String lfoFrequencyId, juce::String lfoDepthId, juce::String filterId,
						juce::String filterCutoffId, juce::String filterResonanceId, juce::String name);
	~OscillatorComponent() override;

	void resized() override;

  private:
	OscillatorPickerComponent oscillatorPicker;
	IconSliderComponent gain;
	LFOComponent lfo;
	FilterComponent filter;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscillatorComponent)
};
