# How to write (or not write) a C/C++ Project

## Preaqusiites

- A text editor (preferably vim, a plain [Notepad](https://en.wikipedia.org/wiki/Windows_Notepad) could also do its jobs)
- Know what a shell is (cmd, bash, powershell, etc.)

### Don't

- [DevC++](https://www.bloodshed.net/) (just a wrapper over gcc)
- [CodeBlocks](https://www.codeblocks.org/) (same as above)
- [Visual Studio](https://visualstudio.microsoft.com/) (too complicated, `sln` is mandatory)
- [Keil](https://www.keil.com/) (proprietary outdated stuff and we don't do embedded stuff here yet)
- [Microsoft Visual C++ 6.0](https://news.microsoft.com/1998/06/29/microsoft-introduces-visual-c-6-0/) (what...? It's from 1998!)

Avoid other thing you call an IDE for now.

Don't use [Visual Studio](https://code.visualstudio.com/) Code with fancy extensions until you know what you're doing. You could still use it as a text editor.

We won't get into any embedded stuff (yet!). 
For now just focus on desktop/commandline application.

### Preprocessing, Compiling, Linking

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

You have several choices. Native [LLVM](https://llvm.org/) or [MinGW](https://www.mingw-w64.org/). Choose latter if you need to use [`gcc`](https://gcc.gnu.org/). I will introduce both.

#### [LLVM](https://llvm.org/)

Find [LLVM release in GitHub](https://github.com/llvm/llvm-project/releases). Find Windows
installer called `LLVM-<version>.win64.exe`. (like [`LLVM-17.0.1-win64.exe`](https://github.com/llvm/llvm-project/releases/download/llvmorg-17.0.1/LLVM-17.0.1-win64.exe))
I assume you install it to `C:\Program Files\LLVM` so `clang` should be `C:\Program Files\LLVM\bin\clang.exe`.

To know where your `clang` is, use [`get-command`](https://learn.microsoft.com/en-us/powershell/module/microsoft.powershell.core/get-command) in PowerShell.

```powershell
PS > get-command clang | select source

Source
------
C:\Program Files\LLVM\bin\clang.exe

PS > clang -v
clang version 17.0.1
Target: x86_64-pc-windows-msvc
Thread model: posix
InstalledDir: C:\Program Files\LLVM\bin
```

You're good to go.

Note: Of course there're other ways to get yourself a LLVM environment. As described in [Building Zig on Windows](https://github.com/ziglang/zig/wiki/Building-Zig-on-Windows).

#### MSYS2

Install [MSYS2](https://www.msys2.org/), a unix-like environment for Windows. It provides a package manager (`pacman`) to install the toolchain.

MSYS2 comes with [different environment](https://www.msys2.org/docs/environments/). Choose your favorite one. I'll recommend `uart64` but `mingw64` seems has better compatibility.

Launch the terminal corresponding to your environment. (e.g. `MSYS2 MinGW UCRT x64`). If it's slow when updating the package database, try to apply [one of the Chinese mirror](https://mirrors.tuna.tsinghua.edu.cn/help/msys2/), or set `HTTP_PROXY` and `HTTPS_PROXY` environment variable if you're behind a proxy.

```bash
pacman -Syu # update the package database and upgrade some package
# see https://packages.msys2.org/base/mingw-w64-clang
pacman -S mingw-w64-ucrt-x86_64-clang
```

```bash
$ clang -v
clang version 16.0.5
Target: x86_64-w64-windows-gnu
Thread model: posix
InstalledDir: C:/msys64/ucrt64/bin
```

If you want to use `gcc`.

```bash
# https://packages.msys2.org/base/mingw-w64-gcc
pacman -S mingw-w64-ucrt-x86_64-gcc
```

```bash
$ gcc -v
Using built-in specs.
COLLECT_GCC=C:\msys64\ucrt64\bin\gcc.exe
COLLECT_LTO_WRAPPER=C:/msys64/ucrt64/bin/../lib/gcc/x86_64-w64-mingw32/13.2.0/lto-wrapper.exe
Target: x86_64-w64-mingw32
Configured with: ../gcc-13.2.0/configure --prefix=/ucrt64 --with-local-prefix=/ucrt64/local --build=x86_64-w64-mingw32 --host=x86_64-w64-mingw32 --target=x86_64-w64-mingw32 --with-native-system-header-dir=/ucrt64/include --libexecdir=/ucrt64/lib --enable-bootstrap --enable-checking=release --with-arch=nocona --with-tune=generic --enable-languages=c,lto,c++,fortran,ada,objc,obj-c++,jit --enable-shared --enable-static --enable-libatomic --enable-threads=posix --enable-graphite --enable-fully-dynamic-string --enable-libstdcxx-filesystem-ts --enable-libstdcxx-time --disable-libstdcxx-pch --enable-lto --enable-libgomp --disable-libssp --disable-multilib --disable-rpath --disable-win32-registry --disable-nls --disable-werror --disable-symvers --with-libiconv --with-system-zlib --with-gmp=/ucrt64 --with-mpfr=/ucrt64 --with-mpc=/ucrt64 --with-isl=/ucrt64 --with-pkgversion='Rev2, Built by MSYS2 project' --with-bugurl=https://github.com/msys2/MINGW-packages/issues --with-gnu-as --with-gnu-ld --disable-libstdcxx-debug --with-boot-ldflags=-static-libstdc++ --with-stage1-ldflags=-static-libstdc++
Thread model: posix
Supported LTO compression algorithms: zlib zstd
gcc version 13.2.0 (Rev2, Built by MSYS2 project)
```

Note the target here. `x86_64-pc-windows-msvc` and `x86_64-w64-windows-gnu`
(i.e. `x86_64-w64-mingw32` which is [MinGW-w64](https://www.mingw-w64.org/)) are
NOT binary compatible (?). You might need to recompile your dependencies if you
switch between them. 

```bash
# x86_64-w64-windows-gnu
ldd /ucrt64/bin/clang
        ntdll.dll => /c/WINDOWS/SYSTEM32/ntdll.dll (0x7fffa6e70000)
        KERNEL32.DLL => /c/WINDOWS/System32/KERNEL32.DLL (0x7fffa6020000)
        KERNELBASE.dll => /c/WINDOWS/System32/KERNELBASE.dll (0x7fffa43d0000)
        apphelp.dll => /c/WINDOWS/SYSTEM32/apphelp.dll (0x7fffa12c0000)
        ucrtbase.dll => /c/WINDOWS/System32/ucrtbase.dll (0x7fffa4780000)
        libstdc++-6.dll => /ucrt64/bin/libstdc++-6.dll (0x7ffef6e50000)
        libgcc_s_seh-1.dll => /ucrt64/bin/libgcc_s_seh-1.dll (0x7fff929f0000)
        libwinpthread-1.dll => /ucrt64/bin/libwinpthread-1.dll (0x7fff92c20000)
        libwinpthread-1.dll => /ucrt64/bin/libwinpthread-1.dll (0x1ac9a730000)
        libclang-cpp.dll => /ucrt64/bin/libclang-cpp.dll (0x7ffef3ab0000)
        VERSION.dll => /c/WINDOWS/SYSTEM32/VERSION.dll (0x7fff99e30000)
        msvcrt.dll => /c/WINDOWS/System32/msvcrt.dll (0x7fffa6370000)
        libLLVM-16.dll => /ucrt64/bin/libLLVM-16.dll (0x7ffee9cf0000)
        libLLVM-16.dll => /ucrt64/bin/libLLVM-16.dll (0x1ac9a8b0000)
        ADVAPI32.dll => /c/WINDOWS/System32/ADVAPI32.dll (0x7fffa58a0000)
        sechost.dll => /c/WINDOWS/System32/sechost.dll (0x7fffa5730000)
        RPCRT4.dll => /c/WINDOWS/System32/RPCRT4.dll (0x7fffa5610000)
        ole32.dll => /c/WINDOWS/System32/ole32.dll (0x7fffa60f0000)
        msvcp_win.dll => /c/WINDOWS/System32/msvcp_win.dll (0x7fffa4330000)
        GDI32.dll => /c/WINDOWS/System32/GDI32.dll (0x7fffa5870000)
        win32u.dll => /c/WINDOWS/System32/win32u.dll (0x7fffa4ba0000)
        gdi32full.dll => /c/WINDOWS/System32/gdi32full.dll (0x7fffa48a0000)
        USER32.dll => /c/WINDOWS/System32/USER32.dll (0x7fffa6580000)
        combase.dll => /c/WINDOWS/System32/combase.dll (0x7fffa5b10000)
        SHELL32.dll => /c/WINDOWS/System32/SHELL32.dll (0x7fffa4e10000)
        libffi-8.dll => /ucrt64/bin/libffi-8.dll (0x7fff928c0000)
        zlib1.dll => /ucrt64/bin/zlib1.dll (0x7fff928a0000)
        libzstd.dll => /ucrt64/bin/libzstd.dll (0x7fff87bd0000)
        libxml2-2.dll => /ucrt64/bin/libxml2-2.dll (0x7fff71940000)
        WS2_32.dll => /c/WINDOWS/System32/WS2_32.dll (0x7fffa57e0000)
        liblzma-5.dll => /ucrt64/bin/liblzma-5.dll (0x7fff92640000)
        libiconv-2.dll => /ucrt64/bin/libiconv-2.dll (0x7fff71ba0000)

# x86_64-pc-windows-msvc
ldd "C:\Program Files\LLVM\bin\clang.exe"
        ntdll.dll => /c/WINDOWS/SYSTEM32/ntdll.dll (0x7fffa6e70000)
        KERNEL32.DLL => /c/WINDOWS/System32/KERNEL32.DLL (0x7fffa6020000)
        KERNELBASE.dll => /c/WINDOWS/System32/KERNELBASE.dll (0x7fffa43d0000)
        ADVAPI32.dll => /c/WINDOWS/System32/ADVAPI32.dll (0x7fffa58a0000)
        msvcrt.dll => /c/WINDOWS/System32/msvcrt.dll (0x7fffa6370000)
        sechost.dll => /c/WINDOWS/System32/sechost.dll (0x7fffa5730000)
        MSVCP140.dll => /c/Program Files/LLVM/bin/MSVCP140.dll (0x7fff87c60000)
        RPCRT4.dll => /c/WINDOWS/System32/RPCRT4.dll (0x7fffa5610000)
        ucrtbase.dll => /c/WINDOWS/System32/ucrtbase.dll (0x7fffa4780000)
        OLEAUT32.dll => /c/WINDOWS/System32/OLEAUT32.dll (0x7fffa6290000)
        msvcp_win.dll => /c/WINDOWS/System32/msvcp_win.dll (0x7fffa4330000)
        VCRUNTIME140.dll => /c/Program Files/LLVM/bin/VCRUNTIME140.dll (0x7fff92830000)
        combase.dll => /c/WINDOWS/System32/combase.dll (0x7fffa5b10000)
        VCRUNTIME140_1.dll => /c/Program Files/LLVM/bin/VCRUNTIME140_1.dll (0x7fff92c30000)
        VERSION.dll => /c/WINDOWS/SYSTEM32/VERSION.dll (0x7fff99e30000)
```

##### Difference between environments

- Different C++ standard library. `mingw64` uses `libstdc++` while `clang64` uses `libc++`. 
- Different C Runtime Library. `mingw64` uses `msvcrt` while `clang64` an `uart64` uses `ucrt`.

#### [WSL](https://docs.microsoft.com/en-us/windows/wsl/install-win10) or [Docker](https://www.docker.com/)

You could use [WSL](https://docs.microsoft.com/en-us/windows/wsl/install-win10) (Windows Subsystem for Linux) to get full Linux experience. 
Because the rest is the same as [Linux](#linux), I won't talk about it here.

#### Notes

- [Using Clang on Windows for C++](https://wetmelon.github.io/clang-on-windows.html)
- Like fancy terminal? See [Terminals](https://www.msys2.org/docs/terminals/). I recommend [Windows Terminal](https://github.com/microsoft/terminal).
- You could search your MSYS2 packages [here](https://packages.msys2.org/queue).
- [what is the difference between x86_64-pc-windows-msvc and x86_64-pc-windows-gnu targets in clang](https://stackoverflow.com/questions/73184707/what-is-the-difference-between-x86-64-pc-windows-msvc-and-x86-64-pc-windows-gnu)
- [What's the difference between windows-gnu and windows-msvc release?](https://github.com/sharkdp/fd/issues/726)

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

Simple stuff that doesn't need a build system. 

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

TODO: see [Library](src/Library). A example of writing a library and use it.

```bash
# from clang help message
 -c                      Only run preprocess, compile, and assemble steps

clang -c -o hello.o hello.c
clang -o hello hello.o --verbose
# you will find it just calls ld
# clang/gcc is just a compiler driver
```

- [What does the "rcs" option in ar do?](https://stackoverflow.com/questions/29714300/what-does-the-rcs-option-in-ar-do)

### [`pkg-config`](https://www.freedesktop.org/wiki/Software/pkg-config/)

TODO: A example of using a third-party library like [libcurl](https://curl.se/libcurl/).

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

Note: I didn't realize [Keil MDK v6 Community Edition](https://www.keil.arm.com/) and a new build system called [cSolution](https://github.com/ARM-software/vscode-cmsis-csolution) have been released for a while.
