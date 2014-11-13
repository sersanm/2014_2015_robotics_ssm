/**
 * @file    MyRobot.cpp
 * @brief   Detect wall.
 *
 * @author  Sergio Sánchez Martín <100292704@alumnos.uc3m.es>
 * @date    2014-11
 */

#include "MyRobot.h"

//////////////////////////////////////////////

MyRobot::MyRobot() : DifferentialWheels()
{
    _time_step = 64;

    _left_speed = 0;
    _right_speed = 0;

    _forward_camera=getCamera("camera_f");
    _forward_camera->enable(_time_step);

}


//////////////////////////////////////////////

MyRobot::~MyRobot()
{
    _forward_camera->disable();

}

//////////////////////////////////////////////


void MyRobot::run()
{
    int sum = 0;
    unsigned char green = 0, red = 0, blue = 0;
    double percentage_white = 0.0;

    //Get size of image for forward camera
    int image_width_f = _forward_camera->getWidth();
    int image_height_f = _forward_camera->getHeight();

    while (step(_time_step) != -1) {

        sum = 0;
        const unsigned char *image_f = _forward_camera->getImage();

        //Loop for get size of green, red and yellow
        for (int x = 0; x < image_width_f; x++) {
            for (int y = 0; y < image_height_f; y++) {
                green = _forward_camera->imageGetGreen(image_f, image_width_f, x, y);
                red = _forward_camera->imageGetRed(image_f, image_width_f, x, y);
                blue = _forward_camera->imageGetBlue(image_f, image_width_f, x, y);

                if ((green > 190) && (red > 190) && (blue > 190)) {
                    sum = sum + 1;
                }
            }
        }

        percentage_white = (sum / (float) (image_width_f * image_height_f)) * 100;
        cout << "Percentage of white in forward camera image: " << percentage_white << endl;

        if (percentage_white>80)
        {
            cout<<"Wall detected"<<endl;
        }

        // Turn around slowly
        _left_speed = 5;
        _right_speed = -5;

        // Set the motor speeds
        setSpeed(_left_speed, _right_speed);

    }

}

//////////////////////////////////////////////

