# ENHANCED - experimental!

The ENHANCED library is an API set-up of some of the modern methods written in C++. Such methods are built-in in JavaScript, Python and other high-level languages. By emulating the functions, you decrease the complexity of a project significantly. In other words, it's supposed to mirror the approach to scripting languages and simplify code.

I wrote it to make life easier for C++ developers who prefer back-end toolsets to be written strictly in C++. The developer could extend, analyze the toolsets and - most importantly - not dimish performance.

Still in development, the split function is available as a tryout and it runs properly. In case you wanna use the API, delete the main section and import it from the current working directory.


All definitions declared within the ENHANCED namespace.

Samples are included in the main file; or you can check them out here.

## Examples:
	#include "Emulator.cc"
	
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
	_iter.removeAll(""); // clear the string of empty data
	_iter<<"!";
	_iter = _iter.map([](auto&item){ // using the map function to replace all exclamation points in a string. This might well be the most effective way to filter your data - by callbacks. 
                if(item=="!")return(std::string)"?";
                return item;
	});
	
	std::cout << "-----------------" << std::endl;
	while(++_iter){
		std::cout << (*_iter);

	}
	std::cout << std::endl; // output: "WHERETOGO?"
	std::cout << "-----------------" << std::endl;
	
	std::cout << _iter << std::endl; // show the list format
	
	Iterator<std::string>("192.168.0.1", "."); // splitting an IP address and having it as an Iterator
