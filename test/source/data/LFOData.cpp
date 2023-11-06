#include <gtest/gtest.h>
#include "data/LFOData.h"
#include "JuceHeader.h"

TEST(LFODataTest, TestCanInstantiate)
{
	LFOData lfoData;
	ASSERT_TRUE(true);
}

TEST(LFODataTest, TestProcessIsBound)
{
	LFOData lfoData;
	juce::dsp::ProcessSpec spec{44100.0, 512, 2};
	lfoData.prepare(spec);
	lfoData.setParameters(440.0f, 1.0f);

	juce::AudioBuffer<float> buffer(2, 512); // Assuming a buffer with 2 channels and 512 samples
	juce::dsp::AudioBlock<float> block(buffer);
	lfoData.process(block);

	EXPECT_GE(lfoData.getFrequency(), -1.0f);
	EXPECT_LE(lfoData.getFrequency(), 1.0f);
}

TEST(LFODataTest, TestProcessWithoutPrepare)
{
	LFOData lfoData;
	juce::AudioBuffer<float> buffer(2, 512); // Assuming a buffer with 2 channels and 512 samples
	juce::dsp::AudioBlock<float> block(buffer);

	EXPECT_DEATH(lfoData.process(block), "Assertion failed.*isPrepared");
}