#include <dht.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define DHT11_PIN 7


dht DHT;

//intializing variables.
int moisture,temp,light,humid,val;



char okState[] =  "happy ";
char coolState[] =  "heater plz";
char hotState[] = "AC req";
char dryState[] = "Thirsty ";
char moistState[] = "Flooding";
char darkState[] = "Give me some sun shine";


void interpretSituation(){
  
    boolean tempWasGood = true;
    boolean moistWasGood = true;
    boolean lightWasGood = true;


    // Check temperature
    if (temp < 19) {
        lcd.print(coolState);
        lcd.print("\n");
        
        Serial.println(coolState);
        
        tempWasGood = false;
        
        digitalWrite(13, HIGH);
    
    } else if (temp > 35) {
        lcd.print(hotState);
        
        Serial.println(hotState);
        
        tempWasGood = false; 
        
        digitalWrite(13, HIGH);  
    }

    // Check moisture
    if (moisture > 70) {
        lcd.print(moistState);
        
        Serial.println(moistState);
        
        moistWasGood = false;
        
        digitalWrite(13, HIGH);
    
    } else if (moisture < 20) {
        lcd.print(dryState);
        
        Serial.println(dryState);
        
        moistWasGood = false; 
        
        digitalWrite(13, HIGH);  
    }

    // Check light
    if (light < 50) {
        lcd.print(darkState);
        
        Serial.println(darkState);
        
        lightWasGood = false;
        
        digitalWrite(13, HIGH);
    }

    // If everything was good
    if (tempWasGood && moistWasGood && lightWasGood) {
        lcd.print(okState);
        
        Serial.println(okState);
        
        digitalWrite(13, LOW);
    }
}

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  
  pinMode(13, OUTPUT);

  analogWrite(6,20);
  
  
  lcd.begin(16, 2);
  
  lcd.setCursor(0, 0);

  Serial.println("Reading From the Sensors ...");

  

  //delay(2000);
}

void loop() {
  
  // put your main code here, to run repeatedly:
  //moisture reading is taken from A0 analog pin.
  moisture = analogRead(A0);
  
  moisture = map(moisture,1023,0,0,100);

  Serial.print("Moisture Reading is :");
  
  Serial.print(moisture);
  
  Serial.println("%");

  //temperature,humidity readings are taken from dht11
  int chk = DHT.read11(DHT11_PIN);

  temp = DHT.temperature;

  humid = DHT.humidity;
  
  Serial.print("Temperature = ");
  
  Serial.println(temp);
  
  Serial.print("Humidity = ");
  
  Serial.println(humid);


  //taking light readings from A1 analog pin.
  light = analogRead(A1);
  
  light = map(light,1023,0,0,100);
  
  Serial.print("Light Reading is :");
  
  Serial.println(light);
 
  lcd.autoscroll();

  //calling the function to know the present situation
  interpretSituation();
  
  Serial.println("----------------------");
  
  delay(2000);
  
}
