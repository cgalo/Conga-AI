cmake_minimum_required(VERSION 3.17)
project(Conga_AI)

set(CMAKE_CXX_STANDARD 14)

add_executable(Conga_AI main.cpp Game/Game.cpp Game/Game.h Space/Space.cpp Space/Space.h Board/Board.cpp Board/Board.h AI_Agent/AI_Agent.cpp AI_Agent/AI_Agent.h)