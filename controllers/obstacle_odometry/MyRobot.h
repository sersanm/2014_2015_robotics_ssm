/**
 * @file    MyRobot.h
 * @brief   Avoid obstacle using odometry.
 *
 * @author  Sergio Sánchez Martín <100292704@alumnos.uc3m.es>
 * @date    2014-11
 */

#include <iostream>
#include <webots/DifferentialWheels.hpp>

using namespace std;
using namespace webots;

#define MAX_SPEED       70
#define DESIRED_DISTANCE   36.2

class MyRobot : public DifferentialWheels {
private:
    int _time_step;

    double _left_speed, _right_speed;
    double _left_encoder, _right_encoder;

public:
    /**
         * @brief Empty constructor of the class.
         */
    MyRobot();

    /**
         * @brief Destructor of the class.
         */
    ~MyRobot();

    /**
         * @brief User defined function for initializing and running the template class.
         */
    void run();

    /**
          * @brief Function for follow a straight line.
          */
    void straight(double distance);

    /**
          * @brief Function for turn right.
          * @param distance
          * @return
          */
    void turn_right(double distance);

    /**
          * @brief Function for turn right.
          * @param distance
          * @return
          */
    void turn_left(double distance);


    /**
          * @brief Function for turn right.
          * @param distance
          * @return
          */
    void forward(double distance);
};
