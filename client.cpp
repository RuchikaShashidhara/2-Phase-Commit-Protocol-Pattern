#include <iostream>
#include <string>

using namespace std;

#include "include/Amazon.h"

int main()
{
	Amazon *A = new Amazon("India");
	A->registerUser();
	
	string id;
	cout << "Enter ID: ";
	cin >> id;
	vector <string> record = A->getUserDetails(id);
	
	for(auto i : record)
		cout << i << ' ';
	cout << '\n';
}
