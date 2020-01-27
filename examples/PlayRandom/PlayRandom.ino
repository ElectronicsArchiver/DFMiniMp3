// this example will play a random track from all on the sd 
//
// it expects the sd card to contain some mp3 files

#include <SoftwareSerial.h>
#include <DFMiniMp3.h>

// implement a notification class,
// its member methods will get called 
//
class Mp3Notify
{
public:
  static void OnError(uint16_t errorCode)
  {
    // see DfMp3_Error for code meaning
    Serial.println();
    Serial.print("Com Error ");
    Serial.println(errorCode);
  }
  static void OnPlayFinished(DfMp3_PlaySource source, uint16_t track)
  {
    Serial.print("Play finished for #");
    Serial.println(track);  
  }
  static void OnPlaySourceOnline(DfMp3_PlaySource source)
  {
    if (source & DfMp3_PlaySource_Sd) 
    {
        Serial.println("Card online ");
    }
    if (source & DfMp3_PlaySource_Usb) 
    {
        Serial.println("USB Disk online ");
    }
  }
  static void OnPlaySourceInserted(DfMp3_PlaySource source)
  {
    if (source & DfMp3_PlaySource_Sd) 
    {
        Serial.println("Card inserted ");
    }
    if (source & DfMp3_PlaySource_Usb) 
    {
        Serial.println("USB Disk inserted ");
    }
  }
  static void OnPlaySourceRemoved(DfMp3_PlaySource source)
  {
    if (source & DfMp3_PlaySource_Sd) 
    {
        Serial.println("Card removed ");
    }
    if (source & DfMp3_PlaySource_Usb) 
    {
        Serial.println("USB Disk removed ");
    }
  }
};

// instance a DFMiniMp3 object, 
// defined with the above notification class and the hardware serial class
//
DFMiniMp3<HardwareSerial, Mp3Notify> mp3(Serial1);

// Some arduino boards only have one hardware serial port, so a software serial port is needed instead.
// comment out the above definition and uncomment these lines
//SoftwareSerial secondarySerial(10, 11); // RX, TX
//DFMiniMp3<SoftwareSerial, Mp3Notify> mp3(secondarySerial);

void setup() 
{
  
  Serial.begin(115200);

  Serial.println("initializing...");
  
  mp3.begin();
  mp3.reset(); 
  
  // show some properties and set the volume
  uint16_t volume = mp3.getVolume();
  Serial.print("volume ");
  Serial.println(volume);
  mp3.setVolume(24);
  
  uint16_t count = mp3.getTotalTrackCount(DfMp3_PlaySource_Sd);
  Serial.print("files ");
  Serial.println(count);

  uint16_t mode = mp3.getPlaybackMode();
  Serial.print("playback mode ");
  Serial.println(mode);
  
  Serial.println("starting...");
  
  mp3.playRandomTrackFromAll(); // random of all folders on sd
}

void loop() 
{
  // calling mp3.loop() periodically allows for notifications 
  // to be handled without interrupts
  mp3.loop();
}
