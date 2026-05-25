#include <string>

#include <Canvas.hpp>
#include <widgets/Circle.hpp>

class ShapesScreen: public Canvas
{
public:
    /**
     * @brief Constructor
     */
    ShapesScreen() = default;

    /**
     * @brief Execution of the State action.
     */
    void init() override
    {
        static const WidgetAndPositions filled{.x = 0, .y = 0, .widget = filled_circle_};
        static const WidgetAndPositions outlined{.x = get_width() / 2, .y = 0, .widget = outline_circle_};

        static const std::array<const std::reference_wrapper<const WidgetAndPositions>, 2> widgets{filled, outlined};

        add(widgets);

        // add(&counter_text3, 0, 21);
        // add(&counter_text4, 0, 30);
        // validate();
    }

    void up_date() override
    {
    }

private:
    static constexpr uint8_t FIGURE_WIDTH{8};

    Circle<FIGURE_WIDTH> filled_circle_{true};
    Circle<FIGURE_WIDTH> outline_circle_{false};
};