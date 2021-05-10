#include <iostream>
#include <vector>

using namespace std;

#include "../include/DBFile.h"

DBFile :: DBFile(int num_of_row, int num_of_col) : File(num_of_col, num_of_row)
{    
    /* Initialize semaphore to be locked, shared between threads & 1 as default value */
    sem_init(&__semaphore_lock, 1, 1);  
}

DBFile :: ~DBFile()
{
    
}

bool DBFile :: acquire_lock(long sec, long nsec)
{
    struct timespec ts;

    /* if error is thrown, no lock is acquired & semaphore is unchanged */
    if (clock_gettime(CLOCK_REALTIME, &ts) == -1)   
    {
        return false;
    } 

    /* Add the time upto which the semaphore should be locked to timespec*/
    ts.tv_sec += sec;
    ts.tv_nsec += nsec;

    int check_aquired = sem_timedwait(&__semaphore_lock, &ts);

    /*0 : The calling process (acquiring lock) successfully performed the semaphore lock operation*/
    if (check_aquired == 0)  
    {
        return true;
    }
    /*-1 : The call (acquiring lock) was unsuccessful (errno is set). The state of the semaphore is unchanged. */
    else   
    {
        return false;
    }
}

void DBFile :: release_lock()
{
    sem_post(&__semaphore_lock);
}

Log_t* DBFile :: read(Log_t *operation)
{
    /* Updating log values to the log that returns the read operation details*/
    Log_t *log_read_value = new Log_t;
    log_read_value->record_op = operation->record_op;
    log_read_value->read_op = operation->read_op;
    log_read_value->row = operation->row;
    log_read_value->col = operation->col;

    /* read operation */
    if (operation->read_op == 1) 
    { 
        log_read_value->value = readRecord(operation->row);
    }

    return log_read_value;
}

Log_t* DBFile :: write(Log_t *operation)
{
    /* Updating log values to the log that returns the write operation details*/
    Log_t *log_write_prev_value = new Log_t;
    log_write_prev_value->record_op = operation->record_op;
    log_write_prev_value->read_op = operation->read_op;    

    /* update operation */
    if (operation->read_op == 0)    
    {
    	return NULL;

        log_write_prev_value->row = operation->row;
        log_write_prev_value->col = operation->col;
        log_write_prev_value->value = readRecord(operation->row);

        /* update record operation */
        if (operation->record_op == 1)  
        {
            updateRecord(operation->row, operation->value);
        }
        /* update cell operation */
        else   
        {
            updateCell(operation->row, operation->col, operation->value[operation->col]);
        }
    }

    /* add record operation */
    else if (operation->read_op == 2)   
    {
        log_write_prev_value->row = addRecord(operation->value);
        log_write_prev_value->read_op = 3;
        operation->row = log_write_prev_value->row;
        
    }

    /* delete record operation */
    else if (operation->read_op == 3)
    {
		cout << "[DBFile] Deleting record\n";
    	deleteRecord(operation->row);
    	return NULL;
    }

    return log_write_prev_value;
}
