#include "functions.h"

void junction_1(){
    while (junction_count < 2){
      Serial.println("meka                k");
      read_sensor_values();
      calculate_pid();
      motor_control();
        }
    followPath();
}
void junction_2(){
  bool distance_tof_less_than_100 = false; // Flag to track if distance_tof < 100 has been satisfied
  unsigned long start_time = millis();
  do {
    read_sensor_values();  
    while ((millis()-start_time)<100){
        calculate_pid();
        motor_control();
        read_sensor_values();
    }
    TCA9548A_tof_sensor(tof_front, 1); // Call the loop function of the MeasureDistanceTOF object 
    calculate_pid();
    motor_control();
    
    // Check if distance_tof < 100 and the condition hasn't been satisfied before
    if (distance_tof < 100 && !distance_tof_less_than_100 && distance_tof != 0) {
      distance_tof_less_than_100 = true; // Set the flag to true to indicate the condition has been satisfied
      analogWrite(leftmotor_pwm, 0); //Left Motor Speed
      analogWrite(rightmotor_pwm, 0); //Right Motor Speed
      Brake_fast();
      delay(2000); // Stop the bot for 2 seconds
      Serial.print("for timeing handle==1");
      dominant_front_color = TCA9548A_color_sensor(color_front);
      Serial.print("for timeing handle==1");
      while (junction_count < 3){
        read_sensor_values();
        calculate_pid();
        motor_control_reverse();
      }
      Serial.println("meeee");
      Serial.println(gyroDegree);
      followPath();
    }
    
  } while (!(distance_tof < 100) || (distance_tof == 0) );

}

void junction_3(){
    analogWrite(leftmotor_pwm, 0); //Left Motor Speed
    analogWrite(rightmotor_pwm, 0); //Right Motor Speed
    Brake_fast();
    delay(10);
    read_sensor_values();
    unsigned long start_time = millis();
    while ((millis()-start_time)<80){
      calculate_pid();
      motor_control();
      read_sensor_values();
    }
    motor_pos = 0;  motor_pos2 =0;
    Serial.println("for timeing handle");
    count_encoder(0.27);
    motor_pos = 0;  motor_pos2 =0;
    gyroDegree = 0;
    Serial.println("for timeing handle");
    TCA9548A_gyro(gyro,2);
    read_sensor_values();
    while (junction_count < 4){
          read_sensor_values();
          calculate_pid();
          motor_control();
          Serial.println("1111111111111111111111111111111");

    }
    Serial.println("for timeing handle");
    followPath();}

void junction_4(){
    analogWrite(leftmotor_pwm, 0); //Left Motor Speed
    analogWrite(rightmotor_pwm, 0); //Right Motor Speed
    Brake_fast();
    delay(10);
    motor_pos = 0;  motor_pos2 =0;
    delay(10);
    Serial.println("for timeing handle");
    count_encoder(0.28);
    Serial.println("for timeing handle");
    motor_pos = 0;  motor_pos2 =0;
    gyroDegree = 0;
    TCA9548A_gyro(gyro,3);
    while (junction_count < 5){
          read_sensor_values();
          calculate_pid();
          motor_control();
          Serial.println("22222222222222222222222222222");
          if (junction_count == 5){
            analogWrite(leftmotor_pwm, 0); //Left Motor Speed
            analogWrite(rightmotor_pwm, 0); //Right Motor Speed
            Brake_fast();
            delay(10);
            motor_pos = 0;  motor_pos2 =0;
            Serial.println("for timeing handle");
            count_encoder(0.45);
            Serial.println("for timeing handle");
            motor_pos = 0;  motor_pos2 =0;
            Serial.println("for timeing handle");
            TCA9548A_gyro(gyro,2);
            read_sensor_values();
          }
    }
    Serial.println("for timeing handle");
    followPath();}

