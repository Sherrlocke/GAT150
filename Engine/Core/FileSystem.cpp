#include "FileSystem.h"
#include <filesystem>

namespace nc {

	void nc::setFilePath(const std::string& pathName)
	{
		std::filesystem::current_path(pathName);
	}

	std::string nc::getFilePath()
	{
		return std::filesystem::current_path().string();
	}

}