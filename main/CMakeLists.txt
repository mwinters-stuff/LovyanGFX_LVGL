idf_component_register(
    SRCS
        "main.cpp"
        "demos/widgets/lv_demo_widgets.c"
    PRIV_REQUIRES
        spi_flash
        lvgl__lvgl
        LovyanGFX
    INCLUDE_DIRS
        "."
)

# For managed components, we append our directory to its 'private include directories'.
# This allows the source files inside the 'lvgl__lvgl' component to find your lv_conf.h
idf_component_set_property(lvgl__lvgl "PRIV_INCLUDE_DIRS" "${CMAKE_CURRENT_SOURCE_DIR}")