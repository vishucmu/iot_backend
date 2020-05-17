cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
set (CMAKE_CXX_STANDARD 11)


project(iot_risk_assessment)


set(srcs 
         ../Model/Action.cpp
         ../Model/Asset.cpp
         ../Model/Control.cpp
         ../Model/Device.cpp
         ../Model/FrameworkModel.cpp
         ../Model/Property.cpp
         ../Model/Risk.cpp
         ../Model/Vulnerability.cpp
         ../Utils/MappingUtility.cpp
         ../Controller/FrameworkController.cpp
        )

set(incs
         ../Model/Action.hpp
         ../Model/Asset.hpp
         ../Model/Control.hpp
         ../Model/Device.hpp
         ../Model/FrameworkModel.hpp
         ../Model/Property.hpp
         ../Model/Risk.hpp
         ../Model/Vulnerability.hpp
         ../Utils/MappingUtility.hpp
         ../Controller/FrameworkController.hpp
         ../Common/CommonIncludes.h
         )

set(IOT_LIB "bluenotebook")
add_library("${IOT_LIB}" ${srcs})
target_link_libraries("${IOT_LIB}")

include_directories(${incs})

add_executable (iot_risk_assessment ../IOTRiskAssessment/main.cpp)
target_link_libraries (iot_risk_assessment ${IOT_LIB} )


