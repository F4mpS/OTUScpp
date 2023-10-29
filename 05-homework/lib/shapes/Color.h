#pragma once

/**
 * @brief Color struct that represents RGB color with additional transparency parameter
 */
struct Color
{
    Color(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = 0) : r(r), g(g), b(b), a(a) {}
    ~Color() = default;

    uint8_t r; ///< red 0-255
    uint8_t g; ///< green 0-255
    uint8_t b; ///< blue 0-255
    uint8_t a; ///< alpha (transparency) 0-255
};