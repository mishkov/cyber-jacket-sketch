#include <SoftwareSerial.h>

#define MATRIX_WIDTH 8
#define MATRIX_HEIGHT 8
#define ROW_OFF LOW
#define ROW_ON HIGH
#define COLUMN_ON LOW
#define COLUMN_OFF HIGH

const int columnsPins[MATRIX_WIDTH] = { 2, 3, 4, 5, 6, 7, 8, 9 };

const int rowsPins[MATRIX_HEIGHT] = { 10, A4, A5, 13, A0, A1, A2, A3 };
//
//const int pulseImpulse[MATRIX_WIDTH][MATRIX_HEIGHT] = {
//  {0, 0, 0, 0, 1, 0, 0, 0},
//  {0, 0, 0, 0, 1, 0, 0, 0},
//  {0, 0, 0, 0, 1, 0, 0, 0},
//  {0, 0, 0, 1, 0, 1, 0, 0},
//  {0, 0, 0, 1, 0, 1, 0, 0},
//  {0, 1, 0, 1, 0, 1, 0, 1},
//  {1, 0, 1, 0, 0, 0, 1, 0},
//  {0, 0, 0, 0, 0, 0, 1, 0}
//};
//
//const int pulseLine[MATRIX_WIDTH][MATRIX_HEIGHT] = {
//  {0, 0, 0, 0, 0, 0, 0, 0},
//  {0, 0, 0, 0, 0, 0, 0, 0},
//  {0, 0, 0, 0, 0, 0, 0, 0},
//  {0, 0, 0, 0, 0, 0, 0, 0},
//  {0, 0, 0, 0, 0, 0, 0, 0},
//  {0, 0, 0, 0, 0, 0, 0, 0},
//  {1, 1, 1, 1, 1, 1, 1, 1},
//  {0, 0, 0, 0, 0, 0, 0, 0}
//};
//
//void drawPulse() {
//  for (unsigned int shiftCount = 65500;; shiftCount++) {
//    unsigned int shift = shiftCount % 16;
//    unsigned long startTimeFrame = millis();
//    while (millis() - startTimeFrame < 80) {
//      // Show frame
//      for (int row = 0; row < MATRIX_HEIGHT; row++) {
//        int rowPin = rowsPins[row];
//        
//        // Draw line here
//        for (int column = 0; column < MATRIX_WIDTH; column++) {
//          int columnPin = columnsPins[column];
//    
//          // Make shift here
//          if (column+shift < MATRIX_WIDTH) {
//            if (pulseLine[row][column + shift] == 0) {
//              digitalWrite(columnPin, HIGH);
//            }
//          } else if (column+shift < 2 * MATRIX_WIDTH) {
//            if (pulseImpulse[row][column + shift - 8] == 0) {
//                digitalWrite(columnPin, HIGH);
//              }
//          } else if (column+shift < 3 * MATRIX_WIDTH) {
//            if (pulseLine[row][column + shift - 16] == 0) {
//                digitalWrite(columnPin, HIGH);
//              }
//          } else if (column+shift < 4 * MATRIX_WIDTH) {
//            if (pulseImpulse[row][column + shift - 24] == 0) {
//                digitalWrite(columnPin, HIGH);
//              }
//          }
//        }
//    
//        // Show line for 2 milliseconds
//        digitalWrite(rowPin, HIGH);
//        delay(2);
//        digitalWrite(rowPin, LOW);
//        
//        // Reset line
//        for (int column = 0; column < MATRIX_WIDTH; column++) {
//          int columnPin = columnsPins[column];
//          digitalWrite(columnPin, LOW);
//        }
//      }
//    }
//  }
//}

//struct symbol {
//  word key;
//  byte bytes[8];
//};
//
//const byte CHARS_LENGTH = 2;
//
//const symbol chars[CHARS_LENGTH] = {
//  {1087, {255, 128, 128, 128, 255, 0, 0, 0}},
//  {63, {0, 0, 96, 133, 136, 112, 0, 0}}
//};
//
//bool isCharContains(word key) {
//  for (byte i = 0; i < CHARS_LENGTH; i++) {
//    if (chars[i].key == key) {
//      return true;
//    }
//  }
//
//  return false;
//}
//


void drawFromBinaryArray(byte* arr) {
  for (int row = 0; row < MATRIX_HEIGHT; row++) {
    int rowPin = rowsPins[row];
    
    // Draw line here
    for (int column = 0; column < MATRIX_WIDTH; column++) {
      int columnPin = columnsPins[column];
      byte led = arr[row] & (1 << (MATRIX_WIDTH - column - 1));
      if (led == 0) {
        digitalWrite(columnPin, HIGH);
      }
    }
    digitalWrite(rowPin, HIGH);
    delay(2);
    digitalWrite(rowPin, LOW);
    // Reset line
    for (int column = 0; column < MATRIX_WIDTH; column++) {
      int columnPin = columnsPins[column];
      digitalWrite(columnPin, LOW);
    }
  }
}
//
//void drawFromUtf8(byte* arr) {
//  for (int row = 0; row < MATRIX_HEIGHT; row++) {
//    int rowPin = rowsPins[row];
//    
//    // Draw line here
//    for (int column = 0; column < MATRIX_WIDTH; column++) {
//      int columnPin = columnsPins[column];
//      byte led = arr[row] & (1 << (MATRIX_WIDTH - column - 1));
//      if (led == 0) {
//        digitalWrite(columnPin, HIGH);
//      }
//    }
//    digitalWrite(rowPin, HIGH);
//    delay(2);
//    digitalWrite(rowPin, LOW);
//    // Reset line
//    for (int column = 0; column < MATRIX_WIDTH; column++) {
//      int columnPin = columnsPins[column];
//      digitalWrite(columnPin, LOW);
//    }
//  }
//}

