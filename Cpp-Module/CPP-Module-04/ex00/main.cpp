#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int	main(void)
{
	std::cout << "=== CORRECT POLYMORPHISM ===" << std::endl;
	
	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	
	std::cout << j->getType() << std::endl;
	std::cout << i->getType() << std::endl;
	i->makeSound();
	j->makeSound();
	meta->makeSound();
	
	delete	meta;
	delete	j;
	delete	i;
	
	std::cout << "\n=== WRONG POLYMORPHISM ===" << std::endl;
	const WrongAnimal*	w = new WrongCat();
	w->makeSound();
	delete	w;
	
	return (0);
}
