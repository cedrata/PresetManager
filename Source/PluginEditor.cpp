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
    addAndMakeVisible(&saveButton);
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
    saveButton.setBounds(getLocalBounds());
}

//==============================================================================
void PresetManagerAudioProcessorEditor::saveStateAsPreset()
{
    chooser = std::make_unique<juce::FileChooser>("Save", juce::File(cdrt::Paths::MacPath::defaultPresetPath), "*.xml");
    auto chooserFlags = juce::FileBrowserComponent::saveMode
    | juce::FileBrowserComponent::canSelectFiles;


    chooser->launchAsync(chooserFlags, [this] (const juce::FileChooser& fc) {
        auto file = fc.getResult();
        if (file != juce::File{})
            audioProcessor.saveStateAsPreset(file.getFullPathName());
    });
    // call from chooser->launchAsync lambda
}
