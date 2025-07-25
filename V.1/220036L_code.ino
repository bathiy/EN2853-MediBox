#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHTesp.h>
#include <WiFi.h>

//OLED display define
#define ScreenWidth 128
#define ScreenHeight 64
#define OLEDRset -1
#define ScreenAddress 0x3C  

//Pin Define
#define buzzer 12
#define led 14
#define cancel 27
#define Ok 33
#define up 32
#define down 35
#define DHTPIN 13

//Server 
#define NTP_SERVER     "pool.ntp.org"
#define UTC_OFFSET     0

float UTC_OFFSET_DST = 19800; //Sri Lanka time
float offset = 0;

int notes[] = {262, 294, 330, 349, 392, 440, 494, 523};

//Store alarm details. Set 2 alarms
int current_mode = 0;
int max_modes    = 5;
String modes[]   = {"1-Set Time Zone", "2-Set Alarm 1", "3-Set Alarm 2", "4-View Alarms", "5-Delete Alarms"};

int days  = 0;
int hours = 0;
int minu  = 0;
int sec   = 0;
int month = 0;

bool alarm_enabled     = true;
int n_alarms           = 2;
int alarm_hours[]      = {0, 11};
int alarm_minu[]       = {0, 33};
bool alarm_triggered[] = {false, false}; 
bool alarm_exist[]     = {false, true};

//Decalare objects
Adafruit_SSD1306 display(ScreenWidth, ScreenHeight, &Wire, OLEDRset);
DHTesp dhtSensor;

//Functions declare
void check_temp(void);
void run_mode(int mode);
void display_active_alarms(void);
void set_alarm(int alarm);
void set_time_zone(void);
void go_to_menu(void);
void update_time_and_check_alarm(void); 
void alarm_ring(int index);
void updatedateandtime(void);
void print_ln(String text, int size, int row, int column);
void dateAndTime(void);
void delete_alarms(void);
int wait_for_button(void);
float transformUTC(float DSToffset);

void setup()
{
  //Output Pins
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  //Input Pins
  pinMode(cancel, INPUT);
  pinMode(Ok, INPUT);
  pinMode(up, INPUT);
  pinMode(down, INPUT);

  dhtSensor.setup(DHTPIN, DHTesp::DHT22);

  Wire.begin();
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, ScreenAddress))
  {
    Serial.println("SSD1306 allocation failed");
    for (;;);  
  }

  WiFi.begin("Wokwi-GUEST");
  while (WiFi.status() != WL_CONNECTED) {  
      delay(250);
      display.clearDisplay();
      print_ln("Connecting...", 2, 0, 0);
  }

  //WiFi if connected
  display.clearDisplay();
  print_ln("Connected :)", 2, 0, 0);
  
  //Time configuration
  configTime(UTC_OFFSET, UTC_OFFSET_DST, NTP_SERVER);
  delay(500);
  display.clearDisplay();
  delay(200);
  print_ln("Hello", 2, 20, 30); 
  delay(3000);
  display.clearDisplay();
  print_ln("Welcome to MediBox!", 2, 20, 0);
  delay(2000);
  display.clearDisplay(); 
}

void loop()
{
  update_time_and_check_alarm(); 

  if (digitalRead(Ok) == LOW){
    delay(200);
    go_to_menu();
  }
  check_temp();
}

//Displaying function
void print_ln(String text, int size, int row, int column)
{
  display.clearDisplay();  
  display.setTextSize(size);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(column, row);
  display.println(text);
  display.display();
}

//Displaying function without clearing
void print_ln_noclear(String text, int size, int row, int column)
{
  display.setTextSize(size);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(column, row);
  display.println(text);
  display.display();
}

//Show date and time
void dateAndTime(void)
{
  display.clearDisplay();
  String time = ((hours < 10) ? "0": "") + String(hours) + ":" + ((minu < 10) ? "0": "") + String(minu) + ":" + ((sec < 10) ? "0": "") + String(sec); 
  String date = "Date:" + String(days) + "/" + String(month);
  String datetime = time + "           " + date;
  print_ln(datetime, 2, 10, 18);

}

//Updating date and time in relevant variables
void updatedateandtime(void)
{
  struct tm timeinfo;
  getLocalTime(&timeinfo);

  char timeHour[3];
  strftime(timeHour, 3, "%H", &timeinfo);
  hours = atoi(timeHour);

  char timeminutes[3];
  strftime(timeminutes, 3, "%M", &timeinfo);
  minu = atoi(timeminutes);

  char timesec[3];
  strftime(timesec, 3, "%S", &timeinfo);
  sec = atoi(timesec);

  char timedays[3];
  strftime(timedays, 3, "%d", &timeinfo);
  days = atoi(timedays);

  char timeMonth[3];
  strftime(timeMonth,3,"%m",&timeinfo);
  month = atoi(timeMonth);
}

