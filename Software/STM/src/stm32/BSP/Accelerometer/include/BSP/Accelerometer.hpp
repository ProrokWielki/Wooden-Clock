/**
  * Accelerometer.hpp
  *
  *  Created on: 02-05-2019
  *  @author: Paweł Warzecha
  */

#pragma once

namespace BSP2{

struct Accelerations {
    double x;
    double y;
    double z;
};

class Accelerometer
{
public:
    [[nodiscard]] Accelerations get_linear_accelerations() const;
    void update();

private:
    Accelerations accelerations_{};
};

}