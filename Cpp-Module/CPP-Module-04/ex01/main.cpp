#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

static void	testArray(void)
{
	int	i;
	Animal*	animals[10];

	std::cout << "===== ANIMAL ARRAY TEST =====" << std::endl;
	i = 0;
	while (i < 5)
	{
		animals[i] = new Dog();
		i++;
	}
	while (i < 10)
	{
		animals[i] = new Cat();
		i++;
	}
	i = 0;
	while (i < 10)
	{
		animals[i]->makeSound();
		i++;
	}
	i = 0;
	while (i < 10)
	{
		delete	animals[i];
		i++;
	}
}

static void	testDeepCopy(void)
{
	std::cout << "\n===== DEEP COPY TEST=====" << std::endl;
	
	Dog	original;
	original.setIdea(0, "I want a bone");
	original.setIdea(1, "I want to run");
	
	Dog	copy(original);
	
	std::cout << "Original idea[0]: " << original.getIdea(0) << std::endl;
	std::cout << "Copy idea[0]: " << copy.getIdea(0) << std::endl;
	
	original.setIdea(0, "Changed original idea");
	
	std::cout << "\nAfter changing original:" << std::endl;
	std::cout << "Original idea[0]: " << original.getIdea(0) << std::endl;
	std::cout << "Copy idea[0]: " << copy.getIdea(0) << std::endl;
}

int	main(void)
{
	testArray();
	testDeepCopy();
	return (0);
}
