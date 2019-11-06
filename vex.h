/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       vex.h                                                     */
/*    Author:       Vex Robotics                                              */
/*    Created:      1 Feb 2019                                                */
/*    Description:  Default header for V5 projects                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cmath>

#include "v5.h"
#include "v5_vcs.h"

vex::brain Brain;
vex::controller Controller1 = vex::controller();

// drive
vex::motor LF = vex::motor(vex::PORT1,vex::gearSetting::ratio18_1,false); 
vex::motor LB = vex::motor(vex::PORT2,vex::gearSetting::ratio18_1,false);
vex::motor RF = vex::motor(vex::PORT9,vex::gearSetting::ratio18_1,true); // true = reversed
vex::motor RB = vex::motor(vex::PORT10,vex::gearSetting::ratio18_1,true);
// intake
vex::motor intakeLeft = vex::motor(vex::PORT3,vex::gearSetting::ratio18_1,true);
vex::motor intakeRight = vex::motor(vex::PORT8,vex::gearSetting::ratio18_1,true);
// tilter
vex::motor tilt = vex::motor(vex::PORT5,vex::gearSetting::ratio36_1,true);
// lift
vex::motor lift = vex::motor(vex::PORT4,vex::gearSetting::ratio18_1,false);
// sensors
vex::analog_in atonSelectOne = vex::analog_in(Brain.ThreeWirePort.A);
vex::analog_in atonSelectTwo = vex::analog_in(Brain.ThreeWirePort.C);

// motivational quote
void littleCeasars(){
    Controller1.Screen.print("lEtS gEt tHiS bReAd");
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                           User Control Functions                          */
/*                                                                           */
/*---------------------------------------------------------------------------*/

double sgn(double number){
    if (number > 0) number = 1;
    else number = -1;
    return number;
}

// drive
void driveCont(){
    LF.spin(vex::directionType::fwd, Controller1.Axis3.value(), vex::velocityUnits::pct);
    LB.spin(vex::directionType::fwd, Controller1.Axis3.value(), vex::velocityUnits::pct);
    RF.spin(vex::directionType::fwd, Controller1.Axis2.value(), vex::velocityUnits::pct);
    RB.spin(vex::directionType::fwd, Controller1.Axis2.value(), vex::velocityUnits::pct);
}

// set intake power
void setIntakeLeftPower (int power){
    if(power==0) intakeLeft.stop(vex::brakeType::coast);
    else{
        intakeLeft.spin(vex::directionType::fwd,power,vex::velocityUnits::pct);
    }
}
void setIntakeRightPower (int power){
    if(power==0) intakeRight.stop(vex::brakeType::coast);
    else{
        intakeRight.spin(vex::directionType::fwd,power,vex::velocityUnits::pct);
    }
}
void setIntakePower (int pow){
    setIntakeLeftPower(pow);
    setIntakeRightPower(pow);
}
// intake
void intakeCont(){ 
    if(Controller1.ButtonR1.pressing()){ // if buttonR1, intake
    setIntakePower(100);
    }   
    else if(Controller1.ButtonR2.pressing()){ // if buttonR2, detake
    setIntakePower(-100);
    }   
    else setIntakePower(0);
}

// set tilter power
void setTiltMotorPower (int power){
    if(power==0) tilt.stop(vex::brakeType::coast);
    else{
        tilt.spin(vex::directionType::fwd,power,vex::velocityUnits::pct);
    }
}
void setTiltPower (int pow){
 setTiltMotorPower(pow);
}
// tilter --- manual control for emergency only (ex. if macro fails)
void tilterCont(){ 
    if(Controller1.ButtonR1.pressing()){ // if buttonUp, tilt up
     setTiltPower(100);
    }   
    else if(Controller1.ButtonR2.pressing()){ // if buttonDown, tilt down
      setTiltPower(-100);
    }   
    else setTiltPower(0);
}

// set lift power
void setLiftMotorPower (int power){
    if(power==0) lift.stop(vex::brakeType::hold);
    else{
        lift.spin(vex::directionType::fwd,power,vex::velocityUnits::pct);
    }
}
void setLiftPower (int pow){
 setLiftMotorPower(pow);
}
// lift
void liftCont(){ 
    if(Controller1.ButtonR1.pressing()){ // if buttonR1, lift up
     setLiftPower(100);
    }   
    else if(Controller1.ButtonR2.pressing()){ // if buttonR2, lift down
      setLiftPower(-100);
    }   
    else setLiftPower(0);
}

// macy control wishes
/*
L1 - scoring macro                       - in progress (written at end of aton functions)
L2 - toggle                              - not started
R1 - intake          (use L2 for toggle) - done
R2 - detake          (use L2 for toggle) - done (still need control toggle so lift
R1 - lift up         (use L2 for toggle) - done  and intake don't run at same time)
R1 - lift down       (use L2 for toggle) - done
*/


