#include <iostream>

#include "../include/File.h"

using namespace std;

/*
*/
File :: File(int num_of_row, int num_of_col)
{
    __file_total_num_of_row = num_of_row;
    __file_total_num_of_col = num_of_col;
    __time_spec = {2, 0};
    sem_init(&__semaphore_lock, 0, 1);
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
    return __file_total_num_of_row;
}

/*
*/
int File :: getTotalColNum()
{
    return __file_total_num_of_col;
}

/*
*/
bool File :: aquire_lock()
{
    int check_aquired = sem_timedwait(&__semaphore_lock, &__time_spec);
    if (check_aquired == 0)  //0 : The calling process successfully performed the semaphore lock operation
    {
        return true;
    }
    else    //-1 : The call was unsuccessful (errno is set). The state of the semaphore is unchanged. 
    {
        return false;
    }
    return true;
}

/*
*/
void File :: release_lock()
{
    sem_post(&__semaphore_lock);
}

/*
*/
int File :: addRecord(vector<string> record_values)
{
    int row_num = -1;
    if (aquire_lock())
    {
        __file_values.push_back(record_values);
        row_num = __file_values.size() - 1;
    }
    release_lock();
    return row_num;
}

/*
*/
void File :: deleteRecord(int row) 
{ 
    if (aquire_lock())
    {
        if (row < __file_total_num_of_row)
        {   
            __file_values.erase(__file_values.begin() + row);  
        }    
    }
    release_lock();
}

/*
*/
vector<string> File :: readRecord(int row)
{ 
    vector<string> record_values;
    if (aquire_lock())
    {
        for(int ci = 0; ci < __file_total_num_of_col; ci++)
        {
            record_values.push_back(__file_values[row][ci]);
        }
    }
    release_lock();
    return record_values;
}

/*
*/
string File :: readCell(int row, int col) 
{
    string cell_value;  
    if (aquire_lock())
    {  
        if (row < __file_total_num_of_row && col < __file_total_num_of_col)
        {
            cell_value = __file_values[row][col];
        }
        else 
        {
            cell_value = "";
        }    
    }
    release_lock();
    return cell_value;
}

/*
*/
void File :: updateRecord(int row, vector<string> record_values)
{
    if (aquire_lock())
    {
        __file_values[row] = record_values;
    }
    release_lock();
}

/*
*/
void File :: updateCell(int row, int col, string value) 
{
    if (aquire_lock())
    {
        if (row < __file_total_num_of_row && col < __file_total_num_of_col)
        {
            __file_values[row][col] = value;
        }    
    }
    release_lock();
}