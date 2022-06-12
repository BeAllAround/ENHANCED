#include "prerequisites.h"

#define _MAX 3000 // still in question - each allocation when over this size takes too much time, so the only thing we could do is extend the buffer "data" when exceeding a certain number - to update the existing buffer;
#define _reset -1
#define _FREE(v) delete[] v
#define MAX sizeof(T) * _MAX

namespace ENHANCED{
template<class T = std::string>
class Iterator{
	private:
		T *data{nullptr};
		long long size, _power = MAX;
		int counter;
		bool auxiliary(){
			return counter == (size-1);
		}
		void del(){
			if(data != nullptr)
				delete[]data;
		}

	public:
		Iterator() : data{new T[MAX]}, size{0}, counter{-1}{}; // set-up;
		~Iterator(){
			size = 0;
			counter = -1;
			del();
		}

		Iterator(std::initializer_list<T> arr) : Iterator(){
			for(T item : arr)
				*this << item;
		}
		Iterator(std::string);
		Iterator(std::string, std::string);
		operator std::string();

		Iterator(const Iterator<T>&iter): data{new T[iter._power]}, size{iter.size}, counter{iter.counter}, _power{iter._power}{
			std::copy(iter.data, iter.data + size, data);
		}

		Iterator<T>&operator<<(T const v){ // chain-like structure
			if(size >= _power){ // preventing the heat buffer overflow "or equals-to"
				_power *= 10;
				T* data_c = new T[size];
				// std::cout << "_power called" << std::endl;
				std::copy(data, data+size, data_c);
				del();
				data = new T[_power];
				std::copy(data_c, data_c+size, data);
				delete[] data_c;
			}
			data[size++] = v;
			return *this;
		}

		Iterator<T>&operator=(const Iterator<T>&iter){
			del();
			data = new T[iter._power];
			counter = iter.counter;
			size = iter.size;
			_power = iter._power;
			std::copy(iter.data, iter.data + size, data); //
			return *this;
		}
		Iterator(Iterator<T> &&other)noexcept : data{nullptr}, size{0}, counter{-1}{
			*this = std::move(other);
		}

		Iterator<T>&operator=(Iterator<T>&&iter)noexcept{
			if(this != &iter){
				del();
				data = iter.data;
				size = iter.size;
				counter = iter.counter;
				_power = iter._power;
				iter.data = nullptr;
				iter.size = 0;
				iter.counter = -1;
				iter._power = MAX;
				/*
				this->data = new T[_power];
				this->size = iter.size;
				this->counter = iter.counter;
				std::copy(iter.data, iter.data + size, data); //
				iter.data= nullptr;
				*/
			}
			return *this;
		}


		Iterator<T>&append(T const v){
			*this << v;
		}

		void push_back(T v){
			*this << v;
		}

		int index(){ return counter == -1 ? 0 : counter; }

		void empty(){ // do the same thing as in the constructor!
			del();
			data = new T[MAX]; 
			counter = -1;
			size = 0;
		}

		void replace(Iterator<T>&input, Iterator<T>&output){
			input.empty();
			while(++output)
				input << *output;	
		}

		T&atIndex(int index){ 
			if(index <= -1 || index >= size)
				throw "INVALID INDEX!";
			return data[index];
		}

		T&operator[](int index){
			return atIndex(index);
		}

		int length()const{ return size;};
		T&last(){ return data[size-1]; };

		bool includes(T const);
		bool remove(T const);
		void removeAll(T const);
		int findIndex(T const);
		bool pop(void);
		bool is_empty(void)const{ return size == 0; }

		T str();
		T str(T const);

		Iterator<T>trim(int, int);
		Iterator<T>reverse();

		T shift(void){
			if(size >= 1){
				T temp = *data;
				T *data_c = new T[size];
				std::copy(data + 1, data + size, data_c);
				del();
				data = new T[_power];
				std::copy(data_c, data_c + --size, data);
				_FREE(data_c);
				return temp;
			}
			throw "something";
		}

		template<class C, class...types>
		Iterator<T> map(C callback, types...args){ // just use "auto" as lambda is a possible input
			Iterator<T>arr;
			int c_copy{counter};
			front();
			while(this->operator++())
				arr << (callback(this->operator*(), counter, args...));
			counter = c_copy;
			return arr;
		}

		template<class C, class...types>
		Iterator<T> filter(C callback, types...args){
			Iterator<T>arr;
			int c_copy{counter};
			front();
			while(this->operator++())
				if(callback(this->operator*(), counter, args...))
					arr << (this->operator*());
			counter = c_copy;
			return arr;
		}

		void setCounter(int c){
			if(c < -1 || c > size)
				throw "ERROR";
			counter = c;
		}

		void front(){
			return setCounter(_reset);
		}

		void back(){
			return setCounter(size);
		}

		bool operator++(){
			if(counter < size)
				counter++;
			if(counter == size)
				return false;
			return true;
		}

		bool operator--(){
			if(counter > -1){
				counter--;
				if(counter == -1)
					return false;
				return true;
			}
			return false;
		}

