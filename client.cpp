#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "include/Amazon.h"

int main()
{
	Amazon *A = new Amazon("India");

	cout << "Select the operation that you want to perform: \n";
	cout << "1.Register User\n2.Get User Details\n3.Get Transaction Details\n";
	cout << "4.Update User Details\n5.Make Payment\n0.Exit\n\n";

	int op;

	do
	{
		cin >> op;
		switch(op)
		{
			case 1:
			{
				int is_registered = A->registerUser();
				break;
			}
			
			case 2:
			{
				string user_id;
				cout << "Enter ID: ";
				cin >> user_id;
				vector<string> user_details = A->getUserDetails(user_id);
				for (auto it : user_details)
					cout << it << " ";
				cout << endl;
				break;
			}
			
			case 3:
			{
				string transaction_id;
				cout << "Enter ID: ";				
				cin >> transaction_id;
				vector<string> transaction_deatils = A->getTransactionDetails(transaction_id);
				for (auto it : transaction_deatils)
					cout << it << " ";
				cout << endl;
				break;
			}
			
			case 4:
			{
				int is_updated = A->updateUserDetails();
				break;
			}
			
			case 5:
			{
				int is_payment_made = A->makePayment();
				break;
			}
			
			case 0:
			{
				cout << "Exiting\n\n";
				break;
			}
			
			default:
			{
				cout << "Invalid choice\nPlease select correct operation number\n";
				break;
			}
		}
		
	} while(op != 0);

	return 0;
}
