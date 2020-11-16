cmake_minimum_required(VERSION 3.17)
project(Reading_Week C)

set(CMAKE_C_STANDARD 99)

SET(CMAKE_RC_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE}")

if(MINGW)
    set(CMAKE_RC_COMPILER_INIT windres)
    ENABLE_LANGUAGE(RC)
    SET(CMAKE_RC_COMPILE_OBJECT
            "<CMAKE_RC_COMPILER> <FLAGS> -O coff <DEFINES> -i <SOURCE> -o <OBJECT>")
endif(MINGW)


add_executable(Reading_Week check_in.c
        rooms.c
        common.h
        main.c
        check_out.c
        table_booking.c
        utils.c
        types.h
        //${GUI_TYPE}
        ${SOURCE_FILES}
        ${CMAKE_CURRENT_SOURCE_DIR}/rc/icon.rc
)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "Kashyyyk Hotel Booker")