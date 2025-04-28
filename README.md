# W2 Board Package for Arduino

This is a board package for the W2 develop board. This repository contains only the Windows version (both x64 and x86).

## Installation

1. Open Arduino IDE.
2. Go to `File` -> `Preferences`.
3. In the `Additional Board Manager URLs` field, add the following URL:
   ```
   https://github.com/PramSin/W2/releases/download/v1.2.0/w2_windows.json
   ```
4. Click `OK` to save the preferences.
5. Go to `Tools` -> `Board` -> `Boards Manager`.
6. Search for `W2` and install the package.
7. Select the W2 board from `Tools` -> `Board` menu.
8. Select the appropriate port from `Tools` -> `Port` menu.
9. You can now upload sketches to the W2 board using the Arduino IDE.

## Example Sketches

You can find example sketches in the `examples` folder of the package. To access them, go to `File` -> `Examples` and look for the W2 board package.
