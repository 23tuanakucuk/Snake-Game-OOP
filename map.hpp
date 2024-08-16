//
// Created by tuana on 8/14/24.
//

#ifndef MAP_HPP
#define MAP_HPP


#include "definitions.hpp"
#include <utility>
#include "snake.hpp"
#include "map.hpp"
#include "input.hpp"
#include <iostream>
#include <vector>
#include <utility>
#include "randm.hpp"
#include <cstdlib>
#include <ctime>




class SnakeMap
{
public:
    SnakeMap(Snake *snake);
    void redraw(); //exist in library
    std::pair<int, int> bait; // baitx and baity
    void update_bait(bool force_update);
    void update_score();

private:
    char map_array[MAP_HEIGHT][MAP_WIDTH];
    Snake *snake;
};

void clear_map(char map_array[MAP_HEIGHT][MAP_WIDTH]);
void update_snake_head(char map_array[MAP_HEIGHT][MAP_WIDTH], Snake *snake);



inline SnakeMap::SnakeMap(Snake *snake)
{
    this->snake = snake;
    clear_map(this->map_array);
    srand(time(NULL));
    update_bait(true);
}

inline void SnakeMap::redraw(void)
{
    clear_map(this->map_array);
    for (int i = 0; i < MAP_END; i++)
    {
        std::cout << std::endl;
    }
    update_score();
    std::vector<std::pair<int, int>> snake_parts = snake->snake_parts;
    for (int i = 0; i < snake_parts.size(); i++)
    {
        std::pair<int, int> tmp = snake_parts[i];
        map_array[tmp.first][tmp.second] = SNAKE_CHAR;
    }
    update_snake_head(map_array, snake);
    update_bait(false);
    map_array[bait.first][bait.second] = BAIT_CHAR;
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            std::cout << map_array[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

inline void SnakeMap::update_bait(bool force_update)
{
    if (snake->bait_eaten || force_update)
    {
        while (true)
        {
            int random_i = Utill::generateRandomInteger(1, MAP_WIDTH);
            int random_j = Utill::generateRandomInteger(1, MAP_HEIGHT);
            if (map_array[random_i][random_j] == MAP_CHAR)
            {
                bait = std::make_pair(random_i, random_j);
                snake->set_snake_food(bait);
                snake->bait_eaten = false;
                break;
            }
        }
    }
}
inline void clear_map(char map_array[MAP_HEIGHT][MAP_WIDTH])
{
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            map_array[i][j] = MAP_CHAR;
        }
    }
}
inline void update_snake_head(char map_array[MAP_HEIGHT][MAP_WIDTH], Snake *snake)
{
    char snake_head_char = SNAKE_CHAR;
    enum Direction direction = snake->get_direction();
    switch (direction)
    {
    case Right:
        snake_head_char = SNAKE_HEAD_WEST;
        break;
    case Up:
        snake_head_char = SNAKE_HEAD_NORTH;
        break;
    case Left:
        snake_head_char = SNAKE_HEAD_EAST;
        break;
    case Down:
        snake_head_char = SNAKE_HEAD_SOUTH;
        break;
    }
    std::pair<int, int> snake_head = snake->snake_head;
    map_array[snake_head.first][snake_head.second] = snake_head_char;
}
inline void SnakeMap::update_score(void)
{
    std::cout << "Score:" << snake->length << std::endl;
}



#endif //MAP_HPP
