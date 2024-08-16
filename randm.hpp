//
// Created by tuana on 8/15/24.
//

#ifndef RANDM_HPP
#define RANDM_HPP

#include <random>

namespace Utill {
   inline  int generateRandomInteger(int min, int max) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(min, max);
        return dist(gen);
    }
}

#endif //RANDM_HPP
