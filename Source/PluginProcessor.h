/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "IPresetManager.h"
#include "PresetManager.h"

//==============================================================================
/**
*/
class PresetManagerAudioProcessor  : public juce::AudioProcessor,
public cdrt::PresetManager::Interface::IPresetManagerCallback
{
public:
    //==============================================================================
    PresetManagerAudioProcessor();
    ~PresetManagerAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    // juce::Audio Processor
    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    //==============================================================================
    // IPresetManagerCallback
    //==============================================================================
    const juce::PopupMenu getPresetMenu() override;
    int getSelectedPresetId() override;
    int getPreviousPresetId() override;
    int getNextPresetId() override;
    
    //==============================================================================
    juce::Result storePreset(const juce::File &destinationFile) override;
    juce::Result deletePreset(const int id) override;
    int loadDefaultPreset() override;
    int loadPreset(const int id) override;
    
    
    //==============================================================================
    const juce::AudioProcessorValueTreeState& getAudioProcessorValueTreeState();
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();
    void saveStateAsPreset(const juce::String &absoluteFilePath);
    
private:
    //==============================================================================
    // Parameters management
    juce::AudioProcessorValueTreeState apvts;
    
    // Preset Manager
    std::unique_ptr<cdrt::PresetManager::Interface::IPresetManager> presetManager;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetManagerAudioProcessor)
};
