/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

struct LookAndFeel : juce::LookAndFeel_V4
{
    void drawRotarySlider (juce::Graphics&,
                                   int x, int y, int width, int height,
                                   float sliderPosProportional,
                                   float rotaryStartAngle,
                                   float rotaryEndAngle,
                                   juce::Slider&) override { }
    
};

struct RotarySliderLabeled : juce::Slider
{
    RotarySliderLabeled(juce::RangedAudioParameter& rap, const juce::String& unitSuffix) : juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, juce::Slider::TextEntryBoxPosition::NoTextBox),param(&rap), suffix(unitSuffix)
    {
        setLookAndFeel(&lnf);
    }
    
    ~RotarySliderLabeled()
    {
        setLookAndFeel(nullptr);
    }
    
    void paint(juce::Graphics& g) override { };
    juce::Rectangle<int> getSliderBounds() const;
    int getTextHight() const { return 14; };
    juce::String getDisplayString() const;
    
    
private:
    LookAndFeel lnf;

    juce::RangedAudioParameter* param;
    juce::String suffix;
};

struct ResponseCurveComponent: juce::Component, juce::AudioProcessorParameter::Listener, juce::Timer
{
    ResponseCurveComponent(EQpluginAudioProcessor&);
    ~ResponseCurveComponent();
    
    void parameterValueChanged (int parameterIndex, float newValue) override;

    void parameterGestureChanged (int parameterIndex, bool gestureIsStarting) override { };
    
    void timerCallback() override;
    
    void paint(juce::Graphics& g) override;
    
private:
    EQpluginAudioProcessor& audioProcessor;
    juce::Atomic<bool> parametersChanged { false };
    
    MonoChain monoChain;
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
    
    RotarySliderLabeled peakFreqSlider,
    peakGainSlider,
    peakQualitySlider,
    lowCutFreqSlider,
    lowCutSlopeSlider,
    highCutFreqSlider,
    highCutSlopeSlider;
    
    ResponseCurveComponent responseCurveComponent;
    
    using APVTS = juce::AudioProcessorValueTreeState;
    using Attachment = APVTS::SliderAttachment;
    
    Attachment peakFreqSliderAttachment,
                peakGainSliderAttachment,
                peakQualitySliderAttachment,
                lowCutFreqSliderAttachment,
                lowCutSlopeSliderAttachment,
                highCutFreqSliderAttachment,
                highCutSlopeSliderAttachment;
    
    std::vector<juce::Component*> getComps();

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EQpluginAudioProcessorEditor)
};