//Alarms rings at set times
void alarm_ring(int index)
{
  display.clearDisplay();
  print_ln("Take      Medicine", 2, 10, 0);
  digitalWrite(led, HIGH);

  bool break_happend = false;
  //Ring until cancel button is pressed
  while(break_happend == false && digitalRead(cancel) == HIGH)
  {
    for (int i = 0; i < 8; i++) 
    {
      if (digitalRead(cancel) == LOW)
      {
        delay(200);
        break_happend = true;
        break;
      }
      tone(buzzer, notes[i]);
      delay(500); 
      noTone(buzzer);
      delay(5);
    }
  } 
  digitalWrite(led, LOW); 
  display.clearDisplay();
  //Choose snoozing 5 min or off the alarm
  print_ln("Up:Snooze Down:OFF", 2, 5, 0);

  while (true){
    if (digitalRead(up) == LOW)
    {
      delay(200);  
      
      if(alarm_minu[index] >= 55)
      {
        alarm_hours[index] += 1;
        alarm_hours[index] = alarm_hours[index] % 24; 
      }

      alarm_minu[index] += 5;
      alarm_minu[index] = alarm_minu[index] % 60;

      display.clearDisplay();
      print_ln("Alarm SNOOZED", 2, 10, 0);
      delay(1000);
      break;
    }
    else if (digitalRead(down) == LOW)
    {
      delay(200);
      alarm_triggered[index] = true;
      display.clearDisplay();
      print_ln("Alarm OFF", 2, 10, 0);
      delay(1000);
      break;
    }
  }
  display.clearDisplay();
}

//Checking alarm while updating time
void update_time_and_check_alarm(void) 
{
  updatedateandtime();
  dateAndTime();
  
  if (alarm_enabled == true) 
  {
    for (int i = 0; i < n_alarms; i++)
    {
      if (alarm_exist[i] == true && alarm_triggered[i] == false && alarm_hours[i] == hours && alarm_minu[i] == minu)
      {
        alarm_ring(i);        
      }
      if (alarm_hours[i] == 0 && alarm_minu[i] == 0)
      {
        alarm_triggered[i] = false;
      }
    }
  }
}

//Button outputs for below functions
int wait_for_button(void)
{
  while (true){
    if(digitalRead(up) == LOW){
      delay(200);
      return up;
    }

    else if(digitalRead(down) == LOW){
      delay(200);
      return down;
    }

    else if(digitalRead(Ok) == LOW){
      delay(200);
      return Ok;
    }

    else if(digitalRead(cancel) == LOW){
      delay(200);
      return cancel;
    }

    updatedateandtime();
  }
}

//Menu function
void go_to_menu(void)
{
  //delay(500);
  while(true){
    display.clearDisplay();
    print_ln(modes[current_mode], 2, 10, 0);

    int press = wait_for_button();

    if (press == up){
      delay(200);
      current_mode += 1;
      current_mode = current_mode % max_modes;
    }

    else if (press == down){
      delay(200);
      current_mode -= 1;
      if (current_mode < 0){
        current_mode = max_modes - 1;
      }
    }
    
    //Select wanted menu option
    else if (press == Ok){
      delay(200);
      run_mode(current_mode);
      }

    else if (press == cancel){
      current_mode = 0;
      delay(200);
      break;
      }   
  }
}

//UTC show as usual
float transformUTC(float UTCoffset)
{
  float fPart = UTCoffset - (int)UTCoffset;
  float maping = (int)UTCoffset + 0.6 * fPart;
  return maping;
}

//Set the time according to the given DST by the user
void set_time_zone(void)
{
  float temp_time_offset=offset;
  while (true){
    display.clearDisplay();
    float temp_mapping = transformUTC(temp_time_offset);

    print_ln("Enter UTC offset:      " + String(temp_mapping),2,10,0);
    int pressed = wait_for_button();
        
    if (pressed == up & temp_time_offset <12){             
      delay(200);
      temp_time_offset+=0.25;
    }

    else if (pressed == down & temp_time_offset > -12){    
      delay(200);
      temp_time_offset-=0.25;
    }

    else if (pressed == Ok){
      delay(200);
      UTC_OFFSET_DST = temp_time_offset * 3600;
      offset = temp_time_offset;
      configTime(UTC_OFFSET, UTC_OFFSET_DST, NTP_SERVER);
      Serial.println(UTC_OFFSET_DST);
      print_ln("Time Zone set", 2, 10, 0);
      delay(1000);
      break;
    }

    else if (pressed == cancel){
      delay(200);
      return;
    }
  }
}

