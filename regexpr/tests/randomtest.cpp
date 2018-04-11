#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <exception>
#include <vector>
#include <string>

struct pins {
	std::string oname;
	unsigned int opin;
	std::string iname;
	unsigned int ipin;
};

void push_pin(std::string const &str, std::vector<pins> *vec)
{
	size_t n = std::count(str.begin(), str.end(), ':');
	if (n != 2) throw std::invalid_argument { "invalid output" };
	std::stringstream a(str);
	std::string word[2];
	a >> word[0] >> word[1];
	std::cout << "[" << word[0] << "]" << std::endl;
	word[0].replace(word[0].find(":"), word[0].find(":"), " ");
	std::cout << "[" << word[0] << "]" << std::endl;
	std::cout << "[" << word[1] << "]" << std::endl;
	word[1].replace(word[1].find(":"), word[1].find(":"), " ");
	std::cout << "[" << word[1] << "]" << std::endl;
	std::stringstream sstr0{word[0]};
	std::stringstream sstr1{word[1]};
	std::cout << sstr0.str() << std::endl;
	std::cout << sstr1.str() << std::endl;
	pins pin;
	sstr0 >> pin.iname >> pin.ipin;
	sstr1 >> pin.oname >> pin.opin;
	std::cout << "in  :" << "name: " << pin.iname << "\tpin: " << pin.ipin << '\n';
	std::cout << "out :" << "name: " << pin.oname << "\tpin: " << pin.opin << '\n' << std::endl;
	vec->push_back(pin);
}

// int main()
// {
// 	std::string str{"abcdef"};
//
// 	std::cout << str << std::endl;
// 	str.replace(str.begin() + 3, str.begin() + 4, " ");
// 	std::cout << str << std::endl;
// }


int main()
{
	std::string str{"a:1 gate:12"};
	std::stringstream a(str);
	std::string word[2];

	a >> word[0] >> word[1];
	std::cout << "[" << word[0] << "]"<< "[" << word[1] << "]" << std::endl;

	std::cout << "[" << word[0] << "]" << std::endl;
	auto it = word[0].find(":");
	std::cout << it << std::endl;
	word[0].replace(it, it, " ");
	std::cout << "[" << word[0] << "]" << std::endl;

	it = word[1].find(":");
	std::cout << it << std::endl;
	std::cout << "[" << word[1] << "]" << std::endl;
	word[1].replace(it, it, " ");
	std::cout << "[" << word[1] << "]" << std::endl;
}

/*
int main(int ac, char **av)
{
	if (ac != 2) return 1;
	std::ifstream file{ av[1] };

	std::vector<pins> _pins;
	std::string line;
	while (std::getline(file, line)) {
		push_pin(line, &_pins);
	}

	for (auto pin : _pins) {
		std::cout << "in  :" << "name: " << pin.iname << "\tpin: " << pin.ipin << '\n';
		std::cout << "out :" << "name: " << pin.oname << "\tpin: " << pin.opin << '\n' << std::endl;
	}
}
*/
/*
error : n == 0
str.empty()
end != '\0'
*/
