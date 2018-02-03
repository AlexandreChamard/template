/*
** EPITECH PROJECT, 2017
** regexpr.hpp for template
** File description:
** description
*/

#pragma once

#include <utility>
#include <string>

/* P_THEN */
template<typename ...T>
struct p_then;

template<typename T, typename U>
struct p_then<T, U>
{
	std::pair<bool, std::string> operator()(std::string &str)
	{
		T t;
		std::pair<bool, std::string> res = t(str);
		if (res.first == true) {
			U u;
			return u(res.second);
		}
		return res;
	}
};

template<typename T, typename ...other>
struct p_then<T, other...> : public p_then<T, p_then<other...>>
{
};

/* P_OR */
template<typename ...T>
struct p_or;

template<typename T, typename U>
struct p_or<T, U>
{
	std::pair<bool, std::string> operator()(std::string &str)
	{
		T t;
		std::pair<bool, std::string> res = t(str);
		if (res.first == false) {
			U u;
			return u(str);
		}
		return res;
	}
};

template<typename T, typename ...other>
struct p_or<T, other...> : public p_or<T, p_or<other...>>
{
};

/* P_CHAR */
template<char ...c>
struct p_char;

template<char c>
struct p_char<c>
{
	std::pair<bool, std::string> operator()(std::string &str)
	{
		if (str.empty() == false && str.at(0) == c) {
			return std::make_pair(true, str.substr(1));
		}
		return std::make_pair(false, str);
	}
};

template<char c, char ...cs>
struct p_char<c, cs...> : public p_or<p_char<c>, p_char<cs...>>
{
};

//////////////////// OLD REGEXPR ////////////////////

template<std::string const &S>
struct ope_string {
	std::pair<bool, std::string> operator()(std::string &str)
	{
		if (str.find(S) == 0) {
			return std::make_pair(true, str.substr(S.size()));
		}
		return std::make_pair(false, str);
	}
};

struct ope_blank {
	std::pair<bool, std::string> operator()(std::string &str)
	{
		if (str.size() > 0 && std::isblank(str.at(0))) {
			return std::make_pair(true, str.substr(1));
		}
		return std::make_pair(false, str);
	}
};

struct ope_space {
	std::pair<bool, std::string> operator()(std::string &str)
	{
		if (str.size() > 0 && std::isspace(str.at(0))) {
			return std::make_pair(true, str.substr(1));
		}
		return std::make_pair(false, str);
	}
};

struct ope_digit {
	std::pair<bool, std::string> operator()(std::string &str)
	{
		if (str.size() > 0 && str.at(0) >= '0' &&  str.at(0) <= '9') {
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
