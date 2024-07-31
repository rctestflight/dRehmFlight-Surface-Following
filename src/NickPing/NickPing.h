#include <Arduino.h>



class NickPing {
    public:
        int maxPing = 0;
        int myTrigPin = 0;
        int myEchoPin = 0;

        int initCounter = 0;
        bool firstCheck = false;

        unsigned long t_prev = 0;
        unsigned long myOffset = 0;

        bool pulse_started = false;
        unsigned long pulse_ended_time = 0;

        bool firstChange = false;
        unsigned long pulseStart = 0;
        unsigned long echoLength = 0;
        float dist_cm = 0.0;


        NickPing() // constructor 
        {


        }

        void begin(int trigPin, int echoPin, int maxping)
        {
            myTrigPin = trigPin;
            myEchoPin = echoPin;
            maxPing = maxping;
            pinMode(myTrigPin, OUTPUT);
            pinMode(myEchoPin, INPUT);
        }

        void processInterrupt()
        {
            if (digitalRead(myEchoPin) == 1) //rising edge
            {
                pulseStart = micros();
                pulse_started = true;
                //Serial.println("rising edge");
            }

            if (digitalRead(myEchoPin) == 0) //falling edge
            {
                if (pulse_started == false)
                {
                    
                }
                else
                {
                    pulse_started = false;
                    pulse_ended_time = micros();
                    echoLength = micros() - pulseStart;
                    //Serial.println("falling edge, time = ");
                    //Serial.println(echoLength);
                    if (echoLength / 60.0 > 150)
                    {
                        dist_cm = 0.0;
                    }
                    else
                    {
                        dist_cm = echoLength / 60.0;
                    }
                    dist_cm = constrain(dist_cm, 0.0, 120.0);
                    //Serial.println(dist_cm);
                }
            }

        }

        bool update(int flag)
        {

            if (micros() - t_prev > 20000) //50hz
            { 
                t_prev = micros();
                if (pulse_started == false) // only send if there is not a pulse out
                {
                    digitalWrite(myTrigPin, 1);
                    delayMicroseconds(12);
                    digitalWrite(myTrigPin, 0);
                    //Serial.print("Sent: ");
                    //Serial.println(flag);
                }
            }
        return pulse_started;
        }




    private:








};