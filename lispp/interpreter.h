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

	ObjectPtr run(std::istream & is)
	{
		Lexer l(is);

		Token t = l.nextToken();
		if(t.type_ == END)
		{
			return ObjectPtr{};
		}

		ObjectPtr e = expr(l);
		ObjectPtr result = eval(e);
		return result;
	}

	ObjectPtr expr(Lexer & l)
	{
		while(true)
		{
			Token t = l.nextToken();
			if(t.type_ == LP)
			{

			}
			else if(t.type_ == )
			{

			}

		}
	}

	ObjectPtr list()
	{

	}

	ObjectPtr eval(ObjectPtr expr)
	{
	}

private:
	Lexer & lexer_;

};
