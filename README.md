# Quicksand

Quicksand is a take on the Tetris Game which includes random block layouts on top of standard tetrominoes and an emphasis on clearing tiles as fast as possible.   
The project was originally for an end-of-course college project using **C++** and **SFML**.  This repository is a fork of the project featuring refactored code, gameplay changes, and optimizations.
## Game Overview
Quicksand is based on Tetris where the main objective is to build up a high score by completely filling up one or more rows with tiles to clear the row and earn points.   
Score is based on speed. Using soft drops or hard drops will earn significantly more points and the game will speed up as score accumulates.
### Blocks
- The original Tetromino blocks
- Blocks in a randomly connected configuration
- Bomb blocks that will destroy any adjacent tile
### Controls
The games can be played using a keyboard & mouse or by using a controller. List of controls below is based on the Xbox Controller layout:
- **Block Movement:** Left/Right Key, D-Pad Left/Right
- **Rotate Clockwise:** Up/X Key, B/Y Button
- **Rotate Counter-Clockwise:** Ctrl/Z Key, A/X Button
- **Soft Drop:** Down Key, D-Pad Down
- **Hard Drop:** Spacebar Key, D-Pad Up

## Building

Build `Quicksand.sln` using Visual Studio 2019   
   
The game requires [SFML](https://www.sfml-dev.org/) to build.   
If building without the included files, SFML header files and dependencies must be linked or included to compile and build.
More information can be found [here](https://www.sfml-dev.org/tutorials/2.5/) from the Getting Started section.
#### SFML lib files:
```bash
sfml-system.lib
sfml-graphics.lib
sfml-audio.lib
sfml-window.lib
```
Additionally, the executable requires SFML dependencies to run.
#### SFML DLL files:
```bash
openal32.dll
sfml-audio-2.dll
sfml-graphics-2.dll
sfml-system-2.dll
sfml-window-2.dll
```

## Changes from the Original
Multiple changes have been made to the project from the original with varying degrees of significance.   
Here is a non-exhaustive list of improvements to the game:
- Removed copyrighted textures for royalty-free textures
- Changed control layout to align with modern tetris controls
- Random blocks can now be controlled   
 (In the original, The blocks had erratic movement that made it hard to control)
- The AudioPlayer class used to be a lib dependency. Its .cpp and .h files are now included in the project
- Refactored code for readability
- Optimizations to Keyboard & Joystick inputs
- Overall improvements to game logic such as:
   - Improved Scoreboard serialization & deserialization
   - Improved Game-over sequence
- Added the ability to rotate Counter-Clockwise
- Optimized how graphics were drawn
   - Recoloring textures to reduce the number of textures
   - Optimized how the grid was drawn
   - Reduced texture size & resolution compared to original
- Fixed bugs and improved DAS for blocks

## Areas I've worked on for the original
- The Game class (Our Game loop used to be one big function)
   - Overall game logic & loop
   - Soft Drop system
   - Hard Drop system
- Keyboard & Joystick Input system
- Block DAS (Delayed-AutoShift) system
- Gameover Sequence & Scoreboard

## Authors
The members of the original project were instrumental in making this game happen.   
The original team consists of:   
[HongDong1220](https://github.com/hongdong1220)   
[ar201](https://github.com/ar201)   
[Nj123321](https://github.com/Nj123321)   
[KS2019](https://github.com/KS1019)   
[LucyWang520](https://github.com/LucyWang520)   
[Tascate](https://github.com/Tascate) (That's me!)
