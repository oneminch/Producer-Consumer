#include "Song.h"

#include <iostream>
using namespace std;

Song::Song(String* title, String* length)
{
   this->title = title;
   this->length = length;
}

Song::~Song()
{
   delete title;
   delete length;
}

void Song::displaySong()
{
   title->displayString();
   cout << " ";
   length->displayString();
   cout << endl;
}
