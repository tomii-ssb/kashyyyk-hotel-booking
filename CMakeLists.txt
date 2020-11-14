cmake_minimum_required(VERSION 3.17)
project(Reading_Week C)

set(CMAKE_C_STANDARD 99)

add_executable(Reading_Week check_in.c rooms.c common.h main.c check_out.c table_booking.c)