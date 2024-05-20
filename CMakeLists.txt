cmake_minimum_required(VERSION 3.28)
project(NarutoShippuden)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH  ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/modules/")

set(SDL2_PATH "D:/Duc codes again/SDL2-2.28.5/x86_64-w64-mingw32")
set(SDL2_IMAGE_PATH "D:/Duc codes again/SDL2_image-2.8.2/x86_64-w64-mingw32")
set(SDL2_MIXER_PATH "D:/Duc codes again/SDL2_mixer-2.8.0/x86_64-w64-mingw32")
set(SDL2_TTF_PATH "D:/Duc codes again/SDL2_ttf-2.22.0/x86_64-w64-mingw32")
find_package(SDL2 REQUIRED )
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${SDL2_TTF_INCLUDE_DIRS})
include_directories(${SDL2_MIXER_INCLUDE_DIRS})
add_executable(NarutoShippuden main.cpp All_function.h Base_code.h Base_code.cpp
        MainCharacter.cpp
        MainCharacter.h
        map.h
        map.cpp
        TimeHandle.h
        TimeHandle.cpp
        Shuriken.h
        Shuriken.cpp
        Enemy.cpp
        Enemy.h
        All_function.cpp
        ExplosionObj.h
        ExplosionObj.cpp
        TextObj.h
        TextObj.cpp
        HealthBar.cpp
        HealthBar.h
        Boss.cpp
        Boss.h
        Button.h
        Button.cpp)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES} ${SDL2_TTF_LIBRARIES})
