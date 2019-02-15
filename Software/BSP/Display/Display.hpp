/*
 * Display.hpp
 *
 *  Created on: 30 pa� 2018
 *      Author: Proro
 */

#ifndef BSP_DISPLAY_DISPLAY_HPP_
#define BSP_DISPLAY_DISPLAY_HPP_

#include <stdint.h>

class Display
{
public:

	Display(uint8_t width, uint8_t height, uint8_t * fameBuffer);
	~Display();

	void set_frame_buffer(uint8_t * buffer)
	{
	  frameBuffer = buffer;
	}

	void draw_line(uint8_t line_number);

	void draw(void);

	uint8_t get_display_width(void);
	uint8_t get_display_height(void);

protected:

private:

	uint8_t displayWidth;
	uint8_t displayHeight;

	uint8_t * frameBuffer;

	constexpr uint8_t transferSize = 8;
};


#endif /* BSP_DISPLAY_DISPLAY_HPP_ */
