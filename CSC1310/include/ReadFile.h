#if !defined READ_FILE
#define READ_FILE

#include "String_.h"

#include <fstream>
using namespace std;

namespace CSC1310
{
class ReadFile
{
   private:
      ifstream* input_file;
      bool _eof;
      bool closed;

   public:
      ReadFile(const char* file_name);
      ~ReadFile();
      CSC1310::String* readLine();
	  
      bool eof();
      void close();
	  
	  static char* entireFile(const char* file_name, int* length);
};
}

#endif
