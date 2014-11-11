/**
 * @file    MyRobot.h
 * @brief   obstacle avoidance.
 *
 * @author  Sergio Sánchez Martín <100292704@alumnos.uc3m.es>
 * @date    2014-11
 */

#include <iostream>
#include <sstream>
#include <cmath>
#include <webots/DifferentialWheels.hpp>

using namespace std;
using namespace webots;

#define NUM_DISTANCE_SENSOR 16
#define DISTANCE_LIMIT      100
#define MAX_SPEED           30
#define DESIRED_ANGLE   45.0002

class MyRobot : public DifferentialWheels {
private:

    int _time_step;

    DistanceSensor * _distance_sensor[NUM_DISTANCE_SENSOR];
    Compass * _my_compass;
    double _left_speed, _right_speed;

    enum Mode {
        STOP,
        FORWARD,
        TURN_LEFT,
        TURN_RIGHT,
        OBSTACLE_AVOID,
        COMPASS
    };

    Mode _mode;


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
          * @brief An example for converting bearing vector from compass to angle (in degrees).
          * @param in_vector
          * @return
          */
    double convert_bearing_to_degrees(const double* in_vector);
};
