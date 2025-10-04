/**
 * @file Accelerometer.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-06-04
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

namespace BSP2{
struct Accelerations {
    float x;
    float y;
    float z;
};

class Accelerometer
{
public:
    [[nodiscard]] Accelerations get_linear_accelerations() const;
    void update();
    void set_accelerations(BSP2::Accelerations accelerations);

private:
    Accelerations accelerations_{};
};
}