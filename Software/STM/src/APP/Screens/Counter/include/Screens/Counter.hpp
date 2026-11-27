/**
 * Counter.hpp
 *
 *  Created on: 22-09-2019
 *  @author: Paweł Warzecha
 */

#ifndef APP_SCREENS_COUNTER_HPP_
#define APP_SCREENS_COUNTER_HPP_

#include <functional>
#include <string>

#include "Texts/texts.hpp"

#include <Canvas.hpp>
#include <Widget.hpp>
#include <widgets/Text.hpp>

class Counter: public Canvas
{
public:
    /**
     * @brief Constructor
     */
    Counter() = default;

    /**
     * @brief Execution of the State action.
     */
    void init() override;

    void up_date() override;

private:
    uint16_t counter_value{0};
    Text counter_text{"11111", TextFactory::to_image, get_width(), TextAlignment::RIGHT};
    Text counter_text2{"11111", TextFactory::to_image, get_width(), TextAlignment::CENTER};
    Text counter_text3{"11111", TextFactory::to_image, get_width(), TextAlignment::LEFT};
};

#endif /* APP_SCREENS_COUNTER_HPP_ */
