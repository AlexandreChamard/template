/*
** EPITECH PROJECT, 2017
** main.cpp for c++
** File description:
** description
*/

#include <iostream>
#include "evalexpr.hpp"

int main(int ac, char **av)
{
	if (ac != 2) {
		return (1);
	}
	Parser parser;
	std::pair<bool, std::string> p = parser(av[1]);

	std::cout << "end: " << (p.first ? "True" : "False") << " \"" << p.second << "\"" << std::endl;

	return (0);
}
