#pragma once

#ifndef __CPPM_CORE_CONFIG_HPP__
#define __CPPM_CORE_CONFIG_HPP__

#include <serdepp/utility.hpp>
#include <serdepp/attributes.hpp>

#include "cppm/core/package.hpp"
#include "cppm/core/cmake.hpp"
#include "cppm/core/workspace.hpp"
#include "cppm/core/feature.hpp"
#include "cppm/core/dependency.hpp"
#include "cppm/core/cppkg.hpp"
#include "cppm/core/profile.hpp"
#include "cppm/core/target.hpp"
#include "cppm/core/hunter.hpp"

#include "cppm/util/filesystem.h"

namespace cppm::core {
    struct Path
    {
        inline static Path make(const std::string& root_path)  {
          Path path;
          path.root       = root_path;
          path.build      = path.root/"build";
          path.cmake      = path.root/"cmake";
          path.source     = path.root/"src";
          path.include    = path.root/"include";
          path.thirdparty = path.root/"thirdparty";
          return path;
      }
    public:
        fs::path root;
        fs::path build;
        fs::path cmake;
        fs::path source;
        fs::path include;
        fs::path thirdparty;
    };

    struct Config {
        DERIVE_SERDE(Config,
            (&Self::package,          "package")
            (&Self::cmake,            "cmake",       default_se{CMake{}})
            (&Self::hunter,           "hunter")
            (&Self::workspace,        "workspace")
            (&Self::features,         "features",     make_optional) 
            (&Self::dependencies,     "dependencies", make_optional)
            (&Self::dev_dependencies, "dev-dependencies", make_optional)
            (&Self::lib,        "lib")
            (&Self::bins,       "bin",     make_optional)
            (&Self::examples,   "example", make_optional)
            (&Self::benchmarks, "benchmark", make_optional)
            (&Self::tests,      "tests",   make_optional)
            (&Self::profile,    "profile", make_optional)
            (&Self::target,     "target",  make_optional)
        )

        Package package;
        CMake cmake;
        std::optional<Hunter> hunter;
        std::optional<Workspace> workspace;
        std::unordered_map<std::string, std::vector<Feature>> features;
        std::unordered_map<std::string, Dependency> dependencies;
        std::unordered_map<std::string, Dependency> dev_dependencies;
        std::optional<CppkgLib> lib;
        std::vector<CppkgBin> bins;
        std::vector<CppkgExample> examples;
        std::vector<CppkgTest> tests;
        std::vector<CppkgTest> benchmarks;
        std::map<std::string, Profile> profile;
        std::map<std::string, Target> target;
        Path path;

        Config& post_processing(const std::string& config_path);
        static Config load(fs::path config_path);
    };

}

#endif
