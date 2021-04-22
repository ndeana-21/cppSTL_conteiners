//
// Created by ndeana on 22.04.2021.
//
#pragma once

#include <stdlib.h>
#include <iostream>

#include <List>
#include <Vector>
#include <Map>
#include <Stack>
#include <Queue>

#include "ft_stl/List.hpp"
#include "ft_stl/Vector.hpp"
#include "ft_stl/Map.hpp"
#include "ft_stl/Stack.hpp"
#include "ft_stl/Queue.hpp"

#define RESET "\e[0m"
#define BOLD "\e[1m"
#define RED "\e[91m"
#define GREEN "\e[92m"
#define BLUE "\e[94m"

#define SUCCESS "✓"
#define FAIL "❌"

void    testList(void);
void    testVector(void);
void    testMap(void);
void    testStack(void);
void    testQueue(void);

inline void print_header(std::string str) {

}

inline void (std::string str, bool status) {
    if (status)
        std::cout << str + " " << GREEN << SUCCESS << RESET << std::endl;
    else
        std::cout << str + " " << RED << FAIL << RESET << std::endl;
}
