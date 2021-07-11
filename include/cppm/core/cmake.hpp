#pragma once

#ifndef __CPPM_CORE_CMAKE_HPP__
#define __CPPM_CORE_CMAKE_HPP__

#include <serdepp/utility.hpp>
#include <serdepp/attributes.hpp>

namespace cppm::core {
    struct CMake {
        DERIVE_SERDE(CMake,
            (&Self::version,   "version", default_se{"3.12"})
            (&Self::toolchain, "toolchain")
            (&Self::include,   "include", make_optional)
            .no_remain()
        )

        std::string version = "3.12";
        std::optional<std::string> toolchain;
        std::vector<std::string> include;
    };
}


#endif
