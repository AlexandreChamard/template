/*
** EPITECH PROJECT, 2017
** tests.c for template
** File description:
** description
*/

#include <assert.h>
#include <iostream>
#include "../regexpr.hpp"

static inline void tests_p_char()
{
	p_char<'a', 'b', 'c', 'd', 'e'> t;
	std::string str("abcj");

	auto r = t(str);
	assert(r.first == true);
	r = t(r.second);
	assert(r.first == true);
	r = t(r.second);
	assert(r.first == true);
	r = t(r.second);
	assert(r.first == false);
	r.second = r.second.substr(1);
	r = t(r.second);
	assert(r.first == false);
}

static inline void tests_p_then()
{
	{
		p_then<p_char<'O', 'o'>, p_char<'K', 'k'>> ok;

		std::string str1("ok");
		std::string str2("Ok");
		std::string str3("oK");
		std::string str4("OK");
		std::string str5("OKb");
		std::string str6("Ob");
		auto r = ok(str1);
		assert(r.first == true);
		r = ok(str2);
		assert(r.first == true);
		r = ok(str3);
		assert(r.first == true);
		r = ok(str4);
		assert(r.first == true);
		r = ok(str5);
		assert(r.first == true && r.second == "b");
		r = ok(str6);
		assert(r.first == false && r.second == "b");
	}
	{
		p_then<p_char<'b'>, p_char<'o'>,
		p_then<p_char<'n'>, p_char<'j'>, p_char<'o'>,
		p_then<p_then<p_char<'u'>, p_char<'r'>>, p_char<'!'>>>> bonjour;

		std::string str1("bonjour!");
		std::string str2("bonjour");
		std::string str3("oui");
		auto r = bonjour(str1);
		assert(r.first == true);
		r = bonjour(str2);
		assert(r.first == false && r.second == "");
		r = bonjour(str3);
		assert(r.first == false && r.second == "oui");
	}
}

int main()
{
	tests_p_char();
	tests_p_then();
}
