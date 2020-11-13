project(ReadUnstructuredGrid)

cmake_minimum_required(VERSION 2.8.10)

set(CMAKE_C_COMPILER /usr/local/bin/gcc)
set(CMAKE_CXX_COMPILER /usr/local/bin/g++)
set(CMAKE_C_FLAGS "-g -fopenmp -Ofast")
set(CMAKE_CXX_STANDARD 14)

SET(VTKm_DIR /home/sci/ssane/projects/uncertainty_vis/VTKM/install/lib/cmake/vtkm-1.5)
find_package(VTKm REQUIRED QUIET)


set(VTK_DIR "/home/sci/ssane/packages/VTK-build")
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(ReadUnstructuredGrid main.cxx)

  target_include_directories(ReadUnstructuredGrid PRIVATE ${VTKm_INCLUDE_DIRS})
  target_link_libraries(ReadUnstructuredGrid PRIVATE vtkm_cont vtkm_io ${VTKm_LIBRARIES} ${VTK_LIBRARIES} -fopenmp)
#  target_compile_definitions(ReadUnstructuredGrid PRIVATE "VTKM_DEVICE_ADAPTER=VTKM_DEVICE_ADAPTER_SERIAL")
  target_compile_options(ReadUnstructuredGrid PRIVATE ${VTKm_COMPILE_OPTIONS})
