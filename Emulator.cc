#include "Iterator.cc"

namespace ENHANCED{
	ENHANCED::Iterator<std::string>splitToIterator(std::string, std::string);
	#define Emulator(str, s) splitToIterator(str, s)
}


template<>
ENHANCED::Iterator<std::string>::Iterator(std::string str, std::string _split){
	*this = splitToIterator(str, _split);
}

template<class T>
T __split(std::string str, std::function<bool(std::string)> call){ // using a callback for flexibility as regex.text could be used instead if necessary
	T v;
	int i, j;
	bool b = false;
	std::string __s;
	for(i = 0; i < str.length(); i++){
		std::string _s;
		for(j = i; j < str.length(); j++){ // for(j = 0; j < sep.length() && i+j < str.length(); j++){
			_s += str[j];
			if(call(_s)){
				b = true;
				break;
			}
		}
		if(b)
			v.push_back(__s), i += _s.length()-1, __s.clear();
		else
			__s += str[i];
		b = false;
	}
	v.push_back(__s);
	return v;
}

namespace ENHANCED{
std::vector<std::string> split(std::string str, std::string _split){
	if(_split == ""){
		int i;
		std::string item;
		std::vector<std::string>v;
		for(i = 0; i < str.length(); i++)
			v.push_back(item = str[i]);
		return v;
	}
	return __split<std::vector<std::string>>(str, [_split](std::string s)->bool{
			return s == _split;
	});
}
}


ENHANCED::Iterator<std::string> ENHANCED::splitToIterator(std::string str, std::string split){
	if(split == ""){
                int i;
                std::string item;
                Iterator<std::string>v;
                for(i = 0; i < str.length(); i++)
			v.push_back(item = str[i]);
                return v;
        }
	return __split<ENHANCED::Iterator<std::string>>(str, [split](std::string s)->bool{
                        return s == split;
        });
}
