/*
 * Display.cpp
 *
 *  Created on: 30 pa� 2018
 *      Author: Proro
 */

#include "Display.hpp"

#include "HAL.hpp"

#include <string.h>

void Display::draw(void)
{
  for(uint8_t line = 0 ; line < displayHeight ; line++)
    {

    }
}

void Display::draw_line(uint8_t lineNumber)
{
  uint16_t framebufferOffset = lineNumber * displayWidth;
  uint8_t framebufferParts = displayWidth / transferSize;

  uint8_t transfer[transferSize + 1];

  for(uint8_t framebufferPart = 0 ; framebufferPart < framebufferParts ; framebufferPart++)
    {
      memcpy(&( transfer[1] ), &( frameBuffer[framebufferOffset +  framebufferPart * transferSize] ), sizeof(uint8_t) * transferSize);
//      send;
    }
}
