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
        static const WidgetAndPositions ct1{.x = 0, .y = 0, .widget = counter_text1};
        static const WidgetAndPositions ct2{.x = 0, .y = counter_text1.getHeight(), .widget = counter_text2};
        static const WidgetAndPositions ct3{.x = 0, .y = static_cast<uint8_t>(counter_text1.getHeight() + counter_text2.getHeight()), .widget = counter_text3};

        static const std::array<const std::reference_wrapper<const WidgetAndPositions>, 3> widgets{ct1, ct2, ct3};

        add(widgets);
    }

private:
    Text counter_text1{"test", TextFactory::to_image, get_width()};
    Text counter_text2{"abcd", TextFactory::to_image, get_width()};
    Text counter_text3{"1234", TextFactory::to_image, get_width()};
    Text counter_text4{"%*:", TextFactory::to_image, get_width()};
};

#endif /* APP_SCREENS_COUNTER_HPP_ */
