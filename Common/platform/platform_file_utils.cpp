#include "platform_file_utils.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "platform_log.h"

namespace Platform{

    FileData get_file_data(std::string path) {
        assert(!path.empty());
        
        //DEBUG_LOG_WRITE_V("Shaders", path.c_str());
            
        FILE* stream = fopen(path.c_str(), "r");
        assert (stream != NULL);

        fseek(stream, 0, SEEK_END);	
        long stream_size = ftell(stream);
        fseek(stream, 0, SEEK_SET);

        unsigned char* buffer = new unsigned char[stream_size];
        fread(buffer, stream_size, 1, stream);

        assert(ferror(stream) == 0);
        fclose(stream);

        return FileData(stream_size, buffer, NULL);
    }

    void release_file_data(const FileData* file_data) {
        assert(file_data != NULL);	
        assert(file_data->data != NULL);

        free((void*)file_data->data);
    }

}
