/**
 *  @file Images
 *
 *  Created on: 15-02-2018
 *  @author: Paweł Warzecha
 */

#include <widgets/Image.hpp>

#include "Images.hpp"

#include "downArrow.hpp"
#include "leftArrow.hpp"
#include "mario.hpp"
#include "rightArrow.hpp"
#include "upArrow.hpp"

const Image & get_image(ImageType image_type)
{
    const static Image mario{Mario::WIDTH, Mario::HEIGHT, Mario::DATA.data()};
    const static Image up_arrow{UpArrow::WIDTH, UpArrow::HEIGHT, UpArrow::DATA.data()};
    const static Image down_arrow{DownArrow::WIDTH, DownArrow::HEIGHT, DownArrow::DATA.data()};
    const static Image left_arrow{LeftArrow::WIDTH, LeftArrow::HEIGHT, LeftArrow::DATA.data()};
    const static Image right_arrow{RightArrow::WIDTH, RightArrow::HEIGHT, RightArrow::DATA.data()};

    switch (image_type)
    {
        case ImageType::MARIO:
            return mario;
        case ImageType::UP_ARROW:
            return up_arrow;
        case ImageType::DOWN_ARROW:
            return down_arrow;
        case ImageType::LEFT_ARROW:
            return left_arrow;
        case ImageType::RIGHT_ARROW:
            return right_arrow;
        default:
            return mario;
    };
}
