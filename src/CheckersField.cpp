#include "../include/CheckersField.hpp"

CheckersField::CheckersField() : field_(size_, std::vector<Checker>(size_, NONE)) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < size_; ++j) {
            if (i % 2 == 0) {
                if (j % 2 != 0) {
                    field_[i][j] = (i == 0) ? QUEEN_BLACK : BLACK;
                }
            } else {
                if (j % 2 == 0) {
                    field_[i][j] = (i == 0) ? QUEEN_BLACK : BLACK;
                }
            }
        }
    }
    for (int i = 5; i < size_; ++i) {
        for (int j = 0; j < size_; ++j) {
            if (i % 2 == 0) {
                if (j % 2 != 0) {
                    field_[i][j] = (i == size_ - 1) ? QUEEN_WHITE : WHITE;
                }
            } else {
                if (j % 2 == 0) {
                    field_[i][j] = (i == size_ - 1) ? QUEEN_WHITE : WHITE;
                }
            }
        }
    }
    int index = 0;
    for (char i = 'a'; i <= 'h'; ++i) {
        dict_field_[i] = index;
        ++index;
    }
    for (char i = '0'; i < '8'; ++i) {
        dict_field_[i] = i - '0';
    }
}
std::vector<std::vector<Checker>> CheckersField::GetField() {
    return field_;
}
void CheckersField::SetField(std::vector<std::vector<Checker>> &field) {
    field_ = field;
}
int CheckersField::GetIndex(char pos) {
    return dict_field_[pos];
}
void CheckersField::PrintField() const {
    std::cout << "  ";
    for (char i = 'a'; i <= 'h'; ++i) {
        std::cout << i;
    }
    std::cout << "\n";
    for (int i = 0; i < size_; ++i) {
        std::cout << i + 1 << " ";
        for (int j = 0; j < size_; ++j) {
            switch (field_[i][j]) {
                case BLACK: {
                    std::cout << "b";
                    break;
                }
                case QUEEN_BLACK: {
                    std::cout << "b";
                    break;
                }
                case WHITE: {
                    std::cout << "w";
                    break;
                }
                case QUEEN_WHITE: {
                    std::cout << "w";
                    break;
                }
                case NONE: {
                    std::cout << "0";
                    break;
                }
            }
        }
        std::cout << "\n";
    }
}