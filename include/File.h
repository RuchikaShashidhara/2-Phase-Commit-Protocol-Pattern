#ifndef FILE_H
#define FILE_H

#include <string>
#include <vector>
#include <semaphore.h>
#include <time.h>

using namespace std;

/*
*/
class File 
{
    private:
        vector<vector<string>> __file_values;
        int __file_total_num_of_row;
        int __file_total_num_of_col;        
        sem_t __semaphore_lock;
        struct timespec __time_spec;

    public:
        File(int num_of_row, int num_of_col);
        ~File();
        int getTotalRowNum();
        int getTotalColNum();
        bool acquire_lock();
        void release_lock();
        int addRecord(vector<string> record_values);                //op_code = 0
        void deleteRecord(int row);                                 //op_code = 1
        vector<string> readRecord(int row);                         //op_code = 2
        string readCell(int row, int col);                          //op_code = 20
        void updateRecord(int row, vector<string> record_values);   //op_code = 3
        void updateCell(int row, int col, string value);            //op_code = 30 
};

#endif
