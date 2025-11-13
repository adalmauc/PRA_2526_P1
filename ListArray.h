#include <iostream>
#include <stdexcept>
#include "List.h"

template <typename T>
class ListArray : public List<T>{
	private:
		T* arr;
		int max;
		int n;
		static const int MINSIZE =2;

		void resize(int new_size){
			T* temp = new T[new_size];
			int j=0;
			for(int i=0; i<new_size; i++){
				while(arr[j]==nullptr){
					j++;
				}
				temp[i]=arr[j];
				j++;
			}
			delete[] arr;
			arr = temp;
			max = new_size-1;
		}

	public:
		void ListArray(){
			arr = new T[MINSIZE];
			max = MINSIZE;
			n = 0;
		}

		T operator[](int pos){
			if(pos<0 || pos >= n){
				throw(std::out_of_range);
			}else{
			return arr[pos];
			}
		}

		friend std::ostream &operator<<(std::ostream &out, const ListArray<T> &list){
			for(int i=0; i<n; i++){
				out << list.arr[i] << " ";
			}
			return out;
		}

		void insert(int pos, T e) override {
        if (pos < 0 || pos > n) throw std::out_of_range("posicion invalida");
        if (n == max) resize(max * 2);
        for (int i = n; i > pos; i--) arr[i] = arr[i - 1];
        arr[pos] = e;
        n++;
		}

		void append(T e) override {
        insert(n, e);
		}

		void prepend(T e) override {
        insert(0, e);
		}

		T remove(int pos) override {
        if (pos < 0 || pos >= n) throw std::out_of_range("posicion invalida");
        T elem = arr[pos];
        for (int i = pos; i < n - 1; i++) arr[i] = arr[i + 1];
        n--;
        if (n < max / 4 && max / 2 >= MINSIZE) resize(max / 2);
        return elem;
		}

		T get(int pos) override {
        if (pos < 0 || pos >= n) throw std::out_of_range("Posición inválida");
        return arr[pos];
		}

		int search(T e) override {
        for (int i = 0; i < n; i++) {
            if (arr[i] == e) return i;
        }
        return -1;
		}

		bool empty() override {
        return n == 0;
		}

		int size() override {
        return n;
		}
}
