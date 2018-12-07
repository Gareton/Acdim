#include "arc_driver.h"

namespace Driver
{
	Application::Application(Syntax_analysater *saptr)
	{
		_saptr = saptr;
		_errors_count = 0;
	}

	void Application::run()
	{
		try {
			while (true)
			{
				std::cout << "$";
				_saptr->execute();
			}
		}

		catch (...)
		{
			std::cerr << "Something went wrong" << std::endl;
			++_errors_count;
			exit(_errors_count);
		}
	}


	Application::~Application()	{	}
}
