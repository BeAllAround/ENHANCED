#include "Emulator.cc"

using namespace ENHANCED;

void printOut(std::vector<std::string>loop){
	std::cout << "[";
	for(int i =0; i<loop.size(); i++){
		std::cout << '"' << loop[i] << '"';
		if(i!=loop.size()-1)std::cout<< ", ";
	}
	std::cout << "]\n";
}

int main(){
	// you can use it by iterating over an Iterator with the Emulator MACRO
	auto e = ENHANCED::Emulator("  Write  me something  45  ", "  "); 
	std::cout << "[ ";
	while(++e){
		std::cout << *e << ", ";
	};
	std::cout << "]\n";
	// output: [ , Write, me something, 45, , ]

	// or you can use it as a vector
	printOut(ENHANCED::split("  gobble  de  gook  ", "  ")); // output: ["", "gobble", "de", "gook", ""]
	printOut(ENHANCED::split("gobble de gook", " ")); // output: ["gobble", "de", "gook"]
	printOut(ENHANCED::split("gobble de gook", "")); // empty string: ["g", "o", "b", "b", "l", "e", " ", "d", "e", " ", "g", "o", "o", "k"]
	auto _a = ENHANCED::split("GNU", " "); // can't split!
	std::cout << _a[0] << std::endl; // output: "GNU"


	// usage of the Iterator;

	ENHANCED::Iterator<char*>iterator;

	iterator<<"I'm"; // append( item: Type );
	iterator<< " goofy";
	iterator<<"me";
	iterator<<"are";
	iterator<<"are";
	iterator<<"DUMP";
	iterator.remove("me"); // remove an item; returns: 1 if succeeded
	iterator.removeAll("are"); // erase all elements with the value of N
	iterator.pop(); // gets rid of the last element

	while(++iterator){ // loop in order
		std::cout << "index: " << iterator.index() << " " << *iterator << std::endl;
	}
	iterator.setCounter(iterator.length());
	for(;--iterator;){ // loop in reverse
		std::cout << "index: " << iterator.index() << " " << *iterator << std::endl;
	}

	auto vectorIterator = iterator.toVector(); // conversion to std::vector;
	for(int i = 0; i<vectorIterator.size(); i++){
		std::cout << vectorIterator[i];		
	}
	std::cout << std::endl; // outputs: "I'm goofy"

	ENHANCED::Iterator<std::string>_iter = splitToIterator(" REAL WHERE TO GO   ", " "); // pack it up into an Iterator

	_iter.remove("REAL");
	_iter<<"!";
	_iter.removeAll(""); // clear the string of empty data
	_iter = _iter.map([](auto&item, int index){ // using the map function to replace all exclamation points in a string. This might well be the most effective way to filter your data - by callbacks.
                if(item=="!")
			return(std::string)"?";
                return item;
        });
	
         _iter = _iter.filter([](auto&item, int inx){
               if(item!="?")
	       		return true;
               return false;
        });

	std::cout << "-----------------" << std::endl;
	while(++_iter){
		std::cout << (*_iter);

	}
	std::cout << std::endl; // output: "WHERETOGO"
	std::cout << "-----------------" << std::endl;

	_iter.setCounter(_reset);

	// std::cout << _iter << std::endl; // show the list format
	// auto __iter = _iter;
	auto iter_2 = _iter;

	_iter = _iter.trim(1, 3);  // using the trim function
	std::cout << _iter << std::endl; // ["TO", "GO"]
	std::cout << iter_2 << std::endl;

	ENHANCED::Iterator<std::string> __iter_2;
	std::string __s = "SSS";
	__iter_2 <<  __s;
	__s.clear();
	std::cout << "__s" << (bool)(__s=="") << __iter_2[0] << std::endl;

	Iterator<std::string>("192.168.0.1", "."); // splitting an IP address and having it as an Iterator

	return 0;
}