		T&operator*(){
			return counter == -1 ? data[0] : data[counter];
		}

		std::vector<T> toVector(void){
			std::vector<T>arr;
			int c_copy{counter};
			front();
			while(this->operator++())
				arr.push_back(this->operator*());	
			counter = c_copy;
			return arr;
		}
};
	
	template<> // std::string specification
	std::string Iterator<std::string>::str(std::string const join){
		std::string String;
		int c_copy{counter};
		while(this->operator++()){
			String += this->operator*();
			if(!auxiliary())
				String += join;
		}
		counter = c_copy;
		return String;
	}

	template<>
	std::string Iterator<std::string>::str(void){
		return str(""); // reuse virtually the same function
	}

	template<>
	Iterator<std::string>::Iterator(std::string _str) : Iterator(){ // do not forget to initialize the necessaries;
		int i;
		for(i = 0; _str[i] != 0; i++){
			std::string s{_str[i]};
			this->operator<<(s);
		}
	}

	template<>
	Iterator<char>::Iterator(std::string str) : Iterator(){
		int i{0};
		while(str[i] != 0)
			*this << str[i++];
	}

	template<>
	Iterator<std::string>::operator std::string(){
		return this->str();
	}

}


template<class T>
bool ENHANCED::Iterator<T>::includes(T const item){
	int i{};
	while(i < size){
		if(this->atIndex(i) == item)
			return true;
		i++;
	}
	return false;
}

template<class T>
ENHANCED::Iterator<T> ENHANCED::Iterator<T>::reverse(void){
	Iterator<T>arr;
	int c_copy{counter}; // swap the state
	back();
	while(this->operator--())
		arr << this->operator*();
	counter = c_copy;
	return arr;
}

template<class T>
int ENHANCED::Iterator<T>::findIndex(T const item){
	int i{0};
	while(i < size){
		if(this->atIndex(i) == item)
			return i;
		i++;
	}
	return -1;
}

template<class T>
bool ENHANCED::Iterator<T>::remove(T const item){
	Iterator<T>newOne;
	int i;
	if(includes(item)){
		if(findIndex(item) == 0){
			for(i = 1; i < size; i++)
				newOne << this->atIndex(i);
			replace(*this, newOne);
			return true;
				
		}
		for(i = 0; i < findIndex(item); i++)
			newOne << this->atIndex(i);
		for(i = findIndex(item) + 1; i < size; i++)
			newOne << this->atIndex(i);
		replace(*this, newOne);
		return true;

	}
	return false;
}

template<class T>
bool ENHANCED::Iterator<T>::pop(){
	ENHANCED::Iterator<T>newOne;
	int i;
	if(!is_empty()){
		for(i = 0; i < size-1; i++)
			newOne << this->atIndex(i);
		replace(*this, newOne);
		return true;
	}
	return false;
}

template<class T>
void ENHANCED::Iterator<T>::removeAll(T const item){
	while(remove(item));
}

template<class T>
ENHANCED::Iterator<T>ENHANCED::Iterator<T>::trim(int start, int end){
	int i;
	Iterator<T>iter;
	if(start > length() || end > length() || start >= end)
		return iter; // or throw a sink

	for(i = start; i < end; i++)
		iter << atIndex(i);	

	return iter;
}

/*
template<class T>
ENHANCED::Iterator<T>ENHANCED::Iterator<T>::reverse(){
	Iterator<T>arr;
	while(this->operator--())
		arr << this->operator*();
	return arr;
}
*/

std::ostream&operator<<(std::ostream&out, ENHANCED::Iterator<std::string> iter){
	out << '[';
	int i;
	for(i = 0; i < iter.length(); i++){
		out << '"' << iter[i] << '"';
		if(i != iter.length()-1)
			out << ',' << ' ';
	}
	out << ']';
	return out;
}

template<class T>
std::ostream&operator<<(std::ostream&C, ENHANCED::Iterator<T> iter){
	int c = int{0};
	C << "[";
	for(c = 0; c < iter.length(); c++){
		C << iter[c];
		if(c != iter.length()-1)
			C << ", ";
	}
	/* // determine the functionality?
	while(++iter){
		C << *iter;
		if(c!=iter.length()-1)
			C << ", ";
		c++;
	}
	*/
	C << "]";
	return C;
}

std::string strip(const std::string&str){
        std::string instance;
        int i, start, end;
        for(i = 0; i < str.length(); i++)
                if(str[i] == ' ')
                        continue;
                else{
                        start = i;
                        break;
                }
        for(i = str.length() - 1; i >= 0; i--)
                if(str[i] == ' ')
                        continue;
                else{
                        end = i;
                        break;
                }
        for(i = start; i <= end; i++)
                instance += str[i];
        return instance;
}

std::string operator*(std::string const&s, int n){
        std::string v;
        int _;
        for(_ = 0; _ < n; ++_)
                v += s;
        return v;
}

template<typename T>
void print(T v){ std::cout << v << '\n'; }
