#ifndef _LOG_HPP
#define _LOG_HPP

#include <iostream>
#include <string>

namespace duckhero
{
	class Log
	{
	public:
		static void Warning(std::string tag, std::string message);
	};
}

#endif