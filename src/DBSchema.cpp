#include <iostream>
#include <algorithm>

#include "../include/File.h"
#include "../include/DBSchema.h"

using namespace std;

DBSchema :: DBSchema(File* file_values_obj_ptr, vector<string>& schema) 
{
    int row1 = file_values_obj_ptr -> addRecord(schema);
    __db_schema.assign(schema.begin(), schema.end());
}

DBSchema :: ~DBSchema() 
{

}

int DBSchema :: __getRowNum(string id)
{
    int row_num;
    map<string, int>::iterator id_row_num_itr = __id_row_num.find(id);
    if (id_row_num_itr != __id_row_num.end()) 
    {
        row_num = id_row_num_itr -> second;
    }
    else 
    {
        row_num = -1;
    }
    return row_num;
}

int DBSchema :: __getColNum(string schema_col_name) 
{
    int col_num;
    vector<string>::iterator schema_itr = find(__db_schema.begin(), __db_schema.end(), schema_col_name);
    if (schema_itr != __db_schema.end()) 
    {
        col_num = schema_itr - __db_schema.begin();
    }
    else 
    {
        col_num = -1;
    }

    return col_num;
}

pair<bool, int> DBSchema :: getRowNumRecord(string id)
{
	//cout << "[DB Schema] Row ID : " << id << "\n";
    pair<bool, int> result_success_row_num;
    int row_num = __getRowNum(id);
	//cout << "[DB Schema] Row number of the given ID : " << row_num << ">\n";
    
    if (row_num == -1)      // invalid
    {
        result_success_row_num.first = false;
        result_success_row_num.second = -1;
    }
    else    // valid
    {
        result_success_row_num.first = true;
        result_success_row_num.second = row_num;
    }

    return result_success_row_num;
}

pair<bool, pair<int, int>> DBSchema :: getRowColNumsCell(string id, string schema_col_name) 
{
    pair<bool, pair<int, int>> result_success_row_col_nums;
    int row_num = __getRowNum(id);
    int col_num = __getColNum(schema_col_name);
    
    if (row_num == -1 || col_num == -1)     // invalid
    {
        result_success_row_col_nums.first = false;
        result_success_row_col_nums.second.first = -1;
        result_success_row_col_nums.second.second = -1;
    }
    else    // valid
    {
        result_success_row_col_nums.first = true;
        result_success_row_col_nums.second.first = row_num;
        result_success_row_col_nums.second.second = col_num;
    }

    return result_success_row_col_nums;
}

void DBSchema :: updateIdRowNum(int row_num, string id, int op_code)
{
        if (op_code == 0)               // addRecord
        {
            __id_row_num[id] = row_num;
            for(auto it : __id_row_num)
            {
            	//cout << "[DB Schema] Key = " << it.first << "Value = " << it.second << '\n';
            }
			//cout << "[DB Schema] Row ID is updated \n";
        }
        else if (op_code == 1)          // deleteRecord
        {
            __id_row_num.erase(id);
        }
}
