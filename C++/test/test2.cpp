#include <stdlib.h>

#include <algorithm>
#include <array>
#include <charconv>
#include <cmath>
#include <compare>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <locale>
#include <map>
#include <memory>
#include <numbers>
#include <optional>
#include <set>
#include <span>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
//
#include <iostream>

class SpreadSheetCell {
   public:
    SpreadSheetCell() = default;
    SpreadSheetCell(double initialValue);
    SpreadSheetCell(std::string_view initialValue);

    void setValue(const double value);
    void setString(std::string_view value);
    double getValue() const;
    std::string getString() const;

    SpreadSheetCell add(const SpreadSheetCell& cell) const;
    SpreadSheetCell operator+(const SpreadSheetCell& cell) const;
    SpreadSheetCell operator+(const double rhs) const;
    SpreadSheetCell& operator+=(const SpreadSheetCell& rhs);
    SpreadSheetCell& operator-=(const SpreadSheetCell& rhs);
    SpreadSheetCell& operator*=(const SpreadSheetCell& rhs);
    SpreadSheetCell& operator/=(const SpreadSheetCell& rhs);
    [[nodiscard]] bool operator==(const SpreadSheetCell& rhs) const;
    [[nodiscard]] std::partial_ordering operator<=>(
        const SpreadSheetCell& rhs) const;
    [[nodiscard]] bool operator==(const double rhs) const;
    [[nodiscard]] std::partial_ordering operator<=>(const double rhs) const;
    // [[nodiscard]] auto operator<=>(const SpreadSheetCell&) const = default;

    enum class Color { Red = 1, Green, Blue, Yellow };
    void setColor(Color color);
    Color getColor() const;

   private:
    double stringToDouble(std::string_view value) const;
    std::string doubleToString(double value) const;
    double m_value{0};
    Color m_color{Color::Red};
};

SpreadSheetCell::SpreadSheetCell(double initialValue) : m_value{initialValue} {}

SpreadSheetCell::SpreadSheetCell(std::string_view initialValue) {}

double SpreadSheetCell::stringToDouble(std::string_view value) const {
    double number{0};
    std::from_chars(value.data(), value.data() + value.size(), number);
    return number;
}

std::string SpreadSheetCell::doubleToString(double value) const {
    return std::to_string(value);
}

void SpreadSheetCell::setValue(const double value) { m_value = value; }

void SpreadSheetCell::setString(std::string_view value) {
    m_value = stringToDouble(value);
}

double SpreadSheetCell::getValue() const { return m_value; }

std::string SpreadSheetCell::getString() const {
    return std::to_string(m_value);
}

void SpreadSheetCell::setColor(Color color) { m_color = color; }

SpreadSheetCell::Color SpreadSheetCell::getColor() const { return m_color; }

SpreadSheetCell SpreadSheetCell::add(const SpreadSheetCell& cell) const {
    return SpreadSheetCell{getValue() + cell.getValue()};
}

SpreadSheetCell SpreadSheetCell::operator+(const SpreadSheetCell& cell) const {
    return SpreadSheetCell{getValue() + cell.getValue()};
}

SpreadSheetCell SpreadSheetCell::operator+(const double rhs) const {
    return SpreadSheetCell{getValue() + rhs};
}

SpreadSheetCell operator+(const SpreadSheetCell& lhs,
                          const SpreadSheetCell& rhs) {
    auto result{lhs};
    result += rhs;
    return result;
}

SpreadSheetCell operator/(const SpreadSheetCell& lhs,
                          const SpreadSheetCell& rhs) {
    auto result{lhs};
    result /= rhs;
    return result;
}

SpreadSheetCell& SpreadSheetCell::operator+=(const SpreadSheetCell& rhs) {
    setValue(getValue() + rhs.getValue());
    return *this;
}

SpreadSheetCell& SpreadSheetCell::operator-=(const SpreadSheetCell& rhs) {
    setValue(getValue() - rhs.getValue());
    return *this;
}

SpreadSheetCell& SpreadSheetCell::operator*=(const SpreadSheetCell& rhs) {
    setValue(getValue() * rhs.getValue());
    return *this;
}

SpreadSheetCell& SpreadSheetCell::operator/=(const SpreadSheetCell& rhs) {
    if (rhs.getValue() == 0) {
        throw std::invalid_argument{"Divide by zero."};
    }
    setValue(getValue() / rhs.getValue());
    return *this;
}

bool SpreadSheetCell::operator==(const SpreadSheetCell& rhs) const {
    return (getValue() == rhs.getValue());
}

