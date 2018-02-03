/*
** EPITECH PROJECT, 2017
** regexpr.hpp for template
** File description:
** description
*/

#pragma once

#include <utility>
#include <functional>
#include <string>
#include <sstream>

/* PARSERS */
template<typename ...T> struct p_more;
template<typename ...T> struct p_mul;
template<typename ...T> struct p_or;
template<typename ...T> struct p_then;
template<char ...c> struct p_char;
template<bool (*T)(std::string const &)> struct p_apply;
struct p_eof;
struct p_eol;
struct p_space;
struct p_digit;

/* P_MORE */
template<typename T, typename U>
struct p_more<T, U>
{
	std::pair<bool, std::string> operator()(std::string str, std::stringstream *sstr = nullptr)
	{
		T t;
		auto pair = t(str, sstr);
		if (pair.first == true) {
			str = pair.second;
			while (1) {
				pair = t(pair.second, sstr);
				if (pair.first == false) {
					return std::make_pair(true, str);
				}
				str = pair.second;
			}
		}
		return std::make_pair(false, str);
	}
};

template<typename T, typename ...other>
struct p_more<T, other...> : public p_more<T, p_more<other...>> {};

/* P_MUL */
template<typename T>
struct p_mul<T>
{
	std::pair<bool, std::string> operator()(std::string str, std::stringstream *sstr = nullptr)
	{
		std::pair<bool, std::string> pair;
		while (1) {
			T t;
			pair = t(str, sstr);
			if (pair.first == false) {
				return std::make_pair(true, str);
			}
			str = pair.second;
		}
	}
};

template<typename T, typename ...other>
struct p_mul<T, other...> : public p_mul<T, p_mul<other...>> {};

/* P_OR */
template<typename T, typename U>
struct p_or<T, U>
{
	std::pair<bool, std::string> operator()(std::string str, std::stringstream *sstr = nullptr)
	{
		T t;
		std::pair<bool, std::string> res = t(str, sstr);
		if (res.first == false) {
			U u;
			return u(str, sstr);
		}
		return res;
	}
};

template<typename T, typename ...other>
struct p_or<T, other...> : public p_or<T, p_or<other...>> {};

/* P_THEN */
template<typename T, typename U>
struct p_then<T, U>
{
	std::pair<bool, std::string> operator()(std::string str, std::stringstream *sstr = nullptr)
	{
		T t;
		std::pair<bool, std::string> res = t(str, sstr);
		if (res.first == true) {
			U u;
			return u(res.second, sstr);
		}
		return res;
	}
};

template<typename T, typename ...other>
struct p_then<T, other...> : public p_then<T, p_then<other...>> {};

/* P_CHAR */
template<char c>
struct p_char<c>
{
	std::pair<bool, std::string> operator()(std::string str, std::stringstream *sstr = nullptr)
	{
		if (str.empty() == false && str.at(0) == c) {
			if (sstr != nullptr) {
				(*sstr) << str.at(0);
			}
			return std::make_pair(true, str.substr(1));
		}
		return std::make_pair(false, str);
	}
};

template<char c, char ...other>
struct p_char<c, other...> : public p_or<p_char<c>, p_char<other...>> {};

/* P_EOF */
struct p_eof
{
	std::pair<bool, std::string> operator()(std::string str, std::stringstream *sstr = nullptr)
	{
		(void) sstr;
		return std::make_pair(str.empty(), str);
	}
};

/* P_EOL */
struct p_eol : p_char<'\0', '\n'> {};

/* P_SPACE */
struct p_space : public p_mul<p_char<' ', '\t'>> {};

/* P_APPLY */
template<bool (*T)(std::string const &)>
struct p_apply
{
	std::pair<bool, std::string> operator()(std::string str, std::stringstream *sstr = NULL)
	{
		bool res = T(str);
		if (res == true) {
			if (sstr != NULL && str.empty() == false) {
				(*sstr) << str.at(0);
			}
			return std::make_pair(true, str.substr(1));
		}
		return std::make_pair(false, str);
	}
};

struct p_digit : public p_char<'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'> {};
