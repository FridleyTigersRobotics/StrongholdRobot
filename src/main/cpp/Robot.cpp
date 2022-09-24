// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <frc/Joystick.h>
#include <frc/XboxController.h>
#include <frc/TimedRobot.h>
#include <frc/motorcontrol/PWMVictorSPX.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/motorcontrol/PWMSparkMax.h>
#include <frc/DoubleSolenoid.h>
#include <frc/PneumaticsControlModule.h>
#include <frc/Solenoid.h>
/**
 * This is a demo program showing the use of the DifferentialDrive class.
 * Runs the motors with arcade steering.
 */
class Robot : public frc::TimedRobot {
  //frc::XboxController m_stick{0};
  frc::Joystick m_stick{0};
  frc::DoubleSolenoid m_solenoidBallPusher{1, frc::PneumaticsModuleType::CTREPCM, 0, 1};
  frc::Solenoid       m_solenoidLift0     {1, frc::PneumaticsModuleType::CTREPCM, 2};
  frc::Solenoid       m_solenoidLift1     {1, frc::PneumaticsModuleType::CTREPCM, 3};

  frc::PWMVictorSPX m_left1{0};
  frc::PWMVictorSPX m_left2{2};
  frc::PWMVictorSPX m_right1{1};
  frc::PWMVictorSPX m_right2{3};

  frc::PWMVictorSPX m_shoot0{6};
  frc::PWMVictorSPX m_shoot1{7};

  // The motors on the left side of the drive
  frc::SpeedControllerGroup m_leftMotors{m_left1, m_left2};

  // The motors on the right side of the drive
  frc::SpeedControllerGroup m_rightMotors{m_right1, m_right2};

  // The robot's drive
  frc::DifferentialDrive m_drive{m_leftMotors, m_rightMotors};



 public:
  void RobotInit() override {
    // We need to invert one side of the drivetrain so that positive voltages
    // result in both sides moving forward. Depending on how your robot's
    // gearbox is constructed, you might have to invert the left side instead.
    m_rightMotors.SetInverted(true);
  }

  void TeleopPeriodic() override {
    // Drive with arcade style
    m_drive.ArcadeDrive(-m_stick.GetY(), m_stick.GetX());

    m_solenoidLift0.Set(m_stick.GetRawButton(3));
    m_solenoidLift1.Set(m_stick.GetRawButton(3));

    if (m_stick.GetRawButton(7)) 
    {
       m_shoot0.Set(0.8);
       m_shoot1.Set(-0.8);
    } 
    else 
    {
       m_shoot0.Set(0.0);
       m_shoot1.Set(0.0);
    }

    if (m_stick.GetRawButton(8)) 
    {
       m_solenoidBallPusher.Set(frc::DoubleSolenoid::kReverse);
    } 
    else 
    {
       m_solenoidBallPusher.Set(frc::DoubleSolenoid::kForward);
    }
  }
};

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
