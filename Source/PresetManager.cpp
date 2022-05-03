///*
//  ==============================================================================
//
//    PresetManager.cpp
//    Created: 4 Apr 2022 11:09:49pm
//    Author:  Luca Greggio
//
//  ==============================================================================
//*/
//
#include "PresetManager.h"
#include "Paths.h"

namespace cdrt
{
    namespace PresetManager
    {
        namespace Impelementation
        {
            //==========================================================================
            // Public methods
            PresetManager::PresetManager(const juce::File &defaultPreset) noexcept
            : pathsAreBuilt(false), defaultPreset(defaultPreset)
            {
                this->osType = juce::SystemStats::getOperatingSystemType();
            }
            
            PresetManager::~PresetManager()
            {
            }
            
            const juce::PopupMenu PresetManager::getPresetMenu() noexcept
            {
                return this->presetsPopupMenu;
            }
            
            const int PresetManager::getSelectedId() noexcept
            {
                return selectedPresetIndex + 1;
            }
            
            juce::Result PresetManager::initialize() noexcept
            {
                if (!this->validateDefault())
                    return juce::Result::fail("An error occured in the initialization phase, maybe the given default preset is invalid");
                
                this->buildPaths();
                this->refresh();
                
                return juce::Result::ok();
            }
            
            void PresetManager::refresh() noexcept
            {
//                this->listPresets();
//                this->listSubMenus();
                this->buildPopupMenu();
            }
            
            juce::Result PresetManager::storePreset(const juce::File &destinationFile, const juce::ValueTree &currentState) noexcept
            {
                std::unique_ptr<juce::XmlElement> currentStateXML = currentState.createXml();
                
                if (currentStateXML == nullptr)
                    return juce::Result::fail("An error occured saving the current state to a preset");
                
                return juce::Result::ok();
            }
            
            juce::Result PresetManager::deletePreset(const int id) noexcept
            {
                // I'm assuming the id exist because the id is taken from the PopupMenu
                // that has been generated in the current class.
                if (!avaiablePresets.getUnchecked(id).existsAsFile()) return juce::Result::fail("An eror occure deleting the selected preset, the deletion was not succesfull");
                
                return juce::Result::ok();
            }
            
            juce::ValueTree PresetManager::loadPreset(const int id) noexcept
            {
                // I'm assuming the id exist because the id is taken from the PopupMenu
                // that has been generated in the current class.
                // This id - 1 is due to the juce::PopupMenu nature.
                // It's items id start from 1 but the array indexes start from 0.
                // The avaiablePreset is created when the preset folder is explored so i am sure that the avaiablePreset index will be always selectec id - 1

                this->selectedPresetIndex = id - 1;
                
                juce::File fileToLoad = avaiablePresets.getUnchecked(selectedPresetIndex);
                
                std::unique_ptr<juce::XmlElement> stateToLoadXML;
                
//                if (this->selectedPresetIndex == -1)
//                {
//                    stateToLoadXML = juce::XmlDocument(this->defaultPreset).getDocumentElement();
//                    this->selectedPresetIndex = 0;
//                }
//                else
//                {
//                    stateToLoadXML = juce::XmlDocument(fileToLoad).getDocumentElement();
//                }
                stateToLoadXML = juce::XmlDocument(fileToLoad).getDocumentElement();
                
                return juce::ValueTree().fromXml(*stateToLoadXML);
            }
            
            juce::ValueTree PresetManager::loadPreviousPreset() noexcept
            {
                this->selectedPresetIndex =
                ((this->selectedPresetIndex - 1) % avaiablePresets.size() + this->avaiablePresets.size())
                % this->avaiablePresets.size();
                
                std::unique_ptr<juce::XmlElement> stateToLoadXML = juce::XmlDocument(this->avaiablePresets.getUnchecked(this->selectedPresetIndex)).getDocumentElement();
                
                return juce::ValueTree().fromXml(*stateToLoadXML);
            }
            
            juce::ValueTree PresetManager::loadNextPreset() noexcept
            {
                this->selectedPresetIndex = (this->selectedPresetIndex - 1) % this->avaiablePresets.size();
                
                std::unique_ptr<juce::XmlElement> stateToLoadXML = juce::XmlDocument(this->avaiablePresets.getUnchecked(this->selectedPresetIndex)).getDocumentElement();
                
                return juce::ValueTree();
            }
            //==========================================================================
            // Private methods
            bool PresetManager::validateDefault() noexcept
            {
                return defaultPreset.existsAsFile()
                && defaultPreset.getFullPathName().endsWith(cdrt::Constants::Paths::presetExtension);
            }
            
            void PresetManager::buildPaths() noexcept
            {
                if ((osType & juce::SystemStats::MacOSX) != 0)
                {
                    this->separator = cdrt::Constants::Paths::MacPath::separator;
                    this->prefix = cdrt::Constants::Paths::MacPath::presetBaseFolder
                        + separator
                        + cdrt::Constants::Paths::presetFolderName;
                    this->suffix = cdrt::Constants::Paths::presetExtension;
                }
                else if ((osType & juce::SystemStats::Windows) != 0)
                {
                    this->separator = cdrt::Constants::Paths::WinPath::separator;
                    this->prefix = cdrt::Constants::Paths::WinPath::presetBaseFolder
                        + separator
                        + cdrt::Constants::Paths::presetFolderName;
                    this->suffix = cdrt::Constants::Paths::presetExtension;
                }

                this->presetFolder = juce::File(prefix);
                if (!this->presetFolder.exists())
                {
                    this->presetFolder.createDirectory();
                }
                
                pathsAreBuilt = true;
            }
            
            void PresetManager::buildPopupMenu() noexcept
            {
                this->creationIndex = 1;
                this->avaiablePresets.clear();
                this->presetsPopupMenu.clear();
                this->presetsPopupMenu = buildSubMenuRecursive(this->presetFolder);
            }
            
            const juce::PopupMenu PresetManager::buildSubMenuRecursive(const juce::File& directoryToSubMenu) noexcept
            {
                juce::PopupMenu subMenu;
                juce::Array<juce::File> currentSubDirectories =
                    directoryToSubMenu.findChildFiles(juce::File::TypesOfFileToFind::findDirectories,
                                                      false,
                                                      "*",
                                                      juce::File::FollowSymlinks::no);
                currentSubDirectories.sort();
                
                juce::Array<juce::File> currentPresets =
                    directoryToSubMenu.findChildFiles(juce::File::TypesOfFileToFind::findFiles,
                                                      false,
                                                      "*" + cdrt::Constants::Paths::presetExtension,
                                                      juce::File::FollowSymlinks::no);
                currentPresets.sort();
                for (auto p : currentPresets)
                    DBG(p.getFileName());

                // Get all avaiable presets in the current folder if any.
                for (auto preset : currentPresets)
                {
                    // IMPORTANT:
                    //  The creation index must be always GT 0.
                    this->avaiablePresets.add(preset);
                    subMenu.addItem(juce::PopupMenu::Item(preset.getFileName())
                                                   .setID(this->creationIndex)
                                                   .setTicked(false)
                                                   .setEnabled(true));
                    ++this->creationIndex;
                }
                
                // Recursive call foreach sub directory
                for (auto subDirectory : currentSubDirectories)
                    subMenu.addSubMenu(subDirectory.getFileName(), this->buildSubMenuRecursive(subDirectory));
                

                return subMenu;
            }
        } // namespace Implementation
    } // namespace PresetManager
} // namespace cdrt
