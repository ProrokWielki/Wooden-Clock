/**
 *  @file Display.cpp
 *
 *  Created on: 30-11-2018
 *  @author: Paweł Warzecha
 */

#include <cstdint>
#include <exception>

#include "backends/imgui_impl_allegro5.h"
#include "imgui.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include <BSP/BSP.hpp>
#include <BSP/Display.hpp>

void Display::ShowExampleAppCustomRendering() const
{
    // ImGui::SetNextWindowSize(ImVec2(20 * 40, 20 * 40), ImGuiCond_FirstUseEver);
    // if (!ImGui::Begin("Example: Custom rendering"))
    // {
    //     ImGui::End();
    //     return;
    // }

    // Tip: If you do a lot of custom rendering, you probably want to use your own geometrical types and benefit of overloaded operators, etc.
    // Define IM_VEC2_CLASS_EXTRA in imconfig.h to create implicit conversions between your types and ImVec2/ImVec4.
    // ImGui defines overloaded operators but they are internal to imgui.cpp and not exposed outside (to avoid messing with your types)
    // In this example we are not using the maths operators!
    ImDrawList * draw_list = ImGui::GetWindowDrawList();

    // Primitives
    static const float sz {10.0f};

    const ImVec2 p = ImGui::GetCursorScreenPos();

    // ImGui::Button("up");
    // ImGui::Button("down");
    // ImGui::Button("left");
    // ImGui::Button("right");
    // float x = p.x + 4.0f, y = p.y + 4.0f, spacing = 8.0f;
    {
        // auto displayFrameBuffer = BSP::st.getFrameBuffer();
        for (uint32_t x{0}; x < displayWidth; ++x)
        {
            for (uint32_t y{0}; y < displayHeight; ++y)
            {
                const ImVec4 col_on{ImVec4(displayFrameBuffer[y * displayWidth + x] / 255.0, displayFrameBuffer[y * displayWidth + x] / 255.0,
                                           displayFrameBuffer[y * displayWidth + x] / 255.0, 1.0f)};
                const ImU32 off_col{ImColor(col_on)};
                // Draw empty pixel
                draw_list->AddCircleFilled(ImVec2(100 + p.x + x * (sz + 3), 100 + p.y + y * (sz + 3)), sz * 0.5f, off_col, 32);
            }
        }
    }
    // ImGui::End();
}

Display::Display(uint8_t width, uint8_t height, const uint8_t * frameBuffer) : displayWidth(width), displayHeight(height), displayFrameBuffer(frameBuffer)
{
    // Setup Allegro
    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_primitives_addon();
    al_set_new_display_flags(ALLEGRO_RESIZABLE);
    display = al_create_display(1280, 720);
    al_set_window_title(display, "Dear ImGui Allegro 5 example");
    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();

    ImGui_ImplAllegro5_Init(display);
}

void Display::draw() const
{

    // show_rect_window = true;  // Example to show the custom rendering window
    const ImVec4 clear_color = ImVec4(0.f, 0.f, 0.f, 1.00f);
    // // Poll and handle events (inputs, window resize, etc.)
    // // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
    // // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
    // // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
    // // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
    ALLEGRO_EVENT ev;
    while (al_get_next_event(queue, &ev))
    {
        ImGui_ImplAllegro5_ProcessEvent(&ev);
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            // running = false;
        }
        if (ev.type == ALLEGRO_EVENT_DISPLAY_RESIZE)
        {
            ImGui_ImplAllegro5_InvalidateDeviceObjects();
            al_acknowledge_resize(display);
            ImGui_ImplAllegro5_CreateDeviceObjects();
        }
    }

    // // Start the Dear ImGui frame
    ImGui_ImplAllegro5_NewFrame();
    ImGui::NewFrame();

    ImGui::SetNextWindowPos(ImGui::GetMainViewport()->Pos);
    ImGui::SetNextWindowSize(ImGui::GetMainViewport()->Size);
    ImGui::Begin("WoodenClockSimulator");
    ShowExampleAppCustomRendering();

    ImGui::Button("up");
    if (ImGui::IsItemActive())
    {
        BSP::get().button_up.setPressed();
    }
    else
    {
        BSP::get().button_up.setReleased();
    }

    ImGui::Button("down");
    if (ImGui::IsItemActive())
    {
        BSP::get().button_down.setPressed();
    }
    else
    {
        BSP::get().button_down.setReleased();
    }

    ImGui::Button("left");
    if (ImGui::IsItemActive())
    {
        BSP::get().button_left.setPressed();
    }
    else
    {
        BSP::get().button_left.setReleased();
    }

    ImGui::Button("right");
    if (ImGui::IsItemActive())
    {
        BSP::get().button_right.setPressed();
    }
    else
    {
        BSP::get().button_right.setReleased();
    }
    ImGui::End();

    // // Rendering
    ImGui::Render();
    al_clear_to_color(al_map_rgba_f(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w));
    ImGui_ImplAllegro5_RenderDrawData(ImGui::GetDrawData());
    al_flip_display();

    display_redrawn_callback();
}

Display::~Display()
{
    ImGui_ImplAllegro5_Shutdown();
    ImGui::DestroyContext();
    al_destroy_event_queue(queue);
    al_destroy_display(display);
}