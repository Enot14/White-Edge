#ifndef CHARTERS_HPP
#define CHARTERS_HPP

#include <iostream>
#include "Structs.hpp"
#include "engine.hpp"
extern Character meisen;
extern Character yuki;
extern Character Max;
extern Character anna;
extern Character voice_in_head;

inline void inicializate_characters() {
    meisen.name = "Мейсен";
    meisen.voisePitch = 150;
    meisen.speed = 40;
    meisen.colorCode = 11;

    yuki.name = "????";
    yuki.voisePitch = 700;
    yuki.speed = 45;
    yuki.colorCode = 13;

    Max.name = "Максим";
    Max.voisePitch = 500;
    Max.speed = 45;
    Max.colorCode = 2;

    anna.name = "Анна Петрівна";
    anna.voisePitch = 600;
    anna.speed = 43;
    anna.colorCode = 14; //5 - fiol 14- yarki jovti

    voice_in_head.name = "???";
    voice_in_head.voice_path = "music\\";
    voice_in_head.colorCode = 0x0004;
}


#endif
