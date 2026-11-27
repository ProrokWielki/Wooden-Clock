/**
 * Counter.hpp
 *
 *  Created on: 22-09-2019
 *  @author: Paweł Warzecha
 */

#pragma once

#include <format>
#include <string>

#include <Canvas.hpp>
#include <widgets/Text.hpp>

#include <texts.hpp>

#include <BSP/BSP.hpp>

class Temperature: public Canvas
{
public:
    /**
     * @brief Constructor
     */
    Temperature() = default;

    /**
     * @brief Execution of the State action.
     */
    void init() override;

    void up_date() override;

private:
    Text temperature_text{"0*C", TextFactory::to_image, get_width()};
};
