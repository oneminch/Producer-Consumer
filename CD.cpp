#include "CD.h"

#include "ListArrayIterator.h"
#include "ReadFile.h"
#include "Tokens.h"
using namespace CSC1310;

#include <iostream>
using namespace std;

char CD::getRadixChar(CD* cd, int index)  //1-based
{
   String* title = cd->getKey();
   int title_len = title->length();
   if (index <= title_len) 
   {
      return title->charAt(index - 1);
   }
   else
   {
      return 32; //ascii for a space
   }
}

int CD::compare_items(CD* one, CD* two)
{
   String* title_1 = one->getKey();
   String* title_2 = two->getKey();
   int title_compare = title_1->compare(title_2);  //asc
   return title_compare;
}

int CD::compare_keys(String* sk, CD* cd)
{
   String* title_1 = sk;
   String* title_2 = cd->getKey();
   int title_compare = title_1->compare(title_2);  //asc
   return title_compare;
}

CD::CD(String* artist, String* title, int year, int rating, int num_tracks)
{
   this->artist = artist;
   this->title = title;
   this->year = year;
   this->rating = rating;
   this->num_tracks = num_tracks;

   songs = new ListArray<Song>();
}

CD::~CD()
{
   ListArrayIterator<Song>* iter = songs->iterator();
   while(iter->hasNext())
   {
      Song* song = iter->next();
      delete song;
   }
   delete iter;

   delete songs;
   songs = NULL;

   delete artist;
   delete title;
}

String* CD::getKey()
{
   return title;
}

void CD::addSong(String* title, String* length)
{
   int track_count = songs->size();
   if (track_count < num_tracks)
   {
      Song* song = new Song(title, length);
      songs->add(song);
   }
}

void CD::displayCD()
{
   cout << "Artist: ";
   artist->displayString();
   cout << endl;

   cout << "Title: ";
   title->displayString();
   cout << endl;
   cout << "Year: " << year << endl;
   cout << "Rating: " << rating << endl;

   ListArrayIterator<Song>* iter = songs->iterator();
   int count = 1;
   while(iter->hasNext())
   {
      Song* song = iter->next();
      cout << count << " ";
      song->displaySong();
      count++;
   }
   delete iter;
   cout << endl;
}

ListArray<CD>* CD::readCDs(const char* file_name)
{
   ReadFile* rf = new ReadFile(file_name);
   ListArray<CD>* cds = new ListArray<CD>();
   String* artist = rf->readLine();

   while(!rf->eof())
   {

      String* title = rf->readLine();

      String* year_str = rf->readLine();
      int year = year_str->a_to_i();
      delete year_str;

      String* rating_str = rf->readLine();
      int rating = rating_str->a_to_i();
      delete rating_str;

      String* tracks_str = rf->readLine();
      int num_tracks = tracks_str->a_to_i();
      delete tracks_str;

      CD* cd = new CD(artist, title, year, rating, num_tracks);
      cds->add(cd);

      int track_count = 0;
      while(track_count < num_tracks)
      {
         String* tok = rf->readLine();
         Tokens* tokens = new Tokens(tok, ',');
         delete tok;

         String* song_length = tokens->getToken(0);
         String* song_title = tokens->getToken(1);

         cd->addSong(song_title, song_length);
         track_count++;
         delete tokens;
      }

      artist = rf->readLine();
   }

   rf->close();
   delete rf;

   return cds;
}
