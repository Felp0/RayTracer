cmake_minimum_required(VERSION 3.20)
project(RayTracer)

set(CMAKE_CXX_STANDARD 14)

include_directories(RayTracerSmall)

add_executable(RayTracer
        RayTracerSmall/GlobalController.cpp
        RayTracerSmall/GlobalController.h
        RayTracerSmall/main.cpp
        RayTracerSmall/ObjectForPool.cpp
        RayTracerSmall/ObjectForPool.h
        RayTracerSmall/Pool.cpp
        RayTracerSmall/Pool.h
        RayTracerSmall/RayTracer.cpp
        RayTracerSmall/RayTracer.h
        RayTracerSmall/Sphere.h
        RayTracerSmall/Threads.cpp
        RayTracerSmall/Threads.h
        RayTracerSmall/Tracker.cpp
        RayTracerSmall/Tracker.h
        RayTracerSmall/Vec3.h RayTracerSmall/Forking.cpp RayTracerSmall/Forking.h)
