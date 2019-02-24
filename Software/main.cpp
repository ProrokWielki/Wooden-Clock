//#define STM32L452xx

#include <stdint.h>
#include <string.h>
#include "stm32l4xx.h"

#include "HAL.hpp"

#include "APP/Assets/Images/Images.hpp"

uint8_t transfer1[9], transfer2[9], transfer3[9], transfer4[9];

inline void HC595ToggleClk() {
	HAL::CLOCK::set_output_low();
	asm("nop");
	HAL::CLOCK::set_output_high();
}

inline void HC595TriggerOutput() {
	HAL::TRIGGER::set_output_high();
	asm("nop");
	HAL::TRIGGER::set_output_low();
}

int main(void) {

	HAL::init();

	SystemCoreClockUpdate();

	HAL::PB13::set_mode(eOutput);
	HAL::PB13::set_speed(eVeryHighSpeed);

  uint8_t data[] = {0x82, 125, 125, 125, 125, 125, 125, 125, 125, 0xff, 0x00,
                    0b10101010,
                    0b10101010};
  uint8_t data1[] = {0x80, 0, 0x08};

  for(uint32_t i = 0 ; i < 0xffff ; i++)
    {
      ;
    }

	HAL::OUTPUT_EN::set_output_value(eLow);
	HAL::RESET::set_output_value(eLow);
	HAL::DATA_IN::set_output_value(eLow);
	HAL::CLOCK::set_output_value(eLow);
	HAL::TRIGGER::set_output_value(eLow);

	for (uint32_t i = 0; i < 0xffff; i++) {
		;
	}

	HAL::RESET::set_output_value(eHigh);
	HAL::TI_RESET::set_output_value(eLow);
	HAL::DATA_IN::set_output_value(eHigh);

	for (uint8_t i = 0; i < 32; i++) {
		HAL::CLOCK::set_output_low();
		for (uint32_t i = 0; i < 0xffff; i++) {
			;
		}
		HAL::CLOCK::set_output_high();
		for (uint32_t i = 0; i < 0xffff; i++) {
			;
		}
	}

	HAL::TRIGGER::set_output_high();
	HAL::TI_RESET::set_output_high();

	for (uint32_t i = 0; i < 0xffff; i++) {
		;
	}

	HAL::I2C_1::set_slave_address(0x40 >> 1, e7bitAddress);
	HAL::I2C_1::write_data(data1, 3);

	HAL::I2C_2::set_slave_address(0x42 >> 1, e7bitAddress);
	HAL::I2C_2::write_data(data1, 3);

	HAL::I2C_3::set_slave_address(0x44 >> 1, e7bitAddress);
	HAL::I2C_3::write_data(data1, 3);

	HAL::I2C_4::set_slave_address(0x46 >> 1, e7bitAddress);
	HAL::I2C_4::write_data(data1, 3);

	HAL::I2C_1::write_data(data, 13);
	HAL::I2C_2::write_data(data, 13);
	HAL::I2C_3::write_data(data, 13);
	HAL::I2C_4::write_data(data, 13);

	uint8_t currentLine = 0;

	HAL::OUTPUT_EN::set_output_low();

	transfer1[0] = transfer2[0] = transfer3[0] = transfer4[0] = 0x82;

	for (;;) {

		memcpy(&transfer1[1], &Mario_pixel_map[currentLine * 32],
				8 * sizeof(uint8_t));
		memcpy(&transfer2[1], &Mario_pixel_map[currentLine * 32 + 8],
				8 * sizeof(uint8_t));
		memcpy(&transfer3[1], &Mario_pixel_map[currentLine * 32 + 16],
				8 * sizeof(uint8_t));
		memcpy(&transfer4[1], &Mario_pixel_map[currentLine * 32 + 24],
				8 * sizeof(uint8_t));

		HAL::OUTPUT_EN::set_output_high();

		HAL::I2C_1::write_data(transfer1, 9);
		HAL::I2C_2::write_data(transfer2, 9);
		HAL::I2C_3::write_data(transfer3, 9);
		HAL::I2C_4::write_data(transfer4, 9);

		if (0 == currentLine) {
			HAL::DATA_IN::set_output_low();
		} else
			HAL::DATA_IN::set_output_high();

      HC595ToggleClk();
      HC595TriggerOutput();

      HAL::OUTPUT_EN::set_output_low(); // output enable

      for(uint32_t i = 0 ; i < 0xff ; i++)
        ;

      currentLine++;
    }
	}
  return 0;
}
