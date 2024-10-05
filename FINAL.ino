#include <LiquidCrystal_I2C.h>
#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52 
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978
#define REST 0

#define I2C_ADDR  0x27
#define LCD_COLUMNS 16
#define LCD_LINES 2

LiquidCrystal_I2C lcd(I2C_ADDR,LCD_COLUMNS,LCD_LINES);

byte white[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

byte wall[8] = {
  B01110,
  B01110,
  B01110,
  B01110,
  B01110,
  B01110,
  B01110,
  B01110
};

byte people[8] = {
  B00000,
  B01110,
  B01110,
  B00100,
  B01110,
  B00100,
  B00100,
  B01010
};

  int tempo = 180;
  int buzzer = 26;
  int melody[] = {
  NOTE_E5, NOTE_D5, NOTE_FS4, NOTE_GS4,
  NOTE_CS5, NOTE_B4, NOTE_D4, NOTE_E4,
  NOTE_B4, NOTE_A4, NOTE_CS4, NOTE_E4, NOTE_A4,REST,REST,REST
  };
  int interval[] = {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,8,8};
  int notes = sizeof(melody)/ sizeof(melody[0]);
  int wholenote = (60000 * 4) / tempo;
  int divider = 0, noteDuration = 0;

void setup() 
{

  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.createChar(0,white);
  lcd.createChar(1,wall);
  lcd.createChar(2,people);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write(byte(2));
  pinMode(27,INPUT_PULLUP);
}

void loop()
{
  lcd.clear();
  Serial.println("start");
  lcd.setCursor(0,0);
  lcd.write(byte(2));
  int i=1,j=15,k,sco=0,delaynum,PlayNote = 0,rand,btn1;
  delaynum = 300;
  while(i==1){
    rand = random(0, 2);
    if(sco > 1 && delaynum > 50)
    {
      delaynum -= 50;
    }else if(delaynum <= 50 && delaynum > 5){
      delaynum -=5;
    }
  while(j > -1)
  {
    lcd.setCursor(j,rand);
    lcd.write(byte(1));
    delay(delaynum);
    lcd.setCursor(j,rand);
    lcd.write(byte(0));
    j--;

    btn1 = digitalRead(27);
    if(btn1==0)
    {
      if(k == 0){
        k=1;
        lcd.setCursor(0,0);
        lcd.write(byte(0));
        lcd.setCursor(0,k);
        lcd.write(byte(2));
      }else{
        k=0;
        lcd.setCursor(0,1);
        lcd.write(byte(0));
        lcd.setCursor(0,k);
        lcd.write(byte(2));
      }
    }
    Serial.println(btn1);
    if(j==0 && k==rand)
    {
      lcd.setCursor(5,0);
      lcd.print("Game Over");
      lcd.setCursor(5,1);
      lcd.print("SCORE:");
      lcd.print(char((sco/10)+48));
      lcd.print(char((sco%10)+48));
      i=0;
      break;
    }

  if(PlayNote < notes)
  {
    divider = interval[PlayNote];
    if (divider > 0) 
    {
      noteDuration = (wholenote) / divider;
    }
    else if (divider < 0)
    {
      noteDuration = (wholenote) / abs(divider);
    }
    tone(buzzer, melody[PlayNote], noteDuration * 1);
    delay(noteDuration);
    noTone(buzzer);
    PlayNote++;
  }

}
  PlayNote=0;
  sco++;
  j = 14;
  }

  delay(5000);
}