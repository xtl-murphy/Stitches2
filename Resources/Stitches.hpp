/**
 * Stitches
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/5/30 15:47
 **/

#pragma once


#include <map>
#include <set>
#include <vector>
#include <array>
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <iomanip>
#include <cstdint>
#include <string>
#include <thread>
#include <memory>
#include <cstring>
#include <stdexcept>
#include <typeinfo>
#include <typeindex>
#include <optional>
#include <utility>
#include <type_traits>
#include <mutex>
#include <future>
#include <queue>
#include <filesystem>


#include "Utils/Ref.hpp"

#define LOG_TURN_ON

#ifdef _WIN32
    #ifdef LOG_TURN_ON
        #define LOGE(TAG, ...)  printf("%s : ", TAG) && \
                                printf("<%s %s> %s %s:%d INFO: ",__DATE__, __TIME__,__FUNCTION__,__FILE__,__LINE__) && \
                                printf(__VA_ARGS__) && \
                                printf("\n")
        #define LOGI(TAG, ...)  printf("%s : ", TAG) && \
                                printf("<%s %s> %s %s:%d INFO: ",__DATE__, __TIME__,__FUNCTION__,__FILE__,__LINE__) && \
                                printf(__VA_ARGS__) && \
                                printf("\n")
        #define LOGV(TAG, ...)  printf("%s : ", TAG) && \
                                printf("<%s %s> %s %s:%d INFO: ",__DATE__, __TIME__,__FUNCTION__,__FILE__,__LINE__) && \
                                printf(__VA_ARGS__) && \
                                printf("\n")
    #else
        #define LOGE(TAG, ...)
        #define LOGE(TAG, ...)
        #define LOGV(TAG, ...)
    #endif

#elif __ANDROID__
    #ifdef LOG_TURN_ON
        #include <android/log.h>
        #define LOGI(TAG, ...)  __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)
        #define LOGE(TAG, ...)  __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)
        #define LOGV(TAG, ...)  __android_log_print(ANDROID_LOG_VERBOSE, TAG, __VA_ARGS__)
    #else
        #define LOGE(TAG, ...)
        #define LOGE(TAG, ...)
        #define LOGV(TAG, ...)
    #endif
#else
    #ifdef LOG_TURN_ON
    #define LOGE(TAG, ...)  printf("%s : ", TAG) && \
                                    printf("<%s %s> %s %s:%d INFO: ",__DATE__, __TIME__,__FUNCTION__,__FILE__,__LINE__) && \
                                    printf(__VA_ARGS__) && \
                                    printf("\n")
    #define LOGI(TAG, ...)  printf("%s : ", TAG) && \
                                    printf("<%s %s> %s %s:%d INFO: ",__DATE__, __TIME__,__FUNCTION__,__FILE__,__LINE__) && \
                                    printf(__VA_ARGS__) && \
                                    printf("\n")
    #define LOGV(TAG, ...)  printf("%s : ", TAG) && \
                                    printf("<%s %s> %s %s:%d INFO: ",__DATE__, __TIME__,__FUNCTION__,__FILE__,__LINE__) && \
                                    printf(__VA_ARGS__) && \
                                    printf("\n")
    #else
    #define LOGE(TAG, ...)
            #define LOGE(TAG, ...)
            #define LOGV(TAG, ...)
    #endif
#endif

#define NS_STITCHES_BEGIN namespace Stitches {
#define NS_STITCHES_END };
#define USING_STITCHES_VK using namespace Stitches;

#define MAX_COLOR_ATTCHMENT 1

typedef std::string String;

typedef uint32_t uint32;
typedef int32_t  int32;
