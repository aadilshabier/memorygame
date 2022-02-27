# memorygame
A simple game written in SDL2 Using C++

### Prerequsites
* GCC
* CMake
* SDL2.0

### Instructions
1. Clone the repoistory to your local machine
```shell
$ git clone https://github.com/aadilshabier/memorygame.git
$ cd memorygame
```
2. Build the project
```shell
$ mkdir build
$ cmake -B build
$ make -C build
```
An executable `memorygame` is made inside the `build` directory
3. Run the project
```shell
$ ./build/memorygame
```

### Roadmap
- [x] Check if the game has been won
- [ ] Fix maxxed out CPU usage
- [ ] Make a starting and ending screen
- [ ] Better game screen (counter, timer, etc)
- [ ] Make blocks display textures instead of a solid colour
- [ ] Add background music
- [ ] Make a settings menu
