#pragma once

#include <widgets/Image.hpp>

class TextFactory
{
public:
    static Image * to_image(char character);
    static uint8_t font_height();
};
