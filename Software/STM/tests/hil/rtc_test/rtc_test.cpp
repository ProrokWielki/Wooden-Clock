#include <testing_framework.hpp>

#include <HAL/Clock.hpp>
#include <HAL/RTC.hpp>

RegisterTest(RtcTest, rtc_on_start_is_0, [](Test * test) {
    Clock clock;
    RTC_ rtc{clock};

    uint8_t hours{rtc.get_hours()};
    uint8_t minutes{rtc.get_minutes()};

    EXPECT_EQ(hours, 0);
    EXPECT_EQ(minutes, 0);
});

RegisterTest(RtcTest, rtc_after_init_is_running, [](Test * test) {
    Clock clock;
    RTC_ rtc{clock};

    uint8_t seconds_before{rtc.get_seconds()};

    for (unsigned int i{0}; i < 1'000'000; ++i)
    {
    }

    uint8_t seconds_after{rtc.get_seconds()};

    EXPECT_TRUE(seconds_before != seconds_after);
});

RegisterTest(RtcTest, setting_time, [](Test * test) {
    Clock clock;
    RTC_ rtc{clock};

    uint8_t hour_to_be_set{12};
    uint8_t minute_to_be_set{34};

    rtc.set_hours(hour_to_be_set);
    rtc.set_minutes(minute_to_be_set);

    uint8_t hours{rtc.get_hours()};
    uint8_t minutes{rtc.get_minutes()};

    EXPECT_EQ(hours, hour_to_be_set);
    EXPECT_EQ(minutes, minute_to_be_set);
});
