#pragma once

// si
#include <catta/modbus/si/response/ReadError.hpp>

// gui
#include <catta/gui/CsvLogging.hpp>
#include <catta/gui/Value.hpp>

// fltk
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Native_File_Chooser.H>
#include <FL/fl_ask.H>

// std
#include <array>
#include <functional>
#include <optional>
#include <string>

namespace catta
{
namespace gui
{
/**
 * @brief Error shows errors.
 * @author CattaTech - Maik Urbannek
 */
class Error : public Fl_Group
{
  public:
    /**
     * @param[in] X The x coordinate of the widget.
     * @param[in] Y The y coordinate of the widget.
     * @param[in] W The width of the widget.
     * @param[in] H The height of the widget.
     * Constructor.
     */
    Error(const int X, const int Y, const int W, const int H) : Fl_Group(X, Y, W, H, nullptr), _currentTime(std::chrono::microseconds::zero())
    {
        static constexpr int GAP = 5;
        static constexpr int H_LINE = 65;

        static const int PER_LINE = 4;
        const int W_WRITE = (W - (PER_LINE + 1) * GAP) / PER_LINE;

        static const int W_UNIT = 1;
        for (int x = 0; x < 4; x++)
            for (int y = 0; y < 5; y++)
            {
                const std::size_t i = static_cast<std::size_t>(x * 5 + y);
                _value[i] = new Value(X + GAP + (x % PER_LINE) * (GAP + W_WRITE), Y + H_LINE * (y + 1), W_WRITE, H_LINE, NAME_LABEL[i], W_UNIT);
            }

        _save = new Fl_Button(X + GAP + 3 * (GAP + W_WRITE), Y + H_LINE * 7, W_WRITE, 45, "Save Error Log");
        _save->callback(savecb, this);
        _save->hide();
        this->end();
        this->show();
    }
    /**
     * Destructor.
     */
    ~Error()
    {
        delete _save;
        for (std::size_t i = 0; i < SIZE; i++) delete _value[i];
    }
    /**
     * @param[in] data The error to set.
     */
    void setError(const catta::modbus::si::response::ReadError data) noexcept
    {
        if (data.isEmpty())
            _save->hide();
        else
            _save->show();
        _data = data;
        const auto string = [](const catta::modbus::sunspec::ValueU16 value) -> std::string {
            return value.isEmpty() ? "" : value.value() == 0xffff ? "----" : std::to_string(static_cast<std::uint32_t>(value.value()));
        };
        for (std::size_t i = 0; i < SIZE; i++) _value[i]->set(string(data.raw()[i]), nullptr);
    }
    /**
     * @param[in] now The current time.
     * @param[in] stringManufacturer The manufacturer string.
     * @param[in] stringModel The model string.
     * @param[in] stringSerialNumber The serial number string.
     */
    void work(const std::chrono::microseconds now, const catta::modbus::sunspec::String32::Raw& stringManufacturer,
              const catta::modbus::sunspec::String32::Raw& stringModel, const catta::modbus::sunspec::String32::Raw& stringSerialNumber)
    {
        _stringManufacturer = stringManufacturer;
        _stringModel = stringModel;
        _stringSerialNumber = stringSerialNumber;
        _currentTime = now;
    }

  private:
    static constexpr std::uint8_t SIZE = catta::modbus::si::response::ReadError::SIZE;

    Fl_Button* _save;
    std::array<Value*, SIZE> _value;
    catta::gui::CsvLogging _csvLogging;

    std::chrono::microseconds _currentTime;
    catta::modbus::sunspec::String32::Raw _stringManufacturer;
    catta::modbus::sunspec::String32::Raw _stringModel;
    catta::modbus::sunspec::String32::Raw _stringSerialNumber;
    catta::modbus::si::response::ReadError _data;

    static constexpr std::array<const char*, SIZE> NAME_LABEL = {
        "AC_Max",        "AC_Min",    "DC_Max",   "DC_Min",    "Freq_Max", "Freq_Min",     "OT1",          "OT2",     "OT3",     "OT4-UACDIFF",
        "OT5_CURENSENS", "COM-error", "Grid-OFF", "Ext.P.Red", "Rds_off",  "Over_Current", "High_Pac_REL", "SDLATCH", "AVERAGE", "OVERHEAT"};

    static std::string getDate(const std::chrono::microseconds now)
    {
        std::chrono::system_clock::time_point utc_time = std::chrono::time_point<std::chrono::system_clock>(now);
        auto local_zone = std::chrono::current_zone();
        std::chrono::zoned_time local_time{local_zone, floor<std::chrono::seconds>(utc_time)};
        std::string datetime = std::format("{:%Y-%m-%d_%H:%M:%S}", local_time);
        return datetime;
    }

    static void savecb(Fl_Widget*, void* object)
    {
        Error* error = static_cast<Error*>(object);
        if (!error) return;
        Fl_Native_File_Chooser chooser;
        chooser.title("Choose csv logging file");
        chooser.type(Fl_Native_File_Chooser::BROWSE_SAVE_FILE);
        chooser.filter("TXT\t*.txt\n");
        chooser.options(Fl_Native_File_Chooser::SAVEAS_CONFIRM);
        const std::string preset = std::string("Error-") + std::string(error->_stringModel.data()) + "-" +
                                   std::string(error->_stringSerialNumber.data()) + "-" + getDate(error->_currentTime) + ".txt";
        chooser.preset_file(preset.c_str());
        const auto right = [](const std::string& name)
        {
            std::string s;
            for (std::size_t i = 0; i < 15; i++) s += i < name.size() ? name[i] : ' ';
            return s;
        };
        const auto left = [](const std::uint16_t value) -> std::string
        {
            if (value == 0x0000) return "    0";
            if (value == 0xffff) return " ----";
            std::string s;
            for (std::uint16_t f = 10000; f > 0; f /= 10)
            {
                const std::uint16_t d = value / f;
                s += d == 0 ? ' ' : static_cast<char>('0' + d % 10);
            }
            return s;
        };
        if (chooser.show() == 0)  // blocking call/ no boackground communication
        {
            std::string content = std::string(error->_stringModel.data()) + "-" + std::string(error->_stringSerialNumber.data()) + "\n\n" +
                                  getDate(error->_currentTime) + "\n\n";
            for (std::size_t y = 0; y < 5; y++)
                for (std::size_t x = 0; x < 4; x++)
                {
                    const std::size_t i = x * 5 + y;
                    content += right(NAME_LABEL[i]);
                    content += ": ";
                    content += left(error->_data.raw()[i].value());
                    content += x == 3 && y < 4 ? "\n" : "     ";
                }

            if (!error->_csvLogging.start(std::string(chooser.filename()), content)) fl_alert("Could not write: %s", chooser.filename());
        }
    }
};
}  // namespace gui
}  // namespace catta
