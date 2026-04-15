#include "replace.hpp"

std::string replaceAll(const std::string& line, const std::string& s1, const std::string& s2)
{
	std::string res;
	std::size_t start;
	std::size_t pos;

	start = 0;
	pos = line.find(s1, start);
	while (pos != std::string::npos)
	{
		res += line.substr(start, pos - start);
		res += s2;
		start = pos + s1.length();
		pos = line.find(s1, start);
	}
	res += line.substr(start);
	return (res);
}