std::partial_ordering SpreadSheetCell::operator<=>(
    const SpreadSheetCell& rhs) const {
    return getValue() <=> rhs.getValue();
}

bool SpreadSheetCell::operator==(const double rhs) const {
    return getValue() == rhs;
}

std::partial_ordering SpreadSheetCell::operator<=>(const double rhs) const {
    return getValue() <=> rhs;
}

class SpreadSheetApplication {};

class SpreadSheet {
   public:
    SpreadSheet(size_t width, size_t height, SpreadSheetApplication& theApp);
    SpreadSheet(const SpreadSheet& src);
    SpreadSheet(SpreadSheet&& src) noexcept;
    ~SpreadSheet();

    void setCellAt(size_t x, size_t y, const SpreadSheetCell& cell);
    const SpreadSheetCell& getCellAt(size_t x, size_t y) const;
    SpreadSheetCell& getCellAt(size_t x, size_t y);

    void swap(SpreadSheet& other) noexcept;

    SpreadSheet& operator=(const SpreadSheet& rhs);
    SpreadSheet& operator=(SpreadSheet&& rhs) noexcept;

   private:
    void verifyCoordinate(size_t x, size_t y) const;
    size_t m_width{0};
    size_t m_height{0};
    SpreadSheetCell** m_cells{nullptr};
    SpreadSheetApplication& m_theApp;
    static inline size_t ms_counter{0};
    const size_t m_id{0};
};

SpreadSheet::SpreadSheet(size_t width, size_t height,
                         SpreadSheetApplication& theApp)
    : m_width{width}, m_height{height}, m_id{ms_counter++}, m_theApp{theApp} {
    m_cells = new SpreadSheetCell*[m_width];
    for (size_t i = 0; i < m_width; i++) {
        m_cells[i] = new SpreadSheetCell[m_height];
    }
}

SpreadSheet::SpreadSheet(const SpreadSheet& src)
    : SpreadSheet(src.m_width, src.m_height, src.m_theApp) {
    for (size_t i = 0; i < m_width; i++) {
        for (size_t j = 0; j < m_height; j++) {
            m_cells[i][j] = src.m_cells[i][j];
        }
    }
}

SpreadSheet::SpreadSheet(SpreadSheet&& src) noexcept : m_theApp{src.m_theApp} {
    std::swap(*this, src);
}

SpreadSheet::~SpreadSheet() {
    for (size_t i = 0; i < m_width; i++) {
        delete[] m_cells[i];
    }
    delete[] m_cells;
    m_cells = nullptr;
}

void SpreadSheet::verifyCoordinate(size_t x, size_t y) const {
    if (x >= m_width) {
        throw std::out_of_range{
            // std::format("{} must be less than {}.", x, m_width)};
            std::string{std::to_string(x) + " must be less than " +
                        std::to_string(m_width) + "."}};
    }
    if (y >= m_height) {
        throw std::out_of_range{
            // std::format("{} must be less than {}.", y, m_height)};
            std::string{std::to_string(y) + " must be less than " +
                        std::to_string(m_height) + "."}};
    }
}

void SpreadSheet::setCellAt(size_t x, size_t y, const SpreadSheetCell& cell) {
    verifyCoordinate(x, y);
    m_cells[x][y] = cell;
}

const SpreadSheetCell& SpreadSheet::getCellAt(size_t x, size_t y) const {
    verifyCoordinate(x, y);
    return m_cells[x][y];
}

SpreadSheetCell& SpreadSheet::getCellAt(size_t x, size_t y) {
    return const_cast<SpreadSheetCell&>(std::as_const(*this).getCellAt(x, y));
}

void SpreadSheet::swap(SpreadSheet& other) noexcept {
    std::swap(m_width, other.m_width);
    std::swap(m_height, other.m_height);
    std::swap(m_cells, other.m_cells);
}

SpreadSheet& SpreadSheet::operator=(const SpreadSheet& rhs) {
    SpreadSheet temp{rhs};
    swap(temp);
    return *this;
}

SpreadSheet& SpreadSheet::operator=(SpreadSheet&& rhs) noexcept {
    std::swap(*this, rhs);
    return *this;
}

class TextHolder {
   public:
    TextHolder(std::string text) : m_text{std::move(text)} {}
    const std::string& getText() const& { return m_text; }
    std::string&& getText() && { return std::move(m_text); }

   private:
    std::string m_text;
};

int main() {
    clock_t startTime{clock()};
    
    clock_t endTime{clock()};
    std::cout << endTime - startTime << std::endl;
    return 0;
}
