# ENHANCED - experimental!

The ENHANCED library is an API set-up of some of the modern methods written in C++. Such methods are built-in in JavaScript, Python and other high-level languages. By emulating the functions, you decrease the complexity of a project significantly. In other words, it's supposed to mirror the approach to scripting languages and simplify code.

I wrote it to make life easier for C++ developers who prefer back-end toolsets to be written strictly in C++. The developer could extend, analyze the toolsets and - most importantly - not dimish performance.

Still in development, the split function is available as a tryout and it runs properly. In case you wanna use the API, delete the main section and import it from the current working directory.


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
