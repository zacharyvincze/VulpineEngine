# VulpineEngine

An in-development, 2D SDL game engine.

## Current Features

-   Entity-component-system for managing entities.
-   Parser for handling engine configuration and loading in data.
-   Basic sprite renderer.
-   Scene management for handling memory allocation and de-allocation of game objects.
-   Sprite definitions via JSON.

## Planned Features

-   Native C++ scripting for game objects.
-   Tile-based mapping engine.
-   General user input manager.
-   Physics system.
-   And more, although this is what I'm working on currently.

## Compilation Instructions

### Install Necessary Dependencies

```bash
sudo apt install libsdl2-dev libsdl2-image-dev cmake make
```

### Compile using CMake

```bash
mkdir -p build
cd build
cmake ..    # or use 'cmake -G "Ninja" ..' for much faster compile times.
make        # or 'ninja' depending on the build system you used.
```

### Running the program

```bash
build//application  # From the repo's root directory.
```