/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                           Autonomous Functions                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// math vars
double abs(double Var) {
		if (Var < 0)  Var = Var * (-1);
		return Var;
	}

// set drive power
void setLFPower (int power){
    if(power==0) LF.stop(vex::brakeType::coast);
    else{
        LF.spin(vex::directionType::fwd,power,vex::velocityUnits::pct);
    }
}
void setLBPower (int power){
    if(power==0) LB.stop(vex::brakeType::coast);
    else{
        LB.spin(vex::directionType::fwd,power,vex::velocityUnits::pct);
    }
}
void setRFPower (int power){
    if(power==0) RF.stop(vex::brakeType::coast);
    else{
        RF.spin(vex::directionType::fwd,power,vex::velocityUnits::pct);
    }
}
void setRBPower (int power){
    if(power==0) RB.stop(vex::brakeType::coast);
    else{
        RB.spin(vex::directionType::fwd,power,vex::velocityUnits::pct);
    }
}
void setDrivePower(int LF,int LB,int RF,int RB){
        setLFPower(LF);
        setLBPower(LB);
        setRFPower(RF);
        setRBPower(RB);
    }
    void drivePowerSend(int j1,int j2){ // left, right
        int LF=j1; // left
        int RF=j2; // right
         
        setDrivePower(LF,LF,RF,RF);
    }
    void setDrivePower(int left, int right){
        setLFPower(left);
        setLBPower(left);
        setRFPower(right);
        setRBPower(right);
    }

// drive with ramping
bool DriveRampingEnabled;

class Ramping{
    public:
    int ChangePct=1; // amout of Pct change per loop
    int ChangeMsec=1; // amount of time in between loops

    int RequestedPct=0; // used to request Pct value change
    int Pct=0; // pct output
    int MinUpPct=0; // used as moveing up StillSpeed
    int MinDownPct=0; // used as moving down StillSpeed
    int MaxPct=100; // max pct value

    Ramping(); // object specifer

    Ramping(int CP,int CM,int MaxP=100,int MinDP=0,int MinUP=0){
        // ChangePct,ChangeMsec,MaxPct
        ChangePct=CP;
        ChangeMsec=CM;
        MaxPct=MaxP;
        MinUpPct=MinUP;
        MinDownPct=MinDP;
    }

    void TaskRun(){
        if(RequestedPct>Pct){ // ramp up
            Pct=Pct+ChangePct;
        }
        else if(RequestedPct<Pct){ // ramp down
            Pct=Pct-ChangePct;
        }
        // limit Pct
        if(Pct>MaxPct)	Pct=MaxPct;
        if(Pct<-MaxPct)	Pct=-MaxPct;
        if(Pct>0 && Pct<MinUpPct) Pct=MinUpPct;
        if(Pct<0 && Pct>MinDownPct)    Pct=MinDownPct;
    }
}; // end of task

Ramping leftRamp(1,6); // first value = pct of pwr change after each interval passed
Ramping rightRamp(1,6); // second value = number of Msec between each pct change

    int Drive_Ramping(){
        DriveRampingEnabled=true;
        while(DriveRampingEnabled){
            leftRamp.TaskRun();
            rightRamp.TaskRun();
            setDrivePower(leftRamp.Pct,rightRamp.Pct);
            vex::task::sleep(leftRamp.ChangeMsec);
        }
        return 1;
    }

void SetDRpower(int Lpower,int Rpower){ // DMR
    leftRamp.RequestedPct = Lpower;
    rightRamp.RequestedPct = Rpower;
}
void DI(int Lpower,int Rpower){
    leftRamp.RequestedPct=Lpower; // tells ramping to run at inputed power
    rightRamp.RequestedPct=Rpower; 
    
    leftRamp.Pct=Lpower; // instantly changes the ramping pct to desired power instead of ramping up
    rightRamp.Pct=Rpower;
    setDrivePower(leftRamp.Pct,rightRamp.Pct);
}

