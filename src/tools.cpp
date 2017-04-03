#include <iostream>
#include "tools.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;

Tools::Tools() {}

Tools::~Tools() {}

VectorXd Tools::CalculateRMSE(const vector<VectorXd> &estimations,
                              const vector<VectorXd> &ground_truth) {
    /**
    TODO:
      * Calculate the RMSE here.
    */
    VectorXd rmse(4);
    vector<VectorXd> estm_converted;
    rmse << 0, 0, 0, 0;

    if(estimations.size() != ground_truth.size()
       || estimations.size() == 0){
        std::cout << "Invalid estimation or ground_truth data" << std::endl;
        return rmse;
    }

    // convert state vector to px, py, vx, vy
    for (unsigned int i = 0; i < estimations.size(); ++i) {

        VectorXd converted(4);
        converted << estimations[i][0],                        // px
                estimations[i][1],                             // py
                cos(estimations[i][3]) * estimations[i][2],    // vx
                sin(estimations[i][3]) * estimations[i][2];    // vy
        estm_converted.push_back(converted);
    }

    //accumulate squared residuals errors
    for (unsigned int i = 0; i < estm_converted.size(); ++i) {

        VectorXd residual = estm_converted[i] - ground_truth[i];

        //coefficient-wise multiplication
        residual = residual.array() * residual.array();
        rmse += residual;
    }

    //calculate the mean from the rolling sum
    rmse /= estm_converted.size();

    //calculate the squared root from the mean
    rmse = rmse.array().sqrt();

    //return the RMSE for this estimation.
    return rmse;
}