void junction_5(){
    unsigned long start_time = millis();
    while (junction_count < 6){
      
      bool detect_color = false;
      while ((millis()-start_time)<80){
        read_sensor_values();
        calculate_pid();
        motor_control();
      }
      read_sensor_values();
      if (error == 150 && !detect_color){
        bool detect_color = true;
        analogWrite(leftmotor_pwm, 0); //Left Motor Speed
        analogWrite(rightmotor_pwm, 0); //Right Motor Speed
        Brake_fast();
        Serial.println("for timeing handle");
        delay(100);
        motor_pos = 0;  motor_pos2 =0;
        Serial.println("for timeing handle");
        count_encoder(0.27);
        Serial.println("for timeing handle");
        motor_pos = 0;  motor_pos2 =0;

        analogWrite(leftmotor_pwm, 0); //Left Motor Speed
        analogWrite(rightmotor_pwm, 0); //Right Motor Speed
        Brake_fast();
        Serial.println("for timeing handle");
        delay(800);

        dominant_down_left_color = TCA9548A_color_sensor(color_down_left);
        Serial.print("Dominante color  ");
        Serial.println(dominant_down_left_color);  
        Serial.println(" ");


        dominant_down_right_color = TCA9548A_color_sensor(color_down_right);
        Serial.print("Dominante color  ");
        Serial.println(dominant_down_right_color);
        Serial.println(" ");
        
        if (dominant_down_right_color == "Red" || dominant_down_left_color == "Red" || dominant_down_right_color == "Unknown" || dominant_down_left_color == "Unknown"  ){
          digitalWrite(b_green,HIGH);
          analogWrite(leftmotor_pwm, 50); //Left Motor Speed
          analogWrite(rightmotor_pwm, 50+32); //Right Motor Speed
          motor_control_reverse();
          Serial.println("for timeing handle");
          delay(1500);
          analogWrite(leftmotor_pwm, 0); //Left Motor Speed
          analogWrite(rightmotor_pwm, 0); //Right Motor Speed
          Brake_fast();
          delay(50);
          while (junction_count < 6){
            read_sensor_values();
            calculate_pid();
            motor_control_reverse();
            if(junction_count == 6){
              junction_count--;
              followPath();

            }
            }
            }
          
        if((dominant_down_right_color == "Blue" && dominant_down_left_color == "Blue") || (dominant_down_right_color == "Green" && dominant_down_left_color == "Green") ){
          digitalWrite(b_blue,HIGH);
          motor_pos = 0;  motor_pos2 =0;
          Serial.println("for timeing handle");
          count_encoder(-0.5);
          Serial.println("for timeing handle");
          motor_pos = 0;  motor_pos2 =0;
          analogWrite(leftmotor_pwm, 0); //Left Motor Speed
          analogWrite(rightmotor_pwm, 0); //Right Motor Speed
          Brake_fast();
          delay(50);
          while (junction_count < 6){
            read_sensor_values();
            calculate_pid();
            motor_control_reverse();
            if(junction_count == 6){
              junction_count--;
              followPath();

            }
            }
            }


        motor_pos = 0;  motor_pos2 =0;
        Serial.println("for timeing handle");
        count_encoder(0.65);
        Serial.println("for timeing handle");
        motor_pos = 0;  motor_pos2 =0;
        junction_count++;
        followPath();
      }
      Serial.println("array eka");
      calculate_pid();
      motor_control();
    }

    Serial.println("for timeing handle");}

