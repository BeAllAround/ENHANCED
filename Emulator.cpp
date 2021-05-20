#include<iostream>
#include<string>
#include<iterator>

#define INT int
#define PUBLIC public
#define PRIVATE private
#define PROTECTED protected
#define BOOL bool

int match(std::string set, std::string subset, int start){ // unused here
	int c = 0;
	int save;
	if(start>=set.length()){
		return-1;
	}

	for(int i=start; i<set.length(); i++){

		if(set[i]==subset[c]){
			c++;
			if(c==1)save = i;
		}
		if(c==subset.length()){
			return save; // ?
		};

	}
	if(c!=subset.length())return-1;
};

BOOL _trim(std::string _string, std::string _match,int back, int forward){
	std::string s = "";
	int c = 0;
	if(back > _string.length() || (back+forward) > _string.length())return false;

	for(int i= back; i<back+forward; i++){
		s+=_string[i];
	};
	return s==_match;
};

class _Emulator{
PRIVATE:PROTECTED:
	std::string split, entry, _current;
	INT c = 0, c1 = 0;

	PUBLIC:
		bool _switch = true;
		_Emulator()=default;
		_Emulator(std::string, std::string);

		int next(void){
			std::string empty("");
			for(int i=c; i<entry.length(); i++){
				if(_trim(entry, split, i, split.length())){
					c = i + split.length();
					_current = empty;
					return 1;
				}	
				empty += entry[i];

			};
			return 0;
		};

		std::string current(){
			return _current;
		};

};
_Emulator::_Emulator(std::string split, std::string entry):split{split}, entry{entry+split}{
};

int main(void){
	auto e = _Emulator(" ", "Write me something");
	std::string s = "", s1="";

	e = _Emulator("  ", "Write  me something  45");
	std::cout << "[ ";
	while(e.next()){
		std::cout << e.current() << ", ";
	};
	std::cout << "]\n";

	return 0;
};
