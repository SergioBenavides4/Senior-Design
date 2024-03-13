#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <string.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
const char *ssid = "Put your network name on here";
const char *password = "Put your WiFi password here";
WiFiClient client;
#define SERVOMIN 130   // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 400   // This is the 'maximum' pulse length count (out of 4096)
#define USMIN 600      // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX 2400     // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50  // Analog servos run at ~50 Hz updates
const char *serverIP = "Put your local IP address here";
const int serverPort = 8080;

enum ANIMATRONIC { IDLE,
                   EYES_UP,
                   EYES_DOWN,
                   EYES_LEFT,
                   EYES_RIGHT,
                   MOUTH_OPEN,
                   MOUTH_CLOSE,
                   BLINK,
                   HAPPY,
                   SAD,
                   SURPRISED,
                   GRIN,
                   POUT } gState = IDLE;

void AnimatronicControl() {

  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char buff = client.read();
        String key = String(buff);
        Serial.print("Key Pressed: ");
        Serial.println(key);

        //int servoPos = 0;
        //Transitions
        switch (gState) {
          case IDLE:
            if (key == "U") {
              gState = EYES_UP;
            } else if (key == "D") {
              gState = EYES_DOWN;
            } else if (key == "R") {
              gState = EYES_RIGHT;
            } else if (key == "L") {
              gState = EYES_LEFT;
            }

            else if (key == "b") {
              gState = BLINK;
            }

            else if (key == "O") {
              gState = MOUTH_OPEN;
            }

            else if (key == "P") {
              gState = MOUTH_CLOSE;
            }

            else if (key == "G") {
              gState = GRIN;
            }

            else if (key == "T") {
              gState = POUT;
            }

            else if (key == "N") {
              gState = IDLE;
            }

            else if (key == "Z") {
              gState = HAPPY;
            }

            else if (key == "X") {
              gState = SAD;
            }

            else if (key == "C") {
              gState = SURPRISED;
            }

            break;

          case EYES_UP:
            if (key == "U") {
              gState = EYES_UP;
            } else if (key == "D") {
              gState = EYES_DOWN;
            } else if (key == "R") {
              gState = EYES_RIGHT;
            } else if (key == "L") {
              gState = EYES_LEFT;
            }

            else if (key == "b") {
              gState = BLINK;
            }

            else if (key == "O") {
              gState = MOUTH_OPEN;
            }

            else if (key == "P") {
              gState = MOUTH_CLOSE;
            }

            else if (key == "G") {
              gState = GRIN;
            }

            else if (key == "T") {
              gState = POUT;
            }

            else if (key == "N") {
              gState = IDLE;
            }

            else if (key == "Z") {
              gState = HAPPY;
            }

            else if (key == "X") {
              gState = SAD;
            }

            else if (key == "C") {
              gState = SURPRISED;
            }
            break;

          case EYES_DOWN:
            if (key == "U") {
              gState = EYES_UP;
            } else if (key == "D") {
              gState = EYES_DOWN;
            } else if (key == "R") {
              gState = EYES_RIGHT;
            } else if (key == "L") {
              gState = EYES_LEFT;
            }

            else if (key == "b") {
              gState = BLINK;
            }

            else if (key == "O") {
              gState = MOUTH_OPEN;
            }

            else if (key == "P") {
              gState = MOUTH_CLOSE;
            }

            else if (key == "G") {
              gState = GRIN;
            }

            else if (key == "T") {
              gState = POUT;
            }

            else if (key == "N") {
              gState = IDLE;
            }

            else if (key == "Z") {
              gState = HAPPY;
            }

            else if (key == "X") {
              gState = SAD;
            }

            else if (key == "C") {
              gState = SURPRISED;
            }
            break;

          case EYES_LEFT:
            if (key == "U") {
              gState = EYES_UP;
            } else if (key == "D") {
              gState = EYES_DOWN;
            } else if (key == "R") {
              gState = EYES_RIGHT;
            } else if (key == "L") {
              gState = EYES_LEFT;
            }

            else if (key == "b") {
              gState = BLINK;
            }

            else if (key == "O") {
              gState = MOUTH_OPEN;
            }

            else if (key == "P") {
              gState = MOUTH_CLOSE;
            } else if (key == "G") {
              gState = GRIN;
            }

            else if (key == "T") {
              gState = POUT;
            }

            else if (key == "N") {
              gState = IDLE;
            }

            else if (key == "Z") {
              gState = HAPPY;
            }

            else if (key == "X") {
              gState = SAD;
            }

            else if (key == "C") {
              gState = SURPRISED;
            }
            break;

          case EYES_RIGHT:
            if (key == "U") {
              gState = EYES_UP;
            } else if (key == "D") {
              gState = EYES_DOWN;
            } else if (key == "R") {
              gState = EYES_RIGHT;
            } else if (key == "L") {
              gState = EYES_LEFT;
            }

            else if (key == "b") {
              gState = BLINK;
            }

            else if (key == "O") {
              gState = MOUTH_OPEN;
            }

            else if (key == "P") {
              gState = MOUTH_CLOSE;
            }

            else if (key == "G") {
              gState = GRIN;
            }

            else if (key == "T") {
              gState = POUT;
            }

            else if (key == "N") {
              gState = IDLE;
            }

            else if (key == "Z") {
              gState = HAPPY;
            }

            else if (key == "X") {
              gState = SAD;
            }

            else if (key == "C") {
              gState = SURPRISED;
            }
            break;

          case BLINK:
            if (key == "U") {
              gState = EYES_UP;
            } else if (key == "D") {
              gState = EYES_DOWN;
            } else if (key == "R") {
              gState = EYES_RIGHT;
            } else if (key == "L") {
              gState = EYES_LEFT;
            }

            else if (key == "b") {
              gState = BLINK;
            }

            else if (key == "O") {
              gState = MOUTH_OPEN;
            }

            else if (key == "P") {
              gState = MOUTH_CLOSE;
            } else if (key == "G") {
              gState = GRIN;
            }

            else if (key == "T") {
              gState = POUT;
            }

            else if (key == "N") {
              gState = IDLE;
            }

            else if (key == "Z") {
              gState = HAPPY;
            }

            else if (key == "X") {
              gState = SAD;
            }

            else if (key == "C") {
              gState = SURPRISED;
            }
            break;

          case MOUTH_OPEN:
            if (key == "U") {
              gState = EYES_UP;
            } else if (key == "D") {
              gState = EYES_DOWN;
            } else if (key == "R") {
              gState = EYES_RIGHT;
            } else if (key == "L") {
              gState = EYES_LEFT;
            }

            else if (key == "b") {
              gState = BLINK;
            }

            else if (key == "O") {
              gState = MOUTH_OPEN;
            }

            else if (key == "P") {
              gState = MOUTH_CLOSE;
            }

            else if (key == "G") {
              gState = GRIN;
            }

            else if (key == "T") {
              gState = POUT;
            }

            else if (key == "N") {
              gState = IDLE;
            }

            else if (key == "Z") {
              gState = HAPPY;
            }

            else if (key == "X") {
              gState = SAD;
            }

            else if (key == "C") {
              gState = SURPRISED;
            }
            break;

          case MOUTH_CLOSE:
            if (key == "U") {
              gState = EYES_UP;
            } else if (key == "D") {
              gState = EYES_DOWN;
            } else if (key == "R") {
              gState = EYES_RIGHT;
            } else if (key == "L") {
              gState = EYES_LEFT;
            }

            else if (key == "b") {
              gState = BLINK;
            }

            else if (key == "O") {
              gState = MOUTH_OPEN;
            }

            else if (key == "P") {
              gState = MOUTH_CLOSE;
            }

            else if (key == "G") {
              gState = GRIN;
            }

            else if (key == "T") {
              gState = POUT;
            }

            else if (key == "N") {
              gState = IDLE;
            }

            else if (key == "Z") {
              gState = HAPPY;
            }

            else if (key == "X") {
              gState = SAD;
            }

            else if (key == "C") {
              gState = SURPRISED;
            }
            break;

          case HAPPY:
            if (key == "U") {
              gState = EYES_UP;
            } else if (key == "D") {
              gState = EYES_DOWN;
            } else if (key == "R") {
              gState = EYES_RIGHT;
            } else if (key == "L") {
              gState = EYES_LEFT;
            }

            else if (key == "b") {
              gState = BLINK;
            }

            else if (key == "O") {
              gState = MOUTH_OPEN;
            }

            else if (key == "P") {
              gState = MOUTH_CLOSE;
            }

            else if (key == "G") {
              gState = GRIN;
            }

            else if (key == "T") {
              gState = POUT;
            }

            else if (key == "N") {
              gState = IDLE;
            }

            else if (key == "Z") {
              gState = HAPPY;
            }

            else if (key == "X") {
              gState = SAD;
            }

            else if (key == "C") {
              gState = SURPRISED;
            }
            break;

          case SAD:
            if (key == "U") {
              gState = EYES_UP;
            } else if (key == "D") {
              gState = EYES_DOWN;
            } else if (key == "R") {
              gState = EYES_RIGHT;
            } else if (key == "L") {
              gState = EYES_LEFT;
            }

            else if (key == "b") {
              gState = BLINK;
            }

            else if (key == "O") {
              gState = MOUTH_OPEN;
            }

            else if (key == "P") {
              gState = MOUTH_CLOSE;
            }

            else if (key == "G") {
              gState = GRIN;
            }

            else if (key == "T") {
              gState = POUT;
            }

            else if (key == "N") {
              gState = IDLE;
            }

            else if (key == "Z") {
              gState = HAPPY;
            }

            else if (key == "X") {
              gState = SAD;
            }

            else if (key == "C") {
              gState = SURPRISED;
            }
            break;

          case SURPRISED:
            if (key == "U") {
              gState = EYES_UP;
            } else if (key == "D") {
              gState = EYES_DOWN;
            } else if (key == "R") {
              gState = EYES_RIGHT;
            } else if (key == "L") {
              gState = EYES_LEFT;
            }

            else if (key == "b") {
              gState = BLINK;
            }

            else if (key == "O") {
              gState = MOUTH_OPEN;
            }

            else if (key == "P") {
              gState = MOUTH_CLOSE;
            }

            else if (key == "G") {
              gState = GRIN;
            }

            else if (key == "T") {
              gState = POUT;
            }

            else if (key == "N") {
              gState = IDLE;
            }

            else if (key == "Z") {
              gState = HAPPY;
            }

            else if (key == "X") {
              gState = SAD;
            }

            else if (key == "C") {
              gState = SURPRISED;
            }
            break;

          case GRIN:
            if (key == "U") {
              gState = EYES_UP;
            } else if (key == "D") {
              gState = EYES_DOWN;
            } else if (key == "R") {
              gState = EYES_RIGHT;
            } else if (key == "L") {
              gState = EYES_LEFT;
            }

            else if (key == "b") {
              gState = BLINK;
            }

            else if (key == "O") {
              gState = MOUTH_OPEN;
            }

            else if (key == "P") {
              gState = MOUTH_CLOSE;
            }

            else if (key == "G") {
              gState = GRIN;
            }

            else if (key == "T") {
              gState = POUT;
            }

            else if (key == "N") {
              gState = IDLE;
            }

            else if (key == "Z") {
              gState = HAPPY;
            }

            else if (key == "X") {
              gState = SAD;
            }

            else if (key == "C") {
              gState = SURPRISED;
            }

            break;

          case POUT:
            if (key == "U") {
              gState = EYES_UP;
            } else if (key == "D") {
              gState = EYES_DOWN;
            } else if (key == "R") {
              gState = EYES_RIGHT;
            } else if (key == "L") {
              gState = EYES_LEFT;
            }

            else if (key == "b") {
              gState = BLINK;
            }

            else if (key == "O") {
              gState = MOUTH_OPEN;
            }

            else if (key == "P") {
              gState = MOUTH_CLOSE;
            }

            else if (key == "G") {
              gState = GRIN;
            }

            else if (key == "T") {
              gState = POUT;
            }

            else if (key == "N") {
              gState = IDLE;
            }

            else if (key == "Z") {
              gState = HAPPY;
            }

            else if (key == "X") {
              gState = SAD;
            }

            else if (key == "C") {
              gState = SURPRISED;
            }

            break;
        }
        //Actions
        switch (gState) {
          case IDLE:
            pwm.setPWM(0, 0, 370);
            pwm.setPWM(1, 0, 370);

            pwm.setPWM(2, 0, 370);
            pwm.setPWM(3, 0, 370);

            pwm.setPWM(4, 0, 370);
            pwm.setPWM(5, 0, 370);

            //Mouth
            pwm.setPWM(8, 0, 370);
            pwm.setPWM(9, 0, 370);
            pwm.setPWM(10, 0, 370);
            pwm.setPWM(11, 0, 370);

            pwm.setPWM(12, 0, 375);
            pwm.setPWM(13, 0, 370);

            delay(100);

            break;

          case EYES_UP:
            //Move servo 0 up (constrain between 250 and 600) CHANGE THE CHANNEL BELOW FOR DIRECTION
            // servoPos = constrain(pwm.writeMicroseconds(1) + 10,250,600);
            pwm.setPWM(0, 0, 200);
            pwm.setPWM(3, 0, 400);
            delay(100);
            break;

          case EYES_DOWN:
            // Move servo 3 down (constrain between 250 and 600) CHANGE THE CHANNEL BELOW FOR DIRECTION
            // servoPos = constrain(pwm.writeMicroseconds(1) - 10,250,600);
            pwm.setPWM(0, 0, 450);
            pwm.setPWM(3, 0, 300);
            delay(100);
            break;

          case EYES_LEFT:
            // Move servo 1 left (constrain between 250 and 600) CHANGE THE CHANNEL BELOW FOR DIRECTION
            // servoPos = constrain(pwm.writeMicroseconds(0) - 10,250,600);
            pwm.setPWM(1, 0, 500);
            pwm.setPWM(2, 0, 300);
            delay(100);
            break;

          case EYES_RIGHT:
            //Move servo 2 right (constrain between 250 and 600) CHANGE THE CHANNEL BELOW FOR DIRECTION
            // servoPos = constrain(pwm.writeMicroseconds(0) + 10,250,600);
            pwm.setPWM(1, 0, 230);
            pwm.setPWM(2, 0, 470);
            delay(100);
            break;

          case MOUTH_OPEN:
            pwm.setPWM(12, 0, 250);
            pwm.setPWM(13, 0, 450);
            delay(100);
            break;

          case MOUTH_CLOSE:
            pwm.setPWM(12, 0, 355);
            pwm.setPWM(13, 0, 355);
            delay(100);
            break;

          case GRIN:
            pwm.setPWM(8, 0, 200);
            pwm.setPWM(9, 0, 200);

            pwm.setPWM(10, 0, 500);
            pwm.setPWM(11, 0, 500);
            delay(100);
            break;

          case POUT:
            pwm.setPWM(8, 0, 460);
            pwm.setPWM(9, 0, 360);

            pwm.setPWM(10, 0, 250);
            pwm.setPWM(11, 0, 250);
            delay(100);
            break;

          case BLINK:
            // Move servo (insert channel number for eyelid)  (constrain between 250 and 600) CHANGE THE CHANNEL BELOW FOR DIRECTION
            // servoPos = constrain(pwm.writeMicroseconds(0) + 10,250,600);
            pwm.setPWM(4, 0, 500);
            pwm.setPWM(5, 0, 500);
            delay(500);
            pwm.setPWM(4, 0, 300);
            pwm.setPWM(5, 0, 300);
            delay(500);
            break;

          case HAPPY:
            pwm.setPWM(4, 0, 380);
            pwm.setPWM(5, 0, 420);

            pwm.setPWM(8, 0, 200);
            pwm.setPWM(9, 0, 200);

            pwm.setPWM(10, 0, 500);
            pwm.setPWM(11, 0, 500);

            pwm.setPWM(12, 0, 375);
            pwm.setPWM(13, 0, 370);
            delay(100);
            break;

          case SAD:
            pwm.setPWM(4, 0, 330);
            pwm.setPWM(5, 0, 330);

            pwm.setPWM(8, 0, 460);
            pwm.setPWM(9, 0, 360);

            pwm.setPWM(10, 0, 250);
            pwm.setPWM(11, 0, 250);

            pwm.setPWM(12, 0, 375);
            pwm.setPWM(13, 0, 370);
            delay(100);
            break;

          case SURPRISED:
            //Eyelids
            pwm.setPWM(4, 0, 250);
            pwm.setPWM(5, 0, 250);
            // higher cw lower ccw
            pwm.setPWM(8, 0, 560);
            // higher ccw lower cw
            pwm.setPWM(9, 0, 460);

            //lower cw higher cc
            pwm.setPWM(10, 0, 100);
            pwm.setPWM(11, 0, 250);
            //Jaw
            pwm.setPWM(12, 0, 250);
            pwm.setPWM(13, 0, 450);
            delay(100);
            break;
        }
      }
    }
    client.stop();
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // server.begin();
  Serial.println("WiFi connected");
  // Serial.println("IP address: ");
  while (!client.connected()) {
    Serial.println("Connecting to Server...");
    if (client.connect(serverIP, serverPort)) {
      Serial.println("Connected to Server");
    } else {
      Serial.print(".");
      delay(500);
    }
  }
  Serial.println(WiFi.localIP());
  pwm.begin();

  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz update
}



void loop() {
  if (!client.connected()) {
    client.connect(serverIP, 8080);
  }
  AnimatronicControl();
}
