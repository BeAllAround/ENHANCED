#include"./Emulator.cc"

using namespace ENHANCED;

void printOut(std::vector<std::string>loop){
	std::cout << "[";
	for(int i =0; i<loop.size(); i++){
		std::cout << loop[i];
		if(i!=loop.size()-1)std::cout<< ", ";
	}
	std::cout << "]\n";
}

int main(){
	ENHANCED::Iterator<std::string>iterator;

	iterator<<"are";
	iterator<<"I'm";
	iterator<< " goofy";
	iterator<<"me";
	iterator<<"are";
	iterator<<"are";
	iterator<<"are";
	iterator<<"LAST";
	std::cout << iterator.remove("me") << std::endl;
	iterator.removeAll("are"); // erase all elements with the value of N
	iterator.pop();

	std::cout << "----------------" << std::endl;
	while(++iterator){
		std::cout << "index: " << iterator.index() << " " << *iterator << std::endl;
	}

	for(;--iterator;){
		std::cout << "index: " << iterator.index() << " " << *iterator << std::endl;
	}
	while(++iterator){
		std::cout << "index: " << iterator.index() << " " << *iterator << std::endl;
	}
	while(++iterator){
		std::cout << "index: " << iterator.index() << " " << *iterator << std::endl;
	}
	std::cout << "----------------" << std::endl;


	auto vectorIterator = iterator.toVector();
	for(int i = 0; i<vectorIterator.size(); i++){
		std::cout << vectorIterator[i];		
	}
	std::cout << std::endl;
	// outputs: "I'm goofy"
	
	// you can use it by iterating over an Emulator
	auto e = ENHANCED::_Emulator("  Write  me something  45  ", "  ");
	std::cout << "[ ";
	while(e.next()){
		std::cout << e.current() << ", ";
	};
	std::cout << "]\n";
	// output: ["", "Write", "me something", "45", ""]

	// or you can use it as a vector
	printOut(ENHANCED::split("  gobble  de  gook  ", "  ")); // output: ["", "gobble", "de", "gook", ""]
	printOut(ENHANCED::split("gobble de gook", " ")); // output: ["gobble", "de", "gook"]
	printOut(ENHANCED::split("gobble de gook", "")); // empty string: ["g", "o", "b", "b", "l", "e", " ", "d", "e", " ", "g", "o", "o", "k"]
	auto _a = ENHANCED::split("GNU", " "); // can't split!
	std::cout << _a[0] << std::endl; // output: "GNU"

	ENHANCED::Iterator<std::string>_iter = splitToIterator(" REAL WHERE TO GO   ", " "); // pack it up into an Iterator

	_iter.remove("REAL");
	_iter.removeAll("");
	_iter<<"?";
	std::cout << "-----------------" << std::endl;
	while(++_iter){
		std::cout << (*_iter);

	}
	std::cout << std::endl;
	std::cout << "-----------------" << std::endl;

	return 0;
}
