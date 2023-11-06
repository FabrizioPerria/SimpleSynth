#include <gtest/gtest.h>
#include "utils/FilterType.h"

TEST(FilterTypeTest, TestToArray) {
    juce::Array<FilterType::Value> array = FilterType::toArray();
    // Check that the array contains all FilterType values.
    // This will depend on the implementation of FilterType::firstValue and FilterType::lastValue.
    for (int i = (int) FilterType::firstValue; i <= (int) FilterType::lastValue; ++i) {
        EXPECT_TRUE(array.contains(static_cast<FilterType::Value>(i)));
    }
}

TEST(FilterTypeTest, TestToStringArray) {
    juce::StringArray stringArray = FilterType::toStringArray();
    // Check that the string array contains all FilterType values.
    // This will depend on the implementation of FilterType::firstValue and FilterType::lastValue.
    for (int i = (int) FilterType::firstValue; i <= (int) FilterType::lastValue; ++i) {
        EXPECT_TRUE(stringArray.contains(FilterType::toString(static_cast<FilterType::Value>(i))));
    }
}

TEST(FilterTypeTest, TestToString) {
    EXPECT_EQ(FilterType::toString(FilterType::LOWPASS), "Lowpass");
    EXPECT_EQ(FilterType::toString(FilterType::BANDPASS), "Bandpass");
    EXPECT_EQ(FilterType::toString(FilterType::HIGHPASS), "Highpass");
}

TEST(FilterTypeTest, TestFromInt) {
    EXPECT_EQ(FilterType::fromInt(0), FilterType::LOWPASS);
    EXPECT_EQ(FilterType::fromInt(1), FilterType::BANDPASS);
    EXPECT_EQ(FilterType::fromInt(2), FilterType::HIGHPASS);
}

TEST(FilterTypeTest, TestFromIntOutOfBounds) {
    EXPECT_DEATH(FilterType::fromInt(-1), "Assertion failed.*isIntValid");
    EXPECT_DEATH(FilterType::fromInt(4), "Assertion failed.*isIntValid");
}

TEST(FilterTypeTest, TestGetSVG) {
    EXPECT_EQ(FilterType::getSVG(FilterType::LOWPASS).svg, BinaryData::lowpass_svg);
    EXPECT_EQ(FilterType::getSVG(FilterType::BANDPASS).svg, BinaryData::bandpass_svg);
    EXPECT_EQ(FilterType::getSVG(FilterType::HIGHPASS).svg, BinaryData::highpass_svg);
}

TEST(FilterTypeTest, TestGetSVGSize) {
    EXPECT_EQ(FilterType::getSVG(FilterType::LOWPASS).size, BinaryData::lowpass_svgSize);
    EXPECT_EQ(FilterType::getSVG(FilterType::BANDPASS).size, BinaryData::bandpass_svgSize);
    EXPECT_EQ(FilterType::getSVG(FilterType::HIGHPASS).size, BinaryData::highpass_svgSize);
}
