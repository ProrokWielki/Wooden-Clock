/**
 * Display.hpp
 *
 *  Created on: 30-10-2018
 *  @author: Paweł Warzecha
 */

#ifndef BSP_DISPLAY_DISPLAY_HPP_
#define BSP_DISPLAY_DISPLAY_HPP_

#include <stdint.h>

class Display
{
public:
    /**
     * @brief Constructor
     *
     * @param width display width in pixels.
     * @param height display height in pixels.
     * @param fameBuffer pointer to frame buffer.
     */
    Display(uint8_t width, uint8_t height, uint8_t * fameBuffer);

    /**
     * @brief Destructor.
     */
    ~Display(){};

    /**
     * @brief Sets the frame buffer to be displayed.
     *
     * @param buffer pointer to new frame buffer
     */
    void set_frame_buffer(uint8_t * buffer)
    {
        displayFrameBuffer = buffer;
    }

    /**
     * @brief draws next line, has to be called periodically.
     */
    void draw(void);

protected:
private:
    void draw_line(uint8_t line_number);
    bool is_line_drawn();

    uint8_t displayWidth;
    uint8_t displayHeight;

    uint8_t * displayFrameBuffer;

    bool transferComplete[4];

    constexpr static uint8_t transferSize = 8;
};

#endif /* BSP_DISPLAY_DISPLAY_HPP_ */
