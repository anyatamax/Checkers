#include "../include/Player.hpp"

void Player::ReduceCheckers() {
    --count_checkers_;
}
int Player::GetCount() const {
    return count_checkers_;
}
Checker Player::GetColor() const {
    return color_;
};