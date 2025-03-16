#include "GUI.hpp"
#include "Canvas.hpp"
#include <BSP/BSP.hpp>

uint8_t GUI::width_ = 32;
uint8_t GUI::height_ = 32;

uint8_t FrameBuffer1[32][32];
uint8_t FrameBuffer2[32][32];

uint8_t * GUI::front_framebuffer_ = &FrameBuffer1[0][0];  // Todo it cant be like that.
uint8_t * GUI::back_framebuffer_ = &FrameBuffer2[0][0];

void GUI::swap_framebuffers()
{
    if (curent_canvas_->isReady() and isDoubleFrameBuffer)
    {
        std::swap(front_framebuffer_, back_framebuffer_);

        BSP::display.set_frame_buffer(front_framebuffer_);
    }
}

void GUI::update()
{
    if (updateNedded)
    {
        updateNedded = false;
        auto tmp = transiton(recieved_);
        if (tmp != curent_canvas_)
        {
            curent_canvas_ = transiton(recieved_);
            curent_canvas_->clear();
            curent_canvas_->init();
        }
    }
    curent_canvas_->update();
}
