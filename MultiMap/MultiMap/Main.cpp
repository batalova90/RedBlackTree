#include <iostream>
#include "MultiMap.h"


void checkTree();


int main()
{
	setlocale(LC_ALL, "ru");
	MultiMap<int, double> tree;
	tree.Insert(5, 2.2);
	tree.Insert(3, 0.5);
	tree.Insert(8, 1.5);
	tree.Insert(1, 0.2);
	tree.Insert(7, 0.3);
	tree.Insert(9, 0.5);
	tree.Insert(7, 1.1); 
	tree.Insert(12, 0.8); 
	tree.Insert(0, 0.0); //д. сработать правый поворот!!
	tree.Insert(11, 3.0); // д. сработать Right между 11 и 12, и левый между 9 и 11 
	tree.Insert(20, 0.8); //левое вращение, корнем дерева становится 8
	tree.Insert(30, 0.3);
	tree.Insert(25, 0.7);
	tree.Insert(26, 0.8);
	tree.Insert(100, 0.9);
	tree.Insert(110, 1.1);
	tree.Insert(28, 3.5);
	tree.Insert(24, 3.6);
	tree.Insert(112, 5.2);
	tree.Insert(29, 3.5);
	tree.Insert(27, 8.9);


	tree.outputTreeStraight();
	std::cout << " main: " << tree << std::endl;

	//tree.erase(29); 
	/*std::cout << " main: " << tree << std::endl;
	tree.correctInfo(110, 350.0);*/
	tree.erase(110);
	//std::cout << tree << std::endl;
	///MultiMap<int, double> tree2(tree); //дестркутор вызывается с ошибкой
	//std::cout << tree;
	
	MultiMap<int, double>::Iterator it2;
	it2 = tree.ubound(112);
	MultiMap<int, double>::Iterator it3;
	it3 = tree.lbound(24);
	
	std::cout << *it3 << std::endl;
	//проверить на то, что выводятся все элементы
	MultiMap<int, double>::Iterator it4;
	it4 = tree.begin();
	MultiMap<int, double>::Iterator it5;
	it5 = tree.end();
	std::cout << "обход через итератор" << std::endl;
	while (it4 != it5)
	{
		std::cout << *it4;
		++it4;
	}
	
	int N = 10;
	for (int i = 0; i < N; i++)
	{
		checkTree();
		//i = 0;
	}
	return 0;
}

void checkTree()
{
	MultiMap<int, double> tree;
	tree.Insert(3, 0.2);
	tree.Insert(4, 0.5);
	tree.Insert(5, 0.6);
	tree.Insert(6, 0.7);
	tree.Insert(7, 0.8);
	tree.Insert(8, 0.9);
	tree.Insert(9, 1.0);
	tree.Insert(10, 1.1);
	tree.Insert(11, 1.2);
	tree.Insert(12, 1.3);
	tree.Insert(13, 1.4);
	tree.Insert(14, 1.5);
	tree.Insert(15, 1.6);
	tree.Insert(16, 1.7);
	tree.Insert(17, 1.8);
	tree.Insert(18, 1.9);
	tree.Insert(19, 0.2);
	tree.Insert(20, 0.5);
	tree.Insert(21, 0.6);
	tree.Insert(22, 0.7);
	tree.Insert(23, 0.8);
	tree.Insert(24, 0.9);
	tree.Insert(25, 1.0);
	tree.Insert(26, 1.1);
	tree.Insert(27, 1.2);
	tree.Insert(28, 1.3);
	tree.Insert(29, 1.4);
	tree.Insert(30, 1.5);
	tree.Insert(31, 1.6);
	tree.Insert(32, 1.7);
	tree.Insert(33, 1.8);
	tree.Insert(34, 1.9);
	//std::cout << tree;
}

