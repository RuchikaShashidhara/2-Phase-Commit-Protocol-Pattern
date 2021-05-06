#include "header/File.h"
#include "header/DBSchema.h"

#include <iostream>
#include <algorithm>

using namespace std;

/*
*/
DBSchema :: DBSchema(File* file_values_obj_ptr, vector<string>& schema) 
{
    file_values_ptr = file_values_obj_ptr;
    file_values_ptr -> addRecord(schema);
    db_schema.assign(schema.begin(), schema.end());
}

/*
*/
DBSchema :: ~DBSchema() 
{

}

/*
*/
int DBSchema :: getRowNum(string id)
{
    int row_num;
    auto id_row_num_itr = id_row_num.find(id);
    if (id_row_num_itr != id_row_num.end()) 
    {
        row_num = id_row_num_itr -> second;
    }
    else 
    {
        row_num = -1;
    }
    return row_num;
}

/*
*/
int DBSchema :: getColNum(string schema_col_name) 
{
    int col_num;
    auto schema_itr = find(db_schema.begin(), db_schema.end(), schema_col_name);
    if (schema_itr != db_schema.end()) 
    {
        col_num = schema_itr - db_schema.begin();
    }
    else 
    {
        col_num = -1;
    }

    
    return col_num;
}

/*
*/
void DBSchema :: addRecord(vector<string>& record_values) 
{
    file_values_ptr -> addRecord(record_values);
}

/*
*/
void DBSchema :: updateRecord(string id, vector<string>& record_values) 
{
    int row_num = getRowNum(id);
    int total_col = file_values_ptr -> getTotalColNum();
    for (int ci = 0; ci < total_col; ci++)
    {
        file_values_ptr -> updateCellValue(row_num, ci, record_values[ci]);
    }

}

/*
*/
void DBSchema :: updateRecordCell(string id, string schema_col_name, string value) 
{
    int row_num = getRowNum(id);
    int col_num = getColNum(schema_col_name);
    file_values_ptr -> updateCellValue(row_num, col_num, value);
}

/*
*/
void DBSchema :: deleteRecord(string id) 
{
    int row_num = getRowNum(id);
    file_values_ptr -> removeRecord(row_num);
}

/*
*/
vector<string> DBSchema :: readRecord(string id) 
{
    int row_num = getRowNum(id);
    int total_col = file_values_ptr -> getTotalColNum();
    vector<string> record_values(total_col);
    for (int ci = 0; ci < total_col; ci++) 
    {
        record_values[ci] = file_values_ptr -> readCellValue(row_num, ci);
    }
    return record_values;
}