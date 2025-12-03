/**
 * Counter.hpp
 *
 *  Created on: 22-09-2019
 *  @author: Paweł Warzecha
 */

#ifndef APP_SCREENS_TEXT_HPP_
#define APP_SCREENS_TEXT_HPP_

#include <string>

#include <Canvas.hpp>
#include <widgets/Text.hpp>

class TextScreen: public Canvas
{
public:
    /**
     * @brief Constructor
     */
    TextScreen() = default;

    /**
     * @brief Execution of the State action.
     */
    void init() override
    {
        add(&counter_text1, 0, 0);
        add(&counter_text2, 0, counter_text1.getHeight());
        add(&counter_text3, 0, counter_text1.getHeight() + counter_text2.getHeight());
    }

private:
    Text counter_text1{"test", get_width()};
    Text counter_text2{"abcd", get_width()};
    Text counter_text3{"1234", get_width()};
    Text counter_text4{"%*:", get_width()};
};

#endif /* APP_SCREENS_COUNTER_HPP_ */
