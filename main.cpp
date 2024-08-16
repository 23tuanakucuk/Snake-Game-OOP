#include <bits/stdc++.h>
#include "input.hpp"
#include "map.hpp"
#include "snake.hpp"
#include <utility>
#include "definitions.hpp"
#include <utility>



Snake snake;
SnakeMap snake_map(&snake);

void initialize()
{
    input_init();
    input_enter_off();
}

bool is_game_end()
{
    bool result = false;
    std::pair<int, int> snake_head = snake.snake_head;
    if (snake_head.first < 0 || snake_head.first >= MAP_HEIGHT || snake_head.second < 0 || snake_head.second >= MAP_WIDTH)
    {
        result = true;
    }
    if (snake.is_dead)
    {
        result = true;
    }
    return result;
}

void game_over()
{
    std::cout << "GAME IS OVER" << std::endl;
}

void start_game()
{
    while (true)
    {
        snake.update_movement();
        if (is_game_end())
        {
            game_over();
            break;
        }
        snake_map.redraw();

        usleep(PAUSE_LENGTH);

        snake.validate_direction();
    }
}

int main()
{
    initialize();
    start_game();
    return 0;
}