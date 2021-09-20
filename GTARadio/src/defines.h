#define SD_ChipSelectPin 4

#if ((defined(__AVR_ATmega2560__) || defined(__AVR_ATmega2561__)))
    #define TMRPCM_SPEAKER_PIN 11   //Use pin 11 on the MEGA
#else
    #define TMRPCM_SPEAKER_PIN 9    //Use pin 9  on the UNO
#endif

#define NUMBER_OF_STATIONS 39

#define ROWS 4 //Or 2
#if ROWS == 2
    //If we only have two rows, cannot display all info. -1 is fine, as the ScreenController handles when line no is less than 0
    #define LCD_INTRO_LINE -1
    #define LCD_CHANNEL_LINE 0
    #define LCD_SONG_LINE 1
    #define LCD_VOL_LINE -1
#elif ROWS == 4
    #define LCD_INTRO_LINE 0
    #define LCD_CHANNEL_LINE 1
    #define LCD_SONG_LINE 2
    #define LCD_VOL_LINE 3
#else
    //Otherwise, something is WIERD, don't print anything
    #define LCD_INTRO_LINE -1
    #define LCD_CHANNEL_LINE -1
    #define LCD_SONG_LINE -1
    #define LCD_VOL_LINE -1
#endif