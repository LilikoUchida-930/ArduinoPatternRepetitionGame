  // Defining global variables 
  const int GREEN = 6;
  const int BLUE = 7;
  const int RED = 8;
  const int YELLOW = 9;

  const int GREEN_BUTTON = 10;
  const int BLUE_BUTTON = 11;
  const int RED_BUTTON = 12;
  const int YELLOW_BUTTON = 13;

  const int MOTOR = 14;

  int buttonState_GREEN = 0;
  int buttonState_BLUE = 0;
  int buttonState_RED = 0;
  int buttonState_YELLOW = 0;

  unsigned long debounce_delay = 250 ; 
  unsigned long last_debounce_time = 0 ; 



  
void setup() {
  // put your setup code here, to run once:
  // Assign pin modes to each pin. 
  
  pinMode(GREEN, OUTPUT); // Green LED
  pinMode(BLUE, OUTPUT); // Blue LED
  pinMode(RED, OUTPUT); // Red LED
  pinMode(YELLOW, OUTPUT); // Yellow LED

 
  
  pinMode(GREEN_BUTTON, INPUT); // Green button
  pinMode(BLUE_BUTTON, INPUT); // Blue button
  pinMode(RED_BUTTON, INPUT); // Red button 
  pinMode(YELLOW_BUTTON, INPUT); // Yellow button


  pinMode(MOTOR, OUTPUT); // Motor 

}


// Define all functions to be called in the void loop.
void generate_random_pattern(int pattern[]) {
    for (int i=0; i<4; i++){
        pattern[i] = random(1, 5);
    } 
}

void display_pattern(int pattern[]) {
    for (int i=0; i<4; i++){
        if (pattern[i]==1){
           digitalWrite(GREEN, HIGH);
        } else if (pattern[i]==2){
            digitalWrite(BLUE, HIGH);
        } else if (pattern[i]==3){
            digitalWrite(RED, HIGH);
        } else{
            digitalWrite(YELLOW, HIGH);
        }
        delay(900);
        digitalWrite(GREEN, LOW);
        digitalWrite(BLUE, LOW);
        digitalWrite(RED, LOW);
        digitalWrite(YELLOW, LOW);
        delay(100);
    }
} 

bool compare_patterns(int pattern[], int answer[]) {
  for (int i=0; i<4; i++) { 
      if (pattern[i] != answer[i]) {
          return false;
      } 
  }

  return true;
}


void display_pressed_buttons() {
    buttonState_GREEN = digitalRead(GREEN_BUTTON);
    if (buttonState_GREEN == HIGH) {
        digitalWrite(GREEN, LOW);
    } else{
        digitalWrite(GREEN, HIGH);
    }

    buttonState_BLUE = digitalRead(BLUE_BUTTON);
    if (buttonState_BLUE == HIGH) {
        digitalWrite(BLUE, LOW);
    } else{
        digitalWrite(BLUE, HIGH);
    }

    buttonState_RED = digitalRead(RED_BUTTON);
    if (buttonState_RED == HIGH) {
        digitalWrite(RED, LOW);
    } else{
        digitalWrite(RED, HIGH);
    }

    buttonState_YELLOW = digitalRead(YELLOW_BUTTON);
    if (buttonState_YELLOW == HIGH) {
        digitalWrite(YELLOW, LOW);
    } else{
        digitalWrite(YELLOW, HIGH);
    }
}

void loop() {
    
    
  // put your main code here, to run repeatedly:
  int pattern[4];

  generate_random_pattern(pattern);

  Serial.print("Pattern: ");
  for (int i = 0; i < 4; i++) {
    Serial.print(pattern[i]);
    Serial.print(" ");
  }
  Serial.print("\n");

  display_pattern(pattern);


  // input
  // while user hasnt respond
  int answer[4];

  int green_button_prev_state = digitalRead(GREEN_BUTTON);
  int blue_button_prev_state = digitalRead(BLUE_BUTTON);
  int red_button_prev_state = digitalRead(RED_BUTTON);
  int yellow_button_prev_state = digitalRead(YELLOW_BUTTON);
  
  
  int state = 0;
  while (state != 4) {
      display_pressed_buttons();
      // if current time - lastime > delay then do it
      if ((millis() - last_debounce_time) > debounce_delay){
          if (green_button_prev_state == HIGH and digitalRead(GREEN_BUTTON) == LOW){
              Serial.print("green logged\n");
              last_debounce_time = millis();
              answer[state] = 1;
              state = state + 1; 
          } else if (blue_button_prev_state == HIGH and digitalRead(BLUE_BUTTON) == LOW){
              Serial.print("blue logged\n");
              last_debounce_time = millis();
              answer[state] = 2;
              state = state + 1; 
          } else if (red_button_prev_state == HIGH and digitalRead(RED_BUTTON) == LOW){
              Serial.print("red logged\n");
              last_debounce_time = millis();
              answer[state] = 3;
              state = state + 1; 
          } else if (yellow_button_prev_state == HIGH and digitalRead(YELLOW_BUTTON) == LOW){
              Serial.print("yellow logged\n");
              last_debounce_time = millis();
              answer[state] = 4;
              state = state + 1; 
          }
      }

      green_button_prev_state = digitalRead(GREEN_BUTTON);
      blue_button_prev_state = digitalRead(BLUE_BUTTON);
      red_button_prev_state = digitalRead(RED_BUTTON);
      yellow_button_prev_state = digitalRead(YELLOW_BUTTON);


      
      
      // if green's prev state == HIGH and green's curr state == LOW
          // state = state + 1 
      // H H H H H H H H H H H H H LL L L L L L L L L L L H H H H H H HH H HH HHH HH H  L LLLL L L L L  L   HhhhhhHHHHHHH LLLLLLLLLLLLL 
      
  }

  Serial.print("Answer: ");
  for (int i = 0; i < 4; i++) {
    Serial.print(answer[i]);
    Serial.print(" ");
  }
  Serial.print("\n");

  if (compare_patterns(pattern, answer) == true) {
      digitalWrite(MOTOR, HIGH);
      delay(5000);
      digitalWrite(MOTOR, LOW);
      for (int i=0; i<10; i++){
          digitalWrite(GREEN, HIGH);
          digitalWrite(BLUE, HIGH);
          digitalWrite(RED, HIGH);
          digitalWrite(YELLOW, HIGH);
          delay(200);
          digitalWrite(GREEN, LOW);
          digitalWrite(BLUE, LOW);
          digitalWrite(RED, LOW);
          digitalWrite(YELLOW, LOW);
          delay(200);
      // good 
      Serial.print("YaY!!!!\n");
      }
  } else {
      for (int i=0; i<10; i++){
          digitalWrite(RED, HIGH);
          delay(200);
          digitalWrite(RED, LOW);
          delay(200);
          
      }
    Serial.print("fuck up\n");
    }

  delay(2000);

}
