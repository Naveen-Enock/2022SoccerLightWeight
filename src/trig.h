
#ifndef trig
#define trig
#include <Arduino.h>
static bool logAllowed = false;
inline double toRadians(double deg) { return deg * M_PI / 180.0; }
inline double toDegrees(double theta) { return theta * 180.0 / M_PI; }
inline void Log(const char *s) { if(logAllowed) Serial.print(s);}
inline void Log(double d) { if(logAllowed) Serial.print(d);}
inline void Log(int i) { if(logAllowed) Serial.print(i);}
inline void Logln(const char *s) { if(logAllowed) Serial.println(s);}
inline void Logln(double d) { if(logAllowed) Serial.println(d);}
inline void Logln(int i) { if(logAllowed) Serial.println(i);}

#endif