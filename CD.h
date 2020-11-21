#if !defined CD_H
#define CD_H

#include "Song.h"
#include "String_.h"
using CSC1310::String;
#include "ListArray.h"
using CSC1310::ListArray;

class CD
{
   private:
      String* artist;
      String* title;

      int year;
      int rating;
      int num_tracks;

      ListArray<Song>* songs;

   public:
      CD(String* artist, String* title, int year, int rating, int num_tracks);
      virtual ~CD();

      String* getKey();
      void addSong(String* title, String* length);
      void displayCD();

      static ListArray<CD>* readCDs(const char* file_name);

      static int compare_items(CD* one, CD* two);
      static int compare_keys(String* sk, CD* cd);
      static char getRadixChar(CD* cd, int index);  //1-based
};

#endif
