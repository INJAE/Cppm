#include "config/bin.h"
#include "util/filesystem.h"
#include "util/algorithm.hpp"
#include "config/config.h"
#include <string>
#include "util/cmake.h"
#include <fmt/format.h>

namespace cppm
{
    void Bins::parse(table_ptr table) {
        auto table_array = table->get_table_array("bin");
        if(!table_array) return;
        for(const auto& bin_table : *table_array) {
            Bin bin;
            bin.name = *bin_table->get_as<std::string>("name");
            auto source = bin_table->get_array_of<std::string>("source");
            if(source) for(const auto& src : *source) {bin.sources.push_back(src);} 
            list.emplace_back(std::move(bin));
        }
    }

    std::string Bins::generate(Config& config) {
        using namespace fmt::literals;
        using namespace util::cmake;
        std::string gen;
        for(const auto& bin : list) {
            std::vector<std::string> sources;
            for(const auto& src : bin.sources) {
                auto result = util::find_files(config.path.root, std::regex(src), false);
                sources.insert(sources.end(), result.begin(), result.end());
            }
            gen += "set({0}_source {1}\n)"_format(bin.name, util::accumulate(sources, "\n\t"));
            
            gen += "\n\nbuild_binary({0} \"{1}\" \"{2}\")"_format( bin.name
                                                                 ,var(bin.name+"_source")
                                                                 ,var("thirdparty"));
        }
        return gen;
    }
}