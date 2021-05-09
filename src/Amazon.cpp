#include <iostream>
#include <cstdio>

using namespace std;

#include "../include/Amazon.h"
#include "../include/Mediator.h"
#include "../include/Coordinator.h"
#include "../include/Worker.h"

Amazon::Amazon(string branch_name) : branch_name(branch_name) 
{
	this->customer_db = new DBFile(10, 4);
    vector<string> customer_col_names = {
        "customer_id", 
        "name", 
        "phone_no", 
        "address"
    };
    this->customer_db_schema = new DBSchema(customer_db, customer_col_names);
    
    this->payment_db = new DBFile(10, 5);
    vector<string> payment_col_names = {
        "payment_id", 
        "customer_id", 
        "amount", 
        "mode_of_payment", 
        "payment_timestamp"
    };
    this->payment_db_schema = new DBSchema(payment_db, payment_col_names);

    this->shipping_db = new DBFile(10, 5);
    vector<string> shipping_col_names = {
        "shipping_id", 
        "payment_id", 
        "to_location", 
        "is_delivered", 
        "shipment_timestamp"
    };
    this->shipping_db_schema = new DBSchema(shipping_db, shipping_col_names);
    
    IMessageQueue *mq = new MessageQueue("Message system");
    Worker *w1 = new Worker(this->customer_db);
    Worker *w2 = new Worker(this->payment_db);
    Worker *w3 = new Worker(this->shipping_db);
    this->coord = new Coordinator(3, {w1, w2, w3}, mq);    
    
    this->coord->join(mq);
    w1->join(mq);
    w2->join(mq);
    w3->join(mq);
    
    userCount = 0;
    paymentCount = 0;
    shippingCount = 0;
}

int Amazon::registerUser()
{
	char id[20];
	++userCount; 
  	sprintf(id, "c%d", userCount);  
  	string uid(id);	
  	string name, ph, addr;
  	
  	cout << "Enter user's name: ";
  	cin >> name;
  	
  	cout << "Enter user's phone number: ";
  	cin >> ph;
  	
  	cout << "Enter user's address: ";
  	cin >> addr;
  	
	vector <string> new_record = {uid, name, ph, addr};
    Log_t op = {1, 2, -1, -1, new_record};
    
    vector <Log_t *> opList = {&op, NULL, NULL};
    int result = coord->performTransaction(opList);
    
    if(result == 1)
    {
    	cout << "User successfuly registered, user ID: " << id << "\n";  	
    	customer_db_schema->updateIdRowNum(op.row, uid, 0);
    	
    	return 1;  	
    }
    
    else cout << "Registration failed, please try again\n";
    return 0;
}	

vector <string> Amazon::getUserDetails(string id)
{	
    vector<string> record_values;
    pair<bool, int> success_row_num = customer_db_schema->getRowNumRecord(id);
    if (success_row_num.first)
    {
        record_values = customer_db->readRecord(success_row_num.second);
    }
    else
    {
        cout << "Failed to read record\n";
    }
    
    return record_values;
}	

vector <string> Amazon::getTransactionDetails(string id)
{
    vector<string> record_values;
    pair<bool, int> success_row_num = payment_db_schema->getRowNumRecord(id);
    if (success_row_num.first)
    {
        record_values = payment_db->readRecord(success_row_num.second);
    }
    else
    {
        cout << "Failed to read record\n";
    }
    
    return record_values;
}	

int Amazon::updateUserDetails()
{
	string uid, schema_col_name;
	int col_name;
	
	cout << "Enter user ID: ";
	cin >> uid;	
	
	cout << "Select the field whose value has to be changed: \n";
	cout << "1. Name\t2. Phone no\t3. Address\n";
	bool valid;
	do
	{
		valid = true;
		cin >> col_name;
		if(col_name == 1) schema_col_name = "name";
		else if(col_name == 2) schema_col_name = "phone_no";
		else if(col_name == 3) schema_col_name = "address";
		else 
		{
			cout << "Invalid choice\nPlease select a valid number: ";
			valid = false; 
		}		
	}while(!valid);
	
	string value;
	cout << "Enter the new value: ";
	cin >> value;	
	
    pair<bool, pair<int, int>> success_row_num = customer_db_schema->getRowColNumsCell(uid, schema_col_name);
    
    if (success_row_num.first)
    {
    	vector <string> new_record = {uid, "", "", ""};
    	new_record[success_row_num.second.second] = value;
    	
        Log_t op = {0, 0, success_row_num.second.first, success_row_num.second.second, new_record};
        
        vector <Log_t *> opList = {&op, NULL, NULL};
        int result = coord->performTransaction(opList);
        
        if(result == 1)
        {
        	cout << "Details successfuly updated\n";
        	return 1;
        }
        else
        {
        	cout << "Updation failed, please try again\n";
        	return 0;
        }
    }
    
    else
    {
        cout << "Invalid user ID\n";
        return 0;
    }
}	

int Amazon::makePayment()
{
	char id[20];
	
	++paymentCount; 	
  	sprintf(id, "c%d", paymentCount); 
  	string pid(id);; 
  	
	++shippingCount;
  	sprintf(id, "c%d", shippingCount);  
  	string sid(id);
  	
  	string uid, amount, mode, location, delivered, timestamp;
  	
  	cout << "Enter customer ID: ";
  	cin >> uid;
  	
  	cout << "Enter payment amount: ";
  	cin >> amount;
  	
  	cout << "Enter mode of payment: ";
  	cin >> mode;
  	
  	cout << "Enter delivery location: ";
  	cin >> location;
  	
  	delivered = "false";
  	timestamp = "now";
  	
  	vector <string> paymentRecord = {pid, uid, amount, mode, timestamp};
  	vector <string> shippingRecord = {sid, pid, location, delivered, timestamp};  	
  	
    Log_t payment_op = {1, 2, -1, -1, paymentRecord};
    Log_t shipping_op = {1, 2, -1, -1, shippingRecord};
    
    vector <Log_t *> opList = {NULL, &payment_op, &shipping_op};  	
    int result = coord->performTransaction(opList);
    
    if(result == 1)
    {
    	cout << "Details successfuly updated, transaction ID = " << pid << "\n";  
    	  	
    	payment_db_schema->updateIdRowNum(payment_op.row, pid, 0);
    	shipping_db_schema->updateIdRowNum(shipping_op.row, sid, 0);
    	return 1;
    }
    
    else cout << "Updation failed, please try again\n";
    return 0;  	
}	
