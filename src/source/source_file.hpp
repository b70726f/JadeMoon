#pragma once

#include <filesystem>
#include <fstream>
#include <limits>
#include <string_view>
#include <utility>
#include <vector>

#include "jm_int.hpp"
#include "source/i_source.hpp"

class SourceFile : public ISource {
    using LineData = std::pair<u16 const, u16 const>;
    using LineDetails = std::vector<LineData>;

public:
    ~SourceFile() = default;
    SourceFile(std::filesystem::path const);

    char at(u32 index) const override;
    char const* data() const override;
    u32 length() const;
    std::string_view line(u16 const) const override;
    void load();

private:
    inline std::vector<char> load_file_to_memory(std::ifstream& file);
    inline void make_metadata();

    LineDetails lines_details_;
    std::filesystem::path const path_;
    std::vector<char> source_;
};