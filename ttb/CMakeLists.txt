set(BMC_TTB_COMMON_FILES
    charset.c
    dataarea.c
    datafile.c
    file.c
    log.c
    queue.c
    ttb_compile.c
    ttb_native.c
    unicode.c
   )
find_path(ICONV_INCLUDE_DIR iconv.h)
if(ICONV_INCLUDE_DIR)
  add_definitions(-DHAVE_ICONV_H=1)
endif()
add_definitions(-DHAVE_WCHAR_H)
add_definitions(-DPACKAGE_NAME="brltty")
add_definitions(-DTEXT_TABLE_EXTENSION=".ttb")
add_definitions(-DTEXT_SUBTABLE_EXTENSION=".tti")

find_program(ICU_CONFIG icu-config)

if(NOT ICU_CONFIG)
  set(ICU_FOUND FALSE)
else(NOT WHICH_ICU_CONFIG_RESULT EQUAL 0)
  execute_process(COMMAND ${ICU_CONFIG} --exists
                  RESULT_VARIABLE ICU_EXISTS_RESULT)
  if(NOT ${ICU_EXISTS_RESULT} EQUAL 0)
    set(ICU_FOUND FALSE)
  else(NOT ${ICU_EXISTS_RESULT} EQUAL 0)
    execute_process(COMMAND ${ICU_CONFIG} --cppflags-searchpath
                    COMMAND sed s/^-I//g
                    OUTPUT_VARIABLE ICU_INCLUDE_DIRS)

    execute_process(COMMAND ${ICU_CONFIG} --ldflags-libsonly
                    COMMAND tr -d \n
                    COMMAND sed "s/[\t ]*-l/ /g"
                    COMMAND sed "s/^[\t ]*//"
                    COMMAND sed "s/[\t ]*$//"
                    OUTPUT_VARIABLE ICU_LIBRARY_NAMES)

    separate_arguments(ICU_LIBRARY_NAMES)

    foreach(CURRENT_LIB_NAME ${ICU_LIBRARY_NAMES})
      set(CURRENT_LIBRARY ${CURRENT_LIB_NAME}-NOTFOUND)
      find_library(CURRENT_LIBRARY ${CURRENT_LIB_NAME})
      list(APPEND ICU_LIBRARIES ${CURRENT_LIBRARY})
    endforeach(CURRENT_LIB_NAME ${ICU_LIBRARY_NAMES})

    set(ICU_FOUND TRUE)
  endif(NOT ${ICU_EXISTS_RESULT} EQUAL 0)
endif(NOT ICU_CONFIG)

if(ICU_FOUND)
  if(NOT ICU_FIND_QUIETLY)
    MESSAGE(STATUS "Found ICU")
  endif(NOT ICU_FIND_QUIETLY)
else(ICU_FOUND)
  if(ICU_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "Could not find ICU")
  endif(ICU_FIND_REQUIRED)
endif(ICU_FOUND)

if(ICU_FOUND)
  add_definitions("-DHAVE_ICU=1")
endif(ICU_FOUND)

add_executable(tbl2hex tbl2hex.c ${BMC_TTB_COMMON_FILES})
target_link_libraries(tbl2hex ${ICU_LIBRARIES})
add_custom_command(OUTPUT text.auto.h
                   COMMAND tbl2hex ${CMAKE_CURRENT_SOURCE_DIR}/Tables/de.ttb > text.auto.h
                  )
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include/)
add_library(bmc_ttb SHARED ttb_translate.c text.auto.h ${BMC_TTB_COMMON_FILES})
set_target_properties(bmc_ttb
                      PROPERTIES
                      VERSION 0.0.1
                      SOVERSION 0.0
                     )
target_link_libraries(bmc_ttb ${ICU_LIBRARIES})
install(TARGETS bmc_ttb DESTINATION lib)
install(DIRECTORY Tables DESTINATION share/${CMAKE_PROJECT_NAME})