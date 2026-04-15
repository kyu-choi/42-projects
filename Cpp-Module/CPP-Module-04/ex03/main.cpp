#include "IMateriaSource.hpp"
#include "MateriaSource.hpp"
#include "ICharacter.hpp"
#include "Character.hpp"
#include "Ice.hpp"
#include "Cure.hpp"

static void	subject_test(void)
{
	IMateriaSource*	src = new MateriaSource();
	
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());
	
	ICharacter*	me = new Character("me");
	
	AMateria*	tmp;
	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);
	
	ICharacter*	bob = new Character("bob");
	
	me->use(0, *bob);
	me->use(1, *bob);
	
	delete	bob;
	delete	me;
	delete	src;
}

static void	deep_copy_test(void)
{
	std::cout << "\n===== DEEP COPY TEST =====" << std::endl;
	
	Character	a("alice");
	AMateria*	ice = new Ice();
	AMateria*	cure = new Cure();
	
	a.equip(ice);
	a.equip(cure);
	
	Character	b(a);
	
	Character	target("target");
	a.use(0, target);
	b.use(0, target);
}

int	main(void)
{
	subject_test();
	deep_copy_test();
	return (0);
}
