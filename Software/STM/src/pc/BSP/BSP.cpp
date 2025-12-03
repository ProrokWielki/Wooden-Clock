#include <BSP/BSP.hpp>

BSP::BSP()
: display(BSP::DISPLAY_WIDTH, BSP::DISPLAY_HEIGHT, {frame_buffer1.data(), 32 * 32}), button_right{"right"}, button_left{"left"}, button_up{"up"},
  button_down{"down"}
{
}

BSP & BSP::get()
{
    static BSP instance;
    return instance;
}