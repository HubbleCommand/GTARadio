class Potentiometer{
public:
    Potentiometer(int pin, unsigned long increment);
    int getState();
    bool stateChanged();
    
private:
    int potPin;                     // the number of the potentiometer pin
    int potState;                   // the current reading from the input pin
    int lastPotState = 0;           // the previous reading from the input pin
    unsigned long potIncrement;     // the increment to consider as a new value
};