// drive ramping with auto straightening
void driveRamp(double Distance,int Pct=75,int EndWait=200, int Correction=1){ // set default values to 75, 200, 1
        // update ramping speed
        leftRamp.ChangeMsec = 6;
        rightRamp.ChangeMsec = 6;

        double Direction=sgn(Distance);
        int Lpower=0;
        int Rpower=0;
    
        // clear encoder
        LF.resetRotation();
        LB.resetRotation();
        RF.resetRotation();
        RB.resetRotation();
    
        // is it there yet?
        while(std::abs(LF.rotation(vex::rotationUnits::deg))<std::abs(Distance)){
            double LEncValue=LF.rotation(vex::rotationUnits::deg);
            double REncValue=RB.rotation(vex::rotationUnits::deg);
            // straighten
            if(std::abs(LEncValue)>std::abs(REncValue)){
                Lpower=Pct-Correction;
                Rpower=Pct;
            }
            else if(std::abs(LEncValue)<std::abs(REncValue)){
                Lpower=Pct;
                Rpower=Pct-Correction;
            }
            else if(std::abs(LEncValue)==std::abs(REncValue)){
                Lpower=Pct;
                Rpower=Pct;
            }
            // correct direction
            Lpower=Lpower*Direction;
            Rpower=Rpower*Direction;
            // send to SetDRpower
            SetDRpower(Lpower,Rpower);
            vex::task::sleep(1);
        }
        SetDRpower(0,0);
        vex::task::sleep(EndWait);
    }

void rampTurn(double deg,int LPowerSend=40,int RPowerSend=40,int waitTime=200){ // set default values 40, 40, 200
        int Dir=sgn(deg);
        deg=std::abs(deg)/12.56;
        LPowerSend=LPowerSend*Dir;
        RPowerSend=RPowerSend*Dir;

        LF.resetRotation();
        LB.resetRotation();
        RF.resetRotation();
        RB.resetRotation();

        while((std::abs(LF.rotation(vex::rotationUnits::rev))) <std::abs(deg)){
            DI(LPowerSend,-RPowerSend);

            vex::task::sleep(1);
        }
        DI(0,0);
        vex::task::sleep(waitTime);
}

// intake
void intake(int rotations = 200, int power = 100){ // set default values at 200, 100
    int direction = sgn(rotations);
    
    intakeLeft.resetRotation();
    intakeRight.resetRotation();

    // intake for a certain about of degrees then stop using brakeType::coast
    while(abs(intakeLeft.rotation(vex::rotationUnits::deg))<abs(rotations)){
        setIntakePower(power*direction);
    }
    setIntakePower(0);
}
void detake(int rotations = 200, int power = -100){ // set default values at 200, -100
    int direction = sgn(rotations);
    
    intakeLeft.resetRotation();
    intakeRight.resetRotation();

    // intake for a certain about of degrees then stop using brakeType::coast
    while(abs(intakeLeft.rotation(vex::rotationUnits::deg))<abs(rotations)){
        setIntakePower(power*direction);
    }
    setIntakePower(0);
}
void autoIntake(bool On, bool In){
    if(On){
        if(In){
            setIntakePower(100);
        } 
        if(!In){
            setIntakePower(-100);
        } 
    }
    if(!On){
        setIntakePower(0);
    }
}

// tilter
void tiltUp(int pos, int power=50){ // set default power to 50
        tilt.resetRotation();

        tilt.startRotateFor(pos,vex::rotationUnits::deg,power,vex::velocityUnits::pct);
        tilt.setStopping(vex::brakeType::coast);
}
void tiltBack(int rotations, int power = 50){ // set default power to 50
  int direction = sgn(rotations);

    while(abs(tilt.rotation(vex::rotationUnits::deg))<abs(rotations)){
      setTiltPower(power*direction);
    }
    setTiltPower(0);
  }

// lift
void LiftMove(int pos, int power=100){ // set default power to 100
        lift.resetRotation();

        lift.startRotateFor(pos,vex::rotationUnits::deg,power,vex::velocityUnits::pct);
        lift.setStopping(vex::brakeType::hold);
}
void AtonLift(int rotations, int power = 100){ // set default power to 100
  int direction = sgn(rotations);

    while(abs(lift.rotation(vex::rotationUnits::deg))<abs(rotations)){
      setLiftPower(power*direction);
    }
    setLiftPower(0);
  }

