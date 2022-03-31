#include <vector>
#include <string>
#include <map>
#include <iostream>

enum Checker {
    BLACK,
    WHITE,
    NONE,
    QUEEN_BLACK,
    QUEEN_WHITE,
};

class CheckersField {
public:
    CheckersField();
    std::vector<std::vector<Checker>> GetField();
    void SetField(std::vector<std::vector<Checker>> &field);
    int GetIndex(char pos);
    void PrintField() const;
    static const size_t size_field = 8;

private:
    size_t size_ = 8;
    std::vector<std::vector<Checker>> field_;
    std::map<char, int> dict_field_;
};