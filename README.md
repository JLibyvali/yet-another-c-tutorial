# How to write (or not write) a C/C++ Project

## Prerequisites

- A text editor (preferably vim, a plain [Notepad](https://en.wikipedia.org/wiki/Windows_Notepad) could also do its jobs)
- Know what a shell is (cmd, bash, powershell, etc.)

### Don't

- [DevC++](https://www.bloodshed.net/) (just a wrapper over gcc)
- [CodeBlocks](https://www.codeblocks.org/) (same as above)
- [Visual Studio](https://visualstudio.microsoft.com/) (too complicated, `sln` is mandatory)
- [Keil](https://www.keil.com/) (proprietary outdated stuff and we don't do embedded stuff here yet)
- [Microsoft Visual C++ 6.0](https://news.microsoft.com/1998/06/29/microsoft-introduces-visual-c-6-0/) (what...? It's from 1998!)

Avoid other thing you call an IDE for now.

Don't use [Visual Studio Code](https://code.visualstudio.com/) with fancy extensions until you know what you're doing. You could still use it as a text editor.

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

You have several choices. Native [LLVM](https://llvm.org/) or
[MinGW](https://www.mingw-w64.org/). Note that they are different targets so not
binary compatible (`x86_64-pc-windows-msvc` and `x86_64-w64-windows-gnu`) and
you might have problem when linking libraries compiled with different targets.

Choose latter if you need to use [`gcc`](https://gcc.gnu.org/). I will introduce both.

#### [LLVM](https://llvm.org/)

##### Install Visual Studio Build Tools

First you have to install [Build Tools for Visual Studio](https://visualstudio.microsoft.com/downloads/?q=build+tools) (in the
*Tools for Visual Studio* section instead of *Visual Studio*). Don't confuse it
with Visual Studio IDE, though installing the latter will also install the
former.

Once you have install the *Visual Studio Installer*, select *Desktop development
with C++* (which has `MSVC`, `Clang`, `CMake` and `MSBuild` in its description)
and install it. (Remember you don't have to install the whole Visual Studio IDE)

See [Install C and C++ support in Visual Studio](https://learn.microsoft.com/en-us/cpp/build/vscpp-step-0-installation?view=msvc-170) for more details.

##### Install LLVM

If you don't select *C++ Clang Compiler for Windows* (in fact I don't recommend select that but download by yourself) you could install LLVM manually. Find [LLVM release in GitHub](https://github.com/llvm/llvm-project/releases). Find Windows
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

If you installed `clang` without Visual Studio stuff `clang` will complain it cannot find headers and libraries when compiling.

```powershell
clang: warning: unable to find a Visual Studio installation; try running Clang from a developer command prompt [-Wmsvc-not-found]
main.c:1:10: fatal error: 'stdio.h' file not found
    1 | #include <stdio.h>
      |          ^~~~~~~~~
1 error generated.
```

You're good to go.

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

##### Difference between environments and targets

The section is for nerd. Feel free to skip it.

- Different C++ standard library. `mingw64` uses `libstdc++` while `clang64` uses `libc++`. 
- Different C Runtime Library. `mingw64` uses `msvcrt` while `clang64` an `uart64` uses `ucrt`.

Note the target we mentioned above. The compilers installed with two different
methods are actually different targets.  `x86_64-pc-windows-msvc` and
`x86_64-w64-windows-gnu` (i.e. `x86_64-w64-mingw32` which is
[MinGW-w64](https://www.mingw-w64.org/)) are NOT binary compatible (?). You
might need to recompile your dependencies if you switch between them. 

```powershell
# use https://github.com/lucasg/Dependencies to check dependencies
# x86_64-w64-windows-gnu
PS > Dependencies -depth 1 -modules "C:\msys64\ucrt64\bin\clang.exe"
[ROOT] clang.exe : C:\msys64\ucrt64\bin\clang.exe
[ApiSetSchema] api-ms-win-crt-environment-l1-1-0.dll : C:\WINDOWS\system32\ucrtbase.dll
[ApiSetSchema] api-ms-win-crt-heap-l1-1-0.dll : C:\WINDOWS\system32\ucrtbase.dll
[ApiSetSchema] api-ms-win-crt-math-l1-1-0.dll : C:\WINDOWS\system32\ucrtbase.dll
[ApiSetSchema] api-ms-win-crt-private-l1-1-0.dll : C:\WINDOWS\system32\ucrtbase.dll
[ApiSetSchema] api-ms-win-crt-runtime-l1-1-0.dll : C:\WINDOWS\system32\ucrtbase.dll
[ApiSetSchema] api-ms-win-crt-stdio-l1-1-0.dll : C:\WINDOWS\system32\ucrtbase.dll
[ApiSetSchema] api-ms-win-crt-string-l1-1-0.dll : C:\WINDOWS\system32\ucrtbase.dll
[ApiSetSchema] api-ms-win-crt-time-l1-1-0.dll : C:\WINDOWS\system32\ucrtbase.dll
[WellKnownDlls] KERNEL32.dll : C:\WINDOWS\system32\kernel32.dll
[ApplicationDirectory] libstdc++-6.dll : C:\msys64\ucrt64\bin\libstdc++-6.dll
[ApplicationDirectory] libclang-cpp.dll : C:\msys64\ucrt64\bin\libclang-cpp.dll
[ApplicationDirectory] libLLVM-16.dll : C:\msys64\ucrt64\bin\libLLVM-16.dll

# x86_64-pc-windows-msvc
PS > Dependencies -depth 1 -modules "C:\Program Files\LLVM\bin\clang.exe"
[ROOT] clang.exe : C:\Program Files\LLVM\bin\clang.exe
[ApiSetSchema] api-ms-win-crt-stdio-l1-1-0.dll : C:\WINDOWS\system32\ucrtbase.dll
[ApiSetSchema] api-ms-win-crt-runtime-l1-1-0.dll : C:\WINDOWS\system32\ucrtbase.dll
[ApiSetSchema] api-ms-win-crt-math-l1-1-0.dll : C:\WINDOWS\system32\ucrtbase.dll
[ApiSetSchema] api-ms-win-crt-time-l1-1-0.dll : C:\WINDOWS\system32\ucrtbase.dll
[ApiSetSchema] api-ms-win-crt-heap-l1-1-0.dll : C:\WINDOWS\system32\ucrtbase.dll
[ApiSetSchema] api-ms-win-crt-filesystem-l1-1-0.dll : C:\WINDOWS\system32\ucrtbase.dll
[ApiSetSchema] api-ms-win-crt-string-l1-1-0.dll : C:\WINDOWS\system32\ucrtbase.dll
[ApiSetSchema] api-ms-win-crt-convert-l1-1-0.dll : C:\WINDOWS\system32\ucrtbase.dll
[ApiSetSchema] api-ms-win-crt-environment-l1-1-0.dll : C:\WINDOWS\system32\ucrtbase.dll
[ApiSetSchema] api-ms-win-crt-utility-l1-1-0.dll : C:\WINDOWS\system32\ucrtbase.dll
[ApiSetSchema] api-ms-win-crt-locale-l1-1-0.dll : C:\WINDOWS\system32\ucrtbase.dll
[WellKnownDlls] KERNEL32.dll : C:\WINDOWS\system32\kernel32.dll
[WellKnownDlls] ADVAPI32.dll : C:\WINDOWS\system32\advapi32.dll
[WellKnownDlls] OLEAUT32.dll : C:\WINDOWS\system32\OLEAUT32.dll
[WellKnownDlls] SHELL32.dll : C:\WINDOWS\system32\SHELL32.dll
[WellKnownDlls] ole32.dll : C:\WINDOWS\system32\ole32.dll
[ApplicationDirectory] MSVCP140.dll : C:\Program Files\LLVM\bin\MSVCP140.dll
[ApplicationDirectory] VCRUNTIME140.dll : C:\Program Files\LLVM\bin\VCRUNTIME140.dll
[ApplicationDirectory] VCRUNTIME140_1.dll : C:\Program Files\LLVM\bin\VCRUNTIME140_1.dll
[WindowsFolder] VERSION.dll : C:\WINDOWS\system32\VERSION.dll
```

The obvious difference is `libstdc++-6.dll` and `MSVCP140.dll`. The latter is from MSVC since `libc++` is not available in Windows (yet).

#### [WSL](https://docs.microsoft.com/en-us/windows/wsl/install-win10) or [Docker](https://www.docker.com/)

You could use [WSL](https://docs.microsoft.com/en-us/windows/wsl/install-win10) (Windows Subsystem for Linux) to get full Linux experience. 
Because the rest is the same as [Linux](#linux), I won't talk about it here.

#### Notes

- [Using Clang on Windows for C++](https://wetmelon.github.io/clang-on-windows.html)
- Like fancy terminal? See [Terminals](https://www.msys2.org/docs/terminals/). I recommend [Windows Terminal](https://github.com/microsoft/terminal).
- You could search your MSYS2 packages [here](https://packages.msys2.org/queue).
- [what is the difference between x86_64-pc-windows-msvc and x86_64-pc-windows-gnu targets in clang](https://stackoverflow.com/questions/73184707/what-is-the-difference-between-x86-64-pc-windows-msvc-and-x86-64-pc-windows-gnu)
- [What's the difference between windows-gnu and windows-msvc release?](https://github.com/sharkdp/fd/issues/726)
- [C/C++标准库](https://zhuanlan.zhihu.com/p/566419668)
- [Understanding the different flavors of Clang C and C++ compilers in Windows](https://blog.conan.io/2022/10/13/Different-flavors-Clang-compiler-Windows.html)
- [How run clang from command line on Windows?](https://stackoverflow.com/questions/18711595/how-run-clang-from-command-line-on-windows)

### Linux

#### RHEL/CentOS/Fedora

[`yum`](https://en.wikipedia.org/wiki/Yellowdog_Updater,_Modified) should be deprecated. Use [`dnf`](https://en.wikipedia.org/wiki/DNF_(software)) instead.

```bash
sudo dnf install clang
```

Common development tools

```bash
sudo dnf groupinstall "Development Tools"
```

#### Debian/Ubuntu

```bash
sudo apt update
sudo apt install clang
clang --version
```

Common development tools

```bash
sudo apt build-essential
```

#### Arch 

```bash
sudo pacman -Syu
sudo pacman -S clang
clang --version
```

Common development tools

```bash
sudo pacman -S base-devel
```

### macOS

Xcode comes with llvm. If you haven't installed it you could install Xcode Command Line Tools with following command.

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

- [深入淺出 Xcode Command Lines Tool(1) - 初探](https://jamesdouble.github.io/blog/2019/12/19/xcCmdLine-1/)

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
# -lc++ means link `libc++` which is the C++ standard library for clang
clang -o hello hello.cpp -lc++
# gcc use `libstdc++` instead
gcc -o hello hello.cpp -lstdc++
```

What's `libc++` and `libstdc++` you may ask?

```bash
# macOS
$ otool -L hello 

hello:
        /usr/lib/libc++.1.dylib (compatibility version 1.0.0, current version 1500.65.0)        # <<= libc++
        /usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 1319.100.3)
```

```bash
# linux
$ ldd hello

        linux-vdso.so.1 (0x0000007f9d58c000)
        libstdc++.so.6 => /lib/aarch64-linux-gnu/libstdc++.so.6 (0x0000007f9d2f0000)    # <<= libstdc++
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

### Third-party Library

#### [`pkg-config`](https://www.freedesktop.org/wiki/Software/pkg-config/)

UNIX exclusive tool. Skip it if you're using Windows.

System libraries. [pkgs.org](https://pkgs.org/) to search for packages.

- [apt](https://en.wikipedia.org/wiki/APT_(software)) based (Debian, Ubuntu) convention: `lib<name>-dev` for development files, `lib<name>` for runtime files. 
- [RPM](https://en.wikipedia.org/wiki/RPM_Package_Manager) based (CentOS, Fedora) convention: `lib<name>-devel` for development files, `lib<name>` for runtime files. 
- [pacman](https://wiki.archlinux.org/title/Pacman) based (archlinux, Manjaro) convention: `lib<name>` for both development and runtime files.
- [Homebrew](https://brew.sh/) based convention: `lib<name>` for both development and runtime files.

TODO: A example of using a third-party library like [libcurl](https://curl.se/libcurl/).

#### `vckpg`

[vckpg](https://vcpkg.io/en/) is more useful in Windows. In Linux we have our system package manager.

#### [`nix`](https://nixos.org/)

Nix is special since it could run on any distro without messing up your system packages. A functional package manager per say.

TODO: Package management made easy. Docker is also a good choice.

TODO: OpenCV example.


## CMake

I will skip Makefile and go straight to [CMake](https://cmake.org). No one writes Makefile by hand
anymore. Other tools like [meson](https://mesonbuild.com), [bazel](https://bazel.build), [xmake](https://xmake.io), etc. are also good, but I'll just
use CMake.

TODO: Include Path, Library Path, C flags, Target, etc.

## Visual Studio Code

TODO: Use `clangd` as language server. ~~Or just use [Clion](https://www.jetbrains.com/clion/).~~

See [settings.template.jsonc](src/Library/.vscode/settings.template.jsonc) for example.

change `settings.template.jsonc` to `settings.json` and modify it to your needs.

About Visual Studio Code settings, see [*User and Workspace Settings*](https://code.visualstudio.com/docs/getstarted/settings).


## Embeded Stuff

TODO: ldscript, gdb, convert Keil project to CMake, etc.

TODO: a minimal example for Arduino Uno or STM32 Bluepill. Of course do it
without stupid Arduino IDE or STM32CubeMX or PlatformIO.

Note: I didn't realize [Keil MDK v6 Community Edition](https://www.keil.arm.com/) and a new build system called [cSolution](https://github.com/ARM-software/vscode-cmsis-csolution) have been released for a while.
