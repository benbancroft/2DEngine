#pragma once

#include <stdlib.h>
#include <iostream>

namespace Platform{

    struct FileData {
        const long data_length;
        const unsigned char* data;
        const void* file_handle;
        FileData(const long length, const unsigned char* data, const void* handle) : data_length(length), data(data), file_handle(handle) { }
    };

    FileData get_file_data(std::string path);
    void release_file_data(const FileData* file_data);

}
