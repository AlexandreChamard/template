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

static inline void tests_p_or()
{
	p_or<p_then<p_char<'O'>, p_char<'K'>>, p_then<p_char<'O'>, p_char<'U'>, p_char<'I'>>> t;

	std::string str1("OK");
	std::string str2("OUI");
	std::string str3("OKI");
	std::string str4("OUK");
	auto r = t(str1);
	assert(r.first == true);
	r = t(str2);
	assert(r.first == true);
	r = t(str3);
	assert(r.first == true && r.second == "I");
	r = t(str4);
	assert(r.first == false && r.second == "K");
}

static inline void tests_p_mul()
{
	p_then<p_char<'F'>, p_mul<p_char<'*'>>, p_char<'K'>, p_eof> t;

	std::string str1("F***K");
	std::string str2("FK");
	std::string str3("F**");
	std::string str4("F**KK");
	auto r = t(str1);
	assert(r.first == true);
	r = t(str2);
	assert(r.first == true);
	r = t(str3);
	assert(r.first == false && r.second == "");
	r = t(str4);
	assert(r.first == false && r.second == "K");
}

static inline void tests_p_more()
{
	p_then<p_more<p_char<'A'>>, p_char<'H'>, p_eof> t;

	std::string str1("AH");
	std::string str2("AAAAAAAAAAH");
	std::string str3("H");
	std::string str4("AHH");
	auto r = t(str1);
	assert(r.first == true);
	r = t(str2);
	assert(r.first == true);
	r = t(str3);
	assert(r.first == false && r.second == "H");
	r = t(str4);
	assert(r.first == false && r.second == "H");
}

static inline void tests_p_space()
{
	p_then<p_more<p_char<'O'>>, p_mul<p_space>, p_char<'K'>, p_eof> t;

	std::string str1("OK");
	std::string str2("O               K");
	std::string str3("O		K");
	std::string str4("O 	 K");
	auto r = t(str1);
	assert(r.first == true);
	r = t(str2);
	assert(r.first == true);
	r = t(str3);
	assert(r.first == true);
	r = t(str4);
	assert(r.first == true);
}

int main()
{
	tests_p_char();
	tests_p_then();
	tests_p_or();
	tests_p_mul();
	tests_p_more();
	tests_p_space();
}
