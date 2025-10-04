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

struct ALLEGRO_DISPLAY;
struct ALLEGRO_EVENT_QUEUE;

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

    ~Display();

    void draw() const;

    void set_display_redrawn_callback(std::function<void()> callback)
{
    display_redrawn_callback = callback;
}

    /**
     * @brief Sets the frame buffer to be displayed.
     *
     * @param buffer pointer to new frame buffer
     */
    void set_frame_buffer(const uint8_t * buffer)
    {
        displayFrameBuffer = buffer;
    }

    void ShowExampleAppCustomRendering() const;

private:
    uint8_t displayWidth;
    uint8_t displayHeight;

    const uint8_t * displayFrameBuffer;

    ALLEGRO_DISPLAY * display;
    ALLEGRO_EVENT_QUEUE * queue;

    std::function<void()> display_redrawn_callback;
};

#endif /* BSP_DISPLAY_DISPLAY_HPP_ */
