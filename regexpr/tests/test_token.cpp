/*
** EPITECH PROJECT, 2017
** test_token.cpp for template
** File description:
** description
*/

#include <iostream>
#include "../regexpr.hpp"

bool is_digit(std::string const &str)
{
	p_char<'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'> digit;

	return digit(str).first;
}

int main()
{
	p_mul<p_apply<is_digit>> p;
	std::stringstream sstr;

	std::string s("123");
	auto r = p(s);
	std::cout << "res: " << r.first << std::endl;
	std::cout << "str: [" << r.second << "]" << std::endl;
	return 0;
}
