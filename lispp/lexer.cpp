
#include "lexer.h"

#include <map>
#include <cctype>
#include <algorithm>

namespace
{
	std::map<std::string, TokenType> reserve_word =
	{
		{ "T",     TRUE },
		{ "NIL",   NIL },
	};

	bool isValidSymbolChar(int ch, bool first = true)
	{
		static const std::string validStr = "~!@#$%^&*_+`-=<>?,./";
		return std::isalpha(ch) || (std::find(validStr.begin(), validStr.end(), ch) != validStr.end()) || (!first && std::isdigit(ch));
	}
}

Lexer::Lexer(std::istream & in)
    : in_(in)
    , line_(0)
{
}

Token Lexer::nextToken()
{
	while(true)
	{
        next();
        switch(current_)
        {
        case EOF:
            return make_token(END);
        case ' ' : case '\f' : case '\t' : case '\v' :
            break;
        case '\n' :
			++ line_;
            break;
        case '(' :
            return make_token(LP);
        case ')' :
            return make_token(RP);
        case '\'' :
            return make_token(QUOTE);
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            return read_num();
        default :
			if(isValidSymbolChar(current_))
			  return read_symbol();
			// todo: throw error
        }
    }
}

void Lexer::next()
{
    current_ = in_.get();
}

void Lexer::putback()
{
    in_.putback(current_);
}

Token Lexer::read_num()
{
    int num = current_ - '0';
    while(true)
    {
        next();
        if(current_ == EOF || !std::isdigit(current_))
        {
            putback();
            return make_num(num);
        }
        else
        {
			// todo: overflow
            num = num* 10 + (current_ - '0');
        }
    }
}

Token Lexer::read_symbol()
{
	std::string str;
    while(true)
    {
		str.push_back(std::toupper(current_));
		next();
		if(!isValidSymbolChar(current_, false))
		{
			putback();
			auto iter = reserve_word.find(str);
			if(iter != reserve_word.end())
			{
				return make_token(iter->second);
			}
			return make_symbol(std::move(str));
		}
    }
}

