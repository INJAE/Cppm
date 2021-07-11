#pragma once

#ifndef __CPPM_CORE_COMPILER_HPP__
#define __CPPM_CORE_COMPILER_HPP__

#include <serdepp/utility.hpp>


namespace cppm::core {
    struct Compiler {
        DERIVE_SERDE(Compiler,
                     (&Self::version, "version", value_or_struct)
                     (&Self::option,  "option")
                     )
        std::string version;
        std::string option;
    };
}

#endif
