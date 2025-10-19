# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)
set(IDF_TARGET "esp32s3")

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
# "Trim" the build. Include the minimal set of components, main, and anything it depends on.
idf_build_set_property(MINIMAL_BUILD ON)
# idf_build_set_property(LV_CONF_INCLUDE_SIMPLE OFF)
# add_compile_definitions(LV_DEMO_CONF_INCLUDE_SIMPLE)

add_compile_definitions(LV_CONF_PATH=${CMAKE_CURRENT_SOURCE_DIR}/main/lv_conf.h)



project(LovyanGFX_LVGL)

