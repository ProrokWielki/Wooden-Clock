/**
 * Counter.hpp
 *
 *  Created on: 22-09-2019
 *  @author: Paweł Warzecha
 */

#pragma once

#include "Widget.hpp"
#include <Canvas.hpp>
#include <array>
#include <functional>

#include <widgets/Text.hpp>

#include <BSP/Clock.hpp>

#include "Texts/texts.hpp"

class Hour: public Canvas
{
public:
    /**
     * @brief Constructor
     */
    Hour() = default;

    /**
     * @brief Execution of the State action.
     */
    void init() override;

    void up_date() override;

private:
    Text time_text{"00:00", TextFactory::to_image, get_width()};
};
