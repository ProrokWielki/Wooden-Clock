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
        static constexpr uint8_t TEXT_FIELD_HEIGHT{11};

        add(&counter_text, 0, 0);
        add(&counter_text2, 0, TEXT_FIELD_HEIGHT);
        add(&counter_text3, 0, 2 * TEXT_FIELD_HEIGHT);
    }

    void up_date() override
    {
        constexpr static uint16_t MAX_NUMBER{1000};

        if (++counter_value > MAX_NUMBER)
        {
            counter_value = 0;
        }

        counter_text.setText(std::to_string(counter_value), TextAlignment::RIGHT);
        counter_text2.setText(std::to_string(counter_value * 2), TextAlignment::CENTER);
        counter_text3.setText(std::to_string(MAX_NUMBER - counter_value), TextAlignment::LEFT);
    }

private:
    uint16_t counter_value{0};
    Text counter_text{"11111", get_width(), TextAlignment::RIGHT};
    Text counter_text2{"11111", get_width(), TextAlignment::CENTER};
    Text counter_text3{"11111", get_width(), TextAlignment::LEFT};
};

#endif /* APP_SCREENS_COUNTER_HPP_ */
