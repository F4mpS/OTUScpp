#pragma once

/**
 * @brief Color struct that represents RGB color with additional transparency parameter
 */
struct Color
{
    Color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) : r(r), g(g), b(b), a(a) {}

    std::uint8_t r = 0; ///< red 0-255
    std::uint8_t g = 0; ///< green 0-255
    std::uint8_t b = 0; ///< blue 0-255
    std::uint8_t a = 0; ///< alpha (transparency) 0-255
};