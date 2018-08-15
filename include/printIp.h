/*!
 * \file
 * \brief Содержит семейство функций printIp, которые
 * печатают ip побайтно в поток os, разделяя
 * байты точкой. 
 * 
 * Семейство функций printIp(os, ip) принимает поток вывода std::ostream& os,
 * куда осуществляется вывод, и ip адресс, который печатается в os. Функции ничего не возвращают.
 * 
 * Функции перегруженны для следующих типов ip адреса:
 * - базовые типы;
 * - строка std::string (печатается как есть);
 * - контенеры std::vestor и std::list (печать происходит поэлементно);
 * - кортеж std::tupl (печатается поэлементно).
 * 
 * Примеры ипользования приведены в main().
 * 
 * 

 */


#include <type_traits>
#include "forEachTuple.h"

/// \brief Перегрузка для базовых типов. \callergraph
template <typename T>
typename std::enable_if <std::is_integral<T>::value>::type
printIp(std::ostream& os, const T& ip){
	size_t num = sizeof(ip);
	const char* ptr = reinterpret_cast<const char*> (&ip);
	
	os << +(unsigned char) (ptr[num-1]);
	for(int i=num-2; i>=0; --i)
		os << '.' << +(unsigned char) (ptr[i]) ;
	os << std::endl;	
}

/// \brief Перегрузка для строки.
/// \callergraph
template <typename T>
typename std::enable_if <std::is_same<T, std::string>::value >::type
printIp(std::ostream& os, const T& ip){
	os << ip << std::endl;
}

/// \brief Перегрузка для контейнеров std::vector и std::list
template <typename T>
typename std::enable_if <
		std::is_same <std::vector<typename T::value_type>, T>::value ||
		std::is_same <std::list<typename T::value_type>, T>::value
	>::type
printIp (std::ostream& os, const T& ip){
	for (auto ip_part = ip.cbegin(); ip_part != ip.cend(); ++ip_part) {
		if (ip_part != ip.cbegin())
			os << ".";
		os << *ip_part;
	}
	os << std::endl;	
}

namespace __tuple{
	struct callback
	{
		callback(std::ostream& os): os(os) {};
		template<typename T>
		void operator()(int index, T&& t)
		{                                
			if(index != 0)
				os << '.';
			os << t;
		}
	private:
		std::ostream& os;
	};
}

/// \brief Перегрузка для std::tuple
template <typename T>
decltype(std::tuple_size<T>::value, void())
printIp (std::ostream& os, const T& ip){
	__tuple::callback out(os);
	for_each(ip, out);
	os << std::endl;
}
