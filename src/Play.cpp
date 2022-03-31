#include "../include/Play.hpp"

void Game::UpdateField(Player &player, bool from_bot) {
    int index_j_from, index_j_to, index_i_from, index_i_to;
    if (!from_bot) {
        if (cur_move_player_[0].size() != 2 || cur_move_player_[1].size() != 2) {
            std::cout << "Please, repeat enter:\n";
            ReadMove();
        }
        index_j_from = field_class_.GetIndex(cur_move_player_[0][0]);
        index_j_to = field_class_.GetIndex(cur_move_player_[1][0]);
        index_i_from = cur_move_player_[0][1] - '0' - 1;
        index_i_to = cur_move_player_[1][1] - '0' - 1;
    } else {
        index_j_from = cur_move_bot_[0][1];
        index_j_to = cur_move_bot_[1][1];
        index_i_from = cur_move_bot_[0][0];
        index_i_to = cur_move_bot_[1][0];
    }

    // Check if index wrong

    // 4 case:
    field_[index_i_from][index_j_from] = NONE;
    if (index_i_to < index_i_from && index_j_to > index_j_from) {
        int cur_i = index_i_from - 1;
        int cur_j = index_j_from + 1;
        while (cur_i >= 0 && cur_j < CheckersField::size_field && cur_i != index_i_to && cur_j != index_j_to) {
            if (field_[cur_i][cur_j] == WHITE) {
                field_[cur_i][cur_j] = NONE;
                human_.ReduceCheckers();
            } else if (field_[cur_i][cur_j] == BLACK) {
                field_[cur_i][cur_j] = NONE;
                bot_.ReduceCheckers();
            }
            --cur_i;
            ++cur_j;
        }
        field_[index_i_to][index_j_to] = player.GetColor();
    }
    if (index_i_to > index_i_from && index_j_to > index_j_from) {
        int cur_i = index_i_from + 1;
        int cur_j = index_j_from + 1;
        while (cur_i < CheckersField::size_field && cur_j < CheckersField::size_field && cur_i != index_i_to && cur_j != index_j_to) {
            if (field_[cur_i][cur_j] == WHITE) {
                field_[cur_i][cur_j] = NONE;
                human_.ReduceCheckers();
            } else if (field_[cur_i][cur_j] == BLACK) {
                field_[cur_i][cur_j] = NONE;
                bot_.ReduceCheckers();
            }
            ++cur_i;
            ++cur_j;
        }
        field_[index_i_to][index_j_to] = player.GetColor();
    }
    if (index_i_to < index_i_from && index_j_to < index_j_from) {
        int cur_i = index_i_from - 1;
        int cur_j = index_j_from - 1;
        while (cur_i >= 0 && cur_j >= 0 && cur_i != index_i_to && cur_j != index_j_to) {
            if (field_[cur_i][cur_j] == WHITE) {
                field_[cur_i][cur_j] = NONE;
                human_.ReduceCheckers();
            } else if (field_[cur_i][cur_j] == BLACK) {
                field_[cur_i][cur_j] = NONE;
                bot_.ReduceCheckers();
            }
            --cur_i;
            --cur_j;
        }
        field_[index_i_to][index_j_to] = player.GetColor();
    }
    if (index_i_to > index_i_from && index_j_to < index_j_from) {
        int cur_i = index_i_from - 1;
        int cur_j = index_j_from - 1;
        while (cur_i < CheckersField::size_field && cur_j >= 0 && cur_i != index_i_to && cur_j != index_j_to) {
            if (field_[cur_i][cur_j] == WHITE) {
                field_[cur_i][cur_j] = NONE;
                human_.ReduceCheckers();
            } else if (field_[cur_i][cur_j] == BLACK) {
                field_[cur_i][cur_j] = NONE;
                bot_.ReduceCheckers();
            }
            ++cur_i;
            --cur_j;
        }
        field_[index_i_to][index_j_to] = player.GetColor();
    }
    field_class_.SetField(field_);
}

