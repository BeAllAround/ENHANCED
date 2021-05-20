#include<iostream>
#include<string>
#include<iterator>
#include<vector>

#define INT int
#define PUBLIC public
#define PRIVATE private
#define PROTECTED protected
#define BOOL bool
#define _NOT not
#define IF if

int match(std::string set, std::string subset, int start){
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
	BOOL COND;

	PUBLIC:
		bool _switch = false, _switch2 = false;
		_Emulator()=default;
		_Emulator(std::string, std::string);

		BOOL iterate(void){
			if(entry.length()==c1)return false;
			else{
				_current = entry[c1++];
				return true;
			};
		};

		int next(void){
			std::string empty("");
			IF(_switch){
				_current = entry;
				_switch = false;
				_switch2 = true;
				return 1;
			}
			IF(_switch2)return 0;

			if(_NOT COND){
				for(int i=c; i<entry.length(); i++){
					if(_trim(entry, split, i, split.length())){
						c = i + split.length();
						_current = empty;
						return 1;
					}	
					empty += entry[i];

				};
				return 0;
			}else{
				return iterate();
			}
		};

		std::string current(){
			return _current;
		};

};
_Emulator::_Emulator(std::string entry, std::string split):split{split}, entry{entry+split}, COND{split==(std::string)""}{
			IF(match(entry, split, 0)==-1)_switch = true;
};


std::vector<std::string>implement(std::string str, std::string split){
	_Emulator e = _Emulator(str, split);
	std::vector<std::string>myData;
	while(e.next()){
		myData.push_back(e.current());
	}
	return myData;
};

void printOut(std::vector<std::string>loop){
	std::cout << "[ ";
	for(int i =0; i<loop.size(); i++){
		std::cout << loop[i] << ", ";
	}
	std::cout << "]\n";
}

int main(void){
	auto e = _Emulator("Write me something", " ");
	std::string s = "", s1="";

	e = _Emulator("Write  me something  45 ", " ");
	std::cout << "[ ";
	while(e.next()){
		std::cout << e.current() << ", ";
	};
	std::cout << "]\n";
	printOut(implement("gobble  de  gook", "  "));
	printOut(implement("gobble de gook", " "));
	printOut(implement("gobble de gook", "")); // empty string
	auto _a = implement("GNU", " ");
	std::cout << _a[0] << std::endl; // output: "GNU"

	return 0;
};
