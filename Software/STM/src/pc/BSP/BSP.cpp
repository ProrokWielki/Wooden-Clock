#include <BSP/BSP.hpp>

std::array<uint8_t, 32 * 32> frame_buffer1{};
std::array<uint8_t, 32 * 32> frame_buffer2{};

Display BSP::display(32, 32, frame_buffer1.data());
BSP2::Magnetometer BSP::magnetometer;
BSP2::Accelerometer BSP::accelerometer;
BSP2::Clock BSP::clock;

Button BSP::button_right{"right"};
Button BSP::button_left{"left"};
Button BSP::button_up{"up"};
Button BSP::button_down{"down"};

bool BSP::up;
bool BSP::down;
bool BSP::left;
bool BSP::right;