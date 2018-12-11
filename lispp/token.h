#pragma once

#include <variant>
#include <string>
#include <sstream>

enum TokenType : std::uint8_t
{
    LP = 1,		// (
    RP,     	// )
    SYMBOL,
    QUOTE,  	// quote | '
    NUMBER,
    TRUE,		// T
    NIL,		// NIL
	DOT,		// .
	END,		
};

inline const char * getTokenTypeStr(TokenType type)
{
	switch(type)
	{
		case LP:		
			return "LP";
		case RP:		
			return "RP";
		case SYMBOL:	
			return "SYMBOL";
		case QUOTE:
			return "QQUOTE";
		case NUMBER:
			return "NUMBER";
		case TRUE:
			return "TRUE";
		case NIL:
			return "NIL";
		case DOT:
			return "DOT";
		case END:
			return "END";
		default:
			return "ERROR";
	}
};

struct Token
{
	TokenType type_;
	std::variant<
		std::string				// value of symbol
		,int					// value of number
			> value_;
};

inline std::string to_string(const Token & t)
{
	std::stringstream ss;
	ss << "(" << getTokenTypeStr(t.type_);
	std::visit([&ss](auto && arg) { ss << ", " << arg << " )";}, t.value_);
	return ss.str();
}

