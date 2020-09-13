#include <IRremote.h>
#include <EEPROM.h>
const int RECV_PIN=A0;
IRrecv irrecv(RECV_PIN);
decode_results results;

#define Relay1 2  // Load1 Pin Out
#define Relay2 3  // Load2 Pin Out
#define Relay3 4  // Load3 Pin Out
#define Relay4 5  // Load4 Pin Out

int load1, load2, load3, load4, power;

void setup(){// put your setup code here, to run once
  
  Serial.begin(9600);

  pinMode(Relay1, OUTPUT); // declare as output for Load1 Pin Relay1     
  pinMode(Relay2, OUTPUT); // declare as output for Load2 Pin Relay2 
  pinMode(Relay3, OUTPUT); // declare as output for Load3 Pin Relay3  
  pinMode(Relay4, OUTPUT); // declare as output for Load4 Pin Relay4  

 digitalWrite(Relay1, 1); // Turn Off Load1
 digitalWrite(Relay2, 1); // Turn Off Load2
 digitalWrite(Relay3, 1); // Turn Off Load3
 digitalWrite(Relay4, 1); // Turn Off Load4
  
  irrecv.enableIRIn(); // Start the receiver
  irrecv.blink13(true);

load1 = EEPROM.read(1);
load2 = EEPROM.read(2);
load3 = EEPROM.read(3);
load4 = EEPROM.read(4);

power = EEPROM.read(5);
}

void loop() {
  
if(irrecv.decode(&results)){
 Serial.println(results.value,HEX);
  

     if(results.value==0xFFB04F){ // For Load1 On  
load1 = 0; 
EEPROM.write(1, load1);  
}
else if(results.value==0xFF6897){ // For Load1 Off 
load1 = 1; 
EEPROM.write(1, load1);  
}

else if(results.value==0xFF7A85){ // For Load2 On 
load2 = 0; 
EEPROM.write(2, load2);  
}
else if(results.value==0xFF30CF){ // For Load2 Off 
load2 = 1; 
EEPROM.write(2, load2);  
}

else if(results.value==0xFF5AA5){ // For Load3 On 
load3 = 0; 
EEPROM.write(3, load3);  
}
else if(results.value==0xFF10EF){ // For Load3 Off 
load3 = 1; 
EEPROM.write(3, load3);  
}

else if(results.value==0xFF52AD){ // For Load4 On 
load4 = 0; 
EEPROM.write(4, load4);  
}
else if(results.value==0xFF42BD){ // For Load4 Off 
load4 = 1; 
EEPROM.write(4, load4);  
}

else if(results.value==0xFFE21D){ // For Power On 
power = 0; 
EEPROM.write(5, power);     
}    
else if(results.value==0xFFA25D){ // For Power Off
power = 1; 
EEPROM.write(5, power); 
}
    
 irrecv.resume(); // Receive the next value
 delay(100);
 }

if(power==1){  
 digitalWrite(Relay1, 1); // Turn Off Load1
 digitalWrite(Relay2, 1); // Turn Off Load2
 digitalWrite(Relay3, 1); // Turn Off Load3
 digitalWrite(Relay4, 1); // Turn Off Load4
}else{
digitalWrite(Relay1, load1); 
digitalWrite(Relay2, load2); 
digitalWrite(Relay3, load3); 
digitalWrite(Relay4, load4);
}
  
delay(500);  
}
