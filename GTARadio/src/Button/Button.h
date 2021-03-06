class Button{
public:
    Button(int pin);
    void setup();
    bool stateChanged();
    
private:
    int buttonPin;    // the number of the pushbutton pin
    int buttonState;             // the current reading from the input pin
    int lastButtonState = LOW;   // the previous reading from the input pin
    unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
    unsigned long debounceDelay = 100; 
};