//Set alarms for alarm 1 and alarm 2
void set_alarm(int alarm)
{
  int temp_hour = alarm_hours[alarm];
  while (true){
    display.clearDisplay();
    print_ln("Enter hour: "+String(temp_hour), 2, 10, 0);

    int press = wait_for_button();
      if (press == up){
        delay(200);
        temp_hour += 1;
        temp_hour = temp_hour % 24;
      }

      else if (press == down){
        delay(200);
        temp_hour -= 1;
        if (temp_hour < 0){
          temp_hour = 23;
        }
      }

      else if (press == Ok){
        delay(200);
        alarm_hours[alarm] = temp_hour;
        break;
        }

      else if (press == cancel){
        delay(200);
        return;
        }
  }

  int temp_min = alarm_minu[alarm];
  while (true){
    display.clearDisplay();
    print_ln("Enter minutes: "+String(temp_min), 2, 10, 0);

    int press = wait_for_button();
    if (press == up){
      delay(200);
      temp_min += 1;
      temp_min = temp_min % 60;
    }

    else if (press == down){
      delay(200);
      temp_min -= 1;
      if (temp_min < 0){
       temp_min = 59;
      }
    }

    else if (press == Ok){
      delay(200);
      alarm_minu[alarm] = temp_min;
      alarm_triggered[alarm] = false;
      alarm_exist[alarm] = true;
      break;
    }

    else if (press == cancel){
      delay(200);
      return;
    }
  } 
  display.clearDisplay();
  print_ln("Alarm "+String(alarm + 1)+" is set", 2, 10, 0);
  delay(1000); 
}

//Delete alarm
void delete_alarms(void)
{
  int alarm = 0;
  while(true)
  {
    display.clearDisplay();    
    print_ln("Delete the Alarm " +  String(alarm + 1), 2, 10, 0);

    int press = wait_for_button();

    if (press == up)
    {
      delay(200);
      alarm += 1;
      alarm = alarm % 2;
    }

    else if (press == down)
    {
      delay(200);
      alarm -= 1;
      if (alarm < 0){
        alarm = 1;
      }
    }

    else if (press == Ok)
    {
      delay(200);
      alarm_hours[alarm] = 0;
      alarm_minu[alarm] = 0;
      alarm_exist[alarm] = false;
      print_ln("Alarm " + String(alarm + 1) + " is Deleted", 2, 10, 0);
      delay(1000);
      break;
      }

    else if (press == cancel)
    {
      delay(200);
      break;
    }   
  }
}

//Display the activated alarm
void display_active_alarms(void) 
{
  display.clearDisplay();  
  int y_position = 20;  

  for (int i = 0; i < n_alarms; i++) {
    if (alarm_exist[i] == true) 
    {  
      String alarm_text = "Alarm " + String(i + 1) + ": " + String(alarm_hours[i]) + ":" + String(alarm_minu[i]); 
      print_ln_noclear(alarm_text, 1, y_position, 1); 
      y_position += 10;  
    }
    else 
    {
      print_ln_noclear("No active alarm " + String(i + 1), 1, y_position, 1);
      y_position += 10; 
    }
  }

  delay(4000);
}

//Each menu options
void run_mode(int mode){
  if (mode == 0){
    set_time_zone();
  }

  else if (mode == 1|| mode == 2){
    set_alarm(mode - 1);
  }

  else if (mode == 3){
    display_active_alarms();
  }

  else if(mode == 4){
    delete_alarms();
  }
}

//Check the humidity and the tempurature
void check_temp(void){
  TempAndHumidity data = dhtSensor.getTempAndHumidity();
  if (data.temperature > 32){
    display.clearDisplay();
    print_ln("TEMP HIGH", 2, 5, 20);

    tone(buzzer, notes[0]);
    delay(1000); 
    noTone(buzzer);
    delay(50);
  }
  else if (data.temperature < 24){
    display.clearDisplay();
    print_ln("TEMP LOW", 2, 5, 20);  

    tone(buzzer, notes[0]);
    delay(1000); 
    noTone(buzzer); 
    delay(50);
  }
    
  if (data.humidity > 80){
    display.clearDisplay();
    print_ln("HUMIDITY  HIGH", 2, 5, 30);

    tone(buzzer, notes[1]);
    delay(1000); 
    noTone(buzzer);
    delay(50);
  }   
  else if (data.humidity < 65){
    display.clearDisplay();
    print_ln("HUMIDITY  LOW", 2, 5, 30);

    tone(buzzer, notes[1]);
    delay(1000); 
    noTone(buzzer);
    delay(50);
  }
}