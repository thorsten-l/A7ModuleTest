#include <Arduino.h>

#include <string.h>
#include <SoftwareSerial.h>

// Elecrow A7 module PINs
#define RESET_PIN     4
#define ENABLE_PIN    5
#define PWRKEY_PIN    8

#define console       Serial
#define gsmSerial     Serial1

// 2nd Serial for a seperate Ai-Thinker A7 module
SoftwareSerial gpsSerial( 10, 16 );  // RX=10, TX=16, (Arduino Pro Micro)

char inputBuffer[256];   // console input buffer
char inputBuffer2[256];  // input buffer converted to lower case
int inputCursor;
bool gpsReceiver;

void sendCommand( String command )
{
  gsmSerial.flush();
  delay(500);
  console.println(command);
  gsmSerial.print(command);
  gsmSerial.write('\r');
  delay(100);

  while( gsmSerial.available())
  {
    console.write(gsmSerial.read());
  }
}

void waitForGSMBecomeReady()
{
  for( int i=0; i<15; i++)
  {
    char buffer[3];
    char index = 0;

    gsmSerial.flush();
    delay(1000);
    console.print('.');
    gsmSerial.print("AT\r");
    gsmSerial.flush();
    delay(100);

    while( gsmSerial.available())
    {
      char c = gsmSerial.read();

      if ( c == '\r' || c == '\n' )
      {
        if ( buffer[0] == 'O' && buffer[1] == 'K' && index == 2 )
        {
          return;
        }

        index = 0;
      }
      else
      if( index < 3 )
      {
        buffer[index++] = c;
      }
    }
  }
}

void setup()
{
  pinMode( RESET_PIN, OUTPUT );
  pinMode( ENABLE_PIN, OUTPUT );
  pinMode( PWRKEY_PIN, OUTPUT );

  digitalWrite( RESET_PIN, HIGH );
  digitalWrite( ENABLE_PIN, HIGH );
  digitalWrite( PWRKEY_PIN, HIGH );

  console.begin(115200);

  gpsReceiver = false;
  inputCursor = 0;
  inputBuffer[0] = 0;
  inputBuffer2[0] = 0;

  delay(3000);
  digitalWrite( RESET_PIN, LOW );

  console.println();
  console.println();
  console.println("A7 Module Test - 0.1.4 - Dr. Thorsten Ludewig <t.ludewig@gmail.com>");
  console.println("BUILD: " __DATE__ " " __TIME__ );
  console.println();
  gpsSerial.begin(9600);
  gsmSerial.begin(115200);
  delay(1000);
  waitForGSMBecomeReady();
  sendCommand("AT+IPR=9600");
  gsmSerial.begin(9600);
  waitForGSMBecomeReady();
  console.println( "\nGSM module is ready." );
}

void parseConsole()
{
  if ( console.available() )
  {
    char c = Serial.read();
    console.write( c );

    if( c == '\r' || c == '\n' )
    {
      if ( inputCursor > 0 )
      {
        inputCursor = 0;

        console.println( "\n------------------------------------------------------------------" );

        if ( strlen(inputBuffer2) == 6 && strncmp( "gps=on", inputBuffer2, 6 ) == 0 )
        {
          console.println( "Set GPS receiver ON" );
          gpsReceiver = true;
        }

        if ( strlen(inputBuffer2) == 7 && strncmp( "gps=off", inputBuffer2, 7 ) == 0 )
        {
          console.println( "Set GPS receiver OFF" );
          gpsReceiver = false;
        }

        if ( strlen(inputBuffer2) == 5 && strncmp( "ctrlz", inputBuffer2, 5 ) == 0 )
        {
          console.println( "Sending CTRL-Z to GSM module" );
          gsmSerial.write( 26 );
          gsmSerial.flush();
        }

        if( strncmp( "at", inputBuffer2, 2 ) == 0 )
        {
          gsmSerial.print(inputBuffer);
          gsmSerial.write( "\r" );
          gsmSerial.flush();
        }

        if( inputBuffer[0] == '\'' )
        {
          gsmSerial.print(inputBuffer+1);
          gsmSerial.write( "\r" );
          gsmSerial.flush();
        }
      }
    }
    else
    {
      inputBuffer[inputCursor] = c;
      c |= 32; // convert to lower case for ASCII characters
      inputBuffer2[inputCursor++] = c;
      inputBuffer[inputCursor] = 0;
      inputBuffer2[inputCursor] = 0;
      inputCursor %= 255;
    }
  }
}


void loop()
{

  parseConsole();

  if( gsmSerial.available())
  {
    console.write( gsmSerial.read());
  }

  if( gpsReceiver && gpsSerial.available())
  {
    console.write( gpsSerial.read());
  }
}
