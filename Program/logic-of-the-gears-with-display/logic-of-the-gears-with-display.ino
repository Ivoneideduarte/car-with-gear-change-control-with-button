/*
  CAR DESIGN WITH GEAR AND DISPLAY TO SHOW THE EXCHANGE OF GEARS
   Start: 05/03/2021
   Updated: May 21, 2021
   Lesson 01: Logic of marches

   materials:
   01 - 1 x Arduino UNO
   02 - 5 x Buttons
   03 - M-M jumper cables | M-F
   04 - 2 x Wheel motors
   05 - 1 x Bridge H L298D
   06 - 1 x Chassis
   07 - 1 x Boba Wheel
   08 - 1 x 7-segment display
   09 - 2 x 18650 battery
   10 - 1 x Battery holder 18650
   11 - 1 x Keys On/Off
   12 - 1 x Green Led
   13 - 1 x Resistor 220Ohm
   14 - 2 x Resistor 330Ohm
*/

//Pins H bridge
//Left engine
byte ENA = 3, N1 = 13, N2 = 2;
//Right engine
byte ENB = 5, N3 = 4, N4 = 6;

//pin button
byte forwardBtn = 8, leftBtn = 9, rightBtn = 10, backBtn = 11, gearBtn = 12;

//pin light
byte ledGear = 7, numGear = 0;

#define backSpeed 100 //Speed of the back
#define speedTurn 150 //Speed of the turn

bool changerGear = false, y = false;

byte speedMax;

void setup()
{
  Serial.begin(9600);
  Serial.println("Initializing");

  for (byte pin = 2; pin <= 19; pin++) {
    pinMode(pin, OUTPUT); // Initializing by setting all ports to output
  }
  for (byte pin = 8; pin <= 12; pin++) {
    pinMode(pin, INPUT_PULLUP); // Setting the buttons for Arduino's built-in pull-up resistors
  }
  digitalWrite(ledGear, LOW); // The LED indicating the gear change starts off
}

void loop()
{
  if (!digitalRead(gearBtn))
  { // If the pass-the-gear button is pressed, the gear box will be activated and the gear function is called
    changerGear = true;
    gear();
  }

  if (!digitalRead(forwardBtn))
  {
    if (numGear > 0)
    {
      forwardCar(speedMax);
    }
    else
    {
      changerGear = true;
      gear();
    }
  }

  else if (!digitalRead(leftBtn)) leftCar();

  else if (!digitalRead(rightBtn)) rightCar();

  else if (!digitalRead(backBtn)) backCar();

  else stopCar();
}

//Function for change the march
void gear()
{
  while (changerGear)
  {
    Serial.println("Acts Gear: " + String(numGear));
    showGear(numGear); // Displays the gear number on the 7 segment display
    if (!digitalRead(gearBtn))
    { // When you press the button, the indicator LED lights up and the number of gears is increased
      delay(250);
      digitalWrite(ledGear, HIGH);
      numGear++;
      if (numGear > 4)
      {
        if (!y) {
          y = true;
          numGear = 4;
          Serial.println("The next gear is neutral.");
        }
        else {
          y = false;
          numGear = 0;
        }
      }
      Serial.println("Switch to the march: " + String(numGear));
      showGear(numGear); // Shows the gait number on the display
    }
    changerGear = false;
    digitalWrite(ledGear, LOW);
  } //end while
} //end gear

void forwardCar(byte speedMax)
{
  analogWrite(ENA, speedMax);
  digitalWrite(N1, HIGH);
  digitalWrite(N2, LOW);

  analogWrite(ENB, speedMax);
  digitalWrite(N3, HIGH);
  digitalWrite(N4, LOW);

  Serial.println("Speed: " + String(speedMax));
}

void leftCar()
{
  analogWrite(ENA, speedTurn);
  digitalWrite(N1, LOW);
  digitalWrite(N2, HIGH);

  analogWrite(ENB, speedTurn);
  digitalWrite(N3, HIGH);
  digitalWrite(N4, LOW);
}

void rightCar()
{
  analogWrite(ENA, speedTurn);
  digitalWrite(N1, HIGH);
  digitalWrite(N2, LOW);

  analogWrite(ENB, speedTurn);
  digitalWrite(N3, LOW);
  digitalWrite(N4, HIGH);
}

void backCar()
{
  analogWrite(ENA, backSpeed);
  digitalWrite(N1, LOW);
  digitalWrite(N2, HIGH);

  analogWrite(ENB, backSpeed);
  digitalWrite(N3, LOW);
  digitalWrite(N4, HIGH);
}

void stopCar()
{
  analogWrite(ENA, 0);
  digitalWrite(N1, HIGH);
  digitalWrite(N2, LOW);

  analogWrite(ENB, 0);
  digitalWrite(N3, HIGH);
  digitalWrite(N4, LOW);
}

void showGear(byte numGear)
{
  switch (numGear)
  {
    case 0: // neuter
      speedMax = 0;
      //Display(a,c,d,e,f,g);
      Display(1, 1, 1, 1, 1, 0);
      break;

    case 1: // first gear
      speedMax = 70;
      //Display(a,c,d,e,f,g);
      Display(0, 1, 0, 0, 0, 0);
      break;

    case 2: // second gear
      speedMax = 120;
      //Display(a,c,d,e,f,g);
      Display(1, 0, 1, 1, 0, 1);
      break;

    case 3: // third gear
      speedMax = 180;
      //Display(a,c,d,e,f,g);
      Display(1, 1, 1, 0, 0, 1);
      break;

    case 4: // fourth gear
      speedMax = 255;
      //Display(a,c,d,e,f,g);
      Display(0, 1, 0, 0, 1, 1);
      break;
  }
}

void Display(bool a, bool c, bool d, bool e, bool f, bool g)
{
  byte pinA = A0, pinC = A1, pinD = A2, pinE = A3, pinF = A4, pinG = A5; // Setting the display pins
  digitalWrite(pinA, a);
  /*digitalWrite(B, b); Connected on 5V*/
  digitalWrite(pinC, c);
  digitalWrite(pinD, d);
  digitalWrite(pinE, e);
  digitalWrite(pinF, f);
  digitalWrite(pinG, g);
}
