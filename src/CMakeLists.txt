include_directories(${PROJECT_SOURCE_DIR}/include)
add_library(Library SHARED ${PROJECT_SOURCE_DIR}/src/CheckersFiled.cpp ${PROJECT_SOURCE_DIR}/src/Player.cpp ${PROJECT_SOURCE_DIR}/src/Play.cpp)