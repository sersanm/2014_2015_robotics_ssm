/**
 * @file    MyRobot.cpp
 * @brief   obstacle avoidance.
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

    _mode = FORWARD;

    // Get and enable the compass device
    _my_compass = getCompass("compass");
    _my_compass->enable(_time_step);

    //Get the sensors
    _distance_sensor[0] = getDistanceSensor("ds0");
    _distance_sensor[1] = getDistanceSensor("ds1");
    _distance_sensor[2] = getDistanceSensor("ds2");
    _distance_sensor[3] = getDistanceSensor("ds3");
    _distance_sensor[4] = getDistanceSensor("ds4");
    _distance_sensor[5] = getDistanceSensor("ds5");
    _distance_sensor[6] = getDistanceSensor("ds6");
    _distance_sensor[7] = getDistanceSensor("ds7");
    _distance_sensor[8] = getDistanceSensor("ds8");
    _distance_sensor[9] = getDistanceSensor("ds9");
    _distance_sensor[10] = getDistanceSensor("ds10");
    _distance_sensor[11] = getDistanceSensor("ds11");
    _distance_sensor[12] = getDistanceSensor("ds12");
    _distance_sensor[13] = getDistanceSensor("ds13");
    _distance_sensor[14] = getDistanceSensor("ds14");
    _distance_sensor[15] = getDistanceSensor("ds15");

    //Loop for enable the sensors
    for(int i=0; i<NUM_DISTANCE_SENSOR; i++){
        _distance_sensor[i]->enable(_time_step);
    }
}


//////////////////////////////////////////////

MyRobot::~MyRobot()
{
    _my_compass->disable();

    //Loop for disable the sensors
    for (int i=0; i<NUM_DISTANCE_SENSOR; i++) {
        _distance_sensor[i]->disable();
    }
}

//////////////////////////////////////////////

void MyRobot::run()
{
    double compass_angle;
    double ir0_val = 0.0, ir1_val = 0.0, ir2_val = 0.0, ir3_val = 0.0, ir4_val = 0.0, ir5_val = 0.0, ir6_val = 0.0, ir7_val = 0.0;
    double ir8_val = 0.0, ir9_val = 0.0, ir10_val = 0.0, ir11_val = 0.0, ir12_val = 0.0, ir13_val = 0.0, ir14_val = 0.0, ir15_val = 0.0;

    while (step(_time_step) != -1) {
        // Read the sensors
        const double *compass_val = _my_compass->getValues();

        // Read the sensors
        ir0_val = _distance_sensor[0]->getValue();
        ir1_val = _distance_sensor[1]->getValue();
        ir2_val = _distance_sensor[2]->getValue();
        ir3_val = _distance_sensor[3]->getValue();
        ir4_val = _distance_sensor[4]->getValue();
        ir5_val = _distance_sensor[5]->getValue();
        ir6_val = _distance_sensor[6]->getValue();
        ir7_val = _distance_sensor[7]->getValue();
        ir8_val = _distance_sensor[8]->getValue();
        ir9_val = _distance_sensor[9]->getValue();
        ir10_val = _distance_sensor[10]->getValue();
        ir11_val = _distance_sensor[11]->getValue();
        ir12_val = _distance_sensor[12]->getValue();
        ir13_val = _distance_sensor[13]->getValue();
        ir14_val = _distance_sensor[14]->getValue();
        ir15_val = _distance_sensor[15]->getValue();

        // Convert compass bearing vector to angle, in degrees
        compass_angle = convert_bearing_to_degrees(compass_val);

        // Print sensor values to console
        cout << "Compass angle (degrees): " << compass_angle << endl;
        cout << "sensor 0: " << ir0_val << endl;
        cout << "sensor 1: " << ir1_val<< endl;
        cout << "sensor 2: " << ir2_val<< endl;
        cout << "sensor 3: " << ir3_val<< endl;
        cout << "sensor 4: " << ir4_val<< endl;
        cout << "sensor 5: " << ir5_val<< endl;
        cout << "sensor 6: " << ir6_val<< endl;
        cout << "sensor 7: " << ir7_val<< endl;
        cout << "sensor 8: " << ir8_val<< endl;
        cout << "sensor 9: " << ir9_val<< endl;
        cout << "sensor 10: " << ir10_val<< endl;
        cout << "sensor 11: " << ir11_val<< endl;
        cout << "sensor 12: " << ir12_val<< endl;
        cout << "sensor 13: " << ir13_val<< endl;
        cout << "sensor 14: " << ir14_val<< endl;
        cout << "sensor 15: " << ir15_val<< endl;

        _mode = COMPASS;

        if((ir0_val<DISTANCE_LIMIT)&&(ir1_val<DISTANCE_LIMIT)&&(ir15_val<DISTANCE_LIMIT)&&(ir14_val<DISTANCE_LIMIT)){
            _mode=COMPASS;
            cout<<"Mode compass"<<endl;
        }
        else{
            if((ir0_val>DISTANCE_LIMIT)&&(ir1_val>DISTANCE_LIMIT)&&(ir15_val>DISTANCE_LIMIT)&&(ir14_val>DISTANCE_LIMIT)){
                _mode=OBSTACLE_AVOID;
                cout<<"Mode obstacle avoid"<<endl;
            }
            else{ if(((ir0_val>DISTANCE_LIMIT)||(ir1_val>DISTANCE_LIMIT)||(ir15_val>DISTANCE_LIMIT)||(ir14_val>DISTANCE_LIMIT))&&((ir3_val==0)&&(ir4_val==0))){
                    _mode= STOP;
                    _mode=TURN_LEFT;
                    cout<<"Mode turn left"<<endl;
                }
                else{
                    if(((ir0_val>DISTANCE_LIMIT)||(ir1_val>DISTANCE_LIMIT)||(ir2_val>DISTANCE_LIMIT)||(ir3_val>DISTANCE_LIMIT))&&((ir12_val==0)&&(ir11_val==0))){
                        _mode= STOP;
                        _mode=TURN_RIGHT;
                        cout<<"Mode turn right"<<endl;
                    }
                    else{
                        if((ir6_val>DISTANCE_LIMIT)&&(ir7_val>DISTANCE_LIMIT)&&(ir8_val>DISTANCE_LIMIT)&&(ir9_val>DISTANCE_LIMIT)){
                            _mode=STOP;
                            _mode=COMPASS;
                            cout<<"Mode compass (por detras)"<<endl;
                        }
                        else{
                            _mode=STOP;

                        }

                    }


                }

            }
        }







        // Send actuators commands according to the mode
        switch (_mode){
        case STOP:
            _left_speed = 0;
            _right_speed = 0;
            break;
        case FORWARD:
            _left_speed = MAX_SPEED;
            _right_speed = MAX_SPEED;
            break;
        case TURN_LEFT:
            _left_speed = MAX_SPEED +15;
            _right_speed = 0;
            break;
        case TURN_RIGHT:
            _left_speed = 0;
            _right_speed = MAX_SPEED +15;
            break;
        case OBSTACLE_AVOID:
            _left_speed = - MAX_SPEED/20 ;
            _right_speed = -MAX_SPEED ;
            break;
        case COMPASS:
            if (compass_angle < (DESIRED_ANGLE - 5)) {
                // Turn right
                _left_speed = MAX_SPEED;
                _right_speed = MAX_SPEED - 15;
            }

            else {
                if (compass_angle > (DESIRED_ANGLE + 5)) {
                    // Turn left
                    _left_speed = MAX_SPEED - 15;
                    _right_speed = MAX_SPEED;
                }
                else {
                    // Move straight forward
                    _left_speed = MAX_SPEED;
                    _right_speed = MAX_SPEED;

                }
            }
            break;

        default:
            break;
        }

        // Set the motor speeds
        setSpeed(_left_speed, _right_speed);
    }

}

//////////////////////////////////////////////

double MyRobot::convert_bearing_to_degrees(const double* in_vector)
{
    double rad = atan2(in_vector[0], in_vector[2]);
    double deg = rad * (180.0 / M_PI);

    return deg;
}

//////////////////////////////////////////////
