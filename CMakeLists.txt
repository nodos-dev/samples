cmake_minimum_required(VERSION 3.24.2)
project("Samples")

function(add_folder_as_subsystem_project NAME DEPENDENCIES INCLUDE_FOLDERS)
    project(${NAME})
    message("Processing subsystem ${NAME}")

    set(SOURCE_FOLDERS "${CMAKE_CURRENT_SOURCE_DIR}/Source" "${CMAKE_CURRENT_SOURCE_DIR}/Include")
    set(CONFIG_FOLDERS "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/Config")
    foreach(folder IN LISTS SOURCE_FOLDERS)	
        message(STATUS "${PROJECT_NAME}: Scanning ${folder}")
        file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS ${folder} "${folder}/*.cpp" 
            "${folder}/*.cc" "${folder}/*.c" "${folder}/*.inl"
            "${folder}/*.frag" "${folder}/*.vert" "${folder}/*.glsl" "${folder}/*.comp" "${folder}/*.dat" "${folder}/*.natvis")
        file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS ${folder} "${folder}/*.h" "${folder}/*.hpp")
        file(GLOB_RECURSE RESOURCES CONFIGURE_DEPENDS ${folder} "${folder}/*.rc")
        list(APPEND COLLECTED_SOURCES ${SOURCES})
        list(APPEND COLLECTED_HEADERS ${HEADERS})
        list(APPEND COLLECTED_RESOURCES ${RESOURCES})
    endforeach()
    foreach(CONFIG_FOLDER ${CONFIG_FOLDERS})
        file(GLOB_RECURSE CUR_CONFIG_FILES CONFIGURE_DEPENDS ${CONFIG_FOLDER} 
            "${CONFIG_FOLDER}/*.nossys" "${CONFIG_FOLDER}/*.fbs" "${CONFIG_FOLDER}/Defaults.json")
        list(APPEND CONFIG_FILES ${CUR_CONFIG_FILES})
    endforeach()

    if(TARGET ${NAME})
        target_sources(${NAME} PRIVATE ${COLLECTED_SOURCES} ${COLLECTED_HEADERS} ${COLLECTED_RESOURCES} ${CONFIG_FILES})
    else()
        add_library(${NAME} MODULE ${COLLECTED_SOURCES} ${COLLECTED_HEADERS} ${COLLECTED_RESOURCES} ${CONFIG_FILES})
    endif()
    
    set_target_properties(${NAME} PROPERTIES
        CXX_STANDARD 20
        LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/Binaries"
        LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/Binaries"
        LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_SOURCE_DIR}/Binaries"
        LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}/Binaries"
    )

    target_include_directories(${NAME} PRIVATE ${INCLUDE_FOLDERS} ${SOURCE_FOLDERS})

    target_link_libraries(${NAME} PRIVATE ${DEPENDENCIES})
    target_link_libraries(${NAME} PUBLIC nosSubsystemSDK)

endfunction()

function(add_folder_as_plugin_project NAME DEPENDENCIES INCLUDE_FOLDERS)
    project(${NAME})
    message("Processing plugin ${NAME}")

    set(SOURCE_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/Source")
    set(CONFIG_FOLDERS "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/Config")

    file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS ${SOURCE_FOLDER}
        "${SOURCE_FOLDER}/*.cpp" "${SOURCE_FOLDER}/*.inl" "${SOURCE_FOLDER}/*.glsl" "${SOURCE_FOLDER}/*.hlsl"
        "${SOURCE_FOLDER}/*.comp" "${SOURCE_FOLDER}/*.frag" "${SOURCE_FOLDER}/*.vert")
    list(APPEND CONFIG_FILES)
    foreach(CONFIG_FOLDER ${CONFIG_FOLDERS})
        file(GLOB_RECURSE CUR_CONFIG_FILES CONFIGURE_DEPENDS ${CONFIG_FOLDER} 
            "${CONFIG_FOLDER}/*.noscfg" "${CONFIG_FOLDER}/*.nosdef" "${CONFIG_FOLDER}/*.fbs")
        list(APPEND CONFIG_FILES ${CUR_CONFIG_FILES})
    endforeach()
    file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS ${SOURCE_FOLDER} "${SOURCE_FOLDER}/*.h" "${SOURCE_FOLDER}/*.hpp")
    file(GLOB_RECURSE RESOURCES CONFIGURE_DEPENDS ${SOURCE_FOLDER} "${SOURCE_FOLDER}/*.rc")

    set(SHADER_FOLDERS "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/Shaders")
    list(APPEND SHADERS)
    
    foreach(SHADER_FOLDER ${SHADER_FOLDERS})
        file(GLOB_RECURSE CUR_SHADERS CONFIGURE_DEPENDS ${SHADER_FOLDER} 
            "${SHADER_FOLDER}/*.glsl" "${SHADER_FOLDER}/*.comp" "${SHADER_FOLDER}/*.frag" "${SHADER_FOLDER}/*.vert")
        list(APPEND SHADERS ${CUR_SHADERS})
    endforeach()
    
    add_library(${NAME} MODULE ${SOURCES} ${SHADERS} ${HEADERS} ${RESOURCES} ${CONFIG_FILES})
    set_target_properties(${NAME} PROPERTIES
        CXX_STANDARD 20
        LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/Binaries"
        LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/Binaries"
        LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_SOURCE_DIR}/Binaries"
        LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}/Binaries"
    )

    target_include_directories(${NAME} PRIVATE ${INCLUDE_FOLDERS})

    target_link_libraries(${NAME} PRIVATE ${DEPENDENCIES})
    target_link_libraries(${NAME} PUBLIC nosPluginSDK)
endfunction()

# Dependencies
# ------------

# Update subsystems.json if you add dependencies, so that CD can create releases.

# Nodos Subsystem SDK
if (NOT WITH_NODOS)
    list(APPEND CMAKE_MODULE_PATH $ENV{NODOS_SDK_DIR}/cmake)
    find_package(nosSubsystemSDK)
endif()

# Nodos Plugin SDK
if (NOT WITH_NODOS)
    list(APPEND CMAKE_MODULE_PATH $ENV{NODOS_SDK_DIR}/cmake)
    find_package(nosPluginSDK REQUIRED)
endif()

add_subdirectory(AdderSubsystem) # Subsystem prefix is only for distinguishing between nosVulkan repo and this.
add_subdirectory(AdderNodes)
