#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int split(vector<string> &fields, const string &inString, const string &delimiter);

int main()
{
    vector <string> fields;
    const string delimiter = "\t";
    int fieldCount = 0;

  // ifstream constructor opens the file
   ifstream inClientFile( "clients.txt", ios::in );

   // exit program if ifstream could not open file
   if ( !inClientFile )
   {
      cerr << "File could not be opened" << endl;
      return( 1 );
   } // end if

      string lineIn;
      getline (inClientFile,lineIn);

      // display file contents (until eof)
      while ( !inClientFile.eof() )
      {
         // display record
        fieldCount = split(fields, lineIn, delimiter); // call the split function to process string lineIn
         cout << "lineIn = " << lineIn << endl;
         cout << "fields consists of: " << endl;

        for (int i=0; i < fieldCount; i++) // spit out the contents of vector fields
        {
            cout << "\t" << fields[i] << endl;
        }
          cout << endl;
          getline (inClientFile,lineIn); //get the next line from the file stream
      } // end inner while

} // end main

int split(vector<string> &fields, const string &inString, const string &delimiter)
{
    int fieldCount = 0;
    size_t found = 0; // data member to indentify the position where a delimiter was found
    size_t lastpos = 0; // data member to identify the position immediately following a delimiter and continue the search

    fields.clear();
    found = inString.find( delimiter ); //find a delimiter
    while ( found != string::npos) // while still inside inString, push back fields and start looking for another
                                   // delimiter at the position immediately following the previously located delimiter
    {
        fields.push_back(inString.substr(lastpos, found - lastpos));
        fieldCount++;
        lastpos = found + delimiter.size();

        found = inString.find(delimiter,lastpos);

    }// end while

        fields.push_back(inString.substr(lastpos, string::npos));// once the end of the string is reached,
        fieldCount++;                                            // push back vector with everything between the
                                                                 // last found delimiter and the end of the string
    return fieldCount; // end function call
}

