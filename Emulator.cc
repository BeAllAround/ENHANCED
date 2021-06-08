#include "./Iterator.cc"

#define INT int
#define PUBLIC public
#define PRIVATE private
#define PROTECTED protected
#define BOOL bool
#define _NOT not
#define IF if
extern BOOL _trim(std::string, std::string, int, int);

int match(std::string set, std::string subset, int start){
        for(int i=start; i<set.length(); i++){
                if(_trim(set, subset, i, subset.length())){
                        return i;
                }
        }
        return-1;
};

BOOL _trim(std::string _string, std::string _match, int back, int forward){
	std::string s = "";
	int c = 0;

	if(back > _string.length() || (back+forward) > _string.length())return false;
	for(int i= back; i<back+forward; i++){
		s+=_string[i];
	};
	return s==_match;
};

namespace ENHANCED{
class _Emulator{
PRIVATE:PROTECTED:
	std::string split, entry, _current;
	INT c = 0, c1 = 0;
	BOOL COND;

	PUBLIC:
		bool _switch = false, _switch2 = false;
		_Emulator()=default;
		_Emulator(std::string, std::string);

		BOOL iterate(void){
			if(c1==entry.length())return false;
			_current = entry[c1++];
			return true;
		};

		BOOL next(void){
			std::string empty("");
			IF(_switch){
				_current = entry;
				_switch = false;
				_switch2 = true;
				return true;
			}
			IF(_switch2)return false;

			if(_NOT COND){
				for(int i=c; i<entry.length(); i++){
					if(_trim(entry, split, i, split.length())){
						c = i + split.length();
						_current = empty;
						return true;
					}	
					empty += entry[i];

				};
				return false;
			}else{
				return iterate();
			}
		};

		std::string current(){ // redirect
			return _current; // access the variable;
		};

};
	std::vector<std::string>split(std::string, std::string);
	ENHANCED::Iterator<std::string>splitToIterator(std::string, std::string);
	using Emulator = _Emulator;
}

ENHANCED::_Emulator::_Emulator(std::string _entry, std::string _split):split{_split}, COND{_split==(std::string)""}, _switch{match(_entry, _split, 0)==-1}{
	(!_switch) ? entry = _entry+_split : entry = _entry;
};


std::vector<std::string>ENHANCED::split(std::string str, std::string split){
	ENHANCED::_Emulator e(str, split);
	std::vector<std::string>myData;
	while(e.next()){
		myData.push_back(e.current());
	}
	return myData;
}

ENHANCED::Iterator<std::string>ENHANCED::splitToIterator(std::string str, std::string split){
	_Emulator e(str, split);
	ENHANCED::Iterator<std::string>newOne;
	while(e.next()){
		newOne<<(e.current());
	}
	return newOne;
}
