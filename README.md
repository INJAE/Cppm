

[Cppm](https://injae.github.io/cppm/) ***(BETA)*** [Documents](https://injae.github.io/cppm/)
========
![Linux](https://github.com/injae/cppm/workflows/Linux/badge.svg) ![Windows](https://github.com/injae/cppm/workflows/Windows/badge.svg) ![MacOS](https://github.com/injae/cppm/workflows/MacOS/badge.svg) 

![](cppm_demo.gif)

## Dependencies
- c++ compiler (c++17)
- CMake (minimum 3.12)
- Git
- Ccache (optional)

> My native language is not English.  
> Since I used a translator, please let me know if you have any problems with grammar.  
> This project was inspired by Rust's Cargo.  
> Cppm is a cross platform C++ project manager  
> So the configuration of the configuration file is almost similar to Rust's Cargo.toml.  
> Using cppm, you can easily create a cross-platform c ++ project.  
> Projects made with cppm only need c ++ compiler, cmake and git.  
> Projects written in cppm automatically install dependencies.   
> Not many libraries are supported by the cppkg yet. But cppkg package make easy  
> So cppm made the package of the [Hunter Package Manager](https://github.com/ruslo/hunter) available.   
> If there is a library you want to add, please issue a pull request to the [Cppkg repository](https://github.com/injae/cppkg)  
> Cppm auto detect vcpkg toolchain.  

## Easy Config file
```toml
# cppm project config file
[package]
name    = "cppm"
version = "0.0.10"
description = "c++ cmake maker use to toml like Cargo"
git = "https://github.com/injae/cppm.git"
#vcpkg =true # vcpkg auto detect flag, but not recommended option

[cmake]
include  = ["cmake/cppm_install.cmake"]

[lib]
name = "cppm-core"
source = ["src/core/.*", "src/util/.*", "src/cppkg/.*"]

[[bin]]
name   = "cppm"
source = ["src/cmake/.*","src/option/.*", "src/util/.*", "src/main.cpp"]

[[test]]
name   = "cppm-test-check"
source = ["tests/test.cpp"]

[[example]]
name   = "cppm-core-load"
source = ["examples/example.cpp"]

[workspace]
    member = ["libs/nlpo", "libs/tomlpp"]

[dependencies]
fmt      = "6.2.0"
hashpp   = "git"
range-v3 = "git"

[dev-dependencies]
    Catch2 = "2.9.1"

#[target.x64-unix.dependencies]
#[target.x64-unix.dev-dependencies]
#[target.x64-windows.dependencies]
#[target.windows.dev-dependencies]
```

## Easy to make Unregistered Package Add
```console
$ cd {package root}/thirdparty
$ cppm cppkg init -U "https://github.com/fmtlib/fmt/releases/download/6.2.0/fmt-6.2.0.zip" fmt
```
```toml
# fmt/6.2.0/cppkg.toml
[fmt]
version = "6.2.0"
description = ""
module = "fmt::fmt"
url="https://github.com/fmtlib/fmt/releases/download/6.2.0/fmt-6.2.0.zip"
```

```console
$ cd {package root}/thirdparty
$ cppm cppkg init -U "https://github.com/fmtlib/fmt.git" fmt
```
```toml
# fmt/git/cppkg.toml
[fmt]
version = "git"
description = ""
module = "fmt::fmt"
git="https://github.com/fmtlib/fmt.git"
flags="-DFMT_DOC=OFF -DFMT_TEST=OFF -DFMT_FUZZ=OFF" # (optional) for cmake build fast flags
```

## Installation
### Linux 
```console
# install c++17 compiler, cmake and git
git clone --recurse-submodules https://github.com/injae/cppm.git
cd cppm
cmake -Bbuild -DCMAKE_BUILD_TYPE=Release
cd build
cmake --build . --config Release
cd Release
./cppm build install
# Adding to cppm path
export PATH="$HOME/.cppm/bin:$PATH"
```


### Macos
```console
# AppleClang not working (can't use filesystem and optional)
brew install llvm cmake
# Adding to llvm clang env
# export CC=#llvm clang path
# export CXX=#llvm clang++ path 
git clone --recurse-submodules https://github.com/injae/cppm.git
cd cppm
cmake -Bbuild -DCMAKE_BUILD_TYPE=Release -DUSE_CPPM_PATH=ON .
cd build
cmake --build . --config Release
cd Release
./cppm build install
# Adding to cppm path
export PATH="$HOME/.cppm/bin:$PATH"
```
### Windows
```console
# need visual studio , git , cmake
# scoop install git cmake
git clone --recurse-submodules https://github.com/injae/cppm.git
cd cppm
cmake -Bbuild -DCMAKE_BUILD_TYPE=Release -DUSE_CPPM_PATH=ON .
cd build
cmake --build . --config Release --target install --target cppm_link
# Add System Path %USERPROFILE%\.cppm\bin
```

## Features
- [x] easy configure file (cppm.toml)
- [x] generate build command (cppm build {options})
- [x] cmake dependencies auto installer (cppkg)
- [x] none cppm base project build (cppm build) (with cppm-toolchain) command
- [x] easy cppkg file generator (cppm cppkg init)
- [x] auto add CMake project uninstall target (cppm build uninstall) (with cppm-toolchain)
- [x] no sudo, package local install path (~/.cppm/)
- [x] unit test option (cppm test)
- [x] Cppkg package search (cppm search)
- [x] cmake project initialize (cppm init {options} {name})
- [x] cppkg repository update (cppm cppkg update)
- [x] hunter package dependency available 
- [x] auto detect vcpkg
- [x] can use hunter package manager 
- [x] sub project option (cppm.toml [workspace])

## Document
### [GitBook](https://injae.github.io/cppm/)
