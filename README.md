<h1 align="center">eZeus</h1>

eZeus is an open-source implementation of Zeus: Master of Olympus game.

## How To Play

To play eZeus you will need original game files (Zeus: Master of Olympus base game and Poseidon expansion).

Currently only Enlish and Polish versions are supported due to font glyphs limitations.

Only windows binaries are provided. If you want to play on Linux you have to build eZeus yourself.

First download eZeus.zip and extract it in original game's directory (e.g. (...)/Zeus and Poseidon/eZeus). Install VC_redist.x64.exe from eZeus directory. Use engconverter-0.5.exe to convert original game's Zeus_Text.eng file to Zeus_Text.xml and put it in eZeus directory.
Now download eTextureExtractor.zip. Run eTexture.exe and use it to extract texture files and put resulting ((...)/eTextureExtractor/Textures) directory in eZeus directory.

## How To Build on Linux

Make sure you have **git** installed on your system.

Clone the eZeus repository:
```
git clone --recurse-submodules https://github.com/MaurycyLiebner/eZeus
```

You will need to install following packeges:

```
sudo apt install libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev libsdl2-mixer-dev libnoise-dev g++
```

You will need Qt Creator (qt.io).

Open eZeus.pro in Qt Creator and use it to build eZeus.

Before running eZeus binary make sure to setup all files as specified in **How To Play** section. Put eZeus binary in (...)/Zeus and Poseidon/eZeus/Bin directory and run it.

## Authors

**Maurycy Liebner** - 2021 - 2024 - [MaurycyLiebner](https://github.com/MaurycyLiebner)