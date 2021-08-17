#include "Vector2.h"
#include <string>

namespace nc {
	const Vector2 Vector2::up{ 0, -1 };
	const Vector2 Vector2::down{ 0, 1 };
	const Vector2 Vector2::left{ -1, 0 };
	const Vector2 Vector2::right{ 1, 0 };
	const Vector2 Vector2::one{ 1, 1 };
	const Vector2 Vector2::zero{ 0, 0 };

	std::istream& operator>>(std::istream& stream, Vector2& v)
	{
		std::string line;
		std::getline(stream, line);

		if (line.find("{") != std::string::npos) {
			// x
			std::string x = line.substr(line.find("{") + 1, line.find(",") - line.find("{") - 1);
			v.x = std::stof(x);

			// y
			std::string y = line.substr(line.find(",") + 1, line.find("}") - line.find(",") - 1);
			v.y = std::stof(y);
		}

		return stream;
	}
}