void initMatrixPins() {
  for (int column = 0; column < MATRIX_WIDTH; column++) {
    pinMode(columnsPins[column], OUTPUT);
  }
  for (int row = 0; row < MATRIX_HEIGHT; row++) {
    pinMode(rowsPins[row], OUTPUT);
  }
}

void turnMatrixOff() {
  for (int column = 0; column < MATRIX_WIDTH; column++) {
    digitalWrite(columnsPins[column], COLUMN_OFF);
  }
  for (int row = 0; row < MATRIX_HEIGHT; row++) {
    digitalWrite(rowsPins[row], ROW_OFF);
  }
}

const byte rxPin = 11;
const byte txPin = 12;
SoftwareSerial bluetoothSerial(rxPin, txPin);

void setup() {
  initMatrixPins();
  turnMatrixOff();

  Serial.begin(9600);
  bluetoothSerial.begin(9600);
}

//enum NextByte { byte_type, pointer, message_type, size, data};
//enum MessageType { image, text, unknown};
//
//NextByte next_byte = NextByte::byte_type;
//MessageType message_type_ = MessageType::unknown;
//int messageSize = 0;
//bool is_begin_byte_recieved = false;

int next_byte_index = 0;
const int DATA_BUFFER_SIZE = 8;
byte data_buffer[DATA_BUFFER_SIZE];

//MessageType last_recieved_message_type = MessageType::unknown;
//int last_message_size = 0;
byte last_recieved_message[DATA_BUFFER_SIZE];
//bool is_last_message_printed = false;

void loop() {
  while (bluetoothSerial.available()) {
    byte recieved_byte = bluetoothSerial.read();
    data_buffer[next_byte_index] = recieved_byte;
    next_byte_index++;

    // last row is recieved
    if (next_byte_index == DATA_BUFFER_SIZE) {
        for (int i = 0; i < DATA_BUFFER_SIZE; i++) {
          last_recieved_message[i] = data_buffer[i];
        }
      }
      
    // buffer overflow
    if (next_byte_index >= DATA_BUFFER_SIZE) {
      next_byte_index = 0;
    }
  }
  
  drawFromBinaryArray(last_recieved_message);
}
// uncomplete code
//void loop() {
//  while (bluetoothSerial.available()) {
//    byte recieved_byte = bluetoothSerial.read();
//
//    if (next_byte == NextByte::byte_type) {
//      switch (recieved_byte) {
//        case 0:
//          next_byte = NextByte::pointer;
//          break;
//        case 1:
//          next_byte = NextByte::size;
//          break;
//        case 2:
//          next_byte = NextByte::message_type;
//          break;
//        case 3:
//          next_byte = NextByte::data;
//          break;
//        default:
//          is_begin_byte_recieved = false;
//          break;
//      }
//    } else {
//      switch (next_byte) {
//        case NextByte::pointer:
//          if (recieved_byte == 0) {
//            is_begin_byte_recieved = true;
//            next_byte_index = 0;
//          } else if (recieved_byte == 1) {
//            if (is_begin_byte_recieved && messageSize == next_byte_index) {
//              // TODO: Impelement Process data
//              last_recieved_message_type = message_type_;
//              last_message_size = messageSize;
//              is_last_message_printed = false;
//              for (int i = 0; i < messageSize; i++) {
//                last_recieved_message[i] = data_buffer[i];
//              }
//            }
//            
//            is_begin_byte_recieved = false;
//          }
//          break;
//        case NextByte::message_type:
//          if (recieved_byte == 0) {
//            message_type_ = MessageType::image;
//          } else if (recieved_byte == 1) {
//            message_type_ = MessageType::text;
//          } else {
//            message_type_ = MessageType::unknown;
//          }
//          break;
//        case NextByte::size:
//          messageSize = recieved_byte;
//          break;
//        case NextByte::data:
//          data_buffer[next_byte_index] = recieved_byte;
//          next_byte_index++;
//          break;
//      }
//      next_byte = NextByte::byte_type;
//    }
//  }
//
//  switch (last_recieved_message_type) {
//    case image:
//      drawFromBinaryArray(last_recieved_message);
//      break;
//    case text:
//      if (!is_last_message_printed) {
//        Serial.print("Recieved string: ");
//        Serial.println(String((char*) last_recieved_message));
//        for (int i = 0; i < last_message_size; i++) {
//          Serial.print(last_recieved_message[i]);
//          Serial.print(" ");
//        }
//        Serial.println();
//      }
//      
//      is_last_message_printed = true;
//      break;
//  }
//}

// first version of loop()
/*
void loop() {
  while (bluetoothSerial.available()) {
    byte recieved_byte = bluetoothSerial.read();
    data_buffer[next_byte_index] = recieved_byte;
    next_byte_index++;

    // last row is recieved
    if (next_byte_index == DATA_BUFFER_SIZE) {
        for (int i = 0; i < DATA_BUFFER_SIZE; i++) {
          last_received_image[i] = data_buffer[i];
        }
      }
      
    // buffer overflow
    if (next_byte_index >= DATA_BUFFER_SIZE) {
      next_byte_index = 0;
    }
  }
  
  drawFromBinaryArray(last_received_image);
}
*/
