// OOP using C++ - Webinar 4 (22.08.2022)
// Homework - tasks 1 and 2
// Created by Daniil Neserov (e-mail: maidanov1991@yandex.ru)

#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

class ArrayInt {
public: 
	ArrayInt() : m_length(0), m_data(nullptr) {}
	ArrayInt(const int& _size) {
		if (_size > 0) {
			m_length = _size;
			m_data = new int[_size];
		}
		else {
			m_length = 0;
			m_data = nullptr;
		}
	}
	ArrayInt(const int& _size, const int& init_value) {
		if (_size > 0) {
			m_length = _size;
			m_data = new int[_size];
			for (size_t i = 0; i < m_length; i++) {
				m_data[i] = init_value;
			}	
		}
		else {
			m_length = 0;
			m_data = nullptr;
		}
	}
	~ArrayInt() { 
		delete[] m_data;
		m_data = nullptr;
	}
	int size() const { return m_length; }
	int& operator[] (int index) {
		assert(index >= 0 && index < m_length);
		return m_data[index];
	}
	void clear() {
		if (m_data != nullptr) {
			delete[] m_data;
			m_data = nullptr;
			m_length = 0;
		}
	}
	void resize(const int& newSize) {
		if (newSize == m_length) return;
		if (newSize <= 0) {
			clear();
			return;
		}
		else {
			int* newData = new int[newSize];
			int copySize = (newSize >= m_length) ? m_length : newSize;
			for (size_t i = 0; i < copySize; i++) {
				newData[i] = m_data[i];
			}
			for (size_t i = copySize; i < newSize; i++) {
				newData[i] = 0;
			}
			delete[] m_data;
			m_data = newData;
			m_length = newSize;
		}
	}
	void insert(const int& value, const int& index) {
		assert(index >= 0);
		if (index >= m_length) resize(index + 1);
		else resize(m_length + 1);
		for (size_t i = m_length - 1; i > index; i--) {
			m_data[i] = m_data[i - 1];
		}
		m_data[index] = value;
	}
	friend ostream& operator<<(ostream& out, const ArrayInt& AI);

//Task 1------------------------------------------------------------------------------------------------------------------------------------

	void pop_back() {
		assert(m_length > 0);
		if (m_length == 1) clear();
		else resize(m_length - 1);
	}

	void pop_front() {
		assert(m_length > 0);
		if (m_length == 1) clear();
		else {
			int* newData = new int[m_length - 1];
			for (size_t i = m_length - 1; i > 0; i--) {
				newData[i - 1] = m_data[i];
			}
			delete[] m_data;
			m_data = newData;
			m_length--;
		}
	}

	void sort(const int& start_index, const int& end_index) {
		assert(start_index >= 0 && start_index <= end_index && end_index < m_length);
		if (start_index == end_index) return;
		else {
			int i = start_index;
			int j = end_index;
			int pivot = m_data[(start_index + end_index) / 2];
			do {
				while (m_data[i] < pivot) i++;
				while (m_data[j] > pivot) j--;
				if (i <= j) {
					swap(m_data[i], m_data[j]);
					i++;
					j--;
				}
			} while (i <= j);
			if (i < end_index) sort(i, end_index);
			if (j > start_index) sort(start_index, j);	
		}
	}

	void print_element(const int& index) {
		assert(index >= 0 && index < m_length);
		cout << m_data[index] << " ";
	}

//End of task 1-----------------------------------------------------------------------------------------------------------------------------

private:
	int m_length;
	int* m_data;
};

ostream& operator<<(ostream& out, const ArrayInt& AI) {
	for (size_t i = 0; i < AI.m_length; i++) {
		out << AI.m_data[i] << " ";
	}
	return out;
}


//Task 2------------------------------------------------------------------------------------------------------------------------------------

int count_different_numbers(const vector<int>& v) {
	int limit = v.size();
	if (limit == 0 || limit == 1) return limit;
	else {
		vector<int>* v2 = new vector<int>(0);
		v2->push_back(v[0]);
		int counter = 0;
		for (int i = 1; i < limit; i++) {
			if (v[i] == v[i - 1]) continue;
			for (int j = v2->size() - 1; j >= 0; j--) {
				if (v[i] == (*v2)[j]) {
					counter++;
					break;
				}
			}
			if (counter == 0) v2->push_back(v[i]);
			else counter = 0;
		}
		int result = v2->size();
		delete v2;
		return result;
	}
}

//End of task 2-----------------------------------------------------------------------------------------------------------------------------


int main() {
	cout << "Task 1-------------------------------------------------------------------------------------\n";
	ArrayInt Arr(10, 8);
	Arr[0] = 9;
	Arr[2] = 7;
	Arr[3] = 4;
	Arr[4] = 2;
	Arr[5] = 5;
	Arr[6] = 3;
	Arr[8] = 6;
	Arr[9] = 1;
	cout << Arr << endl;
	Arr.pop_back();
	cout << Arr << endl;
	Arr.pop_front();
	cout << Arr << endl;
	Arr.sort(0,Arr.size() - 1);
	cout << Arr << endl;
	Arr.print_element(2);
	Arr.print_element(5);
	cout << endl;
	cout << "End of task 1------------------------------------------------------------------------------\n\n";
	
	cout << "Task 2-------------------------------------------------------------------------------------\n";
	vector<int> V0(0);
	for (int i : V0) cout << i << " ";
	cout << ": number of different integers is " << count_different_numbers(V0) << endl;
	vector<int> V1(1);
	for (int i : V1) cout << i << " ";
	cout << ": number of different integers is " << count_different_numbers(V1) << endl;
	vector<int> V2 = { 1, 2, 3, 4, 4, 4, 4, 4, 5 };
	for (int i : V2) cout << i << " ";
	cout << ": number of different integers is " << count_different_numbers(V2) << endl;
	vector<int> V3(8, -2);
	for (int i : V3) cout << i << " ";
	cout << ": number of different integers is " << count_different_numbers(V3) << endl;
	cout << endl;
	cout << "End of task 2------------------------------------------------------------------------------\n\n";
	
	return 0;
}
