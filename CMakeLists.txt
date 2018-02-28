cmake_minimum_required(VERSION 3.5)
project(MultiThread)

add_compile_options("-std=c++14")


include_directories(${PROJECT_NAME}/include
        )

find_package(Boost REQUIRED COMPONENTS system)


file(GLOB include_files
        "${PROJECT_NAME}/include/*.h*"
        )

file(GLOB examples
        "examples/*.c*"
        )

set(linker pthread boost_system boost_filesystem)

# set(ENV{PROJECT_MANAGER_INCLUDE} ${PROJECT_NAME}/include)

# add_executable(main src/source.cpp ${include_files})


foreach( example_file ${examples} )
    # I used a simple string replace, to cut off .cpp.
    get_filename_component(examplesBase ${example_file} NAME)
    string( REPLACE ".cpp" "" file_name ${examplesBase} )
    add_executable( ${file_name} ${example_file} ${include_files})
    # Make sure YourLib is linked to each app
    target_link_libraries( ${file_name} ${linker})
endforeach( example_file ${examples} )
