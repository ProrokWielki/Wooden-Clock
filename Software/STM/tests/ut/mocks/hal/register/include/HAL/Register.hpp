/**
 * @file register.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-03-10
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include <cstdint>

#include <gmock/gmock.h>

template<typename T>
class Register
{
public:
    explicit Register(volatile uint32_t * const register_pointer)
    {
        this->Constructor(register_pointer);
    }
    MOCK_METHOD(void, Constructor, (volatile uint32_t * const));
    MOCK_METHOD(void, set_value, (uint32_t, uint8_t, uint8_t));
    MOCK_METHOD(uint32_t, get_value, (uint8_t, uint8_t), (const));
    MOCK_METHOD(void, toggle_bit, (uint8_t));
    MOCK_METHOD(void, set_bit, (uint8_t));
    MOCK_METHOD(uint8_t, get_bit, (uint8_t), (const));
    MOCK_METHOD(void, clear_bit, (uint8_t));
    MOCK_METHOD(void, write, (uint32_t));
    MOCK_METHOD(uint32_t, read, (), (const));
    MOCK_METHOD(uintptr_t, get_address, (), (const));
};