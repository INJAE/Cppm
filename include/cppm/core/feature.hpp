#pragma once

#ifndef __CPPM_CORE_FEATURES_HPP__
#define __CPPM_CORE_FEATURES_HPP__

#include <serdepp/utility.hpp>
#include <serdepp/attributes.hpp>

namespace cppm::core {
    enum class FeatureType {
        CMAKE_FLAG,
        REMOTE,
    };

    struct Feature {
        template<class Context>
        constexpr static void serde(Context& context, Feature& value) {
            using namespace serde::attribute;
            using Self = Feature;
            serde::serde_struct(context, value)
                (&Self::key,   "key",   value_or_struct)
                (&Self::value, "value", skip)
                (&Self::type,  "type",  skip);
            if constexpr(Context::is_serialize) {
                if(value.key[0] == '$') {
                    value.type = FeatureType::CMAKE_FLAG;
                    value.value = "OFF";
                }
            }
        }
        Feature() = default;
        Feature(const std::string& key_) : key(key_){}

        std::string value;
        std::string key;
        FeatureType type;
    };
}


#endif
