#include "gyro.h"

MPU6050 gyroAccelTemp;

#define GYRO_Z_OFFSET 16
float gyroCalibrationFactor = 1; // Adjust this calibration factor empirically
bool isFirstLoopComplete;
float previousTime;

void gyro_setup() {
  Wire.begin();
  gyroAccelTemp.initialize();
  Serial.println("Testing device connections...");
  Serial.println(gyroAccelTemp.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  gyroAccelTemp.CalibrateGyro();
  Serial.println("Calibration complete");
  gyroAccelTemp.setZGyroOffset(GYRO_Z_OFFSET);
  gyroAccelTemp.CalibrateGyro(6);
  Serial.println("Fine Tuning Complete");
  isFirstLoopComplete = false;
}

float gyro_loop() {
  float gyroZ = gyroAccelTemp.getRotationZ() / 131.0 * gyroCalibrationFactor; // Apply calibration factor

  if (isFirstLoopComplete) {
    float timeForOneLoop = micros() - previousTime;
    gyroDegree += gyroZ * timeForOneLoop / 1000000.0;
  }
  previousTime = micros();
  
  if (!isFirstLoopComplete) {
    isFirstLoopComplete = true;
  }

  Serial.print("gyroDegree      ");
  Serial.println(gyroDegree);
  return gyroDegree;
}


void sharp_turns(int a) {
  if (a == 1) {
    float currentAngle = 0.0;
    int targetAngle = 170;
    float initialGyroValue = gyroAccelTemp.getRotationZ() / 131.0 * gyroCalibrationFactor;
    unsigned long previousTime = micros(); // Initialize previousTime here

    while (currentAngle < targetAngle) { // Loop until currentAngle reaches targetAngle
      float gyroZ = gyroAccelTemp.getRotationZ() / 131.0 * gyroCalibrationFactor;
      unsigned long currentTime = micros();
      float timeForOneLoop = currentTime - previousTime;
      currentAngle += gyroZ * timeForOneLoop / 1000000.0;
      analogWrite(leftmotor_pwm, 150); //Left Motor Speed
      analogWrite(rightmotor_pwm, 150+38); //Right Motor Speed
      // Read the gyroscope value
      sharpLeftTurn();
      Serial.print("currentAngle   ");
      Serial.println(currentAngle);
      // Adjust the robot's movement based on the deviation from the target angle
      // Here, you may implement your robot's rotation control mechanism,
      // such as adjusting motor speeds or applying appropriate corrections.

      previousTime = currentTime; // Update previousTime

      // Add a break condition in case the target angle is overshot
      if (currentAngle >= targetAngle) {
        break;
      }
    }

    // Stop the robot after reaching the target angle
    // Implement code to stop robot rotation.
    analogWrite(leftmotor_pwm, 0); //Left Motor Speed
    analogWrite(rightmotor_pwm, 0); //Right Motor Speed
    Brake_fast();
    delay(100);
    
    Serial.println("for timing handle-2");
    return;
  }
  else if (a == 2){
    float currentAngle = 0.0;
    int targetAngle = 70;
    float initialGyroValue = gyroAccelTemp.getRotationZ() / 131.0 * gyroCalibrationFactor;
    unsigned long previousTime = micros(); // Initialize previousTime here

    while (currentAngle < targetAngle) { // Loop until currentAngle reaches targetAngle
      float gyroZ = gyroAccelTemp.getRotationZ() / 131.0 * gyroCalibrationFactor;
      unsigned long currentTime = micros();
      float timeForOneLoop = currentTime - previousTime;
      currentAngle += gyroZ * timeForOneLoop / 1000000.0;
      analogWrite(leftmotor_pwm, 150); //Left Motor Speed
      analogWrite(rightmotor_pwm, 150+38); //Right Motor Speed
      // Read the gyroscope value
      sharpLeftTurn();
      Serial.print("currentAngle   ");
      Serial.println(currentAngle);
      // Adjust the robot's movement based on the deviation from the target angle
      // Here, you may implement your robot's rotation control mechanism,
      // such as adjusting motor speeds or applying appropriate corrections.

      previousTime = currentTime; // Update previousTime

      // Add a break condition in case the target angle is overshot
      if (currentAngle >= targetAngle) {
        break;
      }
    }

    // Stop the robot after reaching the target angle
    // Implement code to stop robot rotation.
    analogWrite(leftmotor_pwm, 0); //Left Motor Speed
    analogWrite(rightmotor_pwm, 0); //Right Motor Speed
    Brake_fast();
    delay(100);
    read_sensor_values();
    if(error = +160){
    analogWrite(leftmotor_pwm, 150); //Left Motor Speed
    analogWrite(rightmotor_pwm, 188); //Right Motor Speed
    left();
    delay(80);
    }
    Serial.println("for timing handle-2");
    return;
  }
  else if (a == 3) {
    float currentAngle = 0.0;
    int targetAngle = -70;
    float initialGyroValue = gyroAccelTemp.getRotationZ() / 131.0 * gyroCalibrationFactor;
    unsigned long previousTime = micros(); // Initialize previousTime here

    while (currentAngle > targetAngle) { // Loop until currentAngle reaches or goes below targetAngle
        float gyroZ = gyroAccelTemp.getRotationZ() / 131.0 * gyroCalibrationFactor;
        unsigned long currentTime = micros();
        float timeForOneLoop = currentTime - previousTime;
        currentAngle += gyroZ * timeForOneLoop / 1000000.0;
      analogWrite(leftmotor_pwm, 150); //Left Motor Speed
      analogWrite(rightmotor_pwm, 150+38); //Right Motor Speed
        // Read the gyroscope value
        sharpRightTurn();
        Serial.print("currentAngle   ");
        Serial.println(currentAngle);
        // Adjust the robot's movement based on the deviation from the target angle
        // Here, you may implement your robot's rotation control mechanism,
        // such as adjusting motor speeds or applying appropriate corrections.

        previousTime = currentTime; // Update previousTime
        if (currentAngle <= targetAngle) {
        break;
      }
    }

    // Stop the robot after reaching the target angle or going below it
    // Implement code to stop robot rotation.
    analogWrite(leftmotor_pwm, 0); // Left Motor Speed
    analogWrite(rightmotor_pwm, 0); // Right Motor Speed
    Brake_fast();
    delay(100);
    read_sensor_values();
    if(error = -160){
    analogWrite(leftmotor_pwm, 150); //Left Motor Speed
    analogWrite(rightmotor_pwm, 188); //Right Motor Speed
    right();
    delay(80);
    }
    Serial.println("for timing handle-2");
    return;
  }
  else if (a == 4) {
    float currentAngle = 0.0;
    int targetAngle = -60;
    float initialGyroValue = gyroAccelTemp.getRotationZ() / 131.0 * gyroCalibrationFactor;
    unsigned long previousTime = micros(); // Initialize previousTime here

    while (currentAngle > targetAngle) { // Loop until currentAngle reaches or goes below targetAngle
        float gyroZ = gyroAccelTemp.getRotationZ() / 131.0 * gyroCalibrationFactor;
        unsigned long currentTime = micros();
        float timeForOneLoop = currentTime - previousTime;
        currentAngle += gyroZ * timeForOneLoop / 1000000.0;
      analogWrite(leftmotor_pwm, 150); //Left Motor Speed
      analogWrite(rightmotor_pwm, 150+38); //Right Motor Speed
        // Read the gyroscope value
        sharpRightTurn();
        Serial.print("currentAngle   ");
        Serial.println(currentAngle);
        // Adjust the robot's movement based on the deviation from the target angle
        // Here, you may implement your robot's rotation control mechanism,
        // such as adjusting motor speeds or applying appropriate corrections.

        previousTime = currentTime; // Update previousTime
        if (currentAngle <= targetAngle) {
        break;
      }
    }

    // Stop the robot after reaching the target angle or going below it
    // Implement code to stop robot rotation.
    analogWrite(leftmotor_pwm, 0); // Left Motor Speed
    analogWrite(rightmotor_pwm, 0); // Right Motor Speed
    Brake_fast();
    delay(100);
    Serial.println("for timing handle-2");
    return;
  }
}
