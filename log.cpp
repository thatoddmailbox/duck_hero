#include "log.hpp"

namespace duckhero
{
	void Log::Warning(std::string tag, std::string message)
	{
		std::cerr << "[" << tag << "][warning] " << message << std::endl;
	}
}