/**
 *  @file Images
 *
 *  Created on: 27-07-2025
 *  @author: Paweł Warzecha
 */

#pragma once

class Image;

enum class ImageType
{
    MARIO,
    UP_ARROW,
    DOWN_ARROW,
    LEFT_ARROW,
    RIGHT_ARROW
};

Image & get_image(ImageType image_type);
