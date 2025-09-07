#include "computeRxDelay.h"



void calculate_delays_sequential(double* delays) {

    const double factor = C / (2 * SampleRate);

    for (int k = 0; k < numPoints; k++) {
        double z_dis = k * factor;
        double z_dis_sq = z_dis * z_dis;

        for (int j = 0; j < numElements; j++) {
            for (int i = 0; i < numTrigs; i++) {
                double x_dis = (j - i) * Pitch;
                double d_rx = std::sqrt(x_dis * x_dis + z_dis_sq);
                delays[k * numElements * numTrigs + j * numTrigs + i] = d_rx / C;
            }
        }
    }

    return;
}

void calculate_delays_sequential(std::vector<double>& delays) {


    const double factor = C / (2 * SampleRate);

    for (int k = 0; k < numPoints; k++) {
        double z_dis = k * factor;
        double z_dis_sq = z_dis * z_dis;

        for (int j = 0; j < numElements; j++) {
            for (int i = 0; i < numTrigs; i++) {
                double x_dis = (j - i) * Pitch;
                double d_rx = std::sqrt(x_dis * x_dis + z_dis_sq);
                delays[k * numElements * numTrigs + j * numTrigs + i] = d_rx / C;
            }
        }
    }

    return;
}

void calculate_delays_parallel(double* delays) {

    const double factor = C / (2 * SampleRate);

#pragma omp parallel for 
    for (int k = 0; k < numPoints; k++) {
        double z_dis = k * factor;
        double z_dis_sq = z_dis * z_dis;

        for (int j = 0; j < numElements; j++) {
            for (int i = 0; i < numTrigs; i++) {
                double x_dis = (j - i) * Pitch;
                double d_rx = std::sqrt(x_dis * x_dis + z_dis_sq);
                delays[k * numElements * numTrigs + j * numTrigs + i] = d_rx / C;
            }
        }
    }

    return;
}


void calculate_delays_parallel(std::vector<double>& delays) {


    const double factor = C / (2 * SampleRate);
   
#pragma omp parallel for 
    for (int k = 0; k < numPoints; k++) {
        double z_dis = k * factor;
        double z_dis_sq = z_dis * z_dis;

        for (int j = 0; j < numElements; j++) {
            for (int i = 0; i < numTrigs; i++) {
                double x_dis = (j - i) * Pitch;
                double d_rx = std::sqrt(x_dis * x_dis + z_dis_sq);
                delays[k * numElements * numTrigs + j * numTrigs + i] = d_rx / C;
            }
        }
    }

    return;
}