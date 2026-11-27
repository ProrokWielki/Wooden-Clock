/**
 * StataAccel.hpp
 *
 *  Created on: 02-05-2020
 *  @author: Paweł Warzecha
 */

#ifndef APP_STATEMACHINE_STATES_STATEACCEL_HPP_
#define APP_STATEMACHINE_STATES_STATEACCEL_HPP_

#include <Canvas.hpp>
#include <widgets/Image.hpp>

#include <BSP/Accelerometer.hpp>
#include <BSP/BSP.hpp>

#include <cstdint>
#include <limits>

class StateAccel: public Canvas
{
public:
    explicit StateAccel(BSP2::Accelerometer & accel);
    void init() override;
    void up_date() override;

private:
    BSP2::Accelerometer & accel_;
    std::array<uint8_t, get_width() * get_height()> empty_frame_buffer{};
    Image magnet;
};

#endif /* APP_STATEMACHINE_STATES_STATENORTH_HPP_ */
