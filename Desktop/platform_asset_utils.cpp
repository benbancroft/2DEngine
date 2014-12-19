#include "platform/platform_asset_utils.h"
#include "platform/platform_file_utils.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

namespace Platform{

    FileData get_asset_data(std::string relative_path) {
        assert(!relative_path.empty());
        return get_file_data(relative_path);
    }

    void release_asset_data(const FileData* file_data) {
        assert(file_data != NULL);
        release_file_data(file_data);
    }

}
