/**
 * GUI.hpp
 *
 *  Created on: 04-04-2019
 *  @author: Paweł Warzecha
 */

#ifndef APP_GUI_GUI_HPP_
#define APP_GUI_GUI_HPP_

#include <array>
#include <cstdint>
#include <map>
#include <utility>

enum class Signal;
class Canvas;

typedef std::map<std::pair<Canvas *, Signal>, Canvas *> CanvasesTransitions;

class GUI
{

public:
    /**
     *  Default constructor
     */
    GUI(CanvasesTransitions transitionMatrix, Canvas * startState) : transitionMatrix_(transitionMatrix), curent_canvas_(startState)
    {
        //        curent_canvas_->init();
    }

    /**
     * @brief Swaps frame buffers if they are ready to swap.
     */
    void swap_framebuffers();

    void update();

    uint8_t * getFrameBuffer()
    {
        return front_framebufferPointer;
    }

    void signal_callback(const Signal & signal)
    {
        recieved_ = signal;
        updateNedded = true;
    }

    static uint8_t * getFrontFrameBuffer()
    {
        return front_framebuffer_;
    }

    static uint8_t * getBackFrameBuffer()
    {
        return back_framebuffer_;
    }

private:
    CanvasesTransitions transitionMatrix_;

    Canvas * transiton(Signal signal)
    {

        Canvas * state_to_retrun;
        try
        {
            state_to_retrun = transitionMatrix_.at(std::make_pair(curent_canvas_, signal));
        } catch (...)
        {
            state_to_retrun = curent_canvas_;
        }

        return state_to_retrun;
    }

    Signal recieved_{};

    bool updateNedded{false};

    static uint8_t width_;
    static uint8_t height_;

    static uint8_t * front_framebuffer_;
    static uint8_t * back_framebuffer_;

    uint8_t * front_framebufferPointer{front_framebuffer_};

    bool isDoubleFrameBuffer{true};

    Canvas * curent_canvas_;
};

#endif /* APP_GUI_GUI_HPP_ */
