/**
 * DataContainer.hpp
 *
 *  Created on: 10-03-2019
 *  @author: Paweł Warzecha
 */

#ifndef APP_DATACONTAINER_HPP_
#define APP_DATACONTAINER_HPP_

#include <GUI.hpp>

#include "Screens/Counter.hpp"
#include "Screens/StateAccel.hpp"
#include "Screens/StateArrows.hpp"
#include "Screens/StateHourglass.hpp"
#include "Screens/StateMario.hpp"
#include "Screens/StateNorth.hpp"
#include "Screens/StateText.hpp"

enum class Signal
{
    BUTTON1,
    BUTTON2,
    BUTTON3,
    BUTTON4
};

class DataContainer
{
public:
    static uint8_t FrameBuffer1[];
    static uint8_t FrameBuffer2[];

    static GUI stateMachine;

    static StateMario Mario;
    static StateArrows Arrows;
    static StateHourglass Hourglass;
    static StateNorth North;
    static StateText Text;
    static Counter CounterView;
    static StateAccel Accel;
};

#endif /* APP_DATACONTAINER_HPP_ */
