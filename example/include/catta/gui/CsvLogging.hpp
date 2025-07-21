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
    void start(const std::string& file, const std::string& header)
    {
        _file = file;
        writeline(std::ios_base::out, header);
    }

    /**
     * @param content The line content.
     */
    void line(const std::string& content) { writeline(std::ios_base::app, content); }

  private:
    std::string _file;
    void writeline(const std::ios_base::openmode mode, const std::string& content)
    {
        std::ofstream outfile;
        outfile.open(_file.c_str(), mode);
        outfile << content.c_str() << '\n';
    }
};
}  // namespace gui
}  // namespace catta
