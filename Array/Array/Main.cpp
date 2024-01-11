#include "Array.h"

int main() {
	srand(time(0));
	Array<int> arr("Array", 5);
	size_t user_answer = 1;
	cout << "0 - Exit\n1 - add num\n2 - get size\n3 - get sum\n4 - get avg\n5 - print\n6 - print nums > avg\n7 - sort" << endl;
	while (user_answer != 0) {
		cout << "Enter num: ";
		cin >> user_answer;
		switch (user_answer) {
		case 0:
			break;
		case 1:
			{
				int num;
				cout << "Enter num: ";
				cin >> num;
				arr.push_back(num);
			}
			break;
		case 2:
			cout << "Size = " << arr.size() << endl;
			break;
		case 3:
			cout << "Sum = " << arr.sum() << endl;
			break;
		case 4:
			cout << "AVG = " << arr.avg() << endl;
			break;
		case 5:
			arr.print();
			break;
		case 6:
			arr.printNumsByAVG();
			break;
		case 7:
			arr.sort();
			break;
		default:
			cout << "Invalid variant" << endl;
			break;
		}
	}
}