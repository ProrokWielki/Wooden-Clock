/**
 * StateNorth.hpp
 *
 *  Created on: 02-05-2019
 *  @author: Paweł Warzecha
 */

#ifndef APP_STATEMACHINE_STATES_STATENORTH_HPP_
#define APP_STATEMACHINE_STATES_STATENORTH_HPP_

#include <Canvas.hpp>
#include <widgets/Image.hpp>

#include <BSP/Magnetometer.hpp>

#include <BSP/BSP.hpp>
#include <array>
#include <limits>

class StateNorth: public Canvas
{
public:
    explicit StateNorth(BSP2::Magnetometer & magneto);

    void init() override;

    void up_date() override;

private:
    BSP2::Magnetometer & magneto_;
    std::array<uint8_t, get_width() * get_height()> empty_frame_buffer{};
    Image magnet;
};

#endif /* APP_STATEMACHINE_STATES_STATENORTH_HPP_ */
