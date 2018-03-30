/*
  Copyright (C) 2018   Gerardo Barbarov Rostan  
                       Singular Devices Maker Studio            
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>. 

  
  <IR_PROTOCOL><CODE><BITS><PULSES>
  
*/
#include <IRremote.h>

IRsend OPTIKEY_HC;

// pins for IR LED:
const int IR_PIN = 3;
// pins for RED LED:
const int RED_PIN = LED_BUILTIN;

int DEBUG_ON=0;

int PROTOCOL;    
long int CODE;
int NBIT;
int NPULSE;

String SPROTOCOL;    
String SCODE;
String SNBIT;
String SNPULSE;
  
int P_DELAY=40; // delay IR pulse 
int E_DELAY=200;// delay end IR secuence 

String readString; 
int ind1; 
int ind2;
int ind3; 
int ind4; 


void setup() {
  // initialize serial:
  Serial.begin(9600);
  //pins outputs:
  pinMode(IR_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  digitalWrite(IR_PIN,1);
  Serial.println("OPTIKEY HC OK");
}

int REMOTE_CONTROL(int P,int C,int Nb,int Np)
{digitalWrite(RED_PIN,1);
 for (int i = 0; i < Np; i++)
         {switch (P)  
                  {case 0:OPTIKEY_HC.sendRaw(C,Nb,Nb); // no use this !!! first reading documentation of  IR library 
                   break;
                   case 1:OPTIKEY_HC.sendLG(C, Nb);
                   break;
                   case 2:OPTIKEY_HC.sendNEC(C, Nb);  // verificated con LG TV and UZOPI radio
                   break;
                   case 3:OPTIKEY_HC.sendRC5(C, Nb);
                   break;
                   case 4:OPTIKEY_HC.sendRC6(C, Nb);
                   break;           
                   case 5:OPTIKEY_HC.sendSony(C, Nb);
                   break;           
                   case 6:OPTIKEY_HC.sendPanasonic(C, Nb);
                   break;           
                   case 7:OPTIKEY_HC.sendJVC(C,Nb,1);
                   break;           
                   case 8:OPTIKEY_HC.sendSharp(C, Nb);
                   break; 
                   case 9:OPTIKEY_HC.sendSAMSUNG(C, Nb);
                   break;                  
                   };  
                   delay(P_DELAY);    
        }    
 delay(E_DELAY);   
 digitalWrite(RED_PIN,0);    
};  

void loop() {    
   if (Serial.available())  {
    char c = Serial.read(); 
    if (c == '\n') {SPROTOCOL="";
                    SCODE="";                    
                    SNBIT="";
                    SNPULSE="";
      
      ind1 = readString.indexOf(',');  //finds location of first ,
      SPROTOCOL = readString.substring(0, ind1);   //captures first data String
      PROTOCOL=SPROTOCOL.toInt();
      ind2 = readString.indexOf(',', ind1+1 );   //finds location of second ,
      SCODE = readString.substring(ind1+1, ind2+1);   //captures second data String
      CODE=SCODE.toInt();
      ind3 = readString.indexOf(',', ind2+1 );
      SNBIT = readString.substring(ind2+1, ind3+1);   //captures second data String
      NBIT=SNBIT.toInt();      
      SNPULSE = readString.substring(ind3+1);
      NPULSE=SNPULSE.toInt();      
       
      
      if (DEBUG_ON==1){Serial.print("protocol = ");
                       Serial.println(PROTOCOL);
                       Serial.print("code = ");
                       Serial.println(CODE);
                       Serial.print("nbits = ");
                       Serial.println(NBIT);
                       Serial.print("npulse = ");
                       Serial.println(NPULSE);
                       Serial.println();};

      REMOTE_CONTROL(PROTOCOL,CODE,NBIT,NPULSE);  
      Serial.println("OK");
      readString="";     
    } 
    else {     
      readString += c; 
    }
  }


  
}
