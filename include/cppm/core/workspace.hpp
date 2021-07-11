#pragma once

#ifndef __CPPM_CORE_WORKSPACE_HPP__
#define __CPPM_CORE_WORKSPACE_HPP__


#include <serdepp/utility.hpp>
#include <serdepp/attributes.hpp>

namespace cppm::core {
    struct Workspace {
        DERIVE_SERDE(Workspace, (&Self::member, "member", make_optional).no_remain())
        std::vector<std::string> member;
    };
}

#endif
