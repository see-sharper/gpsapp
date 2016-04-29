// First, let's create our "shorthand" for the pins
// Same as in the Blink an LED example:

int ledPin = D7;
FuelGauge fuel;

void setup()
{

   // Here's the pin configuration, same as last time
   pinMode(ledPin, OUTPUT);

   // declare a Spark.function so that we can turn the LED on and off from the cloud.
   Particle.function("led",ledToggle);

   // declare a Spark.function so that we can get the battery status
   Particle.function("battLevel", pubBatt);

   // For good measure, let's also make sure both LEDs are off when we start:
   digitalWrite(ledPin, LOW);

}


void loop()
{
   // Nothing to do here
}

// We're going to have a super cool function now that gets called when a matching API request is sent
// This is the ledToggle function we registered to the "led" Spark.function earlier.


int ledToggle(String command) {
    /* Spark.functions always take a string as an argument and return an integer.
    Since we can pass a string, it means that we can give the program commands on how the function should be used.
    In this case, telling the function "on" will turn the LED on and telling it "off" will turn the LED off.
    Then, the function returns a value to us to let us know what happened.
    In this case, it will return 1 for the LEDs turning on, 0 for the LEDs turning off,
    and -1 if we received a totally bogus command that didn't do anything to the LEDs.
    */

    if (command=="on") {
        digitalWrite(ledPin,HIGH);
        return 1;
    }
    else if (command=="off") {
        digitalWrite(ledPin,LOW);
        return 0;
    }
    else {
        return -1;
    }
}

int pubBatt(String command){
    // Publish the battery voltage and percentage of battery remaining
    // if you want to be really efficient, just report one of these
    // the String::format("%f.2") part gives us a string to publish,
    // but with only 2 decimal points to save space
    Particle.publish("B",
          "v:" + String::format("%.2f",fuel.getVCell()) +
          ",c:" + String::format("%.2f",fuel.getSoC()),
          60, PRIVATE
    );
    // if there's more than 10% of the battery left, then return 1
    //if(fuel.getSoC()>10){ return 1;}
    // if you're running out of battery, return 0
    //else { return 0;}
    return(int(fuel.getSoC()));
}
