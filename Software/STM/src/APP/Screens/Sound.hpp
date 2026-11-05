/**
 * @file Sound.hpp
 * @author Pawel Warzecha (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-10-11
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include "Sounds/Sounds.hpp"
#include <string>

#include <BSP/AudioOutput.hpp>
#include <BSP/BSP.hpp>
#include <Canvas.hpp>
#include <widgets/Text.hpp>

class SoundScreen: public Canvas
{
public:
    /**
     * @brief Constructor
     */
    SoundScreen() = default;

    /**
     * @brief Execution of the State action.
     */
    void init() override
    {
        static const WidgetAndPositions ct1{.x = 0, .y = 0, .widget = counter_text1};

        BSP::get().audio_output.play(get_sound(SoundType::TWINKLE_TWINKLE));

        static const std::array<const std::reference_wrapper<const WidgetAndPositions>, 1> widgets{ct1};

        add(widgets);
    }

private:
    Text counter_text1{"sound", TextFactory::to_image, get_width()};
};
