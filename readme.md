# Setting Up Godot With C++

- [gdextension_cpp_example](https://docs.godotengine.org/en/stable/tutorials/scripting/cpp/gdextension_cpp_example.html)

## Using godot-cpp Extension

- [godot-cpp](https://github.com/godotengine/godot-cpp)
- Add the repo as a submodule
  - `git submodule add -b 4.5 https://github.com/godotengine/godot-cpp`
- Initialize the submodule
  - `git submodule update --init`

## Build C++ For Godot

- `scons platform=linux compiledb=yes` # or whatever architecture

## Install Python Scons

- On Arch based linux:
  - [AUR-scons](https://archlinux.org/packages/extra/any/scons/)
  - `sudo pacman -Syu scons`

## Clang Intellisense for Godot C++

- `scons compiledb=yes`