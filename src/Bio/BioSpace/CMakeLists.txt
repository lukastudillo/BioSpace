cmake_minimum_required(VERSION 3.16)
project(BioSpace LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(BioSpaceConsole
    main.cpp
    planta.h
    planta.cpp
    gestor_inventario.h
    gestor_inventario.cpp
)
