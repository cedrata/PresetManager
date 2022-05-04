/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PresetManager.h"

//==============================================================================
/**
*/
class PresetManagerAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    juce::String extracted(juce::String &tempDbgBuf);
    
PresetManagerAudioProcessorEditor (PresetManagerAudioProcessor&);
    ~PresetManagerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    void initializePresetManager();
    void refreshPresetManager();
    void initializeCallbacks();
    void saveStateAsPreset();
    juce::File getNewPresetFile();
    
    //==============================================================================
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PresetManagerAudioProcessor& audioProcessor;
    
    // Buttons and Dials
    juce::TextButton saveButton;
    bool asyncExecution;
    juce::ComboBox presetComboBox;
    juce::TextButton previousPresetButton;
    juce::TextButton nextPresetButton;
    
    // File chooser for preset
    std::unique_ptr<juce::FileChooser> chooser;
    
    // Preset Manager
//    cdrt::PresetManager presetManager;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetManagerAudioProcessorEditor)
};
