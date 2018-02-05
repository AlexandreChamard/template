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
#include <iostream>

/* PARSERS */
template<typename T> struct p_more;
template<typename T> struct p_mul;
template<typename ...T> struct p_or;
template<typename ...T> struct p_then;
template<char ...c> struct p_char;
template<bool (*T)(std::string const &)> struct p_apply;
template<typename T> struct p_not;
template<typename T, typename U> struct p_separate;
struct p_eof;
struct p_eol;
struct p_space;
struct p_digit;
template<typename T> struct p_ltrim;
template<typename T> struct p_rtrim;
template<typename T> struct p_trim;

/* P_MORE */
template<typename T>
struct p_more
{
	std::pair<bool, std::string> operator()(std::string str, std::stringstream *sstr = nullptr)
	{
		T t;
		auto pair = t(str, sstr);
		if (pair.first == false) {
			return std::make_pair(false, str);
		}
		str = pair.second;
		while (1) {
			pair = t(pair.second, sstr);
			if (pair.first == false) {
				return std::make_pair(true, str);
			}
			str = pair.second;
		}
	}
};

/* P_MUL */
template<typename T>
struct p_mul
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

/* P_NOT */
template<typename T>
struct p_not
{
	std::pair<bool, std::string> operator()(std::string str, std::stringstream *sstr = nullptr)
	{
		T t;
		auto tp = t(str);
		return std::make_pair(!tp.first, tp.second);
	}
};

/* P_SEPARATE */
template<typename T, typename U>
struct p_separate : public p_then<T, p_mul<p_then<U, T>>> {};

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
struct p_eol
{
	std::pair<bool, std::string> operator()(std::string str, std::stringstream *sstr = nullptr)
	{
		p_or<p_char<'\0', '\n'>, p_eof> eol;

		(void) sstr;
		return eol(str);
	}
};

/* P_SPACE */
struct p_space
{
	std::pair<bool, std::string> operator()(std::string str, std::stringstream *sstr = nullptr)
	{
		p_char<' ', '\t'> space;

		(void) sstr;
		return space(str);
	}
};


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

/* P_TOKEN */
template<typename T, typename U>
struct p_token
{
	std::pair<bool, std::string> operator()(std::string &str)
	{
		std::stringstream sstr;

		T t;
		auto tp = t(str, &sstr);
		U u;
		auto up = u(tp.second);
		if (up.first) {
			str = up.second;
		}
		return std::make_pair(tp.first && up.first, sstr.str());
	}
};

template<typename T>
struct p_ltrim : public p_then<p_mul<p_space>, T>{};

template<typename T>
struct p_rtrim : public p_then<T, p_mul<p_space>>{};

template<typename T>
struct p_trim : public p_then<p_ltrim<T>, p_mul<p_space>>{};
