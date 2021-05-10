#include <iostream>

#include "../include/File.h"

using namespace std;

File :: File(int num_of_row, int num_of_col)
{
    __file_total_num_of_row = num_of_row;
    __file_total_num_of_col = num_of_col;
}

int File :: getTotalRowNum()
{
    return __file_total_num_of_row;
}

int File :: getTotalColNum()
{
    return __file_total_num_of_col;
}

int File :: addRecord(vector<string> record_values)
{
    int row_num = -1;
    __file_values.push_back(record_values);
    row_num = __file_values.size() - 1;
    //cout << "[File] Returning row number: " << row_num << '\n';
    return row_num;
}

void File :: deleteRecord(int row) 
{ 
    if (row < __file_total_num_of_row)
    {   
        __file_values.erase(__file_values.begin() + row);  
    }    
}

vector<string> File :: readRecord(int row)
{ 
	//cout << "[File] Entered readRecord\n";
    vector<string> record_values;
    if (row < __file_total_num_of_row)
    {
		//cout << "[File] Passed if condition\n";
		return __file_values[row];
    }        
    return record_values;
}

string File :: readCell(int row, int col) 
{
    string cell_value;   
    if (row < __file_total_num_of_row && col < __file_total_num_of_col)
    {
        cell_value = __file_values[row][col];
    }
    else 
    {
        cell_value = "";
    }    
    return cell_value;
}

void File :: updateRecord(int row, vector<string> record_values)
{
    if (row < __file_total_num_of_row)
    {
        __file_values[row] = record_values;
    }    
}

void File :: updateCell(int row, int col, string value) 
{
    if (row < __file_total_num_of_row && col < __file_total_num_of_col)
    {
        __file_values[row][col] = value;
    }    
}
