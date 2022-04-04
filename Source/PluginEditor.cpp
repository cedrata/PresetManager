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
    saveButton(cdrt::Labels::UI::saveLabel)
{
    saveButton.onClick = [this] () { saveStateAsPreset(); };
    // add event for presets combobox
    // update presets combobox items
    addAndMakeVisible(&saveButton);
    addAndMakeVisible(&presetComboBox);
    presetComboBox.addItem("pippo", 1);
    presetComboBox.addItem("pluto", 2);
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
    juce::Rectangle<int> presetComboBoxArea = getLocalBounds().withTrimmedBottom(getLocalBounds().getHeight()/2).reduced(50);
    saveButton.setBounds(saveButtonArea);
    presetComboBox.setBounds(presetComboBoxArea);
}

//=============================================================================
void PresetManagerAudioProcessorEditor::saveStateAsPreset()
{
    auto presetFolder = new juce::File(cdrt::Constants::Paths::MacPath::presetBaseFolder);
    if (!presetFolder->exists()) presetFolder->createDirectory();
    chooser = std::make_unique<juce::FileChooser>("Save", *presetFolder, "*.xml");
    auto chooserFlags = juce::FileBrowserComponent::saveMode
    | juce::FileBrowserComponent::canSelectFiles;


    chooser->launchAsync(chooserFlags, [this] (const juce::FileChooser& fc) {
        auto file = fc.getResult();
        if (file != juce::File{})
        {
            audioProcessor.saveStateAsPreset(file.getFullPathName());
            // update presets combobox items
        }
    });
}
