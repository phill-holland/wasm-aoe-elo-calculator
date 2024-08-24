set(BINARY ${CMAKE_PROJECT_NAME})

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 20)

set(LLVM_ENABLE_THREADS TRUE)
set(LLVM_PARALLEL_COMPILE_JOBS, 8)
set(LLVM_PARALLEL_LINK_JOBS, 8)

add_library(calculator)
target_sources(
    calculator PUBLIC
    FILE_SET cxx_modules TYPE CXX_MODULES FILES
    modules/point.cxx
    modules/calculator.cxx    
    modules/player.cxx
    modules/team.cxx
    modules/teams.cxx
)

add_executable(${BINARY} modules/main.cxx)

#add_library(${BINARY}_lib STATIC ${SOURCES})

target_link_libraries(${PROJECT_NAME} "${CMAKE_THREAD_LIBS_INIT}")

target_link_libraries(${PROJECT_NAME} calculator)
