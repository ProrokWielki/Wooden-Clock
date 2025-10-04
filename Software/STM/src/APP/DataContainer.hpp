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
#include "Screens/Hour.hpp"
#include "Screens/StateAccel.hpp"
#include "Screens/StateArrows.hpp"
#include "Screens/StateButtons.hpp"
#include "Screens/StateHourglass.hpp"
#include "Screens/StateMario.hpp"
#include "Screens/StateNorth.hpp"
#include "Screens/StateSand.hpp"
#include "Screens/Temperature.hpp"
#include "Screens/Shapes.hpp"
#include "Screens/Text.hpp"

enum class Signal
{
    BUTTON_LEFT,
    BUTTON_RIGHT,
    BUTTON_UP,
    BUTTON_DOWN
};

class DataContainer
{
public:
    static DataContainer & get();

    static StateMario Mario;
    static StateArrows Arrows;
    static StateHourglass Hourglass;
    static StateNorth North;
    static Counter CounterView;
    static StateAccel Accel;
    static StateButtons Buttons;
    static StateSand Sand;
    static Hour StateHour;
    static Temperature temperature;
    static ShapesScreen Shapes;
    static TextScreen text;

    GUI stateMachine;

private:
    DataContainer();
};

#endif /* APP_DATACONTAINER_HPP_ */
