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

    //Loop for get the sensors
    for(int i=0; i < NUM_DISTANCE_SENSOR; i++){
        string cadena;
        ostringstream cambio;
        cambio<<i;
        cadena=cambio.str();

        _distance_sensor[i]=getDistanceSensor("ds"+cadena);
    }

    //Loop for enable the sensors
    for(int i=0; i < NUM_DISTANCE_SENSOR; i++){
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
    double val_ir[16];
    //Inicializo las variables a 0 con un for
    for(int i=0; i < NUM_DISTANCE_SENSOR; i++){
        val_ir[i]=0.0;
    }
    while (step(_time_step) != -1) {
        // Read the sensors
        const double *compass_val = _my_compass->getValues();

        // Read the sensors
        for(int i=0; i < NUM_DISTANCE_SENSOR; i++){

            val_ir[i] = _distance_sensor[i]->getValue();
        }

        // Convert compass bearing vector to angle, in degrees
        compass_angle = convert_bearing_to_degrees(compass_val);

        // Print sensor values to console
        cout << "Compass angle (degrees): " << compass_angle << endl;

        for(int i=0; i < NUM_DISTANCE_SENSOR; i++){

            cout << "sensor " << i << ":" << val_ir[i] <<endl;
        }


        _mode = COMPASS;

        if((val_ir[0]<DISTANCE_LIMIT)&&(val_ir[1]<DISTANCE_LIMIT)&&(val_ir[15]<DISTANCE_LIMIT)&&(val_ir[14]<DISTANCE_LIMIT)){
            _mode=COMPASS;
            cout<<"Mode compass"<<endl;
        }
        else{
            if((val_ir[0]>DISTANCE_LIMIT)&&(val_ir[1]>DISTANCE_LIMIT)&&(val_ir[15]>DISTANCE_LIMIT)&&(val_ir[14]>DISTANCE_LIMIT)){
                _mode=OBSTACLE_AVOID;
                cout<<"Mode obstacle avoid"<<endl;
            }
            else{ if(((val_ir[0]>DISTANCE_LIMIT)||(val_ir[1]>DISTANCE_LIMIT)||(val_ir[15]>DISTANCE_LIMIT)||(val_ir[14]>DISTANCE_LIMIT))&&((val_ir[3]==0)&&(val_ir[4]==0))){
                    _mode= STOP;
                    _mode=TURN_LEFT;
                    cout<<"Mode turn left"<<endl;
                }
                else{
                    if(((val_ir[0]>DISTANCE_LIMIT)||(val_ir[1]>DISTANCE_LIMIT)||(val_ir[2]>DISTANCE_LIMIT)||(val_ir[3]>DISTANCE_LIMIT))&&((val_ir[12]==0)&&(val_ir[11]==0))){
                        _mode= STOP;
                        _mode=TURN_RIGHT;
                        cout<<"Mode turn right"<<endl;
                    }
                    else{
                        if((val_ir[6]>DISTANCE_LIMIT)&&(val_ir[7]>DISTANCE_LIMIT)&&(val_ir[8]>DISTANCE_LIMIT)&&(val_ir[9]>DISTANCE_LIMIT)){
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
