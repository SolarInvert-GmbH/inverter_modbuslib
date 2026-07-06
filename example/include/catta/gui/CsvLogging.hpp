#pragma once

// std
#include <cstdio>
#include <string>

// fltk
#include <FL/fl_utf8.h>

namespace catta
{
namespace gui
{

/**
 * @brief Handles csv logging.
 * @author CattaTech - Maik Urbannek
 */
class CsvLogging
{
  public:
    /**
     * Default Contrstructor.
     */
    CsvLogging() : _file() {}

    /**
     * @param[in] file Path to file.
     * @param[in] header Header line.
     */
    bool start(const std::string& file, const std::string& header)
    {
        _file = file;
        return writeline("w", header);
    }

    /**
     * @param content The line content.
     */
    void line(const std::string& content) { writeline("a", content); }

  private:
    std::string _file;
    bool writeline(const char* mode, const std::string& content)
    {
        FILE* fp = fl_fopen(_file.c_str(), mode);
        if (!fp) return false;

        bool ok = std::fputs(content.c_str(), fp) >= 0 && std::fputc('\n', fp) >= 0;

        if (std::fclose(fp) != 0) ok = false;

        return ok;
    }
};
}  // namespace gui
}  // namespace catta
