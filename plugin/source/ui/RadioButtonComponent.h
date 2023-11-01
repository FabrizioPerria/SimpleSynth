#pragma once

#include "JuceHeader.h"
#include "utils/OscillatorType.h"

class RadioButtonComponent : public juce::Component
{
  public:
	RadioButtonComponent();
	~RadioButtonComponent() override;

	void addButton(const char *svgImage, const size_t svgSize, const juce::String name);

	void addListener(juce::Button::Listener *listener);
	void removeListener(juce::Button::Listener *listener);

	void setSelected(const int index);
	const int getIndex(const juce::String name) const;

	void resized() override;

  private:
	juce::OwnedArray<juce::DrawableButton> buttons;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RadioButtonComponent)
};
