// Dear ImGui: standalone example application for Allegro 5
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

// On Windows, you can install Allegro5 using vcpkg:
//   git clone https://github.com/Microsoft/vcpkg
//   cd vcpkg
//   bootstrap - vcpkg.bat
//   vcpkg install allegro5 --triplet=x86-windows   ; for win32
//   vcpkg install allegro5 --triplet=x64-windows   ; for win64
//   vcpkg integrate install                        ; register include and libs in Visual Studio

#include "../APP/Assets/Images/Mario.cpp"
#include "BSP/Display.hpp"
#include "OS/os_abstraction.hpp"
#include <APP.hpp>
#include <BSP/BSP.hpp>
#include <cstring>
#include <iostream>
#include <stdint.h>

int main(int, char **)
{

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error
    // and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which
    // ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    // io.Fonts->AddFontDefault();
    // io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    // io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    // io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    // io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    // ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    // IM_ASSERT(font != NULL);

    // bool show_rect_window = true;

    // ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // // Main loop
    // bool running = true;
    // const uint8_t * const frame_buffer = &Mario_pixel_map[0];  // Example frame buffer, replace with actual data

    // Display display(32, 32, frame_buffer);

    // Initialize the display

    // Create a task to handle the display
    //     std::cout << "first" << std::endl;

    // char aasd[] = "asd";
    // OsAbstraction::create_task(
    // aasd, 1024, 1,
    // []() {
    //     // Display display(32, 32, frame_buffer);
    //     while (1)
    //     {
 
    //     }
    // },
    // 1000);

    std::cout << "Display task created" << std::endl;
    APP_init();
    std::cout << "APP initialized" << std::endl;
    
    while (true)
    {
           BSP::display.draw();
    }

    return 0;
}