void junction_6_right(){
      TCA9548A_gyro(gyro,3);
      read_sensor_values();
      if (junction_count <7){
        unsigned long start_time = millis();
        while ((millis()-start_time)<80){
          calculate_pid();
          motor_control();
          read_sensor_values();
        }
        Serial.println("if (junction_count <7)");
        // motor_pos = 0;
        // Serial.println("for timeing handle");
        // count_encoder(0.45);
        // Serial.println("for timeing handle");
        // motor_pos = 0;;
        while(junction_count <7){
          read_sensor_values();
          calculate_pid();
          motor_control();
          Serial.println("while(junction_count <7)");
          if(junction_count == 7){
            motor_pos = 0;  motor_pos2 =0;
            Serial.println("for timeing handle");
            count_encoder(0.38);
            motor_pos = 0;  motor_pos2 =0;
            TCA9548A_gyro(gyro,2);
            Serial.println("if (junction_count ========7)");
          }
        }
        }
      if (junction_count <8){
        Serial.println("if (junction_count <8)");
        while(junction_count <8){
        read_sensor_values();
        calculate_pid();
        motor_control();
        Serial.println("while(junction_count <8)");
        if(junction_count == 8){
          initial_motor_speed = 50;
          Serial.println("Initial Motor Speed: " + String(initial_motor_speed));
          motor_pos = 0;  motor_pos2 =0;
          Serial.println("for timeing handle");
          count_encoder(0.4);
          motor_pos = 0;  motor_pos2 =0;
          TCA9548A_gyro(gyro,4);
          Serial.println("if (junction_count ===========8)");
        }
      }
      }
      if (junction_count <9){
        float threshold = 2.5;
        unsigned long start_time = millis();
        Serial.println("if (junction_count <9)");
        while (junction_count < 9){
          read_sensor_values();
          calculate_pid();
          motor_control();
          Serial.println("Initial Motor Speed: " + String(initial_motor_speed));
          if ((millis()-start_time > 2000) && (millis()-start_time < 12600)){
            digitalWrite( b_red,HIGH);
            sharp_ir_ultra_loop();
            read_sensor_values();
            calculate_pid();
            motor_control();
            Serial.println("Initial Motor Speed: " + String(initial_motor_speed));
            Serial.println(" if ((millis()-start_time > 3000) && (millis()-start_time < 13000))");
          if(millis()-start_time > 12500){
            digitalWrite( b_red,LOW);
            sharp_ir_ultra_loop();
            read_sensor_values();
            calculate_pid();
            motor_control();
            Serial.println(" inside loop ");
            float variance = calculateStatistics();
            if (variance   < threshold ){
              digitalWrite(a_green,HIGH);
              // delay(5000);
            }
            else{
              digitalWrite(a_blue,HIGH);
              // delay(5000);
            } 
          }
          }
          if(junction_count ==9){
            Serial.println("if (junction_count =======9)");
            read_sensor_values();
            analogWrite(leftmotor_pwm, 0); //Left Motor Speed
            analogWrite(rightmotor_pwm, 0); //Right Motor Speed
            Brake_fast();
            delay(10);
            motor_pos = 0;  motor_pos2 =0;
            Serial.println("for timeing handle");
            count_encoder(0.18);
            Serial.println("for timeing handle");
            motor_pos = 0;  motor_pos2 =0;
            gyroDegree = 0;
            TCA9548A_gyro(gyro,4);
            initial_motor_speed = 150;

            while (junction_count < 10){
              read_sensor_values();
              calculate_pid();
              motor_control();
              if (junction_count == 10){
                motor_pos = 0;  motor_pos2 =0;
                Serial.println("for timeing handle");
                count_encoder(0.4);
                Serial.println("for timeing handle");
                motor_pos = 0;  motor_pos2 =0;
                gyroDegree = 0;
                TCA9548A_gyro(gyro,3);
                while (junction_count < 11){
                  read_sensor_values();
                  calculate_pid();
                  motor_control();
                  if (junction_count == 11){
                    motor_pos = 0;  motor_pos2 =0;
                    Serial.println("for timeing handle");
                    count_encoder(0.5);
                    Serial.println("for timeing handle");
                    motor_pos = 0;  motor_pos2 =0;
                    gyroDegree = 0;
                    TCA9548A_gyro(gyro,3);
                    followPath();
                    }
            }
            Serial.println("for timeing handle");
          }
      }
      }
      Serial.println("for timeing handle");
    }
}
}


