cmake_minimum_required(VERSION 2.8.3)
project(bayesian_webclass)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED)

## System dependencies are found with CMake's conventions
find_package(Boost REQUIRED COMPONENTS filesystem system)
find_package(CURL REQUIRED)
find_package(LibXML++ REQUIRED)
find_package(Threads REQUIRED)
include_directories(${LibXML++_INCLUDE_DIRS} ${CURL_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
set(LIBS ${LIBS} ${LibXML++_LIBRARIES} ${CURL_LIBRARIES} ${Boost_LIBRARIES} ${Threads_LIBRARIES} /usr/lib/libtidy.so)
set(faif_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/)

## find_package(Tidy REQUIRED)
##include_directories(/usr/lib/ /usr/lib/x86_64/)

##if(Tidy)
##    message("Found tidy.")
##else()
##    message("Again...")
##endif()

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=c++11)
    set( WARNING_FLAGS -Wall )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif(CMAKE_COMPILER_IS_GNUCXX)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set( WARNING_FLAGS "-Wall -Wno-overloaded-virtual" )
endif()

## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  INCLUDE_DIRS include
  #  LIBRARIES bayesian_webclass
  #  CATKIN_DEPENDS other_catkin_pkg
  #  DEPENDS system_lib
)


###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations

include_directories(include
    ${catkin_INCLUDE_DIRS}
    ${faif_INCLUDE_DIRS}
)

## Add cmake target dependencies of the library
## as an example, code may need to be generated before libraries
## either from message generation or dynamic reconfigure
#add_dependencies(bayesian_webclass ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Declare a C++ executable
# add_executable(tidy src/tidy.cpp)
# target_link_libraries(tidy
#     ${LIBS}
# )


add_library(CSV STATIC include/bayesian_webclass/csv.h src/csv.cpp)
add_library(HTTP STATIC include/bayesian_webclass/http_downloader.h src/http_downloader.cpp )
add_library(DataPrep STATIC include/bayesian_webclass/data_preprocessor.h src/data_preprocessor.cpp)
add_library(Dict STATIC include/bayesian_webclass/dictionary.h src/dictionary.cpp)
add_library(Classifier STATIC include/bayesian_webclass/classifier.h src/classifier.cpp)

add_executable(test_p src/test.cpp)
target_link_libraries(test_p
        Classifier
        Dict
        DataPrep
        HTTP
        CSV
        ${catkin_LIBRARIES}
        ${LIBS}
        )
    #add_dependencies(test_p ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables and/or libraries for installation
install(TARGETS test_p
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

## Mark cpp header files for installation
#install(DIRECTORY include/${PROJECT_NAME}
#  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#  FILES_MATCHING PATTERN "*.h"
#)

## Mark txt files for installation
install(DIRECTORY txt/
  DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}/${PROJECT_NAME}
  FILES_MATCHING PATTERN "*.txt"
)

## Mark xml files for installation
install(DIRECTORY xml/
  DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}/${PROJECT_NAME}
  FILES_MATCHING PATTERN "*.xml"
)
install(DIRECTORY csv/
  DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}/${PROJECT_NAME}
  FILES_MATCHING PATTERN "*.csv"
)

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
#catkin_add_gtest(${PROJECT_NAME}-test test/test_bayesian_webclass.cpp)
catkin_add_gtest(url_validation_gtest test/url_validation_gtest.cpp WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/test)
catkin_add_gtest(csv_gtest test/csv_gtest.cpp WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/test)
if(TARGET url_validation_gtest)
    target_link_libraries(url_validation_gtest HTTP)
endif()
if(TARGET csv_gtest)
    target_link_libraries(csv_gtest CSV HTTP DataPrep)
endif()
## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
