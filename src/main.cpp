#include <iostream>
#include <type_traits>
#include <vector>
#include <list>

#include "forEachTuple.h"

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

//на мой взгляд лучше использовать перегрузку, на в задании требуется специализация
template <typename T>
typename std::enable_if <std::is_same<T, std::string>::value >::type
printIp(std::ostream& os, const T& ip){
	os << ip << std::endl;
}

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

template <typename T>
decltype(std::tuple_size<T>::value, void())
printIp (std::ostream& os, T& ip){
	__tuple::callback out(os);
	for_each(ip, out);
	os << std::endl;
}

int main(int argc, char** argv)
{
	printIp(std::cout, char(-1));
	printIp(std::cout, short(0));
	printIp(std::cout, int(2130706433));
	printIp(std::cout, long(8875824491850138409));
					
	std::string str("string");
	printIp(std::cout, str);
	
	std::vector<int> tt;
	tt.push_back(10);
	printIp(std::cout, tt);
	
	auto tmp = std::make_tuple(1,2,3);
	printIp(std::cout, tmp);
	
	return 0;
}
