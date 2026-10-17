#include <Adafruit_PWMServoDriver.h>
#include<Wire.h>
#include <stdint.h>
#include <Arduino.h>
#include<BluetoothSerial.h>


#define SDA_PIN                    13  // Fixed for TL_RAN PCB
#define SCL_PIN                    14  // Fixed for TL_RAN PCB
#define PCA_ENABLE_PIN_NO           3
#define SERVO_FREQ  50
#define SOFT_TX_BAUD       9600
#define SOFT_TX_PIN_NO     1
#define USMIN      600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX     2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
const uint16_t servoMin = 150;  // Min pulse length for the servo
const uint16_t servoMax = 600;  // Max pulse length for the servo

BluetoothSerial  SerialBT;

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
int position_uS;
uint8_t servo_num = 0;
int PWM_CHANNEL_NO_LASER = 0;
const unsigned long MICROSECOND_PER_BIT = (1000000UL / SOFT_TX_BAUD);



void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_BT");
  pinMode(PCA_ENABLE_PIN_NO, OUTPUT);
  digitalWrite(PCA_ENABLE_PIN_NO, LOW);
  Wire.begin(SDA_PIN, SCL_PIN);
  Serial.print("waiting for connection.....");
  pwm.begin();
  pwm.setOscillatorFrequency(25000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

String cmd;
void loop() {
  if (SerialBT.available()) {
     cmd = SerialBT.readStringUntil('\n'); // Read input until newline
    // if (cmd.length() >= 2) {
    //   cmd = cmd.substring(0, cmd.length() - 2);
    // }
  //  String cmd="#I#2100#1200#223#0#1#1#";
      Serial.print("Received: ");
      Serial.println(cmd);
    
    if ((isValidCommand(cmd.c_str())) > 0) { // Convert String to char* and check if the command is valid
      Serial.println("successfull");
      process_command(cmd.c_str());   // Call the function to process the command
    } else {
      Serial.println("fail");   // Print an error message if the command is invalid
    }
  }

}
// int string_to_integer(const char* str) {
//   int result = 0;
//   int position_multiplier = 1000;  // Initialize with the most significant position multiplier
  
//   for (const char* p = str; *p != '\0'; ++p) {
//     result += ((*p - '0') * position_multiplier); // Multiply the digit by its position multiplier and add to result
//     position_multiplier /= 10;  // Update the position multiplier for the next digit
//   }
//   return result;
// }
// int string_to_integer(char* str) {
//     int result = 0;
//     int sign = 1;
    
//     // Skip leading non-digit characters and handle optional sign
//     while (*str && !isdigit(*str)) {
//         if (*str == '-') {
//             sign = -1;
//         }
//         str++;
//     }

//     // Parse digits until a non-digit character is encountered
//     while (*str && isdigit(*str)) {
//         result = result * 10 + (*str - '0');
//         str++;
//     }

//     return result * sign;
// }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int string_to_integer(const char* str) {
  int result = 0;
  int position_multiplier = 1;  // Start with the least significant position

  for (const char* p = str; *p != '\0'; ++p) {
    if (*p < '0' || *p > '9') {
      Serial.println("Error: Invalid character found in string.");  // Print error message
      return 0;  // Or return a default value, or throw an exception if appropriate
    }
    result = result * 10 + (*p - '0');
  }
  return result;
}

