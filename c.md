# How to write (or not write) a C/C++ Project

## Preaqusiites

- A text editor (preferably vim, a plain [Notepad](https://en.wikipedia.org/wiki/Windows_Notepad) could also do it jobs)
- Know what a shell is (cmd, bash, powershell, etc.)

### Don't

- DevC++ (just a wrapper over gcc)
- CodeBlocks (same as above)
- Visual Studio (too complicated, GUI stuff, no good)
- Keil (don't use proprietary outdated stuff)
- Microsoft Visual C++ 6.0 (what...?)

Avoid other thing you call an IDE for now.

Don't use Visual Studio Code until you know what you're doing, we'll get to that later.

### Preprocessing, Compiling, Linking

We won't get into any embeded stuff. Just focus on desktop/commandline application.

As you learned in your traditional C/C++ course

- [Preprocessing](https://en.wikipedia.org/wiki/C_preprocessor)
- [Compiling](https://en.wikipedia.org/wiki/Compiler) 
- [Linking](https://en.wikipedia.org/wiki/Linker_(computing))

We have to get a compiler collection (or toolchain) to do the job.

### Family of compilers

Major

- [GNU Compiler Collection](https://gcc.gnu.org/)
- [Clang](https://clang.llvm.org/)
- [Microsoft Visual C++ (MSVC)](https://en.wikipedia.org/wiki/Microsoft_Visual_C%2B%2B)

Minor

- [Arm Compiler](https://developer.arm.com/tools-and-software/embedded/arm-compiler)
- [IAR Embedded Workbench](https://www.iar.com/iar-embedded-workbench/)
- [Intel C++ Compiler](https://software.intel.com/content/www/us/en/develop/tools/compilers.html)
- [NVIDIA CUDA Compiler](https://developer.nvidia.com/cuda-llvm-compiler)
- [SDCC](http://sdcc.sourceforge.net/) (useful when dealing stupid 8051)

The list could go on and on, but we'll focus on the major ones. Especially GCC and Clang since MSVC is not cross-platform.

See also:

- [Use the Microsoft C++ toolset from the command line](https://learn.microsoft.com/en-us/cpp/build/building-on-the-command-line?view=msvc-170)

## Installations

I will only talk about clang and gcc. MSVC is not cross-platform and I don't use it.

### Windows

Install [MSYS2](https://www.msys2.org/), a unix-like environment for Windows. It provides a package manager (pacman) to install the toolchain.

[Different environment](https://www.msys2.org/docs/environments/). I choose `UCRT64`.

```bash
pacman -Syu
pacman -S mingw-w64-clang
clang --version
```

Or just use [WSL](https://docs.microsoft.com/en-us/windows/wsl/install-win10) (Windows Subsystem for Linux) and install clang on it.

#### Notes

- [Using Clang on Windows for C++](https://wetmelon.github.io/clang-on-windows.html)
- Like fancy terminal? See [Terminals](https://www.msys2.org/docs/terminals/). I recommend [Windows Terminal](https://github.com/microsoft/terminal).
- You could search your packages [here](https://packages.msys2.org/queue).

### Linux

#### Debian/Ubuntu

```bash
sudo apt update
sudo apt install clang
clang --version
```

#### Arch 

```bash
sudo pacman -Syu
sudo pacman -S clang
clang --version
```

### macOS

XCode comes with clang. 

```bash
xcode-select --install 
clang --version
```

## Simple Commandline

### Hello World

I don't explain the code. The point is how to build it.

```c
#include <stdio.h>
int main(){
  printf("Hello World!\n");
}
```

```bash
clang -o hello hello.c
# or gcc
gcc -o hello hello.c 
./hello
```

Simple. `-o` means output to a file called `hello`. If you don't specify it, the output file will be `a.out`.

### Static Library

TODO

## CMake

I will skip Makefile and go straight to CMake. No one writes Makefile by hand
anymore. Other tools like meson, bazel, xmake, etc. are also good, but I'll just
use CMake.

TODO: Include Path, Library Path, C flags, Target, etc.

## Visual Studio Code

TODO: Use `clangd` as language server. ~~Or just use [Clion](https://www.jetbrains.com/clion/).~~

## Nix

TODO: Package management made easy. Docker is also a good choice.

## Embeded Stuff

TODO: ldscript, gdb, convert Keil project to CMake, etc.
