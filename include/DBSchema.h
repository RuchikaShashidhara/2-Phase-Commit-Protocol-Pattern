#ifndef DBSCHEMA_H
#define DBSCHEMA_H

#include "header/File.h"

#include <string>
#include <vector>
#include <map>

using namespace std;

/*
*/
class DBSchema
{
    private:
        File* file_values_ptr;
        map<string, int> id_row_num;
        vector<string> db_schema;

    public:
        DBSchema(File* file_values_obj_ptr, vector<string>& schema);
        ~DBSchema();
        int getRowNum(string id);
        int getColNum(string schema_col_name);
        void addRecord(vector<string> &record_values);
        // doubt
        void updateRecord(string id, vector<string>& record_values);
        // doubt
        void updateRecordCell(string id, string schema_col_name, string value);
        void deleteRecord(string id);
        vector<string> readRecord(string id);
        
};

#endif