bool Game::CheckPosition(int i, int j) {
    if (i > 0 && j < CheckersField::size_field) {
        if (field_[i - 1][j + 1] == WHITE) {
            if (i < CheckersField::size_field && j > 0) {
                if (field_[i + 1][j - 1] == NONE) {
                    return false;
                }
            }
        }
    }
    if (i > 0 && j > 0) {
        if (field_[i - 1][j - 1] == WHITE) {
            if (i < CheckersField::size_field && j < CheckersField::size_field) {
                if (field_[i + 1][j + 1] == NONE) {
                    return false;
                }
            }
        }
    }
    if (i < CheckersField::size_field && j > 0) {
        if (field_[i + 1][j - 1] == WHITE) {
            if (i > 0 && j < CheckersField::size_field) {
                if (field_[i - 1][j + 1] == NONE) {
                    return false;
                }
            }
        }
    }
    if (i < CheckersField::size_field && j < CheckersField::size_field) {
        if (field_[i + 1][j + 1] == WHITE) {
            if (i > 0 && j > 0) {
                if (field_[i - 1][j - 1] == NONE) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool Game::CheckForEat(std::vector<int> &from, std::vector<int> &to, bool safety) {
    for (int i = 0; i < CheckersField::size_field; ++i) {
        for (int j = 0; j < CheckersField::size_field; ++j) {
            if (field_[i][j] == BLACK) {
                if (i > 0) {
                    if (j > 0) {
                        if (field_[i - 1][j - 1] == WHITE && i - 1 > 0 && j - 1 > 0 && field_[i - 2][j - 2] == NONE) {
                            field_[i - 1][j - 1] = NONE;
                            if (!safety || CheckPosition(i - 2, j - 2)) {
                                field_[i - 1][j - 1] = WHITE;
                                from[0] = i;
                                from[1] = j;
                                to[0] = i - 2;
                                to[1] = j - 2;
                                return true;
                            }
                            field_[i - 1][j - 1] = WHITE;
                        }
                    }
                    if (j < CheckersField::size_field) {
                        if (field_[i - 1][j + 1] == WHITE && i - 1 > 0 && j + 1 < CheckersField::size_field && field_[i - 2][j + 2] == NONE) {
                            field_[i - 1][j + 1] = NONE;
                            if (!safety || CheckPosition(i - 2, j + 2)) {
                                field_[i - 1][j + 1] = WHITE;
                                from[0] = i;
                                from[1] = j;
                                to[0] = i - 2;
                                to[1] = j + 2;
                                return true;
                            }
                            field_[i - 1][j + 1] = WHITE;
                        }
                    }
                }
                if (i < CheckersField::size_field) {
                    if (j > 0) {
                        if (field_[i + 1][j - 1] == WHITE && i + 1 <CheckersField::size_field && j - 1 > 0 && field_[i + 2][j - 2] == NONE) {
                            field_[i + 1][j - 1] = NONE;
                            if (!safety || CheckPosition(i + 2, j - 2)) {
                                field_[i + 1][j - 1] = WHITE;
                                from[0] = i;
                                from[1] = j;
                                to[0] = i + 2;
                                to[1] = j - 2;
                                return true;
                            }
                            field_[i + 1][j - 1] = WHITE;
                        }
                    }
                    if (j < CheckersField::size_field) {
                        if (field_[i + 1][j + 1] == WHITE && i + 1 < CheckersField::size_field && j + 1 < CheckersField::size_field && field_[i + 2][j + 2] == NONE) {
                            field_[i + 1][j + 1] = NONE;
                            if (!safety || CheckPosition(i + 2, j + 2)) {
                                field_[i + 1][j + 1] = WHITE;
                                from[0] = i;
                                from[1] = j;
                                to[0] = i + 2;
                                to[1] = j + 2;
                                return true;
                            }
                            field_[i + 1][j + 1] = WHITE;
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool Game::CheckForMove(std::vector<int> &from, std::vector<int> &to, bool safety) {
    for (int i = 0; i < CheckersField::size_field; ++i) {
        for (int j = 0; j < CheckersField::size_field; ++j) {
            if (field_[i][j] == BLACK) {
                if (i < CheckersField::size_field) {
                    if (j > 0) {
                        if (field_[i + 1][j - 1] == NONE) {
                            if (!safety || CheckPosition(i + 1, j - 1)) {
                                from[0] = i;
                                from[1] = j;
                                to[0] = i + 1;
                                to[1] = j - 1;
                                return true;
                            }
                        }
                    }
                    if (j < CheckersField::size_field) {
                        if (field_[i + 1][j + 1] == NONE) {
                            if (!safety || CheckPosition(i + 1, j + 1)) {
                                from[0] = i;
                                from[1] = j;
                                to[0] = i + 1;
                                to[1] = j + 1;
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool Game::GetMove() {
    bool has_good_move = false;
    std::vector<int> from(2);
    std::vector<int> to(2);
    has_good_move = CheckForEat(from, to, true);
    if (!has_good_move) {
        has_good_move = CheckForMove(from, to, true);
        if (!has_good_move) {
            has_good_move = CheckForEat(from, to, false);
            if (!has_good_move) {
                has_good_move = CheckForMove(from, to, false);
            }
        }
    }
    cur_move_bot_[0] = from;
    cur_move_bot_[1] = to;
    return has_good_move;
}

void Game::ReadMove() {
    std::cout << "Please, enter your move:\n";
    std::cin >> cur_move_player_[0] >> cur_move_player_[1];
    UpdateField(human_, false);
}

void Game::GameLoop() {
    std::cout << "This is your play field. You are going to play for the whites.\n";
    field_class_.PrintField();
    while(true) {
        ReadMove();
        if (human_.GetCount() == 0) {
            std::cout << "You failed(\n";
            break;
        }
        std::cout << "Bot's move...\n";
        if (GetMove()) {
            UpdateField(bot_, true);
            if (bot_.GetCount() == 0) {
                std::cout << "You win!\n";
                break;
            }
            std::cout << "Bot did his move, you will see the play field:\n";
            field_class_.PrintField();
        } else {
            std::cout << "You win!\n";
            break;
        }
    }
}