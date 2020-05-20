/**
 *  Clock.hpp
 *
 *  Created on: 06-05-2020
 *  Author: Paweł Warzecha
 */
#ifndef HAL_DAC_DAC_HPP_
#define HAL_DAC_DAC_HPP_

#include "../Register/Register.hpp"

class DAC
{
public:
private:
    Register CR;
    Register SWTRGR;
    Register DHR12R1;
    Register DHR12L1;
    Register DHR8R1;
    Register DHR12R2;
    Register DHR12L2;
    Register DHR8R2;
    Register DHR12RD;
    Register DHR12LD;
    Register DHR8RD;
    Register DOR1;
    Register DOR2;
    Register SR;
    Register CCR;
    Register MCR;
    Register SHSR1;
    Register SGSR2;
    Register SHHR;
    Register SHRR;
};

#endif /* HAL_DAC_DAC_HPP_ */
