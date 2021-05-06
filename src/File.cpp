#include "header/File.h"

#include <iostream>

using namespace std;

/*
*/
File :: File(int num_of_row, int num_of_col)
{
    vector<string> empty_row_record_container(num_of_col);
    for (int ri = 0; ri < num_of_row; ri++)
    {
        file_values.push_back(empty_row_record_container);
    }
}

/*
*/
File :: ~File()
{

}

/*
*/
int File :: getTotalRowNum()
{
    return file_total_num_of_row;
}

/*
*/
int File :: getTotalColNum()
{
    return file_total_num_of_col;
}

/*
*/
int File :: getSemaphore()
{
    return semaphore;
}

/*
*/
void File :: setSemaphore(int semaphore_value)
{
    semaphore = semaphore_value;
}
/*
*/
string File :: readCellValue(int row, int col) 
{
    string cell_value;
    if (row < file_total_num_of_row && col < file_total_num_of_col)
    {
        cell_value = file_values[row][col];
    }
    else 
    {
        cell_value = "";
    }
    
    return cell_value;
}

/*
*/
void File :: updateCellValue(int row, int col, string value) 
{
    if (row < file_total_num_of_row && col < file_total_num_of_col)
    {
        file_values[row][col] = value;
    }
}

/*
*/
void File :: addRecord(vector<string>& record_values)
{
    for(int ci = 0; ci < file_total_num_of_col; ci++) 
    {
        file_values.push_back(record_values);
    }
}

/*
*/
void File :: removeRecord(int row) 
{
    if (row < file_total_num_of_row)
    {
        file_values.erase(file_values.begin() + row);
    }
}