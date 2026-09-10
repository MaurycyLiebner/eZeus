#!/usr/bin/env bash

set -Eeuo pipefail
trap 'printf "[!] Build failed at line %s: %s\n" "$LINENO" "$BASH_COMMAND" >&2' ERR

BASE_CPATH=${CPATH:-}
BASE_LIBRARY_PATH=${LIBRARY_PATH:-}

## Script for compiling eZeus on Apple Silicon as Universal Binary.
# softwareupdate --install-rosetta
# /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
# arch -x86_64 /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
# brew install sdl2 sdl2_mixer sdl2_image sdl2_ttf git qt make dylibbundler fluid-synth
# arch -x86_64 /usr/local/bin/brew install sdl2 sdl2_mixer sdl2_image sdl2_ttf git qt make dylibbundler fluid-synth

function macos_patch
{
	echo "[*] Checking source compatibility..."
	find . -type d -name 'build_*' -prune -o -type f -name "*.cpp" -print | while IFS= read -r file; do

    if grep -E -q '^[^/[:space:]]*.*std::random_shuffle' "$file"; then
        perl -0777 -pi.bak -e '
            s{
                ^ ([ \t]* )
                (?! // | /\* )
                (.*?)
                std::random_shuffle\(\s*
                ([^;]+?)\.begin\(\)\s*,\s*
                \3\.end\(\)\s*
                \s*\);
            }
            {
                my $indent=$1;
                my $container=$3;
                "${indent}std::shuffle(${container}.begin(), ${container}.end(), std::default_random_engine(std::random_device{}()));"
            }gexm;
        ' "$file"

        if ! grep -q "#include <random>" "$file"; then
            sed -i '' '1i\
#include <random>
' "$file"
        fi

        if ! grep -q "#include <algorithm>" "$file"; then
            sed -i '' '1i\
#include <algorithm>
' "$file"
        fi

        echo "    Conversion of $file done."
    fi
done


    perl -i -pe 's/\x{EF}\x{BB}\x{BF}//g' engine/egameboard.cpp
    
PRO_FILE="eZeus.pro"
TMP_FILE="${PRO_FILE}.tmp"
PRO_MODE=$(stat -f '%Lp' "$PRO_FILE")

echo "[*] Updating $PRO_FILE..."

SRC_LINE_NUM=$(grep -n "^SOURCES += \\\\" "$PRO_FILE" | cut -d: -f1 || true)

if [ -z "$SRC_LINE_NUM" ]; then
    echo "Fehler: Zeile 'SOURCES += \\' nicht gefunden in $PRO_FILE"
    exit 1
fi

{
cat <<'EOM'
TEMPLATE = app
CONFIG += c++17
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++17
QMAKE_LFLAGS += -stdlib=libc++

macx {
    !equals(QMAKE_APPLE_DEVICE_ARCHS, arm64): !equals(QMAKE_APPLE_DEVICE_ARCHS, x86_64): QMAKE_APPLE_DEVICE_ARCHS = arm64

    message("Target architecture: $$QMAKE_APPLE_DEVICE_ARCHS")

    contains(QMAKE_APPLE_DEVICE_ARCHS, x86_64) {
        INCLUDEPATH += /usr/local/include/SDL2
        LIBS += -L/usr/local/lib -lSDL2_mixer
        message("Building for x86_64")
    }

    contains(QMAKE_APPLE_DEVICE_ARCHS, arm64) {
        INCLUDEPATH += /opt/homebrew/include/SDL2
        LIBS += -L/opt/homebrew/lib -lSDL2_mixer
        message("Building for arm64")
    }

    QMAKE_MAC_SDK = macosx
    QMAKE_CFLAGS_RELEASE += -O3
    QMAKE_CXXFLAGS_RELEASE += -O3
}

win32 {
    RC_ICONS += C:\\Users\\maury\\Documents\\eZeusBuild\\zeus.ico
    QMAKE_CFLAGS_RELEASE += /O2 -O2 /GL
    QMAKE_CXXFLAGS_RELEASE += /O2 -O2 /GL

    INCLUDEPATH += C:\\Users\\maury\\Documents\\eZeusLibs\\SDL2-2.30.5\\include

    LIBS += -LC:\\Users\\maury\\Documents\\eZeusLibs\\SDL2-2.30.5\\lib\\x64
    LIBS += -LC:\\Users\\maury\\Documents\\eZeusLibs\\SDL2_ttf-2.22.0\\lib\\x64
    LIBS += -LC:\\Users\\maury\\Documents\\eZeusLibs\\SDL2_mixer-2.8.0\\lib\\x64
    LIBS += -LC:\\Users\\maury\\Documents\\eZeusLibs\\SDL2_image-2.8.2\\lib\\x64
}

unix:!macx {
    QMAKE_CFLAGS_RELEASE -= -O2
    QMAKE_CFLAGS_RELEASE -= -O1
    QMAKE_CXXFLAGS_RELEASE -= -O2
    QMAKE_CXXFLAGS_RELEASE -= -O1
    QMAKE_CFLAGS_RELEASE += -m64 -O3
    QMAKE_CXXFLAGS_RELEASE += -m64 -O3

    QMAKE_LFLAGS += -no-pie

    LIBS += -lpthread
    LIBS += -L/usr/lib/x86_64-linux-gnu
    LIBS += -lstdc++fs
    LIBS += -lnoise
}
LIBS += -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
EOM
    printf '\n'
    tail -n +"$SRC_LINE_NUM" "$PRO_FILE"
} > "$TMP_FILE"

chmod "$PRO_MODE" "$TMP_FILE"
mv "$TMP_FILE" "$PRO_FILE"
rm -f "$TMP_FILE.rest"

}

function build_arch
{
    ARCH=$1
    BUILDDIR="build_${ARCH}"

    echo "[*] Building for $ARCH..."
    rm -rf "$BUILDDIR"
    mkdir -p "$BUILDDIR/libs"
    pushd "$BUILDDIR" >/dev/null

    if [ "$ARCH" = "arm64" ]; then
        export CPATH="/opt/homebrew/include${BASE_CPATH:+:$BASE_CPATH}"
        export LIBRARY_PATH="/opt/homebrew/lib${BASE_LIBRARY_PATH:+:$BASE_LIBRARY_PATH}"
    else
        export CPATH="/usr/local/include${BASE_CPATH:+:$BASE_CPATH}"
        export LIBRARY_PATH="/usr/local/lib${BASE_LIBRARY_PATH:+:$BASE_LIBRARY_PATH}"
    fi

    qmake "QMAKE_APPLE_DEVICE_ARCHS=$ARCH" ..
    make -j"$(sysctl -n hw.ncpu)"

    dylibbundler -of -cd -b -x "eZeus" -d "libs" -p "@executable_path/libs/"
    
    curl --fail --location --remote-name --show-error https://github.com/MacThings/eZeus/releases/download/Zeus/Zeus_MM.xml
	curl --fail --location --remote-name --show-error https://github.com/MacThings/eZeus/releases/download/Zeus/Zeus_Text.xml
        
    make clean
    rm -f Makefile
    
    popd >/dev/null
}

macos_patch
build_arch arm64
build_arch x86_64

printf '\n\nBuild completed!\nDownload Windows package:\n%s\n\n' \
    'https://github.com/MaurycyLiebner/eZeus/releases/download/0.8.1-beta/eZeus-0.8.1-beta.zip'
printf '%s\n' 'Copy the two .xml files in the buildfolder to your eZeus root folder (not to the Bin folder within eZeus) and you are done.'
