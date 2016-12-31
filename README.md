# evaLUAtion2

evaLUAtion2 is a shooter game providing a test platform for artificial intelligence scripts in Lua language. Written in Unreal Engine 4 and designed for academic use, it allows users to define the behavior of bots based on their perception of surrounding world.

## Features

 * Lua 5.3-based scripting API providing information about the current state of the game and methods for controlling characters.
 * Gameplay allowing to control characters either by Lua scripts or user's mouse & keyboard.
 * A tool for editing game maps.
 * A profile manager allowing to bundle customized sets of game preferences and character lists.

## User's Manual

A [detailed user's guide](http://docdro.id/NiUYXnC) (in Polish) is available, explaining usage of the application's GUI and the basics of evaLUAtion2 scripting. An English translation of the guide is somewhere in the agenda :-)

## Libraries, Tools & Building

All of the libraries mentioned below were used in their 64-bit versions.

 * Unreal Engine 4.13.2
 * Visual C++ 2015
 * Lua 5.3.3
 * LuaBridge
 * Boost 1.62.0

To build the application, edit the paths in `Source\evaLUAtion2\evaLUAtion2.build.cs` to point to the aforementioned libraries' folders. Afterwards, you should be able to build the app and package it.

Please note that, while potentially suitable for cross-platform use (just as the entire Unreal Engine platform), the application has not yet been successfully compiled, let alone tested, for platforms other than Windows x64.
