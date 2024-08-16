//
// Created by tuana on 8/15/24.
//

#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "definitions.hpp"
#include  "input.hpp"
#include <vector>
#include <utility>
#include <semaphore.h>
#include <pthread.h>
#include <vector>
#include <utility>
#include  "snake.hpp"

class Snake {
public:
    Snake();

    void update_direction(enum Direction direction);

    void update_next_direction(enum Direction direction);

    enum Direction get_direction();

    void validate_direction();

    std::vector<std::pair<int, int> > snake_parts;
    std::pair<int, int> snake_head;

    void update_movement();

    void set_snake_food(std::pair<int, int> bait);

    bool bait_eaten;
    bool is_dead;
    int length;

private:
    pthread_t input_thread;
    sem_t snake_sem;
    enum Direction direction;
    enum Direction next_direction;
    std::pair<int, int> bait;
    int snake_world_array[MAP_HEIGHT][MAP_WIDTH];

    void clear_snake_world();

    void initialize_snake();

    static void *input_thread_work(void *arg);
};




inline void* Snake::input_thread_work(void *arg)

 {
      Snake *snake = (struct  Snake *)arg;
     while (true)
     {
         enum Direction direction = get_input();
         snake->update_next_direction(direction);
     }
 }

inline Snake::Snake()
 {
     direction = Left;
     next_direction = direction;
     bait_eaten = false;
     is_dead = false;
     length = INITIAL_LENGTH;
     clear_snake_world();
     initialize_snake();
     sem_init(&snake_sem, 0, 1);
     pthread_create(&input_thread, NULL, &Snake::input_thread_work, this);
 }



inline void Snake::update_direction(enum Direction direction)
{
         sem_wait(&this->snake_sem);
         switch (direction)
         {
             case Right:
                 if (this->direction != Left)
                 {
                     this->direction = direction;
                 }
             break;
             case Down:
                 if (this->direction != Up)
                 {
                     this->direction = direction;
                 }
             break;
             case Left:
                 if (this->direction != Right)
                 {
                     this->direction = direction;
                 }
             break;
             case Up:
                 if (this->direction != Down)
                 {
                     this->direction = direction;
                 }
             break;
         }
         sem_post(&this->snake_sem);
}

inline void Snake::update_next_direction(enum Direction direction)
{
    this->next_direction = direction;
}

inline enum Direction Snake::get_direction(void)
{
    enum Direction direction= Left;
    sem_wait(&this->snake_sem);
    direction = this->direction;
    sem_post(&this->snake_sem);
    return direction;
}

inline void Snake::validate_direction(void)
{
    if (next_direction != Error)
    {
        update_direction(next_direction);
    }
}

inline void Snake::update_movement(void)
{
    std::pair<int, int> movement_part;
    enum Direction direction = get_direction();
    switch (direction)
    {
    case Right:
        movement_part = std::make_pair(snake_head.first, snake_head.second - 1);
        break;
    case Up:
        movement_part = std::make_pair(snake_head.first - 1, snake_head.second);
        break;
    case Left:
        movement_part = std::make_pair(snake_head.first, snake_head.second + 1);
        break;
    case Down:
        movement_part = std::make_pair(snake_head.first + 1, snake_head.second);
        break;
    }
    snake_head = movement_part;
    snake_parts.push_back(movement_part);
    bait_eaten = snake_head.first == bait.first && snake_head.second == bait.second;
    if (bait_eaten)
    {
        length++;
    }
    else
    {
        std::pair<int, int> tail = snake_parts.front();
        snake_world_array[tail.first][tail.second]--;
        snake_parts.erase(snake_parts.begin());
    }
    int head_value = ++snake_world_array[snake_head.first][snake_head.second];
    if (head_value > 1)
    {
        is_dead = true;
    }
}

inline void Snake::set_snake_food(std::pair<int, int> bait)
{
    this->bait = bait;
}
inline void Snake::clear_snake_world(void)
{
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            snake_world_array[i][j] = 0;
        }
    }
}
inline void Snake::initialize_snake(void)
{
    for (int i = 0; i < INITIAL_LENGTH; i++)
    {
        std::pair<int, int> snake_part = std::make_pair(MAP_HEIGHT / 2, MAP_WIDTH / 2 - (INITIAL_LENGTH / 2) + i);
        snake_parts.push_back(snake_part);
        snake_world_array[snake_part.first][snake_part.second] = 1;
    }
    snake_head = snake_parts[snake_parts.size() - 1];
}




#endif //SNAKE_HPP
