#if !defined WRITE_FILE
#define WRITE_FILE

#include "String_.h"
using CSC1310::String;

#include <fstream>
using namespace std;

namespace CSC1310
{
class WriteFile
{
   private:
      ofstream* output_file;
      bool closed;

   public:
      WriteFile(const char* file_name);
      ~WriteFile();
      void writeLine(String* line);
      static void entireFile(const char* file_name, char* file_contents, int file_length);
      void close();
};
}

#endif
