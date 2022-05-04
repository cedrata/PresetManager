# PresetManager
Basic preset manager template for JUCE.

The aim of this project is to provide a simple preset manamager implementation to add in every project if needed.

## TODOs
It is not completed yet but soon will be. At the moment is missing selecting the saved preset, the delete preset handler, then show user when current preset has been chaned.
Everithing is ready in the PresetManager class, handlers must be added in Editor class.
To do the selection of the last added preset add a variable inside the PresetManager class "lastStored" then when doing refresh after building the popupmenu get the index of "lastStored". Missing something, not completely working...
