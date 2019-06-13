/*
 * File:          robot1.c
 * Date:
 * Description:
 * Author:
 * Modifications:
 */

/*
 * You may need to add include files like <webots/distance_sensor.h> or
 * <webots/differential_wheels.h>, etc.
 */
#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/keyboard.h>
#include <webots/distance_sensor.h>
#include <webots/position_sensor.h>

#include <stdio.h>
/*
 * You may want to add macros here.
 */
#define TIME_STEP 1000

/*
 * This is the main program.
 * The arguments of the main function can be specified by the
 * "controllerArgs" field of the Robot node
 */
int main(int argc, char **argv)
{
  /* necessary to initialize webots stuff */
  wb_robot_init();

  /*keyboard devices*/
  wb_keyboard_enable(TIME_STEP);
  int pressed_key;

  /*
   * You should declare here WbDeviceTag variables for storing
   * robot devices like this:
   *  WbDeviceTag my_sensor = wb_robot_get_device("my_sensor");
   *  WbDeviceTag my_actuator = wb_robot_get_device("my_actuator");
   */
   /*Motor devices*/
   WbDeviceTag wheel_right= wb_robot_get_device("motor_right");
   WbDeviceTag wheel_left= wb_robot_get_device("motor_left");

   wb_motor_set_position(wheel_right, INFINITY);
   wb_motor_set_position(wheel_left, INFINITY);
   double vl_value;
   double vr_value;
   double rpml_value;
   double rpmr_value;
   double linearv_l;
   double linearv_r;

   /*distance sensor devices*/
   WbDeviceTag dist_sensor=wb_robot_get_device("distance_sensor");
   wb_distance_sensor_enable(dist_sensor, TIME_STEP);
   double ds_value;

   /*encoder*/
   WbDeviceTag encoder = wb_robot_get_device("encoder1");
   wb_position_sensor_enable(encoder, TIME_STEP);
   double ps_value;
  /* main loop
   * Perform simulation steps of TIME_STEP milliseconds
   * and leave the loop when the simulation is over
   */
  while (wb_robot_step(TIME_STEP) != -1) {

    /*
     * Read the sensors :
     * Enter here functions to read sensor data, like:
     *  double val = wb_distance_sensor_get_value(my_sensor);
     */

    /*Keyboard sensor*/
    pressed_key = wb_keyboard_get_key();

   /*Read distance sensor*/
    ds_value = wb_distance_sensor_get_value(dist_sensor);
    printf("Distance sensor: %lf\n", ds_value);

    /*Read encoder1*/
    ps_value = wb_position_sensor_get_value(encoder);
    /*printf("encoder = %lf\n", ps_value);
    double rpm_value;*/

    /* Process sensor data here */

    /*
     * Enter here functions to send actuator commands, like:
     * wb_differential_wheels_set_speed(100.0,100.0);
     */

    /*Keyboard conditions*/

    if (pressed_key == WB_KEYBOARD_UP){
     vl_value=-40; /*w=V/r*/
     vr_value=-40; /*w=V/r*/
     rpml_value=vl_value/0.104771; /*RPM= w/((0.10472))*/
     rpmr_value=vr_value/0.104771; /*RPM= w/((0.10472))*/
     linearv_l= 0.007853*rpml_value;
     linearv_r= 0.007853*rpmr_value;   
     wb_motor_set_velocity(wheel_right, -40);
     wb_motor_set_velocity(wheel_left,  -40);
     printf("Velocity right wheel   %lf m/s\n", linearv_r);
     printf("Velocity left wheel  %lf m/s\n", linearv_l );
     printf("RPM left wheel  %lf \n", rpml_value );
     printf("RPM right wheel  %lf \n", rpmr_value );
     }
    if (pressed_key==WB_KEYBOARD_DOWN){
     vl_value=0.13; /*w=V/r*/
     vr_value=0.13; /*w=V/r*/
     rpml_value=vl_value/0.104771; /*RPM= w/((0.10472))*/
     rpmr_value=vr_value/0.104771; /*RPM= w/((0.10472))*/
     linearv_l= 0.007853*rpml_value;
     linearv_r= 0.007853*rpmr_value;   
     wb_motor_set_velocity(wheel_right, 0.13);
     wb_motor_set_velocity(wheel_left,  0.13);
     printf("Velocity right wheel   %lf m/s\n", linearv_r);
     printf("Velocity left wheel  %lf m/s\n", linearv_l );
     printf("RPM left wheel  %lf \n", rpml_value );
     printf("RPM right wheel  %lf \n", rpmr_value );
     }
    if (pressed_key==WB_KEYBOARD_RIGHT){
     vl_value= 40; /*w=V/r*/
     vr_value=-40; /*w=V/r*/
     rpml_value=vl_value/0.104771; /*RPM= w/(0.10472))*/
     rpmr_value=vr_value/0.104771; /*RPM= w/((0.10472))*/
     linearv_l= 0.007853*rpml_value;
     linearv_r= 0.007853*rpmr_value;   
     wb_motor_set_velocity(wheel_left,   40);
     wb_motor_set_velocity(wheel_right, -40);
     printf("Velocity right wheel   %lf m/s\n", linearv_r);
     printf("Velocity left wheel  %lf m/s\n", linearv_l );
     printf("RPM left wheel  %lf \n", rpml_value );
     printf("RPM right wheel  %lf \n", rpmr_value );
     }
    if (pressed_key==WB_KEYBOARD_LEFT){
     vl_value= 40; /*w=V/r*/
     vr_value=-40; /*w=V/r*/
     rpml_value=vl_value/0.104771; /*RPM= w/(0.10472))*/
     rpmr_value=vr_value/0.104771; /*RPM= w/((0.10472))*/
     linearv_l= 0.007853*rpml_value;
     linearv_r= 0.007853*rpmr_value;    
     wb_motor_set_velocity(wheel_left,  -40);
     printf("Velocity right wheel   %lf m/s\n", linearv_r);
     printf("Velocity left wheel  %lf m/s\n", linearv_l );
     printf("RPM left wheel  %lf \n", rpml_value );
     printf("RPM right wheel  %lf \n", rpmr_value );
     }



  };

  /* Enter your cleanup code here */

  /* This is necessary to cleanup webots resources */
  wb_robot_cleanup();

  return 0;
}
