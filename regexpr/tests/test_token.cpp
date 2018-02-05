/*
** EPITECH PROJECT, 2017
** test_token.cpp for template
** File description:
** description
*/

#include <iostream>
#include <queue>
#include "../regexpr.hpp"

bool is_digit(std::string const &str)
{
	p_digit digit;

	return digit(str).first;
}

int main(int ac, char **av)
{
	if (ac != 2) return (1);
	p_token<p_trim<p_more<p_digit>>, p_or<p_char<','>, p_eof>> t;

	std::string str = av[1];
	auto r = t(str);
	while (r.first == true) {
		std::cout << "token: [" << r.second << "]" << std::endl;
		r = t(str);
	};
	return 0;
}
