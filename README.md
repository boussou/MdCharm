# MdCharm

Modern Qt-based Markdown editor migrated to Qt WebEngine.

## Linux Dependencies

Install the following packages before building.

### Arch Linux (pacman)
- qt5-base
- qt5-tools (qmake, lrelease, etc.)
- qt5-webengine
- qt5-webchannel
- hunspell
- glib2
- zlib
- python (Python 3)
- gcc, make (base-devel)

Command (example):
```bash
sudo pacman -S --needed qt5-base qt5-tools qt5-webengine qt5-webchannel hunspell glib2 zlib python base-devel
```

### Debian/Ubuntu (apt)
- build-essential
- qtbase5-dev
- qttools5-dev qttools5-dev-tools
- qtwebengine5-dev
- qtwebchannel5-dev
- libhunspell-dev
- libglib2.0-dev
- zlib1g-dev
- python3

Command (example):
```bash
sudo apt update && sudo apt install -y \
  build-essential qtbase5-dev qttools5-dev qttools5-dev-tools \
  qtwebengine5-dev qtwebchannel5-dev \
  libhunspell-dev libglib2.0-dev zlib1g-dev python3
```

Notes:
- No external leg/peg tool is required; the MultiMarkdown PEG generator is bundled and built from `src/lib/multimarkdown/peg/`.
- Breakpad is vendored; system glib headers are required.

## Build

From the repository root (`MdCharm/`):
```bash
cd src
qmake CONFIG+=release
make -j$(nproc)
```

The binary will be created at:
- `src/release/mdcharm`

## Run
```bash
./src/release/mdcharm
```

## Troubleshooting
- If qmake is missing, install `qt5-tools` (Arch) or `qttools5-dev qttools5-dev-tools` (Debian/Ubuntu).
- If linking fails for Hunspell, ensure `libhunspell-1.7` (or matching -dev) is installed.
- If WebEngine headers are missing, install `qt5-webengine` (Arch) or `qtwebengine5-dev` (Debian/Ubuntu).
- Ensure Python 3 is the default `python` on Arch, or invoke scripts with `python3`.
