#include <APP.hpp>
#include <BSP/BSP.hpp>
#include <cstring>

int main()
{

    APP_init();

    while (true)
    {
        BSP::get().display.draw();
    }

    return 0;
}
