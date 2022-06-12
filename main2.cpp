#include "Emulator.cc"


#include <time.h>
#define start_time clock_t s_t_a_r_t = clock();
#define end_time printf("[Cpu_time_used: %f]\n", ((double) (clock() - s_t_a_r_t)) / CLOCKS_PER_SEC);

using namespace ENHANCED;
using namespace std;

void _v(Iterator<char>&iter){
	char c;
	while(++iter){
		c = *iter;
		std::cout << c << std::endl;
		if(c == '(')
			_v(iter);

	}
}

std::string reverse_words(std::string str)
{ // ENHANCED in action!
        return splitToIterator(str, " ").map([](auto item, auto inx){
                        return splitToIterator(item, "").reverse().str();
        }).str(" ");
}

namespace std{ //
	Iterator<string>_split(string str, string _){
		return splitToIterator(str, _);
	}
	using namespace ENHANCED; // reuse the namespace and all its definitions
	using IteratorStr = Iterator<>; // invoke the default template;
} 

int main(){
	Iterator<char> iter;
	// Heavy Tests # 1
	
	std::cout << "Heavy Tests #1" << std::endl;
	start_time;
	auto l = std::Iterator<int>();
	
	for(long i = 0; i < 400000000; i++)
		l << i;
	std::cout << l[399999999] << std::endl;
	end_time; // [Cpu_time_used: 4.202416] the miliseconds vary from machine to machine; tested using "-fsanitize=address" - so no memory leaks or anything of that kind
	return 1;
}
