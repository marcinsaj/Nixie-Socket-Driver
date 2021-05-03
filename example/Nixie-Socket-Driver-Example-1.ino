// Nixie Socket Driver by Marcin Saj https://nixietester.com
// https://github.com/marcinsaj/Nixie-Socket-Driver
//
// Driving Nixie Sockets Example #1
//
// This example demonstrates how to control up to 6 nixie sockets.
// The control is carried out using up to six Nixie Tube Drivers in serial connection.

#define DIN_PIN   A0          // Nixie socket driver (shift register) serial data input pin             
#define CLK_PIN   A2          // Nixie socket driver clock input pin
#define EN_PIN    A1          // Nixie socket driver enable input pin

// Bit notation of 15-segment tube symbols                                  
uint16_t symbol_nixie_tube[]={
  0b0011111110001000,   // 0 
  0b0000000000010001,   // 1
  0b0010100101001000,   // 2
  0b0001100111000000,   // 3
  0b0011001001000100,   // 4
  0b0000101100100100,   // 5
  0b0001111101000100,   // 6
  0b0000000110010000,   // 7
  0b0011111101000100,   // 8
  0b0011101101000100,   // 9 
  0b0011011101000100,   // A
  0b0011100101010001,   // B 
  0b0000111100000000,   // C 
  0b0011100100010001,   // D 
  0b0000111100000100,   // E
  0b0000011100000100,   // F
  0b0001111101000000,   // G
  0b0011011001000100,   // H
  0b0000100100010001,   // I
  0b0011110000000000,   // J
  0b0000011010100100,   // K
  0b0000111000000000,   // L
  0b0011011010000010,   // M
  0b0011011000100010,   // N 
  0b0011111100000000,   // O 
  0b0010011101000100,   // P 
  0b0011111100100000,   // Q
  0b0010011101100100,   // R
  0b0001101101000100,   // S
  0b0000000100010001,   // T
  0b0011111000000000,   // U
  0b0000011010001000,   // V
  0b0011011000101000,   // W
  0b0000000010101010,   // X
  0b0000000010001010,   // Y
  0b0000100110001000    // Z             
};

// Bit numbers 
//
//            8
//       ___________
//      |\    |    /|
//      | \   |0  / |
//    9 | 1\  |  /7 | 13
//      |   \ | /   |
//      |____\|/____| 
//      | 2  /|\  6 |
//      |   / | \   |
//   10 |  /  |4 \  | 12
//      | /3  |  5\ |
//      |/    |    \|
//       ¯¯¯¯¯¯¯¯¯¯¯
//            11
//       /¯¯¯¯¯¯¯¯¯\
//            14    
//  ______________________
// | SOCKET 20A, 24A, 26A |
//  ¯¯¯¯¯|¯¯¯¯¯¯¯¯¯¯|¯¯¯¯¯


// Bit notation of 10-segment tube digits 
uint16_t digit_nixie_tube[]={
  0b0000000000000001,   // 0 
  0b0000000000000010,   // 1
  0b0000000000000100,   // 2
  0b0000000000001000,   // 3
  0b0000000000010000,   // 4
  0b0000000000100000,   // 5
  0b0000000001000000,   // 6
  0b0000000010000000,   // 7
  0b0000000100000000,   // 8
  0b0000001000000000    // 9    
};


// Function prototype with optional parameters
void NixieDisplay(int tube1 = 255, int tube2 = 255, int tube3 = 255, int tube4 = 255, int tube5 = 255, int tube6 = 255);

void setup() 
{  
    pinMode(DIN_PIN, OUTPUT); 
    digitalWrite(DIN_PIN, LOW);    
    
    pinMode(CLK_PIN, OUTPUT);
    digitalWrite(CLK_PIN, LOW);         
  
    pinMode(EN_PIN, OUTPUT);
    digitalWrite(EN_PIN, LOW);
}

void loop ()
{
  // NixieDisplay(1);
  // NixieDisplay(1, 2);
  // NixieDisplay(1, 2, 3);
  // NixieDisplay(1, 2, 3, 4);
  // NixieDisplay(1, 2, 3, 4, 5);
  // NixieDisplay(1, 2, 3, 4, 5, 6);   //  NixieDisplay(tube1, tube2, tube3, tube4, tube5, tube6);

  for(int i = 0; i < 10; i++)
  {
    NixieDisplay(i, i, i, i, i, i);  
    delay(1000);
  }     
}

// Function with optional parameters 
void NixieDisplay(int tube1, int tube2 , int tube3, int tube4, int tube5, int tube6)
{
  StartShiftOutData();
  if (tube6 != 255) ShowDigit(tube6); //ShowSymbol(tube6);
  if (tube5 != 255) ShowDigit(tube5); //ShowSymbol(tube5);
  if (tube4 != 255) ShowDigit(tube4); //ShowSymbol(tube4);
  if (tube3 != 255) ShowDigit(tube3); //ShowSymbol(tube3);
  if (tube2 != 255) ShowDigit(tube2); //ShowSymbol(tube2);
  if (tube1 != 255) ShowDigit(tube1); //ShowSymbol(tube1);
  EndShiftOutData();  
}

void ShowDigit(int digit)
{
  ShiftOutData(digit_nixie_tube[digit]);
}

void ShowSymbol(int symbol)
{
  ShiftOutData(symbol_nixie_tube[symbol]);  
}

void StartShiftOutData()
{
  // Ground EN pin and hold low for as long as you are transmitting
  digitalWrite(EN_PIN, LOW);  
}

void ShiftOutData(uint16_t character)
{ 
  uint8_t first_half = character >> 8;  
  uint8_t second_half = character;     
  shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, first_half);
  shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, second_half);
}

void EndShiftOutData()
{
  // Return the latch pin high to signal chip that it
  // no longer needs to listen for information
  digitalWrite(EN_PIN, HIGH);   
}
