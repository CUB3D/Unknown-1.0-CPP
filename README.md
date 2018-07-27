# Unknown
A 2D c++ game engine, built using SDL

### Dependencies:
* SDL2
* SDL2_image
* SDL2_TTF
* RapidJSON

### To use:
* Clone the repo:
```
git clone --recursive git@github.com:CUB3D/Unknown-1.0-CPP.git
```
### Linux setup
* Install dependancies

Debian/Ubuntu:
```
sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev libbox2d-dev rapidjson-dev cmake build-essential python
```

Arch:
```
sudo pacman -S libsdl2 libsdl2-image libsdl2-mixer libsdl2-ttf libxbox2d rapidjson cmake g++ python
```
* Setup the project:
```
cd Unknown-1.0-CPP
source tools/env.sh
setup
```
* Build:
```
make build
cd build
cmake ..
make -j 4
```
* Test:
```
test
```
Optionally steps 3 & 4 can be skipped if using clion

### Windows setup
* Download libs
https://www.libsdl.org/release/SDL2-devel-2.0.8-VC.zip
https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.0.14-VC.zip
https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.3-VC.zip
https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-devel-2.0.2-VC.zip
and extract to Libs
* Install Python3.X (Make sure to include debug libs)
If you already have python installed but without debug libs, uninstall and reinstall with debug libs
* Make a directory for buildling
* Open cmake-gui and select the cloned source as the source and the new build directory as the output
* Press Configure (The first time this will fail)
* Manually set the paths for SDL2, SDL2_IMAGE, SDL2_TTF, SDL2_MIXER, PYTHON and BOX2D as well as SDL2MAIN_LIBRARY
* Press configure again
* Press generate
* Press Open Project
