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

#include "../Assets/Images/Images.hpp"

class StateMario: public RotatableCanvas
{
public:
    StateMario() : mario(32, 32, Mario_pixel_map)
    {
    }
    void init() override
    {
        add(&mario, 0, 0);

        // validate();
    }

    void up_date() override
    {
    }

private:
    Image mario;
};

#endif /* APP_STATEMACHINE_STATES_STATEMARIO_HPP_ */
