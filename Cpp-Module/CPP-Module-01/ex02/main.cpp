
#include <iostream>
#include <string>

int	main(void)
{
	std::string str;
	std::string* stringPTR;
	std::string& stringREF = str;

	str = "HI THIS IS BRAIN";
	stringPTR = &str;
	
	std::cout << "주소 출력" << std::endl;
	
	std::cout << &str << std::endl;
	std::cout << stringPTR << std::endl;
	std::cout << &stringREF << std::endl;
	
	std::cout << std::endl;
	
	std::cout << "값 출력" << std::endl;
	
	std::cout << str << std::endl;
	std::cout << *stringPTR << std::endl;
	std::cout << stringREF << std::endl;
	
	return (0);
}
