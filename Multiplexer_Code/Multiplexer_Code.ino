// Extend Analog Inputs for NodeMCU board using 16 channel Analog Multiplexer

// Note Summary
// Note : Safety is very important when dealing with electricity. We take no responsibilities while you do it at your own risk.
// Note : NodeMCU is a very famous micro-controller with Wifi function which is commonly used for Internet Of Thing (IOT) application. 
// Note : However,NodeMCU only has one analog input which only allow to read one analog sensor.  
// Note : This code is made practical to convert 1 Analog Input to up to 16 Analog Inputs using the 16-channel Analog Multiplexer Module.
// Note : The main code for 16 channel Analog Multiplexer was Written by Sachin Soni for techiesms YouTube channel & community (https://www.youtube.com/watch?v=02spXPoa_Y8)
// Note : Solarduino is only to modify the code to suit our own undertanding and application.
 
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/////////////*/


    /* 0- General */

    #define S0 D0                             /* Assign Multiplexer pin S0 connect to pin D0 of NodeMCU */
    #define S1 D1                             /* Assign Multiplexer pin S1 connect to pin D1 of NodeMCU */
    #define S2 D2                             /* Assign Multiplexer pin S2 connect to pin D2 of NodeMCU */
    #define S3 D3                             /* Assign Multiplexer pin S3 connect to pin D3 of NodeMCU */
    #define SIG A0                            /* Assign SIG pin as Analog output for all 16 channels of Multiplexer to pin A0 of NodeMCU */

    int decimal = 2;                          // Decimal places of the sensor value outputs 
    int sensor0;                            /* Assign the name "sensor0" as analog output value from Channel C0 */
    int sensor1;                            /* Assign the name "sensor1" as analog output value from Channel C1 */
    int sensor2;                            /* Assign the name "sensor2" as analog output value from Channel C2 */
    int sensor3;                            /* Assign the name "sensor3" as analog output value from Channel C3 */
    int sensor4;                            /* Assign the name "sensor4" as analog output value from Channel C4 */
    int sensor5;                            /* Assign the name "sensor5" as analog output value from Channel C5 */
    int sensor6;                            /* Assign the name "sensor6" as analog output value from Channel C6 */
    int sensor7;                            /* Assign the name "sensor7" as analog output value from Channel C7 */
    int sensor8;                            /* Assign the name "sensor8" as analog output value from Channel C8 */
    int sensor9;                            /* Assign the name "sensor9" as analog output value from Channel C9 */
    int sensor10;                           /* Assign the name "sensor10" as analog output value from Channel C10 */
    int sensor11;                           /* Assign the name "sensor11" as analog output value from Channel C11 */
    int sensor12;                           /* Assign the name "sensor12" as analog output value from Channel C12 */
    int sensor13;                           /* Assign the name "sensor13" as analog output value from Channel C13 */
    int sensor14;                           /* Assign the name "sensor14" as analog output value from Channel C14 */
    int sensor15;                           /* Assign the name "sensor15" as analog output value from Channel C15 */


void setup() {                                /* Put your codes here to run only once during micro controller startup */

    /* 0- General */
    
    pinMode(S0,OUTPUT);                       /* Define digital signal pin as output to the Multiplexer pin SO */        
    pinMode(S1,OUTPUT);                       /* Define digital signal pin as output to the Multiplexer pin S1 */  
    pinMode(S2,OUTPUT);                       /* Define digital signal pin as output to the Multiplexer pin S2 */ 
    pinMode(S3,OUTPUT);                       /* Define digital signal pin as output to the Multiplexer pin S3 */  
    pinMode(SIG, INPUT);                      /* Define analog signal pin as input or receiver from the Multiplexer pin SIG */  
    
    Serial.begin(9600);                       /* to display readings in Serial Monitor at 9600 baud rates */

}

