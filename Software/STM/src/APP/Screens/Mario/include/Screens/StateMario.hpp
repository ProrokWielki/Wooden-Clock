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
    StateMario();

    void init() override;

    void up_date() override;

private:
    const Image & mario;
};

#endif /* APP_STATEMACHINE_STATES_STATEMARIO_HPP_ */
