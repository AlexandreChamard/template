/*
** EPITECH PROJECT, 2017
** evalexpr.hpp for c++
** File description:
** description
*/

#pragma once

#include <iostream>
#include <utility>
#include <string>

template<typename F, typename S>
struct ope_then {
	std::pair<bool, std::string> operator()(std::string &str)
	{
		F f;
		std::pair<bool, std::string> fp = f(str);
		if (fp.first == true) {
			S s;
			return s(fp.second);
		}
		return fp;
	}
};

template<char C>
struct ope_char {
	std::pair<bool, std::string> operator()(std::string const &str)
	{
		if (str.size() > 0 && str.at(0) == C) {
			return std::make_pair(true, str.substr(1));
		}
		return std::make_pair(false, str);
	}
};

template<typename T>
struct ope_more {
	std::pair<bool, std::string> operator()(std::string &str)
	{
		T t;
		std::pair<bool, std::string> pair = t(str);
		if (pair.first == true) {
			while (1) {
				std::pair<bool, std::string> pair2 = t(pair.second);
				if (pair2.first == false) {
					return pair;
				}
				pair = pair2;
			}
		}
		return pair;
	}
};

template<typename T>
struct ope_mul {
	std::pair<bool, std::string> operator()(std::string &str)
	{
		std::pair<bool, std::string> pair{true, str};
		while (1) {
			T t;
			std::pair<bool, std::string> pair2 = t(pair.second);
			if (pair2.first == false) {
				return std::make_pair(true, pair2.second);
			}
			pair = pair2;
		}
	}
};

template<typename F, typename S>
struct ope_or {
	std::pair<bool, std::string> operator()(std::string &str)
	{
		F f;
		std::pair<bool, std::string> fp = f(str);
		if (fp.first == false) {
			S s;
			return s(str);
		}
		return fp;
	}
};

struct ope_digit : public ope_or<ope_char<'0'>, ope_or<ope_char<'1'>,
		ope_or<ope_char<'2'>, ope_or<ope_char<'3'>,
		ope_or<ope_char<'4'>, ope_or<ope_char<'5'>,
		ope_or<ope_char<'6'>, ope_or<ope_char<'7'>,
		ope_or<ope_char<'8'>, ope_char<'9'>>>>>>>>>>
{
};

struct ope_num : public ope_then<ope_mul<ope_char<' '>>, ope_more<ope_digit>>
{
};

struct ope_high : public ope_then<ope_num, ope_mul<ope_then<ope_or<ope_char<'*'>, ope_or<ope_char<'/'>, ope_char<'%'>>>, ope_num>>>
{
};

struct ope_low : public ope_then<ope_high, ope_mul<ope_then<ope_or<ope_char<'+'>, ope_char<'-'>>, ope_high>>>
{
};

struct Parser : public ope_low
{
	std::pair<bool, std::string> operator()(std::string const &str)
	{
		std::string str2 = str;
		std::pair<bool, std::string> pair = ope_low::operator()(str2);
		if (pair.second.size() == 0) {
			return pair;
		}
		return std::make_pair(false, str);
	}
};
