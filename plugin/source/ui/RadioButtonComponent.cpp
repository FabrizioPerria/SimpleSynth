#include "ui/RadioButtonComponent.h"
#include "BinaryData.h"
#include <memory>

RadioButtonComponent::RadioButtonComponent() 
{
}

RadioButtonComponent::~RadioButtonComponent()
{
	buttons.clear();
}

void RadioButtonComponent::addListener(juce::Button::Listener *listener)
{
	for (auto &button : buttons)
		button->addListener(listener);
}

void RadioButtonComponent::removeListener(juce::Button::Listener *listener)
{
	for (auto &button : buttons)
		button->removeListener(listener);
}

void RadioButtonComponent::resized()
{
	juce::FlexBox fb;
	fb.flexDirection = juce::FlexBox::Direction::row;
	fb.flexWrap = juce::FlexBox::Wrap::wrap;

	for (auto &button : buttons)
        fb.items.add(juce::FlexItem(*button).withFlex(1));

	fb.performLayout(getLocalBounds().withHeight(getHeight() / 10).withWidth(getWidth() / 3).reduced(10));
}

void RadioButtonComponent::addButton(const char *svg, const size_t size, const juce::String name)
{
	auto buttonImage = juce::Drawable::createFromImageData(svg, size);
	auto buttonImageSelected = juce::Drawable::createFromImageData(svg, size);
	buttonImage->replaceColour(juce::Colours::black, juce::Colours::cyan);
	buttonImageSelected->replaceColour(juce::Colours::black, juce::Colours::red);

	auto button =
		std::make_unique<juce::DrawableButton>(name, juce::DrawableButton::ButtonStyle::ImageOnButtonBackground);
	button->setImages(buttonImage.get(), nullptr, nullptr, nullptr, buttonImageSelected.get());
	button->setClickingTogglesState(true);
	button->setRadioGroupId(1);
	addAndMakeVisible(button.get());
	button->setBounds(0, 0, 100, 100);

	buttons.add(std::move(button));
}

void RadioButtonComponent::setSelected(const int index)
{
    buttons[index]->setToggleState(true, juce::NotificationType::dontSendNotification);
}

const int RadioButtonComponent::getIndex(const juce::String name) const
{
    for (int i = 0; i < buttons.size(); ++i)
        if (buttons[i]->getName() == name)
            return i;

    return -1;
}
