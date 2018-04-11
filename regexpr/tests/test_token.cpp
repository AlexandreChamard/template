/*
** EPITECH PROJECT, 2017
** test_token.cpp for template
** File description:
** description
*/

#include <iostream>
#include <queue>
#include "../regexpr.hpp"

int main(int ac, char **av)
{
	if (ac != 2) return (1);
	p_token<p_end<p_char<'\0'>, p_or<p_not<p_char<':'>>, p_not<p_eof>>>, p_eof> token;

	std::string str = av[1];
	auto r = token(str);

	std::cout << "end: " << r.first << std::endl;
	std::cout << "token: [" << r.second << "]" << std::endl;
	return 0;
}

/*
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
*/
