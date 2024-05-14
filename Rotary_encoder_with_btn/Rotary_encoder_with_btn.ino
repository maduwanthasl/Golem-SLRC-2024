#define outputA 4
#define outputB 5
#define btn 7

int counter = 0; 
int aState;
int aLastState; 
int press = false; 

void setup() { 
  pinMode (outputA,INPUT);
  pinMode (outputB,INPUT);
  pinMode(btn,INPUT_PULLUP);
  
  Serial.begin (9600);
  // Reads the initial state of the outputA
  aLastState = digitalRead(outputA);  
} 

void loop() { 

  int btnState = digitalRead(btn); // Read the state of the button
  
  // Check if the button is pressed (LOW state)
  if (btnState == LOW) {
    press = true;
    delay(1000);
    Serial.println("btn");
  } else {
    // Button is not pressed, do something else
  }

  aState = digitalRead(outputA); // Reads the "current" state of the outputA
  // If the previous and the current state of the outputA are different, that means a Pulse has occured
  if (aState != aLastState){     
    // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
    if (digitalRead(outputB) != aState) { 
      counter ++;
    } else {
      counter --;
    }
    Serial.print("Position: ");
    Serial.println(counter);
  } 
  aLastState = aState; // Updates the previous state of the outputA with the current state
}