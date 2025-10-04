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
        add(&filled_circle_, 0, 0);
        add(&outline_circle_, 16, 0);
        // add(&counter_text3, 0, 21);
        // add(&counter_text4, 0, 30);
        // validate();
    }

    void up_date() override
    {
    }

private:
    Circle<8> filled_circle_{true};
    Circle<8> outline_circle_{false};
};