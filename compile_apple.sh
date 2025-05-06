## Needed for compile on an Arm Device:
# softwareupdate --install-rosetta
# /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
# arch -x86_64 /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
# brew install sdl2 sdl2_mixer sdl2_image sdl2_ttf git qt make dylibbundler fluid-synth
# arch -x86_64 /usr/local/bin/brew install sdl2 sdl2_mixer sdl2_image sdl2_ttf git qt make dylibbundler fluid-synth

# Set environment paths for x86 architecture
export CPATH=/usr/local/include:$CPATH
export LIBRARY_PATH=/usr/local/lib:$LIBRARY_PATH

# Clean previous builds if necessary
rm -rf build

# Create build directory
mkdir build

# Enter build directory
cd build

# Build x86
echo "Building for x86_64..."
qmake QMAKE_APPLE_DEVICE_ARCHS=x86_64 ..
make
make clean
mv eZeus eZeus_x86

echo "x86_64 build completed successfully!"

# Set environment paths for arm64 architecture
export CPATH=/opt/homebrew/include:$CPATH
export LIBRARY_PATH=/opt/homebrew/lib:$LIBRARY_PATH

# Build arm64
echo "Building for ARM64..."
qmake QMAKE_APPLE_DEVICE_ARCHS=arm64 ..
make
make clean
mv eZeus eZeus_arm64

rm Makefile

mkdir libs_x86 libs_arm64 libs

dylibbundler -of -cd -b -x "eZeus_x86" -d "libs_x86" -p "@executable_path/libs/"
dylibbundler -of -cd -b -x "eZeus_arm64" -d "libs_arm64" -p "@executable_path/libs/"

cd libs_arm64

for a in *.dylib; do lipo "$a" ../libs_x86/"$a" -output ../libs/"$a" -create; done

cd ..

rm -rf libs_*

mkdir -p eZeus/Bin

lipo eZeus_arm64 eZeus_x86 -output eZeus/Bin/eZeus -create

mv libs eZeus/Bin

rm eZeus_*

cd ..

cp -r fonts build/eZeus/Fonts
cp -r sanctuaries build/eZeus/Sanctuaries
cp -r text build/eZeus/Text
cp -r Adventures build/eZeus
mkdir build/eZeus/Save
cp Zeus_Text.xml Zeus_Text_DE.xml build/eZeus

cd build

mkdir DATA Audio Model

echo "Builds completed!"

echo -e "\n\n\nYou need to Place the file 'binary.e' into build/eZeus' and put the Gamefiles into DATA, Audio and Model Folder.\n\n\n"
