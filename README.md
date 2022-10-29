# SDL2 Game Engine
A C++ Game Engine Using SDL2 Framework

### Requirements

- [MinGW] https://www.mingw-w64.org/downloads)
- [SDL](https://github.com/libsdl-org/SDL/releases)
- [SDL_ttf](https://github.com/libsdl-org/SDL_ttf/releases)
- [SDL_mixer](https://github.com/libsdl-org/SDL_mixer/releases)
- [SDL_image](https://github.com/libsdl-org/SDL_image/releases)

### Configuration

##### MacOS

- Download `SDL2 dmg` file, open and copy `SDL2.Framework` to `/Library/Frameworks`
- Download `SDL2_ttf dmg` file, open and copy `SDL2_ttf.Framework` to `/Library/Frameworks`
- Download `SDL2_image dmg` file, open and copy `SDL2_image.Framework` to `/Library/Frameworks`

##### Windows

Follow [this tutorial](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/mingw/index.php)

##### All Systems

- Copy file `templates/Makefile` to root folder and configure as you want.
- Copy file `templates/src/config.hpp` to `src` folder and configure as you want.

### How to Build

- **Mac:** `make mac`
- **Linux:** `make gnu`
- **Windows:** `make win`
