#ifndef __CPPM_CONFIG_COMPILER_H__
#define __CPPM_CONFIG_COMPILER_H__

#include "config/base_config.h"
#include <map>
#include <string>

namespace cppm
{
    struct CompilerType 
    {
        std::string name;
        std::string version;
        std::string option;
    };

    class Compiler : public base_config
    {
    public:
        void parse(table_ptr table);
        std::string generate();
         ~Compiler() {} 
    public:
        std::map<std::string, CompilerType> debug_list;
        std::map<std::string, CompilerType> release_list;
    };
}

#endif