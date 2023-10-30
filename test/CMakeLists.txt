cmake_minimum_required(VERSION 3.22)

macro(ADD_PREFIX_TO_LIST input_list prefix output_list)
    set(${output_list})
    foreach(item ${${input_list}})
        list(APPEND ${output_list} "${prefix}/${item}")
    endforeach()
endmacro()

project(SimpleSynthTest VERSION 0.1.0)

set(LIBS_TO_TEST "SimpleSynth")

enable_testing()
add_executable(${PROJECT_NAME})

get_target_property(SIMPLE_SYNTH_JUCE_HEADER SimpleSynth JUCE_LIBRARY_CODE)
target_sources(${PROJECT_NAME}
    PRIVATE
    source/AudioProcessorTest.cpp
)
ADD_PREFIX_TO_LIST(LIBS_TO_TEST "${CMAKE_CURRENT_SOURCE_DIR}/include" INCLUDE_LIB_DIRS)
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${INCLUDE_LIB_DIRS}
        ${JUCE_SOURCE_DIR}/modules
        ${SIMPLE_SYNTH_JUCE_HEADER}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        ${LIBS_TO_TEST}
        GTest::gtest_main
)

target_compile_definitions(${PROJECT_NAME}
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
        JUCE_SILENCE_XCODE_15_LINKER_WARNING=1
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
