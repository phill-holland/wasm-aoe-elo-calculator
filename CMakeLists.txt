cmake_minimum_required(VERSION 3.30)

project(elo-calculator LANGUAGES CXX)

set(THREADS_PREFER_PTHREAD_FLAG ON)

set(LLVM_ENABLE_THREADS TRUE)
set(LLVM_PARALLEL_COMPILE_JOBS, 8)
set(LLVM_PARALLEL_LINK_JOBS, 8)

enable_testing()

find_package(Threads REQUIRED)

include_directories("/usr/include")

add_subdirectory("src")

