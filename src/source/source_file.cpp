#include "source/source_file.hpp"

SourceFile::SourceFile(std::filesystem::path const path)
    : lines_details_ {}
    , path_ { path }
    , source_ {}
{
}

char SourceFile::at(u32 index) const
{
    return source_.at(index);
}

char const* SourceFile::data() const
{
    return source_.data();
}

u32 SourceFile::length() const
{
    return source_.size();
}

std::string_view SourceFile::line(u16 const line_number) const
{
    auto [line_start_offset, line_length] = lines_details_.at(line_number);

    return { source_.data() + line_start_offset, line_length };
}

void SourceFile::load()
{
    std::ifstream file {};
    file.open(path_, std::ios::in);

    if (!file.good()) {
        throw std::runtime_error { "Could not open a file" };
    }

    source_ = load_file_to_memory_(file);
    file.close();

    make_metadata_();
}

std::vector<char> SourceFile::load_file_to_memory_(std::ifstream& file)
{
    auto file_buffer = std::vector<char> { std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };
    file_buffer.push_back('\0');
    return file_buffer;
}

void SourceFile::make_metadata_()
{
    u32 line_start_offset = 0;
    u32 file_offset = 0;

    for (auto character : source_) {
        bool eol = (character == '\n');
        bool eof = (file_offset == source_.size() - 1);

        if (eol || eof) {
            u16 line_length = file_offset - line_start_offset;

            if (eof)
                line_length += 1;

            lines_details_.push_back(LineData { line_start_offset, line_length });
            line_start_offset = file_offset + 1;
        }

        ++file_offset;
    }
}