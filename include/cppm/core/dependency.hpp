#pragma once

#ifndef __CPPM_CORE_DEPENDENCY_HPP__
#define __CPPM_CORE_DEPENDENCY_HPP__

#include <serdepp/utility.hpp>
#include <serdepp/attributes.hpp>

#include "cppm/core/feature.hpp"
#include "cppm/core/cppkg.hpp"
#include <algorithm>

namespace cppm::core {

    enum class link_type { PUBLIC, PRIVATE, INTERFACE };
    enum class repo_type { cppkg, hunter, system, vcpkg, workspace };

    struct Dependency {
        DERIVE_SERDE(Dependency,
                     (&Self::version,    "version",  value_or_struct)
                     (&Self::description, "description", default_se{""})
                     (&Self::type,       "type",     default_se{cppkg_type::lib})
                     (&Self::repo,       "repo",     default_se{repo_type::cppkg})
                     (&Self::link,       "link",     default_se{link_type::PRIVATE}, to_lower)
                     (&Self::module,     "module")
                     (&Self::features,   "feature-map", make_optional)
                     (&Self::default_feature, "features", make_optional)
                     (&Self::default_features_flag, "default_features", default_se{true})
                     (&Self::custom,     "custom",   default_se{false})
                     (&Self::no_cmake,   "no_module",default_se{false})
                     (&Self::optional,   "optional", default_se{false})
                     (&Self::components, "components")
                     (&Self::path,       "path")
                     (&Self::git,        "git")
                     (&Self::branch,     "branch")
                     (&Self::url,        "url")
                     (&Self::sha256,     "sha256")
                     (&Self::helper,     "helper")
                     (&Self::flags,      "flags")
                     )

        std::string name;
        cppkg_type type;
        std::string version;
        link_type link;
        repo_type repo;
        std::string description;
        std::map<std::string, std::vector<Feature>> features;
        std::vector<Feature> default_feature;
        std::optional<std::string> components;
        std::optional<std::string> path;

        std::optional<std::string> git;
        std::optional<std::string> branch;

        std::optional<std::string> url;
        std::optional<std::string> sha256;

        std::optional<std::string> helper;
        std::optional<std::string> flags;

        bool custom;
        bool no_cmake;
        bool optional;
        bool default_features_flag;
        std::optional<std::string> module;

    };
}

//namespace serde{
//    using cppm::core::link_type;
//    template<typename serde_ctx>
//    struct serde_serializer<link_type, serde_ctx>{
//        inline static auto from(serde_ctx& ctx, link_type& data, std::string_view key) {
//            std::string buffer = serialize_at<std::string>(ctx.adaptor, key);
//            std::transform(buffer.begin(), buffer.end(), buffer.begin(), ::toupper);
//            data = type::enum_t::from_str<link_type>(buffer);
//        }
//        inline static auto into(serde_ctx& ctx, const link_type& data, std::string_view key) {
//            std::string buffer = std::string{type::enum_t::to_str(data)};
//            std::transform(buffer.begin(), buffer.end(), buffer.begin(), ::tolower);
//            deserialize_by_from<typename serde_ctx::Adaptor>(ctx.adaptor, buffer, key);
//        }
//    };
//}


#endif
