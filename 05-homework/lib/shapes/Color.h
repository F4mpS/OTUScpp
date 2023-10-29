#pragma once

/**
 * @brief Color struct that represents RGB color with additional transparency parameter
 */
struct Color
{
    Color() = default;
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) {}

    uint8_t r = 0; ///< red 0-255
    uint8_t g = 0; ///< green 0-255
    uint8_t b = 0; ///< blue 0-255
    uint8_t a = 0; ///< alpha (transparency) 0-255
};