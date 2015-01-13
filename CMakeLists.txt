INCLUDE(FindPkgConfig)
cmake_minimum_required (VERSION 2.6)


project (font-converter)
set(FONTCONVERTER_VERSION "1.0")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

pkg_check_modules(FONTFORGE REQUIRED libfontforge>=2.0.0)
include_directories(${FONTFORGE_INCLUDE_DIRS})
link_directories(${FONTFORGE_LIBRARY_DIRS})

#Fontforge bridge library
set(FONT_CONVERTER_SRC ${FONT_CONVERTER_SRC}
  src/ff-bridge.c
  src/utility/c-helper.c
)
set(FFBRIDGE_LIB ffbridge)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
set(FFBRIDGE_LIBS ${FFBRIDGE_LIBS} ${FONTFORGE_LIBRARIES})

add_library(${FFBRIDGE_LIB} SHARED ${FONT_CONVERTER_SRC})
target_link_libraries(${FFBRIDGE_LIB} ${FFBRIDGE_LIBS})

#Main Executable font-converter
set(FONT_CONVERTER_SRC ${FONT_CONVERTER_SRC}
  src/font-converter.cpp
)
set(OUTPUT_BIN font-converter)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
set(FONT_CONVERTER_LIBS ${FONT_CONVERTER_LIBS} ${FONTFORGE_LIBRARIES})

add_executable(${OUTPUT_BIN} ${FONT_CONVERTER_SRC})
target_link_libraries(${OUTPUT_BIN} ${FONT_CONVERTER_LIBS})


# cxxtest
find_package(CxxTest)

# fontforge starts using pkg-config 'correctly' since 2.0.0

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
      #      ${CMAKE_CURRENT_SOURCE_DIR}/test/src/eot-test.h
    ) 
  
  foreach(_CURTEST ${TEST_SRCS})
    GET_FILENAME_COMPONENT(_NAME_WE ${_CURTEST} NAME_WE)
    set(CUR_CPP_FILE  ${CMAKE_CURRENT_SOURCE_DIR}/test/src/${_NAME_WE}.cpp)
    add_custom_command(
      OUTPUT  ${CUR_CPP_FILE}
      DEPENDS ${_CURTEST}
      COMMAND ${CXXTEST_TESTGEN_INTERPRETER}
      ${CXXTEST_TESTGEN_EXECUTABLE} ${CXXTEST_TESTGEN_ARGS} --part -o ${CUR_CPP_FILE} ${_CURTEST}
      ) 
    set(TEST_CPP_SRCS ${TEST_CPP_SRCS} ${CUR_CPP_FILE})
  endforeach(_CURTEST)
  
    set (_CURTEST ${CMAKE_CURRENT_SOURCE_DIR}/test/src/eot-test.h)

    # Need to write a test with main function (without --part option)
    GET_FILENAME_COMPONENT(_NAME_WE ${_CURTEST} NAME_WE)
    set(CUR_CPP_FILE  ${CMAKE_CURRENT_SOURCE_DIR}/test/src/${_NAME_WE}.cpp)
    add_custom_command(
      OUTPUT  ${CUR_CPP_FILE}
      DEPENDS ${_CURTEST}
      COMMAND ${CXXTEST_TESTGEN_INTERPRETER}
      ${CXXTEST_TESTGEN_EXECUTABLE} ${CXXTEST_TESTGEN_ARGS} -o ${CUR_CPP_FILE} ${_CURTEST}
      ) 
    set(TEST_CPP_SRCS ${TEST_CPP_SRCS} ${CUR_CPP_FILE})

    #add_executable(${OUTPUT_BIN}-test src/ff-bridge.c ${TEST_CPP_SRCS})
  add_executable(${OUTPUT_BIN}-test ${TEST_CPP_SRCS})
  target_link_libraries(${OUTPUT_BIN}-test ${FFBRIDGE_LIB} )
endif()

