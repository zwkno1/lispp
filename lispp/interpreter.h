#pragma once

#include "token.h"
#include "lexer.h"
#include "object.h"

class Interpreter
{
public:
	Interpreter(Lexer & lexer)
		: lexer_(lexer)
	{
	}

	ObjectPtr expr()
	{


	}

	ObjectPtr list()
	{
	}

private:
	Lexer & lexer_;

};
