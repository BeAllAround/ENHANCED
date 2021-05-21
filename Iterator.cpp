#include<iostream>
#include<vector>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

namespace ENHANCED{
template<class T>
class Iterator{
	protected:private:
		T*data;
		int size;
		int counter;
	public:
		Iterator():data{(T*)malloc(1000)}, size{0}, counter{-1}{}; // set-up;

		Iterator<T>&Yield(T v){
			data[size++] = v;
			return*this;
		};

		int index(){ return counter==-1 ? 0 : counter; };

		int length(){ return size;};
		T&last(){ return data[size-1]; };


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
		

int main(){
	ENHANCED::Iterator<char*>iterator;

	iterator.Yield("I AM");
	iterator.Yield("goofy");
	while(++iterator){
		std::cout << "index: " << iterator.index() << " " << *iterator << std::endl;
	}
	for(;--iterator;){
		std::cout << "index: " << iterator.index() << " " << *iterator << std::endl;
	}
	while(++iterator){
		std::cout << "index: " << iterator.index() << " " << *iterator << std::endl;
	}

	auto vectorIterator = iterator.toVector();
	for(int i = 0; i<vectorIterator.size(); i++){
		std::cout << vectorIterator[i] << std::endl;		
	}

	return 0;
};
