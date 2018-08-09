#include <iostream>

template <class T>
void printIp(std::ostream& os, const T& ip){
	size_t num = sizeof(ip);
	const char* ptr = reinterpret_cast<const char*> (&ip);
	
	os << +(unsigned char) (ptr[num-1]);
	for(int i=num-2; i>=0; --i)
		os << '.' << +(unsigned char) (ptr[i]) ;
	os << std::endl;	
}

template <typename... Args, template <typename ...Args> class Conteiner>
void printIp (std::ostream& os, const Conteiner<Args...>& ip){
	for (auto ip_part = ip.cbegin(); ip_part != ip.cend(); ++ip_part) {
		if (ip_part != ip.cbegin())
			os << ".";
		os << *ip_part;
	}
	os << std::endl;	
}

int main(int argc, char** argv)
{
	printIp(std::cout, char(-1));
	printIp(std::cout, short(0));
	printIp(std::cout, int(2130706433));
	printIp(std::cout, long(8875824491850138409));
		
	return 0;
}
