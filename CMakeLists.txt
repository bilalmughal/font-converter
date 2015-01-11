INCLUDE(FindPkgConfig)
cmake_minimum_required (VERSION 2.6)

project (font-converter)

set(OUTPUT_BIN bin/font-converter)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(FONT_CONVERTER_SRC ${FONT_CONVERTER_SRC}
  src/ff-bridge.c
  src/font-converter.cpp
)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
set(FONT_CONVERTER_LIBS ${FONT_CONVERTER_LIBS} ${FONTFORGE_LIBRARIES})

add_executable(${OUTPUT_BIN} ${FONT_CONVERTER_SRC})
target_link_libraries(${OUTPUT_BIN} ${FONT_CONVERTER_LIBS})

# cxxtest
find_package(CxxTest)

# fontforge starts using pkg-config 'correctly' since 2.0.0
pkg_check_modules(FONTFORGE REQUIRED libfontforge>=2.0.0)
include_directories(${FONTFORGE_INCLUDE_DIRS})
link_directories(${FONTFORGE_LIBRARY_DIRS})

#if(CXXTEST_FOUND)
#	include_directories(${CXXTEST_INCLUDE_DIR})
#	enable_testing()
#
#  CXXTEST_ADD_TEST(font-converter-test test/src/ff-test.cpp 
#    ${CMAKE_CURRENT_SOURCE_DIR}/test/src/ff-test.h
#    )
#  #target_link_libraries(font-config-test ff-bridge.c.o)
#endif()

if(CXXTEST_FOUND)
	include_directories(${CXXTEST_INCLUDE_DIR})
  enable_testing()
  set(TEST_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/test/src/ff-test.h 
    #${CMAKE_CURRENT_SOURCE_DIR}/test/src/ff-test1.h
    ) 
  
  foreach(_CURTEST ${TEST_SRCS})
    GET_FILENAME_COMPONENT(_NAME_WE ${_CURTEST} NAME_WE)
    set(CUR_CPP_FILE  ${CMAKE_CURRENT_SOURCE_DIR}/test/src/${_NAME_WE}.cpp)
    add_custom_command(
      OUTPUT  ${CUR_CPP_FILE}
      DEPENDS ${_CURTEST}
      COMMAND ${CXXTEST_TESTGEN_INTERPRETER}
      ${CXXTEST_TESTGEN_EXECUTABLE} ${CXXTEST_TESTGEN_ARGS} -o ${CUR_CPP_FILE} ${_CURTEST}
      ) 
    set(TEST_CPP_SRCS ${TEST_CPP_SRCS} ${CUR_CPP_FILE})
  endforeach(_CURTEST)

  add_executable(${OUTPUT_BIN}-test src/ff-bridge.c ${TEST_CPP_SRCS})
endif()