void loop() {                                 /* Put your codes here to run over and over again endlessly */

    /* 0- General */

    // Channel 0 (C0 pin - binary output 0,0,0,0)
    digitalWrite(S0,LOW); digitalWrite(S1,LOW); digitalWrite(S2,LOW); digitalWrite(S3,LOW);
    sensor0 = analogRead(SIG);
  
    // Channel 1 (C1 pin - binary output 1,0,0,0)
    digitalWrite(S0,HIGH); digitalWrite(S1,LOW); digitalWrite(S2,LOW); digitalWrite(S3,LOW);
    sensor1 = analogRead(SIG);
  
    // Channel 2 (C2 pin - binary output 0,1,0,0)
    digitalWrite(S0,LOW); digitalWrite(S1,HIGH); digitalWrite(S2,LOW); digitalWrite(S3,LOW);
    sensor2 = analogRead(SIG);
  
    // Channel 3 (C3 pin - binary output 1,1,0,0)
    digitalWrite(S0,HIGH); digitalWrite(S1,HIGH); digitalWrite(S2,LOW); digitalWrite(S3,LOW);
    sensor3 = analogRead(SIG);
  
    // Channel 4 (C4 pin - binary output 0,0,1,0)
    digitalWrite(S0,LOW); digitalWrite(S1,LOW); digitalWrite(S2,HIGH); digitalWrite(S3,LOW);
    sensor4 = analogRead(SIG);
  
    // Channel 5 (C5 pin - binary output 1,0,1,0)
    digitalWrite(S0,HIGH); digitalWrite(S1,LOW); digitalWrite(S2,HIGH); digitalWrite(S3,LOW);
    sensor5 = analogRead(SIG);

    // Channel 6 (C6 pin - binary output 0,1,1,0)
    digitalWrite(S0,LOW); digitalWrite(S1,HIGH); digitalWrite(S2,HIGH); digitalWrite(S3,LOW);
    sensor6 = analogRead(SIG);

    // Channel 7 (C7 pin - binary output 1,1,1,0)
    digitalWrite(S0,HIGH); digitalWrite(S1,HIGH); digitalWrite(S2,HIGH); digitalWrite(S3,LOW);
    sensor7 = analogRead(SIG);

    // Channel 8 (C8 pin - binary output 0,0,0,1)
    digitalWrite(S0,LOW); digitalWrite(S1,LOW); digitalWrite(S2,LOW); digitalWrite(S3,HIGH);
    sensor8 = analogRead(SIG);

    // Channel 9 (C9 pin - binary output 1,0,0,1)
    digitalWrite(S0,HIGH); digitalWrite(S1,LOW); digitalWrite(S2,LOW); digitalWrite(S3,HIGH);
    sensor9 = analogRead(SIG);

    // Channel 10 (C10 pin - binary output 0,1,0,1)
    digitalWrite(S0,LOW); digitalWrite(S1,HIGH); digitalWrite(S2,LOW); digitalWrite(S3,HIGH);
    sensor10 = analogRead(SIG);

    // Channel 11 (C11 pin - binary output 1,1,0,1)
    digitalWrite(S0,HIGH); digitalWrite(S1,HIGH); digitalWrite(S2,LOW); digitalWrite(S3,HIGH);
    sensor11 = analogRead(SIG);

    // Channel 12 (C12 pin - binary output 0,0,1,1)
    digitalWrite(S0,LOW); digitalWrite(S1,LOW); digitalWrite(S2,HIGH); digitalWrite(S3,HIGH);
    sensor12 = analogRead(SIG);

    // Channel 13 (C13 pin - binary output 1,0,1,1)
    digitalWrite(S0,HIGH); digitalWrite(S1,LOW); digitalWrite(S2,HIGH); digitalWrite(S3,HIGH);
    sensor13 = analogRead(SIG);

    // Channel 14 (C14 pin - binary output 0,1,1,1)
    digitalWrite(S0,LOW); digitalWrite(S1,HIGH); digitalWrite(S2,HIGH); digitalWrite(S3,HIGH);
    sensor14 = analogRead(SIG);

    // Channel 15 (C15 pin - binary output 1,1,1,1)
    digitalWrite(S0,HIGH); digitalWrite(S1,HIGH); digitalWrite(S2,HIGH); digitalWrite(S3,HIGH);
    sensor15 = analogRead(SIG);

    Serial.print("Sensor 0 : ");Serial.println(sensor0);          /* state value for sensor 0 */
    Serial.print("Sensor 1 : ");Serial.println(sensor1);          /* state value for sensor 1 */
    Serial.print("Sensor 2 : ");Serial.println(sensor2);          /* state value for sensor 2 */
    Serial.print("Sensor 3 : ");Serial.println(sensor3);          /* state value for sensor 3 */
    Serial.print("Sensor 4 : ");Serial.println(sensor4);          /* state value for sensor 4 */
    Serial.print("Sensor 5 : ");Serial.println(sensor5);          /* state value for sensor 5 */
    Serial.print("Sensor 6 : ");Serial.println(sensor6);          /* state value for sensor 6 */
    Serial.print("Sensor 7 : ");Serial.println(sensor7);          /* state value for sensor 7 */
    Serial.print("Sensor 8 : ");Serial.println(sensor8);          /* state value for sensor 8 */
    Serial.print("Sensor 9 : ");Serial.println(sensor9);          /* state value for sensor 9 */
    Serial.print("Sensor 10 : ");Serial.println(sensor10);        /* state value for sensor 10 */
    Serial.print("Sensor 11 : ");Serial.println(sensor11);        /* state value for sensor 11 */
    Serial.print("Sensor 12 : ");Serial.println(sensor12);        /* state value for sensor 12 */
    Serial.print("Sensor 13 : ");Serial.println(sensor13);        /* state value for sensor 13 */
    Serial.print("Sensor 14 : ");Serial.println(sensor14);        /* state value for sensor 14 */
    Serial.print("Sensor 15 : ");Serial.println(sensor15);        /* state value for sensor 15 */
  
    delay(1000);                                                  // Read the value every second

}
