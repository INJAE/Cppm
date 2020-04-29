# Dependencies
***[cppkg](https://github.com/injae/cppkg)*** is cppm central package repository  
cppm use it by default to find requested packages  
if you want to use ***[Hunter Package Manage](https://github.com/cpp-pm/hunter)*** manager set repo="hunter"  
you can find package with ***cppm cppkg search***
```console
$ cppm cppkg search -h
Usage:
   cppm cppkg search [--verbose]

Option:
   --all [-a]                      :show all package 
   --help [-h]                     :show cppm commands and options
   --repo [-r] {repo name}         :show {repo_name}'s packages  # cppkg or hunter
```

## Adding a Dependency
add ***[dependencies]*** in your ***cppm.toml***file 
```toml
[dependencies]
fmt = "6.2.0"
```
Re-run ***cppm build***, and Cppm Search yout package thirdparty directory ***thirdparty/fmt/6.2.0/cppkg.toml***  
if can't find it cppm search from ***[cppkg](https://github.com/injae/cppkg)*** repository and copy to ***thirdparty/fmt/6.2.0/cppkg.toml***

You can easily add unregistered packages

if you want to add unregistered package need to make cppkg.toml file
if unregistered package is cmake base package only need 3 config ***version*** ***git or url*** *** module ***
### Example fmt library
6.2.0 version config  
```toml
# thirdparty/fmt/6.2.0/cppkg.toml
[fmt]
version = "6.2.0"
description = "A modern formatting library"
module = "fmt::fmt"
url="https://github.com/fmtlib/fmt/releases/download/6.2.0/fmt-6.2.0.zip"
flags="-DFMT_DOC=OFF -DFMT_TEST=OFF -DFMT_FUZZ=OFF" # (optional) for cmake build fast flags
```

git repository version  
git version dependency always git version check in CMake build step  
```toml
# thirdparty/fmt/git/cppkg.toml
[fmt]
version = "git"
description = "A modern formatting library"
module = "fmt::fmt"
git="https://github.com/fmtlib/fmt.git"
flags="-DFMT_DOC=OFF -DFMT_TEST=OFF -DFMT_FUZZ=OFF" # (optional) for cmake build fast flags
```

Hunter package manager version  
```toml
[dependencies]
fmt = {version="latest", module="fmt::fmt", repo="hunter"}
```



# Dependency Format
```toml
[${name}] 
    version = "x.x.x|git|latest(hunter only)"
    type = "lib(default)|bin|cmake(incomplete)"
    git = "..." # if git version 
    url = "..." # if x.x.x version
    module = "..." # (require)
    link = "public(default)|private|interface"
    custom = "false(default)|true" # this config table export ${name}.cmake.in 
                                   # if you wan't custom ${name}.cmake.in this option set true
    repo = "cppkg(default)|hunter"
    flags="${cmake build flags}"
    components = "..."
```