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

#include <texts.hpp>

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
    void init() override;

private:
    Text counter_text1{"test", TextFactory::to_image, get_width()};
    Text counter_text2{"abcd", TextFactory::to_image, get_width()};
    Text counter_text3{"1234", TextFactory::to_image, get_width()};
    Text counter_text4{"%*:", TextFactory::to_image, get_width()};
};

#endif /* APP_SCREENS_COUNTER_HPP_ */
