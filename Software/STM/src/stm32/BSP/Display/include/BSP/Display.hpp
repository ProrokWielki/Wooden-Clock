/**
 * Display.hpp
 *
 *  Created on: 30-10-2018
 *  @author: Paweł Warzecha
 */

#ifndef BSP_DISPLAY_DISPLAY_HPP_
#define BSP_DISPLAY_DISPLAY_HPP_

#include <array>
#include <cstdint>
#include <functional>

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
    Display(uint8_t width, uint8_t height, const uint8_t * fameBuffer);

    void init();

    /**
     * @brief Sets the frame buffer to be displayed.
     *
     * @param buffer pointer to new frame buffer
     */
    void set_frame_buffer(const uint8_t * buffer)
    {
        displayFrameBuffer = buffer;
    }

    /**
     * @brief draws next line, has to be called periodically.
     */
    void draw();

    /**
     * @brief Sets function to be called every time the full display is redrawn.
     *
     * @param callback function to be called.
     */
    void set_dispaly_redrawn_callback(std::function<void()> callback);

    bool is_line_drawn();
    void draw_next_line();

protected:
private:
    void transfer_complete(const uint8_t transferNumber);

    std::function<void()> display_redrawn_callback;

    uint8_t displayWidth;
    uint8_t displayHeight;

    const uint8_t * displayFrameBuffer;

    std::array<volatile bool, 4> transferComplete;

    volatile uint8_t currentLine_{0};

    constexpr static uint8_t transferSize = 8;
};

#endif /* BSP_DISPLAY_DISPLAY_HPP_ */
