#include <iostream>
#include <string>
#include <functional>
#include <vector>

#define _RETURN return
#define THIS this
#define _STRING string
#define _THROW(message) throw(_STRING(message));
#define _VOID_ void

/*
 * DEVELOPED ESPECUALLY FOR JAVASCRIPT ADDICTS, including myself!
 */

using namespace std;

template<class call, class...types>using _function = call(*)(types...);


//////////////////////////////////////////////////////////////////////////////
template<typename T,class TR=T> // the same embedded definition/implementation - like a JS engine;
class scope{
	template<class...types>using _TYPEC = _function<_VOID_, _function<_VOID_, T>, _function<_VOID_, TR>, types...>;

	protected:private:
		friend void _r(auto self, auto arg){
			  self->_resolve(arg);
		}

		T returnValue;
		TR rejectValue;


	       	bool c = false;
		// string state = "pending...";
		static scope<T, TR>instance;
		static int staticConstructor;

	        T resolveBack(T arg){
			return arg;
		};
		TR rejectBack(TR arg){
			return arg;

		};



		const void reset(void){ //
			instance.returnValue = T{};
			instance.rejectValue = TR{};
			instance.c = 0;
		};

		static void auxiliaryResolver(T);
		static void auxiliaryRejector(TR);


		scope(_VOID_); // cloak the constructor;

		void _resolve(T args){
			if(!c){
				returnValue = resolveBack(args);
				c = true;
			}
		};
	public:
		void _reject(TR args){
			if(!c){
				rejectValue = rejectBack(args);
				c = true;

			}
		};
		template<class...types>
			scope(std::function<void(std::function<void(T)>, std::function<void(TR)>)> callback, types...args);

		template<class...types>
			scope(std::function<void(std::function<void(T)>)> callback, types...args){
				scope();
				auto res = [this](T ar)->void{ // bind design
					return _r(this, ar);
				};
				callback(res, args...);
		}

		static scope<T, TR> resolve(T);
		static scope<T, TR> reject(TR);

		template<class C, class...types>
			scope<T, TR>*then(C, types...);

		scope<T, TR>* then(void);

		T& await(void);

		template<typename...types>
			static scope<T, TR> async(_function<T, types...>, types...);
};

template<class T, class TR>
int scope<T, TR>::staticConstructor{0};

template<class T, class TR>
scope<T, TR> scope<T, TR>::instance{};

template<class T, class TR>
scope<T, TR> scope<T, TR>::resolve(T item){
	scope<T, TR> _instance{}; // reset;
	auxiliaryResolver(item); // scope<T>::auxiliaryResolver(item);
	return _instance;
};

template<class T, class TR>
scope<T, TR> scope<T, TR>::reject(TR item){
	scope<T, TR> _instance{}; // reset;
	auxiliaryRejector(item);
	return _instance;
};

template<class T, class TR>
void scope<T, TR>::auxiliaryResolver(T item){
	return instance._resolve(item);
};

template<class T, class TR>
void scope<T, TR>::auxiliaryRejector(TR item){
	return instance._reject(item);
};


template<class T, class TR> // specification;
template<typename C, typename...types>
scope<T, TR>* scope<T, TR>::then(C callback, types...args){
	//__check(); // needless - for now;
	callback(returnValue, rejectValue, args...);
	_RETURN THIS;
};

template<class T, class TR>
scope<T, TR>* scope<T, TR>::then(){
	_RETURN THIS;
};

template<class T, class TR>
T& scope<T, TR>::await(){
	return returnValue;
};

template<class T, class TR>
scope<T, TR>::scope(_VOID_){
	reset();
};

template<class T, class TR>
template<class...types>
scope<T, TR> scope<T, TR>::async(_function<T, types...>callback, types...args){
	return resolve(callback(args...));
};


namespace ECMA{
	template<class T, class TR=T>
		using Promise = scope<T, TR>;
	
	template<class TYPE_, class TYPE__, typename...types>
		using wrap = _function<void, _function<void, TYPE_>, _function<void, TYPE__>, types...>;

	template<class TYPE_, typename...types>
		using wrapAsync = _function<TYPE_, types...>;
};

//////////////////////////////////////////////////////////////////////////////


void callback(auto resolve, auto reject, auto outside){
	resolve(*outside);
};

int main(void){ // usage;
	auto a1 = ECMA::Promise<int, int>([](auto resolve){ // placeholder
			resolve(5101);
	});

	auto a2 = ECMA::Promise<int>([](auto resolve){
			resolve(11);
	});

	a1.then([](auto resolve, auto reject){
			std::cout << resolve << std::endl;
	});

	a2.then([](auto resolve, auto reject){
			std::cout << resolve << std::endl;
	});

	std::cout << a1.await() << std::endl; // won't work - reject first executed
	std::cout << a2.await() << std::endl;
	return 0;
};
