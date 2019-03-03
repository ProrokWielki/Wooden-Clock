/**
 * TLC59208F.hpp
 *
 *  Created on: 27-02-2019
 *  @author: Paweł Warzecha
 */

#ifndef DRV_TLC59208F_TLC59208F_HPP_
#define DRV_TLC59208F_TLC59208F_HPP_

#include <stdint.h>
#include <string.h>

template<typename I2C, uint8_t ADDRESS, typename RESET_PIN>
class TLC59208F
{
public:
    static void init()
    {

        RESET_PIN::set_mode(eOutput);
        RESET_PIN::set_speed(eVeryHighSpeed);

        RESET_PIN::set_output_low();
        I2C::set_slave_address(ADDRESS >> 1, e7bitAddress);
        RESET_PIN::set_output_high();
    }

    static void set_register_value(uint8_t registerAddress, uint8_t valueToBeSet)
    {

        static uint8_t dataToBeSend[2];

        dataToBeSend[0] = registerAddress;
        dataToBeSend[1] = valueToBeSet;

        I2C::write_data(dataToBeSend, 2);
    }

    static void set_registers_values(const uint8_t registerStartAddress, const uint8_t * const valuesToBeSet, const uint8_t numberOfValues)
    {

        static uint8_t dataToBeSend[16];

        dataToBeSend[0] = registerStartAddress | 0x80;
        memcpy(&(dataToBeSend[1]), valuesToBeSet, (numberOfValues + 1) * sizeof(uint8_t));

        I2C::write_data(dataToBeSend, numberOfValues + 1);
    }

    static void set_all_leds_values(uint8_t * allLedsValues)
    {

        static uint8_t dataToBeSend[9] = {0x82};

        memcpy(&(dataToBeSend[1]), allLedsValues, 8 * sizeof(uint8_t));

        I2C::write_data_DMA(dataToBeSend, 9);
    }

    static void set_transfer_complete_callback(std::function<void()> callback)
    {
        I2C::get_DMA::set_transfer_complete_callback(callback);
        I2C::get_DMA::enable_interrupt(eTransferCompleted);
    }

protected:
private:
};

#endif /* DRV_TLC59208F_TLC59208F_HPP_ */
