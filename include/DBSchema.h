#ifndef DBSCHEMA_H
#define DBSCHEMA_H

#include <string>
#include <vector>
#include <map>
#include <utility>

#include "File.h"

using namespace std;

class DBSchema
{
    private:
        map<string, int> __id_row_num;
            // Stores ID of record as key & Row Number as value  
        vector<string> __db_schema;
            // Stores Column Names of the DB Table File
        int __getRowNum(string id);
            // Used to retieve Row Number
        int __getColNum(string schema_col_name);
            // Used to retrieve Column Number

    public:
        DBSchema(File* file_values_obj_ptr, vector<string>& schema);
        ~DBSchema();                
        pair<bool, int> getRowNumRecord(string id);
            // Used before calling - read, update, delete record operations
        pair<bool, pair<int, int>> getRowColNumsCell(string id, string schema_col_name);
            // Used before calling - read & update cell operations
        void updateIdRowNum(int row_num, string id, int op_code);   
            // Used after calling - add record(0)           
};

#endif
