#pragma once
#ifdef CONTAINER_EXPORTS
#define CONTAINER_API _declspec(dllexport)
#else
#define CONTAINER_API __declspec(dllimport)
#endif

extern "C" CONTAINER_API float* mainEntrance(float [][5], float [], char [], int);