int getM0Command(const char *m) {
  char ch[5];
  strncpy(ch, m + 3, 4);  // Copy 4 characters starting from index 3
  ch[4] = '\0';

  Serial.print("string= ");
  Serial.println(ch);

  int result = string_to_integer(ch);

  if (result == 0) {  // Check for error
    Serial.println("Error converting string to integer for M0.");
  } else {
    Serial.print("Integer value for M0: ");
    Serial.println(result);
  }

  return result;  // Or handle the error differently here
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int getM1Command(const char *m) {
  Serial.println("M1 command called");
  char ch[5];  // Use a 4-character array to accommodate only the digits
  strncpy(ch, m + 8, 4);  // Copy 4 characters starting from index 7
  ch[4] = '\0';

  Serial.print("string= ");
  Serial.println(ch);

  int result = string_to_integer(ch);

  if (result == 0) {  // Check for error
    Serial.println("Error converting string to integer for M1.");
  } else {
    Serial.print("Integer value for M1: ");
    Serial.println(result);
  }

  return result;  // Or handle the error differently here
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int getM2Command(const char *m) {
  Serial.println("M2 command called");
  char ch[4];  // Use a 4-character array to accommodate only the digits
  strncpy(ch, m + 13, 3);  // Copy 4 characters starting from index 7
  ch[3] = '\0';

  Serial.print("string= ");
  Serial.println(ch);

  int result = string_to_integer(ch);

  if (result == 0) {  // Check for error
    Serial.println("Error converting string to integer for M2.");
  } else {
    Serial.print("Integer value for M2: ");
    Serial.println(result);
  }

  return result; 
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int getLEDCommand(const char *m) {
  char ch = m[17];
   Serial.print("LED Command: ");
   Serial.println(ch);
  return ((int) ch - '0');
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int getBeepCommand(const char *m) {
  char ch = m[19];
   Serial.print("Beep Command: ");
  Serial.println(ch);
  
  return ((int) ch - '0');
  
}
//////////////////////////////////////////////////////////////////////////////
int getMagnetCommand(const char *m) {
  char ch = m[21];
   Serial.print("Magnet Command: ");
   Serial.println(ch);
  return ((int) ch - '0');
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool isValidCommand(const char *m) {
  int len = strlen(m);

  // Early return for invalid length
  if (len != 24) {
    Serial.println("Invalid command length");
    return false;
  }
 
  // Check for specific characters at specific positions
  if (m[0] != '#' || m[2] != '#' || m[7] != '#' || m[12] != '#' ||
      m[16] != '#' || m[18] != '#' || m[20] != '#' || m[22] != '#') {
    Serial.println("Invalid command format");
    return false;
  }

  // Check for valid command type (A, E, L, B, M, U, V, W, C, I)
  if (!isalpha(m[1]) || !(strchr("AELBMUVCWI", m[1]))) {
    Serial.println("Invalid command type");
    return false;
  }

  // Check for valid motor, LED, beep, and magnet values
  bool isValidM0 = true, isValidM1 = true, isValidM2 = true, isValidLED = true, isValidBeep = true, isValidMagnet = true;
  for (int i = 3; i <= 6; i++) {
    if (!isdigit(m[i])) {
      isValidM0 = false;
      break;
    }
  }
  for (int i = 8; i <= 11; i++) {
    if (!isdigit(m[i])) {
      isValidM1 = false;
      break;
    }
  }
  for (int i = 13; i <= 15; i++) {
    if (!isdigit(m[i])) {
      isValidM2 = false;
      break;
    }
  }
  isValidLED = isdigit(m[17]);
  isValidBeep = isdigit(m[19]);
  isValidMagnet = isdigit(m[21]);

  // Return true if all values are valid, otherwise print message and return false
  if (isValidM0 && isValidM1 && isValidM2 && isValidLED && isValidBeep && isValidMagnet) {
    return true;
  } else {
    Serial.println("Invalid command value");
    return false;
  }
}






int move_m0(int position_uS ) {
  Serial.println("in move_m0 ");
 // uint16_t pwmValue = map(position_uS, 0, 180, servoMin, servoMax);
   pwm.writeMicroseconds(0, position_uS);
  return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int move_m1(int position_uS) {
   Serial.println("in move_m1 ");
  pwm.writeMicroseconds(1, position_uS );
    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int move_m2( int position_uS) {
    Serial.println("in move_m2 ");   
   pwm.writeMicroseconds(2, position_uS);
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int switch_LED(int led) {
  Serial.println("switch_led function called");
  if (led == 9) {
    pwm.setPWM(PWM_CHANNEL_NO_LASER, 0, 4096); //LASER ON
  }
  else if (led == 0) {
    pwm.setPWM(PWM_CHANNEL_NO_LASER, 4096, 0); //LASER OFF
  }
  else {
    Serial.println("Enter valid value of led");
  }
  return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int switch_buzzer(int buzz) {
  Serial.println("switch_buzzer function called");
  if (buzz >= 1 && buzz <= 4) {
    while (buzz > 0) {
      pwm.setPWM(buzz, 0, 4096);
      delay(400);
      pwm.setPWM(buzz, 4096, 0);
      delay(400);
      buzz--;
    }
  }
  return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int switch_magnet(int magnet) {
  Serial.println("switch_magnet function called");
  if (magnet == 1) {
    pwm.setPWM(magnet, 4096, 0); //OPPOSITE CONDITION
  }
  else if (magnet == 0) {
    pwm.setPWM(magnet, 0, 4096);
  }
  return 0;
}
//////////////////////////////////////////////////////////////////

int process_command(const char *m) {
  Serial.print("Received command type:");
  Serial.println(m[1]);
  switch (m[1]){
    case 'A':
    
    {
      Serial.println("calling move_m0");
      move_m0( getM0Command(m));
      Serial.println("\r\n------------------------------------------");
      Serial.println("calling move_m1");
      move_m1(getM1Command(m));
      Serial.println("\r\n------------------------------------------");
      Serial.println("calling move_m2");
      move_m2(getM2Command(m));
      Serial.println("\r\n------------------------------------------");
      switch_LED(getLEDCommand(m));
      Serial.println("\r\n------------------------------------------");
      switch_buzzer(getBeepCommand(m));
      Serial.println("\r\n------------------------------------------");
      switch_magnet( getMagnetCommand(m));
      Serial.println("\r\n------------------------------------------");
      break;
    }
    case 'I':
    {
      move_m0( getM0Command(m));
      move_m1(getM1Command(m));
      move_m2(getM2Command(m));
      switch_LED(getLEDCommand(m));
      switch_buzzer(getBeepCommand(m));
      switch_magnet( getMagnetCommand(m));
      break;
    }
    case 'E':  //echo
      Serial.print(cmd);
      break;
    case 'U':
    {
      move_m0( getM0Command(m));
      break;
    }
    case 'V':
    {
      move_m1(getM1Command(m));
      break;
    }
    case 'W':
    {
      move_m2(getM2Command(m));
      break;
    }
    case 'M':
    {
      switch_magnet( getMagnetCommand(m));
      break;
    }
    case 'B':
    {
      switch_buzzer(getBeepCommand(m));
      break;
    }
    case 'L':
    {
      switch_LED(getLEDCommand(m));
      break;
    }
    // default:
    //   Serial.println("Unknown command!");
    //   break;
  }
}