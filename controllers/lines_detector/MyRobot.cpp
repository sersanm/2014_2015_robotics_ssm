/**
 * @file    MyRobot.cpp
 * @brief   Detect yellow lines.
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

    _spherical_camera=getCamera("camera_s");
    _spherical_camera->enable(_time_step);

}


//////////////////////////////////////////////

MyRobot::~MyRobot()
{
    _spherical_camera->disable();

}

//////////////////////////////////////////////


void MyRobot::run()
{
    int sum = 0;
    unsigned char green = 0, red = 0, blue = 0;
    double percentage_yellow = 0.0;

    //Get size of image for spherical camera
    int image_width_s = _spherical_camera->getWidth();
    int image_height_s = _spherical_camera->getHeight();

    while (step(_time_step) != -1) {

        sum = 0;
        const unsigned char *image_s = _spherical_camera->getImage();

        //Loop for get size of green, red and blue
        for (int x = 0; x < image_width_s; x++) {
            for (int y = 0; y < image_height_s; y++) {
                green = _spherical_camera->imageGetGreen(image_s, image_width_s, x, y);
                red = _spherical_camera->imageGetRed(image_s, image_width_s, x, y);
                blue = _spherical_camera->imageGetBlue(image_s, image_width_s, x, y);

                if ((green > 245) && (red > 245) && (blue < 51)) {
                    sum = sum + 1;
                }
            }
        }

        percentage_yellow = (sum / (float) (image_width_s * image_height_s)) * 100;
        cout << "Percentage of yellow in spherical camera image: " << percentage_yellow << endl;

        if (percentage_yellow > 0.26)
        {
            cout<<"Yellow line detected"<<endl;
        }

        // Turn around slowly
        _left_speed = 5;
        _right_speed = -5;

        // Set the motor speeds
        setSpeed(_left_speed, _right_speed);

    }

}

//////////////////////////////////////////////

