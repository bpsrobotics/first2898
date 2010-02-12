#include "WPILib.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */ 
class RobotDemo : public SimpleRobot
{
	RobotDrive myRobot; // robot drive system
	Joystick stick; // only joystick
public:
	RobotDemo(void):
		myRobot(4,5,3,7),	// these must be initialized in the same order
		stick(1)		// as they are declared above.
	{
		GetWatchdog().SetExpiration(0.1);
	}

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous(void)
	{
		GetWatchdog().SetEnabled(false);
		myRobot.Drive(0.5, 0.0); 	// drive forwards half speed
		Wait(2.0); 				//    for 2 seconds
		myRobot.Drive(0.0, 0.0); 	// stop robot
	}

	/**
	 * Runs the motors with arcade steering. 
	 */
	void OperatorControl(void)
	{
		AxisCamera &camera = AxisCamera::GetInstance();
		camera.WriteResolution(AxisCamera::kResolution_640x480);
		camera.WriteBrightness(0);
		GetWatchdog().SetEnabled(true);

		/*
		 * the code seams to only work with the camera if the code is run not deployed
		 * deploying the code seams to cause a deadlock with the camera and the operator control
		 * to resolve this deadlock please undeply then reboot and then finally simply run
		 * ensuring that the error "no code" is on the driver station
		 * 
		 * also the setup must inculde the router and driver station for the code to work
		 * properly
		 * 
		 * - Steven Garcia
		 */
		
		while (IsOperatorControl())
		{
			GetWatchdog().Feed();
			myRobot.ArcadeDrive(stick); // drive with arcade style (use right stick)
			Wait(0.005);				// wait for a motor update time
		}
	}
};

START_ROBOT_CLASS(RobotDemo);