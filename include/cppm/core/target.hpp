#pragma once

#ifndef __CPPM_CORE_TARGET_HPP__
#define __CPPM_CORE_TARGET_HPP__

#include <serdepp/utility.hpp>
#include "cppm/core/dependency.hpp"

namespace cppm::core {
    struct Target {
        DERIVE_SERDE(Target,
                     (&Self::dependencies,     "dependencies",     make_optional)
                     (&Self::dev_dependencies, "dev-dependencies", make_optional)
                     .no_remain()
                     )

        std::unordered_map<std::string, Dependency> dependencies;
        std::unordered_map<std::string, Dependency> dev_dependencies;
    };
}


#endif
