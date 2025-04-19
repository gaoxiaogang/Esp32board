

set(SOURCES "")
set(INCLUDE_DIRS "." "fonts" "display" "audio_codecs" "audio_processing" "protocols")

# 添加 main目录下cpp文件
file(GLOB MAIN_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
list(APPEND SOURCES ${MAIN_SOURCES})


# 添加板级公共文件
file(GLOB BOARD_COMMON_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/boards/common/*.cpp)
list(APPEND SOURCES ${BOARD_COMMON_SOURCES})
list(APPEND INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/boards/common)

# 根据 BOARD_TYPE 配置添加对应的板级文件
if(CONFIG_BOARD_TYPE_BREAD_COMPACT_WIFI)
    set(BOARD_TYPE "bread-compact-wifi")
elseif(CONFIG_BOARD_TYPE_BREAD_COMPACT_ESP32)
    set(BOARD_TYPE "bread-compact-esp32")
endif()
file(GLOB BOARD_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/boards/${BOARD_TYPE}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/boards/${BOARD_TYPE}/*.c
)
list(APPEND SOURCES ${BOARD_SOURCES})

# 添加 display目录下cpp文件
file(GLOB DISPLAY_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/display/*.cpp)
list(APPEND SOURCES ${DISPLAY_SOURCES})

# 添加 protocols目录下cpp文件
file(GLOB PROTOCOLS_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/protocols/*.cpp)
list(APPEND SOURCES ${PROTOCOLS_SOURCES})

# 添加 audio_codecs目录下cpp文件
file(GLOB AUDIO_CODECS_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/audio_codecs/*.cpp)
list(APPEND SOURCES ${AUDIO_CODECS_SOURCES})

if(CONFIG_USE_AUDIO_PROCESSOR)
    list(APPEND SOURCES "audio_processing/audio_processor.cc")
endif()
if(CONFIG_USE_WAKE_WORD_DETECT)
    list(APPEND SOURCES "audio_processing/wake_word_detect.cc")
endif()

# 添加 fonts目录下c文件
file(GLOB FONTS_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/fonts/*.c)
list(APPEND SOURCES ${FONTS_SOURCES})

# 根据Kconfig选择语言目录
if(CONFIG_LANGUAGE_ZH_CN)
    set(LANG_DIR "zh-CN")
elseif(CONFIG_LANGUAGE_EN_US)
    set(LANG_DIR "en-US")
endif()
# 定义生成路径
set(LANG_JSON "${CMAKE_CURRENT_SOURCE_DIR}/assets/${LANG_DIR}/language.json")
set(LANG_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/assets/lang_config.h")
file(GLOB LANG_SOUNDS ${CMAKE_CURRENT_SOURCE_DIR}/assets/${LANG_DIR}/*.p3)
file(GLOB COMMON_SOUNDS ${CMAKE_CURRENT_SOURCE_DIR}/assets/common/*.p3)

idf_component_register(SRCS ${SOURCES}
        EMBED_FILES ${LANG_SOUNDS} ${COMMON_SOUNDS}
        INCLUDE_DIRS ${INCLUDE_DIRS}
        WHOLE_ARCHIVE         # 强制链接整个库（适用于模板类等场景）
        )

# 使用 target_compile_definitions 来定义 BOARD_TYPE, BOARD_NAME
# 如果 BOARD_NAME 为空，则使用 BOARD_TYPE
if(NOT BOARD_NAME)
    set(BOARD_NAME ${BOARD_TYPE})
endif()
# 1、可以在代码中使用 BOARD_TYPE、BOARD_NAME
# 2、必须在idf_component_register后使用
target_compile_definitions(${COMPONENT_LIB}
                    PRIVATE BOARD_TYPE=\"${BOARD_TYPE}\" BOARD_NAME=\"${BOARD_NAME}\"
                    )

# 添加生成规则
add_custom_command(
    OUTPUT ${LANG_HEADER}
    COMMAND python ${PROJECT_DIR}/scripts/gen_lang.py
            --input "${LANG_JSON}"
            --output "${LANG_HEADER}"
    DEPENDS
        ${LANG_JSON}
        ${PROJECT_DIR}/scripts/gen_lang.py
    COMMENT "Generating ${LANG_DIR} language config"
)

# 强制建立生成依赖
add_custom_target(lang_header ALL
DEPENDS ${LANG_HEADER}
)