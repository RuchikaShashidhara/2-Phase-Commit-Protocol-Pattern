#ifndef FILE_H
#define FILE_H

#include <string>
#include <vector>

using namespace std;

/*
*/
class File 
{
    private:
        vector<vector<string>> file_values;
        int file_total_num_of_row;
        int file_total_num_of_col;        
        int semaphore;

    public:
        File(int num_of_row, int num_of_col);
        ~File();
        int getTotalRowNum();
        int getTotalColNum();
        int getSemaphore();
        void setSemaphore(int semaphore_value);
        string readCellValue(int row, int col);
        void updateCellValue(int row, int col, string value);
        void addRecord(vector<string>& record_values);
        void removeRecord(int row);

};

#endif