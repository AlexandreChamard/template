/*
** EPITECH PROJECT, 2017
** regexpr.hpp for template
** File description:
** description
*/

#pragma once

#include <utility>
#include <string>

/* P_MORE */
template<typename ...T>
struct p_more;

template<typename T, typename U>
struct p_more<T, U>
{
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

template<typename T, typename ...other>
struct p_more<T, other...> : public p_more<T, p_more<other...>>
{
};

/* P_MUL */
template<typename ...T>
struct p_mul;

template<typename T, typename U>
struct p_mul<T, U>
{
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

template<typename T, typename ...other>
struct p_mul<T, other...> : public p_mul<T, p_mul<other...>>
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

/* P_EOF */
struct p_eof
{
	std::pair<bool, std::string> operator()(std::string &str)
	{
		return std::make_pair(str.empty(), str);
	}
};

/* P_EOL */
struct p_eol : p_char<'\0', '\n'> {};

/* P_SPACE */
struct p_space : public p_mul<p_char<' ', '\t'>> {};

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

struct ope_digit {
	std::pair<bool, std::string> operator()(std::string &str)
	{
		if (str.size() > 0 && str.at(0) >= '0' &&  str.at(0) <= '9') {
			return std::make_pair(true, str.substr(1));
		}
		return std::make_pair(false, str);
	}
};
