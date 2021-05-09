#include <iostream>

#include "../include/FileHelper.h"

using namespace std;

/*
*/
FileHelper :: FileHelper(File *file_values_ptr)
{    
    __file_values_ptr = file_values_ptr;
    sem_init(&__semaphore_lock, 0, 1);
}

/*
*/
FileHelper :: ~FileHelper()
{
    __file_values_ptr = NULL;
}

/*
*/
bool FileHelper :: acquire_lock(long sec, long nsec)
{
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts); //doubt: errors can occur, should it be handled?
    ts.tv_sec += sec;
    ts.tv_nsec += nsec;

    int check_aquired = sem_timedwait(&__semaphore_lock, &ts);
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
void FileHelper :: release_lock()
{
    sem_post(&__semaphore_lock);
}

/*
*/
Log_t* FileHelper :: read(Log_t *operation)
{
    Log_t *log_read_value;
    log_read_value->record_op = operation->record_op;
    log_read_value->read_op = operation->read_op;
    log_read_value->row = operation->row;
    log_read_value->col = operation->col;

    if (operation->read_op == 1) //read operation
    { 
        log_read_value->value = __file_values_ptr->readRecord(operation->row);
    }

    return log_read_value;
}

/*
*/
Log_t* FileHelper:: write(Log_t *operation)
{
    Log_t *log_write_prev_value;
    log_write_prev_value->record_op = operation->record_op;
    log_write_prev_value->read_op = operation->read_op;    

    if (operation->read_op == 0)    //update operation
    {
        log_write_prev_value->row = operation->row;
        log_write_prev_value->col = operation->col;
        log_write_prev_value->value = __file_values_ptr->readRecord(operation->row);

        if (operation->record_op == 1)  //update record operation
        {
            __file_values_ptr->updateRecord(operation->row, operation->value);
        }
        else    //update cell operation
        {
            __file_values_ptr->updateCell(operation->row, operation->col, operation->value[operation->col]);
        }
    }
    else if (operation->read_op == 2)   //add record operation
    {
        log_write_prev_value->row = __file_values_ptr->addRecord(operation->value);
    }

    return log_write_prev_value;
}