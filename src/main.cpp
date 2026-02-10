#include "engine.hpp"
#include "Structs.hpp"
#include "Charters.hpp"

Character meisen;
Character yuki;
Character Max;
Character anna;
Character voice_in_head;

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    system("cls");

    inicializate_characters();
    GameStats state;

    if(!(loadGame(state))) {
        state.karma = 0;
        state.yuki_trust = 0;
    }
    
    switch (state.day)
    {
    case 1:
        day_one(state);
        state.day = 2;
        saveGame(state);
        break;
    case 2:
        day_two(state);
        state.day = 3;
        saveGame(state);
        break;
    default:
        if (state.karma >= 100) {
            pacifist_end();
        } else if(state.karma <= -100) {
            genocide_end();
        } else {
            neutral_end();
        }
    
        break;
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    return 0;
}