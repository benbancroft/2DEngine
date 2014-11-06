#include "platform_file_utils.h"
#include <stdlib.h>

namespace Platform{

    FileData get_asset_data(std::string relative_path);
    void release_asset_data(const FileData* file_data);

}
