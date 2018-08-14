/// \file

/// \mainpage Доманее задание 03 к уроку 10
///
/// \section Задача
///
/// - Необходимо написать функцию печати ip адресса побайтно в стандартный поток
/// вывода std::cout, байты должны разделяться точкой. Примеры использования 
/// функции приведены в main().
/// - Научиться использовать doxygen.
/// 
/// \see main()
/// \see printIp()

#include <iostream>
#include <vector>
#include <list>
#include "printIp.h"

/*! \brief Основная функция проекта.
 *
 * Содержит примеры использования функции printIp().
 */
int main(int argc, char** argv)
{
	printIp(std::cout, char(-1));
	printIp(std::cout, short(0));
	printIp(std::cout, int(2130706433));
	printIp(std::cout, long(8875824491850138409));
						
	std::vector<int> vec;
	vec.emplace_back(1);
	vec.emplace_back(2);
	vec.emplace_back(3);
	vec.emplace_back(15);
	printIp(std::cout, vec);
	
	std::list<int> lst;
	for(const auto& e: vec)
		lst.push_front(e);
	printIp(std::cout, lst);
	
	printIp(std::cout, std::make_tuple("t1", "t2", "t3", "t4"));
	
	
	return 0;
}
