#include <gtest/gtest.h>
#include "data/FilterData.h"
#include "JuceHeader.h"

TEST(FilterDataTest, TestCanInstantiate)
{
	FilterData FilterData;
	ASSERT_TRUE(true);
}

TEST(FilterDataTest, TestProcessWithoutPrepare)
{
    FilterData FilterData;
    juce::AudioBuffer<float> buffer(2, 512); // Assuming a buffer with 2 channels and 512 samples

    EXPECT_DEATH( FilterData.process(buffer), "Assertion failed.*isPrepared");
}