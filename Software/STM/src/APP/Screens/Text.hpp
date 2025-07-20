/**
 * Counter.hpp
 *
 *  Created on: 22-09-2019
 *  @author: Paweł Warzecha
 */

#ifndef APP_SCREENS_TEXT_HPP_
#define APP_SCREENS_TEXT_HPP_

#include "../Assets/Text/texts.hpp"
#include <Canvas.hpp>
#include <string>
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
        add(&counter_text1, 0, 1);
        add(&counter_text2, 0, 11);
        add(&counter_text3, 0, 21);
        // add(&counter_text4, 0, 30);
        // validate();
    }

    void up_date() override
    {
    }

private:
    Text counter_text1{"test"};
    Text counter_text2{"abcd"};
    Text counter_text3{"1234"};
    Text counter_text4{"%*:"};
};

#endif /* APP_SCREENS_COUNTER_HPP_ */
