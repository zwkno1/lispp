
#include <fstream>
#include <iostream>

#include "lexer.h"

int main(int argc, char * argv[])
{
	if(argc < 2)
	  return -1;
	std::ifstream ifs(argv[1]);
	Lexer lexer(ifs);

	while(true)
	{
		Token t = lexer.nextToken();

		std::cout << to_string(t) << std::endl;
		if(t.type_ == END)
		  break;
	}
	return 0;
}
