#if !defined SONG_H
#define SONG_H

#include "String_.h"
using CSC1310::String;

class Song
{
   private:
      String* title;
      String* length;

   public:
      Song(String* title, String* length);
      virtual ~Song();
      void displaySong();
};

#endif
