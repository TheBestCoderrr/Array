#pragma once
#include <iostream>
#include <fstream>
using namespace std;

template<class T>
class Array {
public:
	Array(const char* filename, size_t count_nums = 0);
	~Array() { delete[] filename; }
	size_t size() const;
	void push_back(T value);
	T sum() const;
	double avg() const;
	void print() const;
	void printNumsByAVG() const;
	void sort();
private:
	char* filename;
};

template<class T>
Array<T>::Array(const char* fname,size_t count_nums) : filename(_strdup(fname))
{
	ofstream fcout(filename, ios::binary | ios::app | ios::out);
	if (!fcout.is_open()) throw exception("File not open");
	T num;
	for (size_t i = 0; i < count_nums; i++) {
		num = rand() % 100;
		fcout.write(reinterpret_cast<const char*> (&num), sizeof(num));
	}
	fcout.close();
}

template<class T>
size_t Array<T>::size() const
{
	ifstream fs(filename, ios::binary | ios::in);
	if (!fs.is_open()) throw exception("File not open");
	T num;
	size_t i = 0;
	for (; fs.read(reinterpret_cast<char*> (&num), sizeof(num)); i++);
	fs.close();
	return i;
}

template<class T>
void Array<T>::push_back(T value)
{
	ofstream fcout(filename, ios::binary | ios::app | ios::out);
	if (!fcout.is_open()) throw exception("File not open");
	fcout.write(reinterpret_cast<const char*> (&value), sizeof(value));
	fcout.close();
}

template<class T>
T Array<T>::sum() const
{
	ifstream fs(filename, ios::binary | ios::in);
	if (!fs.is_open()) throw exception("File not open");
	T sum = 0, num;
	for (; fs.read(reinterpret_cast<char*> (&num), sizeof(num));) sum += num;
	fs.close();
	return sum;
}

template<class T>
double Array<T>::avg() const { return double(sum()) / double(size()); }

template<class T>
void Array<T>::print() const
{
	ifstream fs(filename, ios::binary | ios::in);
	if (!fs.is_open()) throw exception("File not open");
	T num;
	for (; fs.read(reinterpret_cast<char*> (&num), sizeof(num));) cout << num << ' ';
	fs.close();
	cout << endl;
}

template<class T>
void Array<T>::printNumsByAVG() const
{
	T avg = this->avg();
	ifstream fs(filename, ios::binary | ios::in);
	if (!fs.is_open()) throw exception("File not open");
	T num;
	for (; fs.read(reinterpret_cast<char*> (&num), sizeof(num));) if(num > avg) cout << num << ' ';
	fs.close();
	cout << endl;
}

template<class T>
void Array<T>::sort()
{
	fstream fs(filename, ios::binary | ios::in | ios::out);
	if (!fs.is_open()) throw exception("File not open");
	size_t size = this->size();
	T num1, num2;
	for (size_t i = 0; i < size - 1; i++) {
		fs.seekg(0, ios::beg);
		for (size_t j = 0; j < size - i - 1; j++) {
			fs.read(reinterpret_cast<char*>(&num1), sizeof(num1));
			fs.read(reinterpret_cast<char*>(&num2), sizeof(num2));
			if (num1 > num2) {
				fs.seekp(-static_cast<streamoff>(2 * sizeof(T)), ios::cur);
				fs.write(reinterpret_cast<const char*>(&num2), sizeof(num2));
				fs.write(reinterpret_cast<const char*>(&num1), sizeof(num1));
			}
			fs.seekp(-static_cast<streamoff>(sizeof(T)), ios::cur);
		}
	}
	fs.close();
}
