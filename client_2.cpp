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
	
	cout << "\n\nLet's try 2db transaction now\n";
	A->makePayment();
	
	string tid;
	cout << "Enter ID: ";
	cin >> tid;
	vector <string> record1 = A->getTransactionDetails(tid);
	
	for(auto i : record1)
		cout << i << ' ';
	cout << '\n';
	
}
