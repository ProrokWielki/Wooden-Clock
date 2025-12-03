#include <APP.hpp>
#include <BSP/BSP.hpp>
#include <cstring>

int main()
{

    app_init();

    while (true)
    {
        BSP::get().display.draw();
    }

    return 0;
}
