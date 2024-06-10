int enA = 6;   
int enB = 7;  
int in1 = 2;
int in2 = 3;
int in3 = 4;
int in4 = 5;
int speed1 = 60; 
int speed2 = 61;
int speed3 = 63;

// Sensor connection and settings a 1 b 2 3 4 c 5 d
int ira = A0;
int ir1 = A1;
int irb = A2;
int ir2 = A3; 
int ir3 = A4;
int ir4 = A5;
int irc = A6;
int ir5 = A7;
int ird = A8;

int thr = 500; // Threshold

// Sensor values
int irvaluea;
int irvalue1;
int irvalueb;
int irvalue2;
int irvalue3;
int irvalue4;
int irvaluec;
int irvalue5;
int irvalued;

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(ira, INPUT);
  pinMode(ir1, INPUT);
  pinMode(irb, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  pinMode(irc, INPUT);
  pinMode(ir5, INPUT);
  pinMode(ird, INPUT);

  Serial.begin(9600);
}

void loop() {
  followline();
}

void forward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, speed3);
  analogWrite(enB, speed3);
}

void forwardright() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, speed2);
  analogWrite(enB, speed3);
}

void forwardleft() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, speed3);
  analogWrite(enB, speed2);
}

void stop() { 
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void turnright() {
  analogWrite(enA, speed1);
  analogWrite(enB, speed1);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void turnleft() {
  analogWrite(enA, speed1);
  analogWrite(enB, speed1);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
}

void reverse() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, speed3);
  analogWrite(enB, speed3);
}

void followline() {
  // Read IR sensor values
  irvaluea = analogRead(ira);
  irvalue1 = analogRead(ir1);
  irvalueb = analogRead(irb);
  irvalue2 = analogRead(ir2);
  irvalue3 = analogRead(ir3);
  irvalue4 = analogRead(ir4);
  irvaluec = analogRead(irc);
  irvalue5 = analogRead(ir5);
  irvalued = analogRead(ird);

  // Debugging output (can be commented out)
  Serial.print("a: "); Serial.print(irvaluea);
  Serial.print(" 1: "); Serial.print(irvalue1);
  Serial.print(" b: "); Serial.print(irvalueb);
  Serial.print(" 2: "); Serial.print(irvalue2);
  Serial.print(" 3: "); Serial.print(irvalue3);
  Serial.print(" 4: "); Serial.print(irvalue4);
  Serial.print(" c: "); Serial.print(irvaluec);
  Serial.print(" 5: "); Serial.print(irvalue5);
  Serial.print(" d: "); Serial.println(irvalued);

  // Control logic based on sensor values
  if (irvalue3 >= thr) {
    if (irvalue2 >= thr && irvalue4 < thr) {
      forwardleft();
      delay(100);
      forward();// Slightly left if both middle and left sensors detect line
    } else if (irvalue4 >= thr && irvalue2 < thr) {
      forwardright(); 
      delay(100);
      forward();// Slightly right if both middle and right sensors detect line
    } else {
      forward();  // Move forward if only middle sensor detects line
    }
  } else if (irvalue2 >= thr) {
    if (irvalue1 >= thr) {
      turnleft();  // Sharp left if both left sensors detect line
    } else {
      forwardleft();
      forward();// Slightly left if only the left sensor detects line
    }
  } else if (irvalue4 >= thr) {
    if (irvalue5 >= thr) {
      turnright();
      delay(100);
      forward();// Sharp right if both right sensors detect line
    } else {
      forwardright();
      delay(100);
      forward();// Slightly right if only the right sensor detects line
    }
  } else if (irvalue1 >= thr || irvalue5 >= thr) {
    if (irvalue1 >= thr) {
      turnleft();
      delay(100);
      forward();// Sharp left if the outer left sensor detects the line
    } else {
      turnright();
      delay(100); 
      forward();// Sharp right if the outer right sensor detects the line
    }
  } else {
    stop();  // Stop if no sensors detect the line
  }
}
