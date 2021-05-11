#include <iostream>
#include <algorithm>

using namespace std;

#include "../include/File.h"
#include "../include/DBSchema.h"

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

    /*Searches for row number given id of record */
    map<string, int>::iterator id_row_num_itr = __id_row_num.find(id);

    /* Returns row number if found, else returns -1 */
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

    /*Searches for col number given id of record */
    vector<string>::iterator schema_itr = find(__db_schema.begin(), __db_schema.end(), schema_col_name);
    
    /* Returns col number if found, else returns -1 */
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
    /* Retrieves corresponding row number*/
    pair<bool, int> result_success_row_num;
    int row_num = __getRowNum(id);
    
    /* Sets invalid row number if retrival was invalid*/
    if (row_num == -1)      // invalid
    {
        result_success_row_num.first = false;
        result_success_row_num.second = -1;
    }
     /* Sets valid row number if retrival was valid*/
    else   
    {
        result_success_row_num.first = true;
        result_success_row_num.second = row_num;
    }

    return result_success_row_num;
}

pair<bool, pair<int, int>> DBSchema :: getRowColNumsCell(string id, string schema_col_name) 
{
    /* Retrieves corresponding row & col numbers*/
    pair<bool, pair<int, int>> result_success_row_col_nums;
    int row_num = __getRowNum(id);
    int col_num = __getColNum(schema_col_name);
    
    /* Sets invalid row & column numbers if retrival was invalid*/
    if (row_num == -1 || col_num == -1)     
    {
        result_success_row_col_nums.first = false;
        result_success_row_col_nums.second.first = -1;
        result_success_row_col_nums.second.second = -1;
    }
    /* Sets valid row & column numbers if retrival was valid*/
    else    
    {
        result_success_row_col_nums.first = true;
        result_success_row_col_nums.second.first = row_num;
        result_success_row_col_nums.second.second = col_num;
    }

    return result_success_row_col_nums;
}

void DBSchema :: updateIdRowNum(int row_num, string id, int op_code)
{
        /* Inserting key-value pair for DB table record id & row number for add new record operation */
        if (op_code == 0)               
        {
            __id_row_num[id] = row_num;
        }
        /* Deleting key-value pair for DB table record id & row number for delete record operation */
        else if (op_code == 1)         
        {
            __id_row_num.erase(id);
        }
}