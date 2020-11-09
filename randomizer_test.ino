// uncomment if using nodemcu board
//#define _USE_NODEMCU_  

#ifdef _USE_NODEMCU_
  #include <ESP8266TrueRandom.h>
#endif

// edit acordingly
#define RED 5 
#define BLUE 4
#define GREEN 10

#define SAMPLE 1 // if you sample more it will take the average of all sample as result
#define RANGE 3000 // range of the random number

#define PRINT_EVERY 1 // if 1 print all
#define PRINT_PER_LINE 1 // if 1 print all in one line

#define DELAY 300 // delay between each number generation

long randNumber;
int printed;
int index_array;
int numbers[SAMPLE];

void setup() {
  index_array = 0;
  printed = 0;
  Serial.begin(9600);
  
  #ifndef _USE_NODEMCU_
    randomSeed(analogRead(0));
  #endif
  
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  
  digitalWrite(RED, LOW);
  digitalWrite(BLUE, LOW);
  digitalWrite(GREEN, LOW);
}

void change_color(){
  digitalWrite(RED, LOW);
  digitalWrite(BLUE, LOW);
  digitalWrite(GREEN, LOW); 
  long num = 0;
  for(int i=0 ;i < SAMPLE; i++){
    num += numbers[i];
  }
  num = num / SAMPLE;
  
  Serial.println("");
  Serial.println("-----------");
  Serial.print("result : ");
  Serial.print(num);
  
  if(num <= (RANGE / 3)){
    digitalWrite(RED, HIGH);
    Serial.println(" => Red");
  }
  else{
    if(num <= ((RANGE/3)*2)){
      digitalWrite(GREEN, HIGH);
      Serial.println(" => Green");
    }
    else{
      digitalWrite(BLUE, HIGH);
      Serial.println(" => Blue");
    }
  }
  
  Serial.println("-----------");
}

void loop() {
  
  #ifdef _USE_NODEMCU_
    randNumber = ESP8266TrueRandom.random(1,RANGE);
  #else
    randNumber = random(1,RANGE);
  #endif
  
  if( index_array % PRINT_EVERY == 0){
    printed++;
    Serial.print(" ");
    Serial.print(randNumber);
    if(printed == PRINT_PER_LINE){
      Serial.println("");
      printed = 0;
    }
  }
  delay(DELAY);
  numbers[index_array] = (int) randNumber;
  index_array++;
  if(index_array == SAMPLE){
    change_color();
    index_array = 0;
  }                 
}
