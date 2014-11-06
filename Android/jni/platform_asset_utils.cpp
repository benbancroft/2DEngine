#include "platform/platform_asset_utils.h"
#include "macros.h"
#include "platform/platform_log.h"
#include <android/asset_manager_jni.h>
#include <assert.h>

static AAssetManager* asset_manager;

extern "C" {
    JNIEXPORT void JNICALL Java_uk_co_benbancroft_AndroidEngine_platform_PlatformFileUtils_init_1asset_1manager(JNIEnv * env, jclass jclazz, jobject java_asset_manager) {
        UNUSED(jclazz);
        asset_manager = AAssetManager_fromJava(env, java_asset_manager);
    }
}

namespace Platform{

    FileData get_asset_data(std::string relative_path) {
        assert(!relative_path.empty());
        AAsset* asset = AAssetManager_open(asset_manager, relative_path.c_str(), AASSET_MODE_STREAMING);
        DEBUG_LOG_WRITE_V("TAG", relative_path.c_str());
        assert(asset != NULL);

        return FileData(AAsset_getLength(asset), reinterpret_cast<const unsigned char*>(AAsset_getBuffer(asset)), asset);
    }

    void release_asset_data(const FileData* file_data) {
        assert(file_data != NULL);
        assert(file_data->file_handle != NULL);
        AAsset_close((AAsset*)file_data->file_handle);
    }

}
