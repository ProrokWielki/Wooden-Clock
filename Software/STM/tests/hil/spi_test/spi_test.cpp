#include "HAL/types.hpp"
#include <cstdint>
#include <span>

#include <testing_framework.hpp>

#include <HAL/Clock.hpp>
#include <HAL/GPIO.hpp>
#include <HAL/SPI.hpp>


RegisterTest(I2cTest, SpiGyroscope, [](Test * test) {
    Clock clock;

    GPIO SPI1_MISO = GPIO(clock, GPIO_Types::Port::A, 11);
    GPIO SPI1_MOSI = GPIO(clock, GPIO_Types::Port::A, 12);
    GPIO SPI1_SCK = GPIO(clock, GPIO_Types::Port::A, 5);

    GPIO SPI1_CS1 = GPIO(clock, GPIO_Types::Port::E, 0);
    GPIO SPI1_CS2 = GPIO(clock, GPIO_Types::Port::B, 9);
    GPIO SPI1_CS3 = GPIO(clock, GPIO_Types::Port::E, 1);

    SPI1_CS1.set_mode(GPIO_Types::PortMode::Output);
    SPI1_CS2.set_mode(GPIO_Types::PortMode::Output);
    SPI1_CS3.set_mode(GPIO_Types::PortMode::Output);

    SPI1_CS1.set_output_high();
    SPI1_CS2.set_output_high();
    SPI1_CS3.set_output_high();

    SPI sut = SPI(clock, SPI_types::SPI_Number::SPI_1, SPI1_MOSI, SPI1_MISO, SPI1_SCK, SPI_types::SPIMode::master, SPI_types::SPIDataSize::_8bits,
                  SPI_types::SPIPolarity::idle_high, SPI_types::SPIPhase::data_on_second_edge, SPI_types::SPIForamt::MSB_first, SPI_types::BaudRatePrescaller::Prescaller_256);

    uint8_t received_data_buffer[10]{};
    std::span<uint8_t> received_data = std::span<uint8_t>(received_data_buffer, 5);

    sut.read_data_from_register(SPI1_CS1, 0x0F | 1 << 7, received_data, 1);

    EXPECT_EQ(received_data[0], 0x68);
});

RegisterTest(SpiTest, SpiBme, [](Test * test) {
    Clock clock;

    GPIO SPI1_MISO = GPIO(clock, GPIO_Types::Port::A, 11);
    GPIO SPI1_MOSI = GPIO(clock, GPIO_Types::Port::A, 12);
    GPIO SPI1_SCK = GPIO(clock, GPIO_Types::Port::A, 5);

    GPIO SPI1_CS1 = GPIO(clock, GPIO_Types::Port::E, 0);
    GPIO SPI1_CS2 = GPIO(clock, GPIO_Types::Port::B, 9);
    GPIO SPI1_CS3 = GPIO(clock, GPIO_Types::Port::E, 1);

    SPI1_CS1.set_mode(GPIO_Types::PortMode::Output);
    SPI1_CS2.set_mode(GPIO_Types::PortMode::Output);
    SPI1_CS3.set_mode(GPIO_Types::PortMode::Output);

    SPI1_CS1.set_output_high();
    SPI1_CS2.set_output_high();
    SPI1_CS3.set_output_high();

    SPI sut = SPI(clock, SPI_types::SPI_Number::SPI_1, SPI1_MOSI, SPI1_MISO, SPI1_SCK, SPI_types::SPIMode::master, SPI_types::SPIDataSize::_8bits,
                  SPI_types::SPIPolarity::idle_high, SPI_types::SPIPhase::data_on_second_edge, SPI_types::SPIForamt::MSB_first, SPI_types::BaudRatePrescaller::Prescaller_256);

    uint8_t received_data_buffer[10]{};
    std::span<uint8_t> received_data = std::span<uint8_t>(received_data_buffer, 5);

    sut.read_data_from_register(SPI1_CS3, 0xD0 | 1 << 7, received_data, 1);

    EXPECT_EQ(received_data[0], 0x60);
});

RegisterTest(SpiTest, SpiMagnetometer, [](Test * test) {
    Clock clock;

    GPIO SPI1_MISO = GPIO(clock, GPIO_Types::Port::A, 11);
    GPIO SPI1_MOSI = GPIO(clock, GPIO_Types::Port::A, 12);
    GPIO SPI1_SCK = GPIO(clock, GPIO_Types::Port::A, 5);

    GPIO SPI1_CS1 = GPIO(clock, GPIO_Types::Port::E, 0);
    GPIO SPI1_CS2 = GPIO(clock, GPIO_Types::Port::B, 9);
    GPIO SPI1_CS3 = GPIO(clock, GPIO_Types::Port::E, 1);

    SPI1_CS1.set_mode(GPIO_Types::PortMode::Output);
    SPI1_CS2.set_mode(GPIO_Types::PortMode::Output);
    SPI1_CS3.set_mode(GPIO_Types::PortMode::Output);

    SPI1_CS1.set_output_high();
    SPI1_CS2.set_output_high();
    SPI1_CS3.set_output_high();

    SPI sut = SPI(clock, SPI_types::SPI_Number::SPI_1, SPI1_MOSI, SPI1_MISO, SPI1_SCK, SPI_types::SPIMode::master, SPI_types::SPIDataSize::_8bits,
                  SPI_types::SPIPolarity::idle_high, SPI_types::SPIPhase::data_on_second_edge, SPI_types::SPIForamt::MSB_first, SPI_types::BaudRatePrescaller::Prescaller_256);

    uint8_t received_data_buffer[10]{};
    std::span<uint8_t> received_data = std::span<uint8_t>(received_data_buffer, 5);

    sut.read_data_from_register(SPI1_CS2, 0x0F | 1 << 7, received_data, 1);

    EXPECT_EQ(received_data[0], 0x3D);
});
