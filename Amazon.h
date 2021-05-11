#ifndef AMAZON_H
#define AMAZON_H

#include <vector>
#include <string>

using namespace std;

#include "include/DBSchema.h"
#include "include/File.h"
#include "include/DBFile.h"
#include "include/Coordinator.h"

class Amazon
{
	private:
		string branch_name;
		
		File *customer_db;
		DBSchema *customer_db_schema;
		
		File *payment_db;
		DBSchema *payment_db_schema;
		
		File *shipping_db;
		DBSchema *shipping_db_schema;
		
		Coordinator *coord;
		
		int userCount;
		int paymentCount;
		int shippingCount;
	
	public:
		Amazon(string branch_name);
		~Amazon();
		int registerUser();
		vector <string> getUserDetails(string id);
		vector <string> getTransactionDetails(string id);
		void printAllTransactions();
		
		int updateUserDetails();
		int makePayment();	
		
		void testCase();		
};

#endif