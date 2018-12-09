#include "config/lib.h"
#include "util/filesystem.h"
#include "util/algorithm.hpp"
#include "config/config.h"
#include "util/cmake.h"
#include <string>
#include <fmt/format.h>

namespace cppm
{
    void Libs::parse(table_ptr table) {
        auto table_array = table->get_table_array("lib");
        if(!table_array) return;
        for(const auto& lib_table : *table_array) {
            Lib lib;
            lib.name = *lib_table->get_as<std::string>("name");
            lib.type = *lib_table->get_as<std::string>("type");
            auto source = lib_table->get_array_of<std::string>("source");
            if(source) for(const auto& src : *source) {lib.sources.push_back(src);} 
            list.emplace_back(std::move(lib));
        }
    }

    std::string Libs::generate(Config& config) {
        using namespace fmt::literals;
        using namespace util::cmake;
        auto lib_type = [&](std::string type) -> std::string {
                 if(type == "shared")           return "SHARED";
           else  if(type == "static")           return "STATIC";
           else  if(type == "header-only")      return "INTERFACE";
           else                                 return "ERROR";
        };
        std::string gen ="";
        for(const auto& lib : list) {
            std::vector<std::string> sources;
            for(const auto& src : lib.sources) {
                auto result = util::find_files(config.path.root, std::regex(src), false);
                sources.insert(sources.end(), result.begin(), result.end());
            }
            gen += "add_library({0} {1} {2})\n"_format(lib.name, lib_type(lib.type), (lib_type(lib.type) != "INTERFACE") ? "\"\"" : "");
            if(lib_type(lib.type) != "INTERFACE") {
                gen += "target_sources({0}\n\tPRIVATE {1}\n)\n"_format(lib.name, util::accumulate(sources, "\n\t"));
                gen += "set_target_properties({0} PROPERTIES LINKER_LANGUAGE CXX)\n"_format(lib.name);
            }
            gen += "target_link_libraries({0} PUBLIC {1})"_format(lib.name , var("thirdparty"));
            gen += "\n\ntarget_install({0} {1})\n"_format(lib.name, lib_type(lib.type));
        }
        return gen;
    }
}
