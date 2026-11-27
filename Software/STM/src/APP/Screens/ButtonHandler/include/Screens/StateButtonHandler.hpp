/**
 * StateButtons.hpp
 *
 *  Created on: 17-05-2020
 *  @author: Paweł Warzecha
 */

#pragma once

#include <array>
#include <functional>

#include <Canvas.hpp>
#include <widgets/Text.hpp>

#include <BSP/BSP.hpp>

#include "ButtonHandler/include/ButtonHandler/ButtonHandler.hpp"
#include "Images/Images.hpp"
#include "Widget.hpp"
#include "texts.hpp"

class StateButtonHandler: public Canvas
{
public:
    /**
     * @brief Constructor.
     */
    StateButtonHandler();

    /**
     * @brief Execution of the State action.
     */
    void init() override;

    void up_date() override;

private:
    Text text{"NONE", TextFactory::to_image, get_width()};
    ButtonHandler button_handler_;
};
