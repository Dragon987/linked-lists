#include <iostream>
#include <random>
#include <ctime>

#include "./single_linked_list.hpp"

class domina
{
public:
	int br, im;

	domina(int _br, int _im)
		: br(_br), im(_im) { std::cout << "Constructed " << br << ' ' << im << '\n'; }

	~domina() { std::cout << "Destructed " << br << ' ' << im << '\n'; }
};



std::ostream& operator<<(std::ostream &stream, const domina &d)
{
	stream << "domina: br = " << d.br << ", im = " << d.im;
	return stream;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
	std::srand(std::time(0));

	linked_lists::single::linked_list<domina> ls;

	for (int i = 0; i < 10; i++)
		ls.add_back(1, 1);

	for (int i = 0; i < ls.get_size(); i++)
		std::cout << i << ". " << ls[i] << '\n';

	try
	{
		ls.remove_position(3);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	std::cout << "------------------------------------------\n";
	for (int i = 0; i < ls.get_size(); i++)
		std::cout << i << ". " << ls[i] << '\n';
	std::cout << "------------------------------------------\n";

	try
	{
		std::cout << ls[1] << '\n';
	}
	catch (std::exception& e)
	{
		std::cout << "EXCEPTION OCCURED: " << e.what() << '\n';
	}
	return 0;
}
