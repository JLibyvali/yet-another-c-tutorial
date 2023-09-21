# How to write (or not write) a C/C++ Project

## Preaqusiites

- A text editor (preferably vim, a plain [Notepad](https://en.wikipedia.org/wiki/Windows_Notepad) could also do its jobs)
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

Install [MSYS2](https://www.msys2.org/), a unix-like environment for Windows. It provides a package manager (`pacman``) to install the toolchain.

[Different environment](https://www.msys2.org/docs/environments/). I choose `UCRT64`.

```bash
pacman -Syu
pacman -S mingw-w64-clang
clang --version
```

Or just use [WSL](https://docs.microsoft.com/en-us/windows/wsl/install-win10) (Windows Subsystem for Linux) and install `clang` on it.

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

Or better, install [Homebrew](https://brew.sh) and install `clang` with it.

```bash
# assuming you have Homebrew installed
brew install llvm

# llvm is keg-only, which means it was not symlinked into /opt/homebrew,
# because macOS already provides this software and installing another version in
# parallel can cause all kinds of trouble.

# If you need to have llvm first in your PATH, run:
#   echo 'export PATH="/opt/homebrew/opt/llvm/bin:$PATH"' >> ~/.zshrc

echo 'export PATH="/opt/homebrew/opt/llvm/bin:$PATH"' >> ~/.zshrc
. ~/.zshrc

# PATH has been changed, check if clang is the one we installed

$ which clang
/opt/homebrew/opt/llvm/bin/clang
```

## Simple Commandline

### Hello World

I don't explain the code. The point is how to build it.

[hello.c](src/HelloWorld/hello.c)

```bash
cd SimpleCommandline/HelloWorld
clang -o hello hello.c
# or gcc
gcc -o hello hello.c 
./hello
```

Simple. `-o` means output to a file called `hello`. If you don't specify it, the output file will be `a.out`.

[hello.cpp](src/HelloWorld/hello.cpp)

C++ would be the same. However, you will need `clang++` to link C++ standard library.

```bash
clang++ -o hello hello.cpp
# or gcc
g++ -o hello hello.cpp
./hello
```

Use `clang` to compile C++ code will result in error.

```bash
clang -o hello hello.cpp

# output
Undefined symbols for architecture arm64:
"std::__1::locale::use_facet(std::__1::locale::id&) const", referenced from:
      std::__1::ctype<char> const& std::__1::use_facet[abi:v15006]<std::__1::ctype<char> >(std::__1::locale const&) in hello-8925e7.o
<more error truncated>
# linker complains it cannot find some symbols.
ld: symbol(s) not found for architecture arm64
clang: error: linker command failed with exit code 1 (use -v to see invocation)
```

You could manually link the C++ standard library though

```bash
# -lc++ means link libc++
clang -o hello hello.cpp -lc++
# gcc
gcc -o hello hello.cpp -lstdc++
```

What's `libc++` you may ask?

```bash
# macOS
$ otool -L hello 

hello:
        /usr/lib/libc++.1.dylib (compatibility version 1.0.0, current version 1500.65.0)
        /usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 1319.100.3)
```

```bash
# linux
$ ldd hello

        linux-vdso.so.1 (0x0000007f9d58c000)
        libstdc++.so.6 => /lib/aarch64-linux-gnu/libstdc++.so.6 (0x0000007f9d2f0000)
        libc.so.6 => /lib/aarch64-linux-gnu/libc.so.6 (0x0000007f9d140000)
        libm.so.6 => /lib/aarch64-linux-gnu/libm.so.6 (0x0000007f9d0a0000)
        libgcc_s.so.1 => /lib/aarch64-linux-gnu/libgcc_s.so.1 (0x0000007f9d060000)
        /lib/ld-linux-aarch64.so.1 (0x0000007f9d54f000)
```

### Library

TODO: see [Library](src/Library)

```bash
# from clang help message
 -c                      Only run preprocess, compile, and assemble steps

clang -c -o hello.o hello.c
clang -o hello hello.o --verbose
# you will find it just calls ld
# clang/gcc is just a compiler driver
```

## CMake

I will skip Makefile and go straight to [CMake](https://cmake.org). No one writes Makefile by hand
anymore. Other tools like [meson](https://mesonbuild.com), [bazel](https://bazel.build), [xmake](https://xmake.io), etc. are also good, but I'll just
use CMake.

TODO: Include Path, Library Path, C flags, Target, etc.

## Visual Studio Code

TODO: Use `clangd` as language server. ~~Or just use [Clion](https://www.jetbrains.com/clion/).~~

See [settings.template.jsonc](src/Library/.vscode/settings.template.jsonc) for example.

change `settings.template.jsonc` to `settings.json` and modify it to your needs.

About Visual Studio Code settings, see "[User and Workspace Settings](https://code.visualstudio.com/docs/getstarted/settings)".

## Nix

TODO: Package management made easy. Docker is also a good choice.

TODO: OpenCV example.

## Embeded Stuff

TODO: ldscript, gdb, convert Keil project to CMake, etc.

TODO: a minimal example for Arduino Uno or STM32 Bluepill. Of course do it
without stupid Arduino IDE or STM32CubeMX or PlatformIO.
