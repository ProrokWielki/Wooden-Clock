/**
 * StateMario.hpp
 *
 *  Created on: 10-03-2019
 *  @author: Paweł Warzecha
 */

#ifndef APP_STATEMACHINE_STATES_STATEMARIO_HPP_
#define APP_STATEMACHINE_STATES_STATEMARIO_HPP_

#include <Canvas.hpp>
#include <RotatableCanvas.hpp>
#include <widgets/Image.hpp>

#include "Images/Images.hpp"

class StateMario: public RotatableCanvas
{
public:
    StateMario() : mario(get_image(ImageType::MARIO))

    {
    }
    void init() override
    {
        static const WidgetAndPositions im{.x = 0, .y = 0, .widget = mario};
        static const std::array<const std::reference_wrapper<const WidgetAndPositions>, 1> widgets{im};

        add(widgets);
    }

    void up_date() override
    {
    }

private:
    const Image & mario;
};

#endif /* APP_STATEMACHINE_STATES_STATEMARIO_HPP_ */
