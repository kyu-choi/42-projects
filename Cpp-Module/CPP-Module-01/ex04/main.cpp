#include "replace.hpp"

int	main(int argc, char **argv)
{
	std::string	filename;
	std::string	s1;
	std::string	s2;
	std::ifstream	infile;
	std::ofstream	outfile;
	std::string	line;

	if (argc != 4)
	{
		std::cout << "Usage: ./replace <filename> <s1> <s2>" << std::endl;
		return (1);
	}
	filename = argv[1];
	s1 = argv[2];
	s2 = argv[3];
	if (s1.empty())
	{
		std::cout << "Error: s1 must not be empty." << std::endl;
		return (1);
	}
	infile.open(filename.c_str());
	if (!infile.is_open())
	{
		std::cout << "Error: could not open input file." << std::endl;
		return (1);
	}
	outfile.open((filename + ".replace").c_str());
	if (!outfile.is_open())
	{
		std::cout << "Error: could not create output file." << std::endl;
		infile.close();
		return (1);
	}
	while (std::getline(infile, line))
	{
		outfile << replaceAll(line, s1, s2);
		if (!infile.eof())
			outfile << std::endl;
	}
	infile.close();
	outfile.close();
	return (0);
}
