#pragma once

#include "JuceHeader.h"

class OscillatorPickerComponent : public juce::Component, public juce::Button::Listener
{
  public:
	OscillatorPickerComponent();
	~OscillatorPickerComponent() override;

	void resized() override;

	void buttonClicked(juce::Button *button) override;

  private:
	juce::DrawableButton sineButton;
	juce::DrawableButton squareButton;
	juce::DrawableButton sawButton;

	void setupButton(juce::DrawableButton &button, const char *svg, size_t size);

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscillatorPickerComponent)
};
