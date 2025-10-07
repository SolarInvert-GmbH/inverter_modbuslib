#pragma once

// std
#include <fstream>
#include <string>

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
        return writeline(std::ios_base::out, header);
    }

    /**
     * @param content The line content.
     */
    void line(const std::string& content) { writeline(std::ios_base::app, content); }

  private:
    std::string _file;
    bool writeline(const std::ios_base::openmode mode, const std::string& content)
    {
        std::ofstream outfile;
        outfile.open(_file.c_str(), mode);
        if (!outfile.is_open()) return false;
        outfile << content.c_str() << '\n';
        return static_cast<bool>(outfile);
    }
};
}  // namespace gui
}  // namespace catta
