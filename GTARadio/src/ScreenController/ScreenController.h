#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

class ScreenController{
public:
    ScreenController(uint8_t addr, int x, int y);
    void setup();
    void setText(String *text);
    void setLine(int lineNo, String text);
    void update();
    
private:
    int x, y;
    String *text;
    LiquidCrystal_I2C* lcd; 
};