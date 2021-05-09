#include <iostream>
#include <vector>

using namespace std;

#include "../include/DBFile.h"


DBFile :: DBFile(int num_of_row, int num_of_col) : File(num_of_col, num_of_row)
{    
    sem_init(&__semaphore_lock, 0, 1);    
}

DBFile :: ~DBFile()
{
    
}

bool DBFile :: acquire_lock(long sec, long nsec)
{
	#if 0
    struct timespec ts;
    if (clock_gettime(CLOCK_REALTIME, &ts) == -1)   // if error is thrown, no lock is acquired & semaphore is unchanged.
    {
    	cout << "[DBFile] locking deadlock\n";
        return false;
    } 
    ts.tv_sec += sec;
    ts.tv_nsec += nsec;

    int check_aquired = sem_timedwait(&__semaphore_lock, &ts);
    #endif
    int check_aquired = sem_trywait(&__semaphore_lock);
    if (check_aquired == 0)  //0 : The calling process successfully performed the semaphore lock operation
    {
        return true;
    }
    else    //-1 : The call was unsuccessful (errno is set). The state of the semaphore is unchanged. 
    {
    	cout << "[DBFile] couldn't acquire lock\n";
        return false;
    }
}

void DBFile :: release_lock()
{
    cout << "[DBFile] releasing lock\n";
    sem_post(&__semaphore_lock);
}

Log_t* DBFile :: read(Log_t *operation)
{
    Log_t *log_read_value = new Log_t;
    log_read_value->record_op = operation->record_op;
    log_read_value->read_op = operation->read_op;
    log_read_value->row = operation->row;
    log_read_value->col = operation->col;

    if (operation->read_op == 1) //read operation
    { 
        log_read_value->value = readRecord(operation->row);
    }

    return log_read_value;
}

Log_t* DBFile :: write(Log_t *operation)
{
    Log_t *log_write_prev_value = new Log_t;
    log_write_prev_value->record_op = operation->record_op;
    log_write_prev_value->read_op = operation->read_op;    

    if (operation->read_op == 0)    //update operation
    {
        log_write_prev_value->row = operation->row;
        log_write_prev_value->col = operation->col;
        log_write_prev_value->value = readRecord(operation->row);

        if (operation->record_op == 1)  //update record operation
        {
            updateRecord(operation->row, operation->value);
        }
        else    //update cell operation
        {
            updateCell(operation->row, operation->col, operation->value[operation->col]);
        }
    }
    else if (operation->read_op == 2)   //add record operation
    {
        log_write_prev_value->row = addRecord(operation->value);
        operation->row = log_write_prev_value->row;
        cout << "\t[DBFile] Updated row value: " << operation->row << '\n';
    }

    return log_write_prev_value;
}