void junction_6_left(){
      TCA9548A_gyro(gyro,2);
      read_sensor_values();
      if (junction_count <7){
        unsigned long start_time = millis();
        while ((millis()-start_time)<80){
          calculate_pid();
          motor_control();
          read_sensor_values();
        }
        Serial.println("if (junction_count <7)");
        // motor_pos = 0;
        // Serial.println("for timeing handle");
        // count_encoder(0.45);
        // Serial.println("for timeing handle");
        // motor_pos = 0;;
        while(junction_count <7){
          read_sensor_values();
          calculate_pid();
          motor_control();
          Serial.println("while(junction_count <7)");
          if(junction_count == 7){
            motor_pos = 0;  motor_pos2 =0;
            Serial.println("for timeing handle");
            count_encoder(0.38);
            motor_pos = 0;  motor_pos2 =0;
            TCA9548A_gyro(gyro,3);
            Serial.println("if (junction_count ========7)");
          }
        }
        }
      if (junction_count <8){
        Serial.println("if (junction_count <8)");
        while(junction_count <8){
        read_sensor_values();
        calculate_pid();
        motor_control();
        Serial.println("while(junction_count <8)");
        if(junction_count == 8){
          initial_motor_speed = 50;
          Serial.println("Initial Motor Speed: " + String(initial_motor_speed));
          motor_pos = 0;  motor_pos2 =0;
          Serial.println("for timeing handle");
          count_encoder(0.4);
          motor_pos = 0;  motor_pos2 =0;
          TCA9548A_gyro(gyro,4);
          Serial.println("if (junction_count ===========8)");
        }
      }
      }
      if (junction_count <9){
        float threshold = 2.5;
        unsigned long start_time = millis();
        Serial.println("if (junction_count <9)");
        while (junction_count < 9){
          read_sensor_values();
          calculate_pid();
          motor_control();
          Serial.println("while(junction_count <8)");
          Serial.println("Initial Motor Speed: " + String(initial_motor_speed));
          if ((millis()-start_time > 2000) && (millis()-start_time < 12600)){
            digitalWrite( b_red,HIGH);
            sharp_ir_ultra_loop();
            read_sensor_values();
            calculate_pid();
            motor_control();
            Serial.println("Initial Motor Speed: " + String(initial_motor_speed));
            Serial.println(" if ((millis()-start_time > 3000) && (millis()-start_time < 13000))");
          if(millis()-start_time > 12500){
            digitalWrite( b_red,LOW);
            sharp_ir_ultra_loop();
            read_sensor_values();
            calculate_pid();
            motor_control();
            Serial.println(" inside loop ");
            float variance = calculateStatistics();
            if (variance   < threshold ){
              digitalWrite(a_green,HIGH);
              // delay(5000);
            }
            else{
              digitalWrite(a_blue,HIGH);
              // delay(5000);
            } 
          }
          }
          if(junction_count ==9){
            Serial.println("if (junction_count =======9)");
            read_sensor_values();
            analogWrite(leftmotor_pwm, 0); //Left Motor Speed
            analogWrite(rightmotor_pwm, 0); //Right Motor Speed
            Brake_fast();
            delay(10);
            motor_pos = 0;  motor_pos2 =0;
            Serial.println("for timeing handle");
            count_encoder(0.30);
            Serial.println("for timeing handle");
            motor_pos = 0;  motor_pos2 =0;
            gyroDegree = 0;
            TCA9548A_gyro(gyro,4);
            initial_motor_speed = 150;
            Serial.println("Initial Motor Speed: " + String(initial_motor_speed));

            while (junction_count < 10){
              read_sensor_values();
              calculate_pid();
              motor_control();
              if (junction_count == 10){
                motor_pos = 0;  motor_pos2 =0;
                Serial.println("for timeing handle");
                count_encoder(0.4);
                Serial.println("for timeing handle");
                motor_pos = 0;  motor_pos2 =0;
                gyroDegree = 0;
                TCA9548A_gyro(gyro,2);
                while (junction_count < 11){
                  read_sensor_values();
                  calculate_pid();
                  motor_control();
                  if (junction_count == 11){
                    motor_pos = 0;  motor_pos2 =0;
                    Serial.println("for timeing handle");
                    count_encoder(0.5);
                    Serial.println("for timeing handle");
                    motor_pos = 0;  motor_pos2 =0;
                    gyroDegree = 0;
                    TCA9548A_gyro(gyro,2);
                    followPath();
                    }
            }
            Serial.println("for timeing handle");
          }
      }
      }
      Serial.println("for timeing handle");
    }
  }}