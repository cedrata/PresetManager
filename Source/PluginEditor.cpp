/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Labels.h"
#include "Paths.h"

//==============================================================================
PresetManagerAudioProcessorEditor::PresetManagerAudioProcessorEditor (PresetManagerAudioProcessor& p)
    : AudioProcessorEditor (&p),
    audioProcessor (p),
    saveButton(cdrt::Labels::UI::saveLabel),
    asyncExecution(false),
    previousPresetButton("<"),
    nextPresetButton(">")
{
    this->initializePresetManager();
    
    this->initializeCallbacks();
    

    addAndMakeVisible(&saveButton);
    addAndMakeVisible(&presetComboBox);
    addAndMakeVisible(&previousPresetButton);
    addAndMakeVisible(&nextPresetButton);
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

PresetManagerAudioProcessorEditor::~PresetManagerAudioProcessorEditor()
{
}

//==============================================================================
void PresetManagerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void PresetManagerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    juce::Rectangle<int> saveButtonArea = getLocalBounds().withTrimmedTop(getLocalBounds().getHeight()/2).reduced(50);
    juce::Rectangle<int> presetComboBoxArea = getLocalBounds().withTrimmedBottom(getLocalBounds().getHeight()/2).reduced(50).withTrimmedLeft(getWidth()/6).withTrimmedRight(getWidth()/6);
    juce::Rectangle<int> previousPresetButtonArea = getLocalBounds().withTrimmedBottom(getLocalBounds().getHeight()/2).reduced(50).withTrimmedRight(getWidth()/6 * 4);
    juce::Rectangle<int> nextPrestButtonArea = getLocalBounds().withTrimmedBottom(getLocalBounds().getHeight()/2).reduced(50).withTrimmedLeft(getWidth()/6 * 4);
    saveButton.setBounds(saveButtonArea);
    previousPresetButton.setBounds(previousPresetButtonArea);
    nextPresetButton.setBounds(nextPrestButtonArea);
    presetComboBox.setBounds(presetComboBoxArea);
}

//=============================================================================
void PresetManagerAudioProcessorEditor::initializePresetManager()
{
    this->refreshPresetManager();
    this->presetComboBox.setSelectedId(this->audioProcessor.loadDefaultPreset());
}

void PresetManagerAudioProcessorEditor::refreshPresetManager()
{
    // PresetManager population
    juce::PopupMenu* pippo = presetComboBox.getRootMenu();
    *pippo = audioProcessor.getPresetMenu();
}

void PresetManagerAudioProcessorEditor::initializeCallbacks()
{
    this->presetComboBox.onChange = [&, this] () {
        this->audioProcessor.loadPreset(this->presetComboBox.getSelectedId());
    };
     
    this->previousPresetButton.onClick = [this] () {
        this->presetComboBox.setSelectedId(this->audioProcessor.getPreviousPresetId());
    };
    
    this->nextPresetButton.onClick = [this] () {
        this->presetComboBox.setSelectedId(this->audioProcessor.getNextPresetId());
    };
   
    this->saveButton.onClick = [this] () {
        this->saveStateAsPreset();
    };
   
}

void PresetManagerAudioProcessorEditor::saveStateAsPreset()
{
    auto presetFolder = juce::File(cdrt::Constants::Paths::MacPath::presetBaseFolder);
    if (!presetFolder.exists()) presetFolder.createDirectory();
    chooser = std::make_unique<juce::FileChooser>("Save", presetFolder, "*.xml");
    auto chooserFlags = juce::FileBrowserComponent::saveMode
    | juce::FileBrowserComponent::canSelectFiles;

    chooser->launchAsync(chooserFlags, [this] (const juce::FileChooser& fc) {
        auto file = fc.getResult();
        if (file != juce::File{})
        {
            this->audioProcessor.storePreset(file);
            this->refreshPresetManager();
            this->presetComboBox.setSelectedId(this->audioProcessor.getSelectedPresetId(), juce::NotificationType::dontSendNotification);
        }
    });
}
