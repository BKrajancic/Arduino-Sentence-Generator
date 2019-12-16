# Simple Sentence Generator
This is a project I worked on which allows for generating sentences from a grammar.

This repo features three example projects:

1. Arduino
2. QT
3. demo

# Projects
## arduino
Two buttons are connected to an arduino, and a liquid crystal display. Pressing a button will send a http get request, and refresh the sentence shown on the display.

## qt_app
A simple app containing 9 buttons and generated text. Pressing a button will send a http get request. The beginning of the url for the HTTP Get is configured, and when a button is pressed its label is appended to the configured url.

## demo
Randomly generates sentences and prints to terminal.

## test
Unit tests to ensure software's correctness.

# Installation

## qt_app
For the QT App there are instructions in the file `qt_app/personal_info_config` which must be followed.

# ardunio
Each file in the directory `arduino` which end with `_config.hpp` contains instructions which must be followed.

# demo and tests
An installation of boost tests is required.

CMAKE is used to build a project. The project folder must be set to the root folder (containing this file `readme.md`).