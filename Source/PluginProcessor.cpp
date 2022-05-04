/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include "PluginParameters.h"

//==============================================================================
PresetManagerAudioProcessor::PresetManagerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, cdrt::PluginParameters::id, createParameters())
#endif
{
//    /Library/Application Support/CedrataDSP/PresetManager/00.Default.xml
    presetManager = std::make_unique<cdrt::PresetManager::Impelementation::PresetManager>(juce::File("/Library/Application Support/CedrataDSP/PresetManager/Default.xml"));
    presetManager->initialize();
}

PresetManagerAudioProcessor::~PresetManagerAudioProcessor()
{
}

//==============================================================================
const juce::String PresetManagerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PresetManagerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PresetManagerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PresetManagerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PresetManagerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PresetManagerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PresetManagerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PresetManagerAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String PresetManagerAudioProcessor::getProgramName (int index)
{
    return {};
}

void PresetManagerAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void PresetManagerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void PresetManagerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PresetManagerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void PresetManagerAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
bool PresetManagerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* PresetManagerAudioProcessor::createEditor()
{
    return new PresetManagerAudioProcessorEditor (*this);
    // return new juce::GenericAudioProcessorEditor (*this);
}

//==============================================================================
void PresetManagerAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void PresetManagerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}


//==============================================================================
const juce::PopupMenu PresetManagerAudioProcessor::getPresetMenu()
{
    return presetManager->getPresetMenu();
}

int PresetManagerAudioProcessor::getPreviousPresetId()
{
    return presetManager->getPreviousPresetId();
}

int PresetManagerAudioProcessor::getNextPresetId()
{
    return presetManager->getNextPresetId();
}
//==============================================================================
juce::Result PresetManagerAudioProcessor::storePreset(const juce::File &destinationFile)
{
    auto storeResult = presetManager->storePreset(destinationFile, apvts.state);
    
    if (storeResult == juce::Result::ok()) presetManager->refresh();
    
    return storeResult;
}

juce::Result PresetManagerAudioProcessor::deletePreset(const int id)
{
    return presetManager->deletePreset(id);
}

int PresetManagerAudioProcessor::loadDefaultPreset()
{
    apvts.state = presetManager->loadDefaultPreset();
    return presetManager->getSelectedId();
}

int PresetManagerAudioProcessor::loadPreset(const int id)
{
    apvts.state = presetManager->loadPreset(id);
    return presetManager->getSelectedId();
}

//==============================================================================
juce::AudioProcessorValueTreeState::ParameterLayout PresetManagerAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;
    
    // Parameter 1
    parameters.push_back (std::make_unique<juce::AudioParameterFloat> (cdrt::PluginParameters::param1::id,
                                                                       cdrt::PluginParameters::param1::name,
                                                                       juce::NormalisableRange<float> (cdrt::PluginParameters::param1::min,
                                                                                                       cdrt::PluginParameters::param1::max),
                                                                       cdrt::PluginParameters::param1::initial));

    // Parameter 2
    parameters.push_back (std::make_unique<juce::AudioParameterFloat> (cdrt::PluginParameters::param2::id,
                                                                       cdrt::PluginParameters::param2::name,
                                                                       juce::NormalisableRange<float> (cdrt::PluginParameters::param2::min,
                                                                                                       cdrt::PluginParameters::param2::max),
                                                                       cdrt::PluginParameters::param2::initial));
    return { parameters.begin(), parameters.end() };
}

const juce::AudioProcessorValueTreeState& PresetManagerAudioProcessor::getAudioProcessorValueTreeState()
{
    return apvts;
}

void PresetManagerAudioProcessor::saveStateAsPreset(const juce::String &absoluteFilePath)
{
    // Explicit writing
    std::unique_ptr<juce::XmlElement> currentStateXML = apvts.state.createXml();
    if ((juce::SystemStats::getOperatingSystemType() & juce::SystemStats::OperatingSystemType::MacOSX) != 0)
    {
         apvts.state.createXml()->writeTo(juce::File(absoluteFilePath));
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PresetManagerAudioProcessor();
}
