/**
 * Counter.hpp
 *
 *  Created on: 22-09-2019
 *  @author: Paweł Warzecha
 */

#ifndef APP_SCREENS_COUNTER_HPP_
#define APP_SCREENS_COUNTER_HPP_

#include <string>

#include <Canvas.hpp>
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
    void init() override
    {
        add(&counter_text, 0, 0);
        // validate();
    }

    void up_date() override
    {
        constexpr static uint16_t MAX_NUMBER{1000};

        if (++counter_value > MAX_NUMBER)
        {
            counter_value = 0;
        }

        counter_text.setText(std::to_string(counter_value), TextAlignment::RIGHT);
    }

private:
    uint16_t counter_value{0};
    Text counter_text{"11111", TextAlignment::RIGHT};
};

#endif /* APP_SCREENS_COUNTER_HPP_ */