// scoring macro -- just the skeleton, still need to adjust values just like an aton routine
void scoring(){ 
  if(Controller1.ButtonL1.pressing()){
    tiltUp(45);
    vex::task::sleep(500);
    driveRamp(-1000);
    tiltBack(-45);
  }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                            Autonomous Selector                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

void atonPots(){
    int SelectValueOne = atonSelectOne.value(vex::percentUnits::pct);
    int SelectValueTwo = atonSelectTwo.value(vex::percentUnits::pct);
    
   if(SelectValueOne > 60){
       if(SelectValueTwo > 80){
          // none
      }
      else if(SelectValueTwo > 50){
          // none
      }
      else if(SelectValueTwo > 30){
          // none
      }
      else if(SelectValueTwo >= 0){
          // none
      }
    }
    
    else if(SelectValueOne > 40){
        if(SelectValueTwo > 80){
            // none
        }
        else if(SelectValueTwo > 50){
            // none
        }
        else if(SelectValueTwo > 30){
            // none
        }
        else if(SelectValueTwo >= 0){
            // none
        }
    }
    else if(SelectValueOne > 20){
        if(SelectValueTwo > 80){
            // none
        }
        else if(SelectValueTwo > 50){
            // none
        }
        else if(SelectValueTwo > 30){
            // none
        }
        else if(SelectValueTwo >= 0){
            // none
        }
    }
    else if(SelectValueOne >= 0){
        if(SelectValueTwo > 80){
            // none
        }
        else if(SelectValueTwo > 50){
            // none
        }
        else if(SelectValueTwo > 30){
            // none
        }
        else if(SelectValueTwo >= 0){
            // none
        }
    }
}

int atonSel(){
    static int SelectValueOne;
    static int SelectValueTwo;

    while(true){

    static int SelectValueOneWas = SelectValueOne;
    static int SelectValueTwoWas = SelectValueTwo;

    SelectValueOne = atonSelectOne.value(vex::percentUnits::pct);
    SelectValueTwo = atonSelectTwo.value(vex::percentUnits::pct);

    if(SelectValueOne!=SelectValueOneWas || SelectValueTwo!=SelectValueTwoWas){
          Brain.Screen.clearScreen();

    if(SelectValueOne > 60){
      if(SelectValueTwo > 80){
          //none
          Brain.Screen.clearLine(1, vex::color::red);
          Brain.Screen.clearLine();
          Brain.Screen.print("N/A");
      }
        else if(SelectValueTwo > 50){
            //none
            Brain.Screen.clearLine(1, vex::color::red);
            Brain.Screen.clearLine();
            Brain.Screen.print("N/A");
        }
        else if(SelectValueTwo > 30){
            //none
            Brain.Screen.clearLine(1, vex::color::red);
            Brain.Screen.clearLine();
            Brain.Screen.print("N/A");
        }
        else if(SelectValueTwo >= 0){
            //none
            Brain.Screen.clearLine(1, vex::color::red);
            Brain.Screen.clearLine();
            Brain.Screen.print("N/A");
        }
    }
    else if(SelectValueOne > 40){
        if(SelectValueTwo > 80){
            //BckRedSniper();
            Brain.Screen.clearLine(1, vex::color::red);
            Brain.Screen.clearLine();
            Brain.Screen.print("N/A");
        }
        else if(SelectValueTwo > 50){
            //BckRedSniperPrk();
            Brain.Screen.clearLine(1, vex::color::red);
            Brain.Screen.clearLine();
            Brain.Screen.print("N/A");
        }
        else if(SelectValueTwo > 30){
            //none
            Brain.Screen.clearLine(1, vex::color::red);
            Brain.Screen.clearLine();
            Brain.Screen.print("N/A");
        }
        else if(SelectValueTwo >= 0){
            //none
            Brain.Screen.clearLine(1, vex::color::red);
            Brain.Screen.clearLine();
            Brain.Screen.print("N/A");
        }
    }

    else if(SelectValueOne > 20){
        if(SelectValueTwo > 80){
            //BckBlueSniper
            Brain.Screen.clearLine(1, vex::color::blue);
            Brain.Screen.clearLine();
            Brain.Screen.print("N/A");
        }
        else if(SelectValueTwo > 50){
            //BackBlueSnipePrk
            Brain.Screen.clearLine(1, vex::color::blue);
            Brain.Screen.clearLine();
            Brain.Screen.print("N/A");
        }
        else if(SelectValueTwo > 30){
            //none
            Brain.Screen.clearLine(1, vex::color::blue);
            Brain.Screen.clearLine();
            Brain.Screen.print("N/A");
        }
        else if(SelectValueTwo >= 0){
            //none
            Brain.Screen.clearLine(1, vex::color::blue);
            Brain.Screen.clearLine();
            Brain.Screen.print("N/A");
        }
    }
    else if(SelectValueOne >= 0){
        if(SelectValueTwo > 80){
            //FrntBlueFlag
            Brain.Screen.clearLine(1, vex::color::blue);
            Brain.Screen.clearLine();
            Brain.Screen.print("N/A");
        }
        else if(SelectValueTwo > 50){
            //FrntBluePrk
            Brain.Screen.clearLine(1, vex::color::blue);
            Brain.Screen.clearLine();
            Brain.Screen.print("N/A");
        }
        else if(SelectValueTwo > 30){
            //none
            Brain.Screen.clearLine(1, vex::color::blue);
            Brain.Screen.clearLine();
            Brain.Screen.print("N/A");
        }
        else if(SelectValueTwo >= 0){
            //none
            Brain.Screen.clearLine(1, vex::color::blue);
            Brain.Screen.clearLine();
            Brain.Screen.print("N/A");
        }
      }
    }
    vex::task::sleep(100);
  }
}