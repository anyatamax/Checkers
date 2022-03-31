#include <iostream>
#include "Player.hpp"

class Game {
public:
    Game()
        : bot_(BLACK)
        , human_(WHITE)
        , field_(field_class_.GetField())
        , cur_move_player_(2, "")
        , cur_move_bot_(2, std::vector<int>(2)){};
    void GameLoop();
    void ReadMove();
    bool GetMove();

private:
    Player bot_;
    Player human_;
    CheckersField field_class_;
    std::vector<std::vector<Checker>> field_;
    std::vector<std::string> cur_move_player_;
    std::vector<std::vector<int>> cur_move_bot_;
    bool quit = false;
    bool CheckPlayer();
    void UpdateField(Player &player, bool from_bot);
    bool CheckForMove(std::vector<int> &from, std::vector<int> &to, bool safety);
    bool CheckForEat(std::vector<int> &from, std::vector<int> &to, bool safety);
    bool CheckPosition(int i, int j);
};