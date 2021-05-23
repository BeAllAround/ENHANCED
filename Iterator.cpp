#include"./prerequisites.h"

namespace ENHANCED{
template<class T>
class Iterator{
	protected:private:
		T*data;
		int size;
		int counter;
	public:
		Iterator():data{(T*)malloc(1000)}, size{0}, counter{-1}{}; // set-up;

		Iterator<T>&operator<<(T v){
			data[size++] = v;
			return*this;
		};

		int index(){ return counter==-1 ? 0 : counter; };
		void empty(){ // do the same thing as in the constructor!
			data = (T*)malloc(1000); 
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

		bool includes(T);
		bool remove(T);			
		int findIndex(T);
		void pop(void);

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
bool ENHANCED::Iterator<T>::includes(T item){
	int i = 0;
	while(i<size){
		if(this->atIndex(i)==item)return true;
		i++;
	}
	return false;
}
template<class T>
int ENHANCED::Iterator<T>::findIndex(T item){
	int i=0;
	while(i<size){
		if(this->atIndex(i)==item)return i;
		i++;
	}
	return-1;
}
template<class T>
bool ENHANCED::Iterator<T>::remove(T item){
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
			newOne<<this->atIndex(i);
		}
		return replace(*this, newOne);
	}
	throw"CAN'T POP!";
}
		

int main(){
	ENHANCED::Iterator<char*>iterator;
	
	iterator<<"I'm";
	iterator<< " goofy";
	iterator<<"me";
	iterator<<"are";
	std::cout << iterator.remove("me") << std::endl;
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

	return 0;
};
