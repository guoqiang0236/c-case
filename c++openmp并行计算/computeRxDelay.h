#pragma once


#include <vector>
#include <cmath>
#include <omp.h>

// 常量定义
const double C = 1540.0;
const double SampleRate = 31.25e6;
const int numPoints = 1024;
const int numElements = 128;
const int numTrigs = numElements;
const double Pitch = 0.3e-3;
const double Focus = 20e-3;

void calculate_delays_sequential(double* delays);
void calculate_delays_sequential(std::vector<double>& delays);

void calculate_delays_parallel(double* delays);
void calculate_delays_parallel(std::vector<double>& delays);