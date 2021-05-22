# ENHANCED - experimental!

The ENHANCED library is an API set up of some of the modern methods written in C++. Such methods are built-in in JavaScript, Python and other high-level languages. By emulating the functions, you're letting the complexity of a project decrease significantly. In other words, it's supposed to mirror the approach to high-level languages and simplify code.

The purpose of writting it is to make life easier for C++ developers who prefer back-end toolsets to be written stricly in C++. For the simple reason that we could extend them and analyse the complexity.

Still in development! The split function is available as a tryout and it runs properly. In case you wanna use the API, delete the main section and import it from the current working directory.


All definitions declared within the ENHANCED namespace.

Samples are included in the main function of each file; or you can check them out here.

## Examples:

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
