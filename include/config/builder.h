#ifndef __CONFIG_BUILDER_H__
#define __CONFIG_BUILDER_H__

#include<string>
#include<yaml-cpp/yaml.h>

namespace cppm
{
    class Builder
    {
    public:
        static Builder parse(YAML::Node& node);
    public:
          std::string type
        ; std::string cpu_core
        ;
    };
}

#endif