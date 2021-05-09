#ifndef AMAZON_H
#define AMAZON_H

#include <vector>
#include <string>

#include "DBSchema.h"
#include "File.h"
#include "DBFile.h"
#include "Coordinator.h"

using namespace std;

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
	
	public:
		Amazon(string branch_name);
		string registerUser(string name, int phno, string address);
		vector <string> getUserDetails(string id);
		vector <string> getTransactionDetails(string id);
		
		int updateUserDetails();
		int makeTransaction();			
};

#endif
