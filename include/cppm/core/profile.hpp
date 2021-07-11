#pragma once

#ifndef __CPPM_CORE_PROFILE_HPP__
#define __CPPM_CORE_PROFILE_HPP__

#include <serdepp/utility.hpp>
#include "cppm/core/compiler.hpp"

namespace cppm::core {
    struct Profile {
        DERIVE_SERDE(Profile,
                     (&Self::package,  "package",  make_optional)
                     (&Self::compiler, "compiler", make_optional)
                     )
        std::map<std::string, Profile> package;
        std::map<std::string, Compiler> compiler;
    };
};


#endif
