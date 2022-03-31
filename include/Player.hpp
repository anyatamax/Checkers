#include "CheckersField.hpp"

class Player {
public:
    explicit Player(Checker color) : color_(color){};
    void ReduceCheckers();
    [[nodiscard]] int GetCount() const;
    [[nodiscard]] Checker GetColor() const;

private:
    int count_checkers_ = 12;
    Checker color_;
};