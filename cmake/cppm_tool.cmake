macro(_load_cppm_variable)
  string(REPLACE "\\" "/" HOME "$ENV{HOME}")
  set(CPPM_ROOT ${HOME}/.cppm)
  list(APPEND CMAKE_PREFIX_PATH "${HOME}/.cppm/local/lib/cmake")
  list(APPEND CMAKE_PREFIX_PATH "${HOME}/.cppm/local/lib/pkgconfig")
  list(APPEND CMAKE_MODULE_PATH "${HOME}/.cppm/tool")
endmacro()

function(cppm_load)
    if(NOT EXISTS ${CPPM_ROOT}/tool)
        find_package(Git REQUIRED)
        if(NOT GIT_FOUND)
            message(FATAL_ERROR "git not found!")
        endif()
        message(STATUS "[cppm] Downloading cppm tool")
        execute_process(
            COMMAND ${GIT_EXECUTABLE} clone https://github.com/injae/cppm_tools.git tool --recursive
            WORKING_DIRECTORY ${CPPM_ROOT}
            )
    endif()
    include(download/git)
    git_clone(tool  URL https://github.com/injae/cppm_tools.git PATH ${CPPM_ROOT}             QUIET)
    git_clone(cppkg URL https://github.com/injae/cppkg.git      PATH ${CPPM_ROOT}/.cppm/repo/ QUIET)
endfunction()

macro(cppm_setting)
  _load_cppm_variable()
  cppm_load()
  include(cppm/setting/1.0.5)
  _cppm_setting()
endmacro()

function(find_cppkg)
    cmake_parse_arguments(ARG "" "" "" ${ARGN})
    include(cppkg/find/1.0.5)
    _find_cppkg(${ARG_UNPARSED_ARGUMENTS})
endfunction()

function(cppm_target_define)
    cmake_parse_arguments(ARG "" "" "" ${ARGN})
    include(cppm/target/define/1.0.5)
    _cppm_target_define(${ARG_UNPARSED_ARGUMENTS})
endfunction()

function(cppm_target_dependencies)
    cmake_parse_arguments(ARG "" "" "" ${ARGN})
    include(cppm/target/dependencies/1.0.5)
    _cppm_target_dependencies(${ARG_UNPARSED_ARGUMENTS})
endfunction()

function(cppm_target_install)
    cmake_parse_arguments(ARG "" "" "" ${ARGN})
    include(cppm/target/install/1.0.5)
    _cppm_target_install(${ARG_UNPARSED_ARGUMENTS})
endfunction()

macro(download_package)
    cmake_parse_arguments(ARG "" "" "" ${ARGN})
    _load_cppm_variable()
    include(cppkg/download/1.0.5)
    _download_package(${ARG_UNPARSED_ARGUMENTS})
endmacro()

