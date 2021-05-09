#ifndef DBSCHEMA_H
#define DBSCHEMA_H

#include <string>
#include <vector>
#include <map>
#include <utility>

#include "File.h"

using namespace std;

/*
*/
class DBSchema
{
    private:
        map<string, int> __id_row_num;
        vector<string> __db_schema;
        int __getRowNum(string id);
        int __getColNum(string schema_col_name);

    public:
        DBSchema(File* file_values_obj_ptr, vector<string>& schema);
        ~DBSchema();                
        pair<bool, int> getRowNumRecord(string id);
            // used before calling - delete record(1), read record(2), update record(3)
        pair<bool, pair<int, int>> getRowColNumsCell(string id, string schema_col_name);
            // used before calling - read cell(20), update cell(30)
        void updateIdRowNum(int row_num, string id, int op_code);   
            // used after calling - add record(0),delete record(1)           
};

#endif
