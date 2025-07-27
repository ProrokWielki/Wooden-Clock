#include <widgets/Animation.hpp>
#include <widgets/Image.hpp>

#include "Hourglass.hpp"

#include "frames/1.hpp"
#include "frames/10.hpp"
#include "frames/11.hpp"
#include "frames/12.hpp"
#include "frames/13.hpp"
#include "frames/14.hpp"
#include "frames/15.hpp"
#include "frames/16.hpp"
#include "frames/17.hpp"
#include "frames/18.hpp"
#include "frames/19.hpp"
#include "frames/2.hpp"
#include "frames/20.hpp"
#include "frames/21.hpp"
#include "frames/3.hpp"
#include "frames/4.hpp"
#include "frames/5.hpp"
#include "frames/6.hpp"
#include "frames/7.hpp"
#include "frames/8.hpp"
#include "frames/9.hpp"

namespace
{
static Image frame_1{Hourglass_Frame_1::WIDTH, Hourglass_Frame_1::HEIGHT, Hourglass_Frame_1::DATA.data()};
static Image frame_2{Hourglass_Frame_2::WIDTH, Hourglass_Frame_2::HEIGHT, Hourglass_Frame_2::DATA.data()};
static Image frame_3{Hourglass_Frame_3::WIDTH, Hourglass_Frame_3::HEIGHT, Hourglass_Frame_3::DATA.data()};
static Image frame_4{Hourglass_Frame_4::WIDTH, Hourglass_Frame_4::HEIGHT, Hourglass_Frame_4::DATA.data()};
static Image frame_5{Hourglass_Frame_5::WIDTH, Hourglass_Frame_5::HEIGHT, Hourglass_Frame_5::DATA.data()};
static Image frame_6{Hourglass_Frame_6::WIDTH, Hourglass_Frame_6::HEIGHT, Hourglass_Frame_6::DATA.data()};
static Image frame_7{Hourglass_Frame_7::WIDTH, Hourglass_Frame_7::HEIGHT, Hourglass_Frame_7::DATA.data()};
static Image frame_8{Hourglass_Frame_8::WIDTH, Hourglass_Frame_8::HEIGHT, Hourglass_Frame_8::DATA.data()};
static Image frame_9{Hourglass_Frame_9::WIDTH, Hourglass_Frame_9::HEIGHT, Hourglass_Frame_9::DATA.data()};
static Image frame_10{Hourglass_Frame_10::WIDTH, Hourglass_Frame_10::HEIGHT, Hourglass_Frame_10::DATA.data()};
static Image frame_11{Hourglass_Frame_11::WIDTH, Hourglass_Frame_11::HEIGHT, Hourglass_Frame_11::DATA.data()};
static Image frame_12{Hourglass_Frame_12::WIDTH, Hourglass_Frame_12::HEIGHT, Hourglass_Frame_12::DATA.data()};
static Image frame_13{Hourglass_Frame_13::WIDTH, Hourglass_Frame_13::HEIGHT, Hourglass_Frame_13::DATA.data()};
static Image frame_14{Hourglass_Frame_14::WIDTH, Hourglass_Frame_14::HEIGHT, Hourglass_Frame_14::DATA.data()};
static Image frame_15{Hourglass_Frame_15::WIDTH, Hourglass_Frame_15::HEIGHT, Hourglass_Frame_15::DATA.data()};
static Image frame_16{Hourglass_Frame_16::WIDTH, Hourglass_Frame_16::HEIGHT, Hourglass_Frame_16::DATA.data()};
static Image frame_17{Hourglass_Frame_17::WIDTH, Hourglass_Frame_17::HEIGHT, Hourglass_Frame_17::DATA.data()};
static Image frame_18{Hourglass_Frame_18::WIDTH, Hourglass_Frame_18::HEIGHT, Hourglass_Frame_18::DATA.data()};
static Image frame_19{Hourglass_Frame_19::WIDTH, Hourglass_Frame_19::HEIGHT, Hourglass_Frame_19::DATA.data()};
static Image frame_20{Hourglass_Frame_20::WIDTH, Hourglass_Frame_20::HEIGHT, Hourglass_Frame_20::DATA.data()};
static Image frame_21{Hourglass_Frame_21::WIDTH, Hourglass_Frame_21::HEIGHT, Hourglass_Frame_21::DATA.data()};
}  // namespace

Animation & getHourglassAnimation()
{
    static Animation Hourglass{{frame_1,  frame_2,  frame_3,  frame_4,  frame_5,  frame_6,  frame_7,  frame_8,  frame_9,  frame_10, frame_11,
                                      frame_12, frame_13, frame_14, frame_15, frame_16, frame_17, frame_18, frame_19, frame_20, frame_21}};

    return Hourglass;
}