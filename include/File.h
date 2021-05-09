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
        vector<vector<string>> __file_values;
        int __file_total_num_of_row;
        int __file_total_num_of_col;           

    public:
        File(int num_of_row, int num_of_col);
        ~File();
        int getTotalRowNum();
        int getTotalColNum();
        int addRecord(vector<string> record_values);                
        void deleteRecord(int row);                                 
        vector<string> readRecord(int row);                         
        string readCell(int row, int col);                        
        void updateRecord(int row, vector<string> record_values);   
        void updateCell(int row, int col, string value);            
};

#endif
