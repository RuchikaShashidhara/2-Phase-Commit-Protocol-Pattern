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
        virtual ~File();
        virtual int getTotalRowNum();
        virtual int getTotalColNum();
        virtual int addRecord(vector<string> record_values);                
        virtual void deleteRecord(int row);                                 
        virtual vector<string> readRecord(int row);                         
        virtual string readCell(int row, int col);                        
        virtual void updateRecord(int row, vector<string> record_values);   
        virtual void updateCell(int row, int col, string value);            
};

#endif
