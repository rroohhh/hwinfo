FILE (GLOB_RECURSE project_SRCS *.cpp *.cxx *.cc *.C *.c *.h *.hpp)
SET (project_LIBS )
SET (project_BIN ${PROJECT_NAME})

ADD_EXECUTABLE(${project_BIN} ${project_SRCS})
TARGET_LINK_LIBRARIES(${project_BIN} ${project_LIBS})

SET_TARGET_PROPERTIES(${project_BIN} PROPERTIES VERSION "${APPLICATION_VERSION_MAJOR}.${APPLICATION_VERSION_MINOR}" OUTPUT_NAME ${project_BIN} CLEAN_DIRECT_OUTPUT 1)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic")

TARGET_COMPILE_FEATURES(${PROJECT_NAME} PRIVATE cxx_constexpr)
TARGET_COMPILE_FEATURES(${PROJECT_NAME} PRIVATE cxx_decltype_auto)

INSTALL(TARGETS ${project_BIN} DESTINATION bin)
INSTALL(FILES "_hwinfo" DESTINATION "share/zsh/site-functions")
