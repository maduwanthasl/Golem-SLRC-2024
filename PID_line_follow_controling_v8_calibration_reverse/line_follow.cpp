#include "line_follow.h"

void followPath(){
  Serial.println("for makea");
  read_sensor_values();
  ColorSensor colorSensor; // Create an instance of the ColorSensor class
  if (junction_count ==1){
    junction_1();
  }
  else if (junction_count == 2 ) { 
    junction_2();
  } 
  else if (junction_count == 3 ){
    junction_3();
  }
    
  else if (junction_count == 4 ){
    junction_4();
  }

  ////color junction /////////////
  else if (junction_count == 5 ){
    junction_5();
  }

  //junction count 6 // this start with color junction 
  else if (junction_count == 6 ){
    analogWrite(leftmotor_pwm, 0); //Left Motor Speed
    analogWrite(rightmotor_pwm, 0); //Right Motor Speed
    Brake_fast();
    delay(100);
    Serial.println("000000");
    //////////////////////////right side/////////////////////////
    if (dominant_down_right_color == dominant_front_color){
      junction_6_right();
      }

    ///////////////////////left side///////////////////////
    else if (dominant_down_left_color == dominant_front_color){
      junction_6_left();
      
 }
}


else if (junction_count ==11){
  Serial.println("if (junction_count 11)");
  while(junction_count <12){
  read_sensor_values();
  calculate_pid();
  motor_control();
  Serial.println("while(junction_count <12)");
  if(junction_count == 12){
    motor_pos = 0;
    motor_pos2 =0;
    Serial.println("for timeing handle");
    count_encoder(0.4);
    motor_pos = 0;
    motor_pos2 =0;
    TCA9548A_gyro(gyro,3);
    Serial.println("if (junction_count ===========12)");
  }
}
}

else if (junction_count ==12){
  Serial.println("if (junction_count =======================12)");
  unsigned long start_time = millis();
  while(millis()-start_time < 80){
  read_sensor_values();
  calculate_pid();
  motor_control();
  Serial.println("while(junction_count <13)");
  }
  stop_bot();
  delay(1000);
  mg995_down();
  
  while(junction_count <13){
    read_sensor_values();  
    calculate_pid();
    motor_control();
    Serial.println("while(junction_count <13)");
    if (error==150) {
      analogWrite(leftmotor_pwm, 0); //Left Motor Speed
      analogWrite(rightmotor_pwm, 0); //Right Motor Speed
      delay(50); // Stop the bot for 2 seconds
      Brake_fast();   
      mg995_down_2();
      mg90_close();  
      delay(1000);
      if(digitalRead(metal_out) ==1){
        mg995_up();
        delay(2000);;
        TCA9548A_gyro(gyro,1);
        while(junction_count <13){
          read_sensor_values();  
          calculate_pid();
          motor_control();
          Serial.println("while(junction_count <13)");
          if(junction_count == 13){
            unsigned long start_time = millis();
            while(millis()-start_time < 200){
            read_sensor_values();
            calculate_pid();
            motor_control();
            Serial.println("while(junction_count <13)");
            }
            motor_pos = 0;
            motor_pos2 =0;
            Serial.println("for timeing handle");
            count_encoder(0.05);
            motor_pos = 0;
            motor_pos2 =0;
            TCA9548A_gyro(gyro,2);
            followPath();
          }
        }

      }else{
        motor_pos = 0;
        motor_pos2 =0;
        Serial.println("for timeing handle");
        count_encoder(-0.25);
        motor_pos = 0;
        motor_pos2 =0;
        stop_bot();
        delay(1500);
        mg90_open();
        mg995_up_2();
        motor_pos = 0;
        motor_pos2 =0;
        Serial.println("for timeing handle");
        count_encoder(-0.35);
        motor_pos = 0;  
        motor_pos2 =0;
        TCA9548A_gyro(gyro,1);
        while(junction_count <13){
          read_sensor_values();  
          calculate_pid();
          motor_control();
          Serial.println("while(junction_count <13)");
          if(junction_count == 13){
            unsigned long start_time = millis();
            while(millis()-start_time < 200){
            read_sensor_values();
            calculate_pid();
            motor_control();
            Serial.println("while(junction_count <13)");
            }
            motor_pos = 0;
            motor_pos2 =0;
            Serial.println("for timeing handle");
            count_encoder(0.2);
            motor_pos = 0;
            motor_pos2 =0;
            TCA9548A_gyro(gyro,3);
            junction_count--;
            while(junction_count <13){
              read_sensor_values();  
              calculate_pid();
              motor_control();
              Serial.println("while(junction_count <13)");
              if (error==150) {
                analogWrite(leftmotor_pwm, 0); //Left Motor Speed
                analogWrite(rightmotor_pwm, 0); //Right Motor Speed
                delay(50); // Stop the bot for 2 seconds
                Brake_fast();   
                mg995_down_2();
                mg90_close();  
                delay(1000);
                if(digitalRead(metal_out) ==1){
                  mg995_up();
                  delay(2000);
                  TCA9548A_gyro(gyro,1);
                  while(junction_count <13){
                    read_sensor_values();
                    calculate_pid();
                    motor_control();
                    if(junction_count == 13){
                      unsigned long start_time = millis();
                      while(millis()-start_time < 200){
                      read_sensor_values();
                      calculate_pid();
                      motor_control();
                      Serial.println("while(junction_count <13)");
                      }
                      motor_pos = 0;  motor_pos2 =0;
                      Serial.println("for timeing handle");
                      count_encoder(0.25);
                      motor_pos = 0;  motor_pos2 =0;
                      followPath();}}
                      }else{
                        motor_pos = 0;  motor_pos2 =0;
                        Serial.println("for timeing handle");
                        count_encoder(-0.25);
                        motor_pos = 0;  motor_pos2 =0;
                        stop_bot();
                        delay(1500);
                        mg90_open();
                        mg995_up_2();
                        motor_pos = 0;  motor_pos2 =0;
                        Serial.println("for timeing handle");
                        count_encoder(-0.35);
                        motor_pos = 0;    motor_pos2 =0;
                        TCA9548A_gyro(gyro,1);
                        while(junction_count <13){
                          read_sensor_values();  
                          calculate_pid();
                          motor_control();
                          Serial.println("while(junction_count <13)");
                          if(junction_count == 13){
                            unsigned long start_time = millis();
                            while(millis()-start_time < 200){
                            read_sensor_values();
                            calculate_pid();
                            motor_control();
                            Serial.println("while(junction_count <13)");
                            }
                            motor_pos = 0;  motor_pos2 =0;
                            Serial.println("for timeing handle");
                            count_encoder(0.2);
                            motor_pos = 0;  motor_pos2 =0;
                            TCA9548A_gyro(gyro,3);
                            junction_count--;
                            while(junction_count <13){
                              read_sensor_values();  
                              calculate_pid();
                              motor_control();
                              Serial.println("while(junction_count <13)");
                              if (error==150) {
                                analogWrite(leftmotor_pwm, 0); //Left Motor Speed
                                analogWrite(rightmotor_pwm, 0); //Right Motor Speed
                                delay(50); // Stop the bot for 2 seconds
                                Brake_fast();   
                                mg995_down_2();
                                mg90_close();  
                                delay(1000);
                                if(digitalRead(metal_out) ==1){
                                  mg995_up();
                                  delay(2000);
                                  TCA9548A_gyro(gyro,1);
                                  while(junction_count <13){
                                    read_sensor_values();
                                    calculate_pid();
                                    motor_control();
                                    if(junction_count == 13){
                                      unsigned long start_time = millis();
                                      while(millis()-start_time < 200){
                                      read_sensor_values();
                                      calculate_pid();
                                      motor_control();
                                      Serial.println("while(junction_count <13)");
                                      }
                                      motor_pos = 0;  motor_pos2 =0;
                                      Serial.println("for timeing handle");
                                      count_encoder(0.25);
                                      motor_pos = 0;  motor_pos2 =0;
                                      TCA9548A_gyro(gyro,3);
                                      followPath();}}}}}}}
                      }
                      }
                    }
        }

      }


      }
      

      
    } 
  }

}

else if (junction_count ==13){
  Serial.println("if (junction_count 11)");
  while(junction_count <14){
  read_sensor_values();
  calculate_pid();
  motor_control();
  Serial.println("while(junction_count <12)");
  if(error == 150){
    motor_pos = 0;  motor_pos2 =0;
    Serial.println("for timeing handle");
    count_encoder(0.4);
    motor_pos = 0;  motor_pos2 =0;
    Serial.println("if (junction_count ===========12)");
    while(junction_count <14){
    read_sensor_values();
    calculate_pid();
    motor_control();
    Serial.println("while(junction_count <12)");
    if(junction_count == 14){
      motor_pos = 0;  motor_pos2 =0;
      Serial.println("for timeing handle");
      count_encoder(0.4);
      motor_pos = 0;  motor_pos2 =0;
      TCA9548A_gyro(gyro,2);
      Serial.println("if (junction_count ===========12)");
      followPath();
  }
}

  }
}
}
else if (junction_count ==14){
  Serial.println("if (junction_count 11)");
  bool distance_tof_less_than_100 = false; // Flag to track if distance_tof < 100 has been satisfied
  unsigned long start_time = millis();
  while ((millis()-start_time)<400){
      calculate_pid();
      motor_control();
      read_sensor_values();}
  do {
    read_sensor_values(); 
    TCA9548A_tof_sensor(tof_front, 1); // Call the loop function of the MeasureDistanceTOF object 
    calculate_pid();
    motor_control();
    if (distance_tof < 250 && !distance_tof_less_than_100 && distance_tof != 0) {
      distance_tof_less_than_100 = true; // Set the flag to true to indicate the condition has been satisfied
      analogWrite(leftmotor_pwm, 0); //Left Motor Speed
      analogWrite(rightmotor_pwm, 0); //Right Motor Speed
      Brake_fast();
      delay(4000); // Stop the bot for 2 seconds
      Serial.print("for timeing handle==1");
      mg995_down();
      mg995_down_2();
      mg90_open();
      mg995_up_2();
      mg995_up();
      unsigned long start_time = millis();
      while ((millis()-start_time)<800){
          calculate_pid();
          motor_control();
          read_sensor_values();}
      motor_pos = 0;  motor_pos2 =0;
      count_encoder(-0.3);
      TCA9548A_gyro(gyro,1);
      while (junction_count < 15){
        read_sensor_values();
        calculate_pid();
        motor_control();
        if(junction_count==15){
          motor_pos = 0;  motor_pos2 =0;
          count_encoder(0.4);
          TCA9548A_gyro(gyro,2);
          followPath();
        }
        
      }
      Serial.println("meeee");      
    }
    
  } while (!(distance_tof < 250) || (distance_tof == 0) );

}
else if (junction_count ==15){
  Serial.println("if (junction_count 11)");
  while(junction_count <16){
  read_sensor_values();
  calculate_pid();
  motor_control();
  Serial.println("while(junction_count <12)");
  if(junction_count == 16){
    motor_pos = 0;  motor_pos2 =0;
    Serial.println("for timeing handle");
    count_encoder(0.3);
    motor_pos = 0;  motor_pos2 =0;
    Serial.println("if (junction_count ===========12)");
    digitalWrite(b_red,HIGH);
  }
}
}

  //         analogWrite(leftmotor_pwm, 70); //Changed from ENA
  //         analogWrite(rightmotor_pwm, 70); //Changed from ENB
  //         sharpLeftTurn();
  //       } while (error != 0 && error != -1 && error != 1);
  //     }
  //   }
  // } 
  else {
    calculate_pid();
    motor_control();
    read_sensor_values();
    Serial.println("55555555555512)");


  }
}