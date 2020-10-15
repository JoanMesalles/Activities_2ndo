#include "../../dep/inc/XML/rapidxml.hpp"
#include "../../dep/inc/XML/rapidxml_utils.hpp"
#include "../../dep/inc/XML/rapidxml_iterators.hpp"
#include "../../dep/inc/XML/rapidxml_print.hpp"
#include "Enemies.h"
#include <iostream>
#include <sstream> 
#include <map>

int main() {
	std::map<std::string, Enemie> enemymap;
	rapidxml::xml_document<> doc;
	std::ifstream file("config.xml");
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);
	std::string name;
	std::string weapon = "weapon";
	std::string live = "live";
	std::string attack = "attack";
	std::string def = "def";
	std::string frq = "frq";
	rapidxml::xml_node<>* pRoot = doc.first_node();

	for (rapidxml::xml_node<>* pNode = pRoot->first_node(); pNode; pNode = pNode->next_sibling())
	{
		std::cout << pNode->first_attribute() << ':' << '\n';
		Enemie enemieaux;
		for (rapidxml::xml_node<>* pNodeI = pNode->first_node(); pNodeI; pNodeI = pNodeI->next_sibling())
		{
			std::cout << pNodeI->name() << ':' << pNodeI->value() << '\n';

			if (pNodeI->name() == live) {
				enemieaux.live = std::stoi(pNodeI->value());
			}

			if (pNodeI->name() == attack) {
				enemieaux.attack = std::stoi(pNodeI->value());
			}

			if (pNodeI->name() == def) {
				enemieaux.def = std::stoi(pNodeI->value());
			}

			if (pNodeI->name() == frq) {
				enemieaux.frq = std::stoi(pNodeI->value());
			}

			if (pNodeI->name() == weapon) {
				for (rapidxml::xml_node<>* pNodeL = pNodeI->first_node(); pNodeL; pNodeL = pNodeL->next_sibling())
				{
					std::cout << pNodeL->name() << ':' << pNodeL->value() << '\n';

				};
			}
			
		};
		//enemymap[pNode->first_attribute()] = enemieaux;
		std::cout << '\n';
	}
	/*
	for (auto it = enemymap.cbegin(); it != enemymap.cend(); ++it)
	{
		std::cout << it->first << "\n";
	}
	*/



	return 0;

}