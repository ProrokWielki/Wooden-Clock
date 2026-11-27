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
    void init() override;

    void up_date() override;

private:
    static constexpr uint8_t FIGURE_WIDTH{8};

    Circle<FIGURE_WIDTH> filled_circle_{true};
    Circle<FIGURE_WIDTH> outline_circle_{false};
};