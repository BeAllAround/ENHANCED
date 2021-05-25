#include "./prerequisites.h"

#define MAX 100000 // still in question

namespace ENHANCED{
template<class T>
class Iterator{
	protected:private:
		T*data;
		int size;
		int counter;
	public:
		Iterator():data{new T[MAX]}, size{0}, counter{-1}{}; // set-up;

		Iterator<T>&operator<<(T const v){ // chain-like structure
			data[size++] = v;
			return*this;
		};

		Iterator<T>&append(T const&v){
			data[size++] = v;
			return*this;
		};

		int index(){ return counter==-1 ? 0 : counter; };
		void empty(){ // do the same thing as in the constructor!
			data = new T[MAX]; 
			counter = -1;
			size = 0;
		};

		void replace(Iterator<T>&input, Iterator<T>&output){
			input.empty();
			while(++output){
				input<<(*output);	
			}	
		}

		T&atIndex(int index){ 
			if(index==-1 && index>counter)throw "INVALID INDEX!";
			return data[index];
		};

		int length(){ return size;};
		T&last(){ return data[size-1]; };

		bool includes(T const);
		bool remove(T const);
		void removeAll(T const);
		int findIndex(T const);
		void pop(void);

		template<class C, class...types>
		Iterator<T>reduce(C callback, types...args){ // just use "auto" as lambda is a possible input
			Iterator<T>arr;
			while(this->operator++()){
				arr<<(callback(this->operator*(), args...));
			}
			return arr;
		}

		bool operator++(){
			counter++;
			if(counter==size){
				counter = -1;
				return false;
			}
			return true;
		}

		bool operator--(){
			if(counter == -1) counter = size; // modify;
			counter--;
			if(counter==-1)return false;
			return true;
		}

		T&operator*(){
			return counter == -1 ? data[0] : data[counter];
		}

		std::vector<T>toVector(void){
			std::vector<T>arr;
			while(this->operator++()){
				arr.push_back(this->operator*());	
			}	
			return arr;
		}
};
}

template<class T>
bool ENHANCED::Iterator<T>::includes(T const item){
	int i = 0;
	while(i<size){
		if(this->atIndex(i)==item)return true;
		i++;
	}
	return false;
}
template<class T>
int ENHANCED::Iterator<T>::findIndex(T const item){
	int i=0;
	while(i<size){
		if(this->atIndex(i)==item)return i;
		i++;
	}
	return-1;
}
template<class T>
bool ENHANCED::Iterator<T>::remove(T const item){
	ENHANCED::Iterator<T>newOne;

	if(includes(item)){
		if(findIndex(item)==0){
			for(int i = 1; i<size; i++){
				newOne<<(this->atIndex(i));
			}	
			replace(*this, newOne);
			return true;
				
		}
		for(int i=0; i<findIndex(item); i++){
			newOne<<(this->atIndex(i));
		}
		for(int i=findIndex(item)+1; i<size; i++){
			newOne<<(this->atIndex(i));
		}
		replace(*this, newOne);
		return true;

	}
	return false;
}
template<class T>
void ENHANCED::Iterator<T>::pop(){
	ENHANCED::Iterator<T>newOne;
	if(size!=0){
		for(int i=0; i<size-1; i++){
			newOne<<(this->atIndex(i));
		}
		return replace(*this, newOne);
	}
	throw"CAN'T POP!";
}

template<class T>
void ENHANCED::Iterator<T>::removeAll(T const item){
	while(remove(item));
}
