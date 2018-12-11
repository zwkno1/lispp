#pragma once

#include <istream>

#include "token.h"

class Lexer
{
public:
    Lexer(std::istream & in);
	Token nextToken();
    //size_t line() const { return line_; }
private:
	inline Token make_token(TokenType type) { return Token{ type }; }

	inline Token make_num(int num) { return Token{NUMBER, num}; }

	inline Token make_symbol(std::string && str) { return Token{SYMBOL, std::move(str)}; }

    void next();

    void putback();

    Token read_num();

    Token read_symbol();

    std::istream & in_;

    size_t line_;

    int current_;
};

