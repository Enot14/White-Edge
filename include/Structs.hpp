#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <iostream>
#include <string>

struct Character {
    std::string name;
    int voisePitch;
    int speed;
    int colorCode;
    std::string voice_path;
};

struct GameStats {
    int karma = 0;
    int yuki_trust = 0;
    int charter = 1;
    bool has_knife = true;
    int max_agresson = 0;
    int day = 1;
    int meisen_agresson = 5;
    int knife_accuraty = 100;
    int knife_skill = 0;
    bool writen_controle = NULL;
    bool leaf = false;
    bool knife = false;
};

#endif