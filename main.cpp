#include "arc_driver.h"
#include "arc_parser.h"
#include "arc_lexer.h"


int main()
{
	Lexer::Lexer_analysater la(&std::cin);
	Parser::Syntax_analysater sa(&la);
	Driver::Application application(&sa);

	application.run();

    return 0;
}
