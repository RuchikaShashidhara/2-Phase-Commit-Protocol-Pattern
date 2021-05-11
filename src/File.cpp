#include <iostream>

using namespace std;

#include "../include/File.h"

File :: File(int num_of_row, int num_of_col)
{
    /* Initialize the file data for size - num_of_row, num_of_col */
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
    vector<string> record_values;

    /* If valid row number is passed, return the row's corresponding record */
    if (row < __file_total_num_of_row)
    {
		return __file_values[row];
    }        

    /* returning empty record, if row number is invalid */
    return record_values;
}

string File :: readCell(int row, int col) 
{
    string cell_value;  

    /* If valid row & col numbers are passed, return the file data's cell value */
    if (row < __file_total_num_of_row && col < __file_total_num_of_col)
    {
        cell_value = __file_values[row][col];
    }
    
    /* Returns Null String if either row or col is invald */
    else 
    {
        cell_value = "";
    }    

    return cell_value;
}

void File :: updateRecord(int row, vector<string> record_values)
{
    /* Updates the corresponding record with record_values, only if row number is valid */
    if (row < __file_total_num_of_row)
    {
        __file_values[row] = record_values;
    }    
}

void File :: updateCell(int row, int col, string value) 
{
    /* Updates the corresponding cell with value, only if both row & col number is valid */
    if (row < __file_total_num_of_row && col < __file_total_num_of_col)
    {
        __file_values[row][col] = value;
    }    
}