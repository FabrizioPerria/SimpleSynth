#include <gtest/gtest.h>
#include "data/OscillatorData.h"
#include "JuceHeader.h"

TEST(OscillatorDataTest, TestCanInstantiate)
{
	OscillatorData OscillatorData;
	ASSERT_TRUE(true);
}

TEST(OscillatorDataTest, TestProcessWithoutPrepare)
{
    OscillatorData OscillatorData;
    juce::AudioBuffer<float> buffer(2, 512); // Assuming a buffer with 2 channels and 512 samples

    auto block = juce::dsp::AudioBlock<float>{ buffer };
    EXPECT_DEATH( OscillatorData.getNextAudioBlock(block), "Assertion failed.*isPrepared");
}