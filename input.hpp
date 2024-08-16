//
// Created by tuana on 8/14/24.
//

#ifndef INPUT_HPP
#define INPUT_HPP

#include "input.hpp"
#include <termios.h>
#include <unistd.h>
#include <bits/stdc++.h>
#include <cstdio>


inline bool gameover;

enum Direction {Error = -1,Right=0,Left=1,Up=2,Down=3};
void input_init(void);
void input_enter_off(void);
void input_enter_on(void);
enum Direction get_input(void);



inline char getUserInput() {
    char input;
    struct  termios old_settings, new_settings;

    tcgetattr(STDIN_FILENO, &old_settings);
    new_settings = old_settings;
    new_settings.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);

    input = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &old_settings);

    return input;
}


struct termios t;
inline void input_enter_off(){
    {
        tcgetattr(STDIN_FILENO, &t);
        t.c_lflag &= ~ICANON;
        tcsetattr(STDIN_FILENO, TCSANOW, &t);
    }
}
inline void input_enter_on(){
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

inline enum Direction get_input()
{
    enum Direction direction = Left;
    char user_input = getUserInput();
    switch (user_input)
    {
        case 'a':
            direction = Right;
        break;
        case 'w':
            direction = Up;
        break;
        case 'd':
            direction = Left;
        break;
        case 's':
            direction = Down;
        break;
        default:
            direction= Error;
        gameover=true;
        break;
    }
    return direction;
}

inline void input_init()
{

}




#endif //INPUT_HPP
