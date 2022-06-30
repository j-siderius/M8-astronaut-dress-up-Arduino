#include <Servo.h>

class ServoThing {
    private:
        int pin;
        Servo servo;

    public:
        ServoThing(int pin) {
            this->pin = pin;
        }

        void begin() {
            servo.attach(pin);
        }

        void move(int position) {
            servo.write(position);
        }
};