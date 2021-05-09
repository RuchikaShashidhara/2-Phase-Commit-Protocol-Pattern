#ifndef FILEHELPER_H
#define FILEHELPER_H

#include <semaphore.h>
#include <time.h>

#include "Logs.h"
#include "File.h"

class FileHelper
{
    private:
        sem_t __semaphore_lock;
        File *__file_values_ptr;    //doubt - should it be associaton / inheritance ?

    public:
        FileHelper(File *file_values_ptr);
        ~FileHelper();
        bool acquire_lock(long sec, long nsec);
        void release_lock();
        Log_t* read(Log_t *operation);
        Log_t* write(Log_t *operation);
};

#endif
