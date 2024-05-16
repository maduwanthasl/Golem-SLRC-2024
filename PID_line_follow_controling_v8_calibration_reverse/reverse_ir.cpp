#include "reverse_ir.h"

// Define the digital pins for S0, S1, S2, S3 connections to the multiplexer
#define S0 52
#define S1 50
#define S2 53
#define S3 51

// Define the analog pin connected to the SIG pin of the multiplexer
#define SIG A0

// Define the number of sensors connected to the multiplexer
#define NUM_SENSORS 6

void reverse_ir_setup() {
    // Set the multiplexer control pins as outputs
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);

    // Begin serial communication
    Serial.begin(9600);
}

void reverse_ir_loop() {
    // Loop through each sensor channel
    for (int channel = 0; channel < NUM_SENSORS; channel++) {
        // Select the channel
        selectChannel(channel);

        // Read the sensor value from the multiplexer
        int sensorValue = analogRead(SIG);

        // Store the sensor value in the array
        reversesensorValues[channel] = sensorValue;

        // Print the sensor value
        Serial.print("Sensor ");
        Serial.print(channel);
        Serial.print(": ");
        Serial.println(sensorValue);

        // Delay for stability (adjust as needed)
        // delay(10);
    }

    // Add additional code or functions here to process the sensor values as needed
}

// Function to select the channel on the multiplexer
void selectChannel(int channel) {
    // Convert channel number to binary and set the control pins accordingly
    digitalWrite(S0, channel & 0x01);
    digitalWrite(S1, (channel >> 1) & 0x01);
    digitalWrite(S2, (channel >> 2) & 0x01);
    digitalWrite(S3, (channel >> 3) & 0x01);
}
