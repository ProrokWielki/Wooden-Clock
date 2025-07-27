#include <widgets/Animation.hpp>
#include <widgets/Image.hpp>

#include "Arrows.hpp"

#include "frames/1.hpp"
#include "frames/2.hpp"

namespace
{
static Image frame_1{Arrows_Frame_1::WIDTH, Arrows_Frame_1::HEIGHT, Arrows_Frame_1::DATA.data()};
static Image frame_2{Arrows_Frame_2::WIDTH, Arrows_Frame_2::HEIGHT, Arrows_Frame_2::DATA.data()};
}  // namespace

Animation & getArrowsAnimation()
{
    static Animation Arrows{{frame_1, frame_2}};
    return Arrows;
}