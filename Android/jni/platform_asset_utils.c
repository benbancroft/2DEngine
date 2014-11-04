#include "platform/platform_asset_utils.h"
#include "macros.h"
#include "platform/platform_log.h"
#include <android/asset_manager_jni.h>
#include <assert.h>

static AAssetManager* asset_manager;


JNIEXPORT void JNICALL Java_uk_co_benbancroft_AndroidEngine_platform_PlatformFileUtils_init_1asset_1manager(JNIEnv * env, jclass jclazz, jobject java_asset_manager) {
	UNUSED(jclazz);
	asset_manager = AAssetManager_fromJava(env, java_asset_manager);
}

FileData get_asset_data(const char* relative_path) {
    assert(relative_path != NULL);
    AAsset* asset = AAssetManager_open(asset_manager, relative_path, AASSET_MODE_STREAMING);
    DEBUG_LOG_WRITE_V("TAG", relative_path);
    assert(asset != NULL);

    return (FileData) { AAsset_getLength(asset), AAsset_getBuffer(asset), asset };
}

void release_asset_data(const FileData* file_data) {
    assert(file_data != NULL);
    assert(file_data->file_handle != NULL);
    AAsset_close((AAsset*)file_data->file_handle);
}