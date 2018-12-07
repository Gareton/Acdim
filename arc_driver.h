#ifndef ARC_DRIVER
#define ARC_DRIVER
#include "arc_parser.h"

namespace Driver
{
	using Parser::Syntax_analysater;

	class Application
	{
	public:
		Application(Syntax_analysater *saptr);
		void run();
		~Application();
	private:
		Syntax_analysater *_saptr;
		std::size_t _errors_count;
	};
}

#endif


