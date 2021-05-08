#include <iostream>
#include <pthread.h>

#include "include/File.h"
#include "include/DBSchema.h"

void addRecord(File* file_obj_ptr, DBSchema *db_schema_obj, string id, vector<string> record_values);
void deleteRecord(File* file_obj_ptr, DBSchema *db_schema_obj, string id);
void readRecord(File* file_obj_ptr, DBSchema *db_schema_obj, string id);
void readCell(File* file_obj_ptr, DBSchema *db_schema_obj, string id, string schema_col_name);
void updateRecord(File* file_obj_ptr, DBSchema *db_schema_obj, string id, vector<string> record_values);
void updateCell(File* file_obj_ptr, DBSchema *db_schema_obj, string id, string schema_col_name, string value);

int main()
{
    cout << "\n\n----- client_file_test without multi-threading -----\n\n";

    File *customer_db = new File(10, 4);
    vector<string> customer_col_names = {
        "customer_id", 
        "name", 
        "phone_no", 
        "address"
    };
    DBSchema *customer_db_schema = new DBSchema(customer_db, customer_col_names);
    
    File *payment_db = new File(10, 5);
    vector<string> payment_col_names = {
        "payment_id", 
        "customer_id", 
        "amount", 
        "mode_of_payment", 
        "payment_timestamp"
    };
    DBSchema *payment_db_schema = new DBSchema(payment_db, payment_col_names);

    File *shipping_db = new File(10, 5);
    vector<string> shipping_col_names = {
        "shipping_id", 
        "payment_id", 
        "to_location", 
        "is_delivered", 
        "shipment_timestamp"
    };
    DBSchema *shipping_db_schema = new DBSchema(shipping_db, shipping_col_names);
 
    addRecord(customer_db, customer_db_schema, "c1", {"c1", "ram", "9972", "bangalore"});
    addRecord(customer_db, customer_db_schema, "c2", {"c2", "pia", "9874", "delhi"});
    addRecord(customer_db, customer_db_schema, "c3", {"c3", "dia", "2345", "pune"});
    addRecord(customer_db, customer_db_schema, "c4", {"c4", "dev", "8193", "chennai"});

    readCell(customer_db, customer_db_schema, "c1", "name"); 
    readCell(customer_db, customer_db_schema, "c2", "phone_no"); 
    readCell(customer_db, customer_db_schema, "c3", "address"); 

    deleteRecord(customer_db, customer_db_schema, "c2"); 
    readCell(customer_db, customer_db_schema, "c2", "phone_no"); 
    readCell(customer_db, customer_db_schema, "c3", "address"); 

    updateRecord(customer_db, customer_db_schema, "c4", {"c4", "devi", "8194", "chennai"});
    readRecord(customer_db, customer_db_schema, "c4");
    updateCell(customer_db, customer_db_schema, "c4", "name", "dev");
    readRecord(customer_db, customer_db_schema, "c4");
    readRecord(customer_db, customer_db_schema, "c1");

    addRecord(customer_db, customer_db_schema, "c5", {"c5", "sai", "8147", "pune"});
    readRecord(customer_db, customer_db_schema, "c5");
    addRecord(customer_db, customer_db_schema, "c6", {"c6", "ria", "7143", "chennai"});
    updateCell(customer_db, customer_db_schema, "c5", "phone_no", "2134");
    readRecord(customer_db, customer_db_schema, "c5");

    return 0;    
}

//op_code = 0  - addrecord
void addRecord(File* file_obj_ptr, DBSchema *db_schema_obj, string id, vector<string> record_values)
{
    cout << "adding record for " << id << endl; 
    int row_num = file_obj_ptr->addRecord(record_values);
    db_schema_obj->updateIdRowNum(row_num, id, 0);
    cout << endl;
}

//op_code = 1  - deleterecord
void deleteRecord(File* file_obj_ptr, DBSchema *db_schema_obj, string id)
{
    cout << "deleting record for " << id << endl; 
    pair<bool, int> success_row_num = db_schema_obj->getRowNumRecord(id);
    if (success_row_num.first)
    {
        file_obj_ptr->deleteRecord(success_row_num.second);
    }
    else
    {
        cout << "failed to delete";
    }
    db_schema_obj->updateIdRowNum(success_row_num.second, id, 1);
    cout << endl << endl;
}

//op_code = 2  - readRecord
void readRecord(File* file_obj_ptr, DBSchema *db_schema_obj, string id)
{
    cout << "reading record for " << id << endl; 
    vector<string> record_values;
    pair<bool, int> success_row_num = db_schema_obj->getRowNumRecord(id);
    if (success_row_num.first)
    {
        record_values = file_obj_ptr->readRecord(success_row_num.second);
    }
    else
    {
        cout << "failed to read record";
    }
    for (uint i = 0; i < record_values.size(); i++)
        cout << record_values[i] << " ";
    cout << endl << endl;
}

//op_code = 20 - readCell
void readCell(File* file_obj_ptr, DBSchema *db_schema_obj, string id, string schema_col_name)
{
    cout << "reading cell for " << id << endl; 
    string cell_value;
    pair<bool, pair<int, int>> success_row_num = db_schema_obj->getRowColNumsCell(id, schema_col_name);
    //cout << success_row_num.second.first << " " << success_row_num.second.second << endl;
    if (success_row_num.first)
    {
        cell_value = file_obj_ptr->readCell(success_row_num.second.first, success_row_num.second.second);
    }
    else
    {
        cout << "failed to read cell";
    }
    cout << cell_value;
    cout << endl << endl;
}

//op_code = 3  - updateRecord
void updateRecord(File* file_obj_ptr, DBSchema *db_schema_obj, string id, vector<string> record_values)
{
    cout << "uppdaing record for " << id << endl; 
    pair<bool, int> success_row_num = db_schema_obj->getRowNumRecord(id);
    if (success_row_num.first)
    {
        file_obj_ptr->updateRecord(success_row_num.second, record_values);
    }
    else
    {
        cout << "failed to update record\n";
    }
    cout << endl;
}

//op_code = 30 - updateCell
void updateCell(File* file_obj_ptr, DBSchema *db_schema_obj, string id, string schema_col_name, string value)
{
    cout << "updating record for " << id << endl; 
    pair<bool, pair<int, int>> success_row_num = db_schema_obj->getRowColNumsCell(id, schema_col_name);
    if (success_row_num.first)
    {
        file_obj_ptr->updateCell(success_row_num.second.first, success_row_num.second.second, value);
    }
    else
    {
        cout << "failed to update record";
    }
    cout << endl;
}
