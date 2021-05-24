/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

struct CustomRotarySlider : juce::Slider
{
    CustomRotarySlider() : juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, juce::Slider::TextEntryBoxPosition::NoTextBox)
    {
        
    }
};

//==============================================================================
/**
*/
class EQpluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    EQpluginAudioProcessorEditor (EQpluginAudioProcessor&);
    ~EQpluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    EQpluginAudioProcessor& audioProcessor;
    
    CustomRotarySlider peakFreqSlider,
    peakGainSlider,
    peakQualitySlider,
    lowCutFreqSlider,
    lowCutSlopeSlider,
    highCutFreqSlider,
    highCutSlopeSlider;
    
    std::vector<juce::Component*> getComps();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EQpluginAudioProcessorEditor)
};
