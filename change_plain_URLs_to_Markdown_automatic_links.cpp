// Markdown automatic hyperlink creation from a list of URLs
// MIT license https://opensource.org/licenses/MIT
// https://stackoverflow.com/questions/2340281/check-if-a-string-contains-a-string-in-c/2340309#2340309
// https://stackoverflow.com/questions/7868936/read-file-line-by-line-using-ifstream-in-c/7868998#7868998
// https://stackoverflow.com/questions/1878001/how-do-i-check-if-a-c-stdstring-starts-with-a-certain-string-and-convert-a/40441240#40441240
// https://stackoverflow.com/questions/9505085/replace-a-line-in-text-file/9505483#9505483
// https://stackoverflow.com/questions/30091667/c-append-data-on-a-txt-file-in-a-specific-way/30092008#30092008
// https://stackoverflow.com/questions/6406356/how-to-write-vector-values-to-a-file/6406393#6406393
// https://stackoverflow.com/questions/874134/find-out-if-string-ends-with-another-string-in-c/874160#874160
// https://stackoverflow.com/questions/1525535/delete-all-items-from-a-c-stdvector/1525546#1525546

#include <cctype> // Required for the *toupper* function.
#include <fstream> // Required for the *fstream*, and *ifstream*, *ofstream* classes.
#include <iostream> // Required for the *cin* and *cout* objects.
#include <string> // Required for the *string* class.
#include <vector> // Required for the *vector* class.

using namespace std;

// Function prototype
char continue_or_exit_program();

int main()
{
  // Constant definition
  const string URL_COMPONENT_1 = "://";
  const string URL_COMPONENT_2 = ".";
  const string URL_COMPONENT_3 = " ";
  const string TWO_CONSECUTIVE_SPACES = "  ";

  // Variable definition
  int file_line_count = 0;

  // Vector definition
  vector<string> markdown_converted_file_contents;
  vector<string> modified_markdown_converted_file_contents; // Temporary vector
  
  // Variable declaration
  string link_conversion_filename;
  char user_continue_choice;
  string line_of_file;
  string modified_line_of_file_with_plain_url; // Temporary variable
  string modified_line_of_file_with_two_consecutive_trailing_spaces; // Temporary variable
  
  cout << "This program modifies a file to change any plain URLs into Markdown automatic hyperlinks." << endl;

  fstream link_conversion_file;

  do
  {
    // User input
    cout << "Enter a filename: ";
    cin >> link_conversion_filename;
    
    // Opening a file for transput
    link_conversion_file.open(link_conversion_filename, ios::in);
    
    // Setting the file line count to zero
    file_line_count = 0;
    
    // Calculation of the file's line count
    while (std::getline(link_conversion_file, line_of_file))
    {
      file_line_count += 1;
    }
    
    link_conversion_file.close();
    link_conversion_file.open(link_conversion_filename, ios::in | ios::out);

    if (file_line_count == 1)
    {
      cout << "The file contains only one line, and was not modified." << endl;
    }
    else if (file_line_count > 1)
    {
      // Variable definition
      int plain_url_found_count = 0;
      int two_consecutive_trailing_spaces_found_count = 0;
      int current_line_number = 0;
      
      // Iteration through each line of a text file, detecting any plain URLs and changing them into Markdown automatic links. All lines are added to a vector as string elements, regardless of whether they were changed or not.
      while (std::getline(link_conversion_file, line_of_file))
      {
        current_line_number += 1;
        // Removing two consecutive trailing spaces from any lines that have them
        if (line_of_file.length() >= TWO_CONSECUTIVE_SPACES.length() && line_of_file.find(TWO_CONSECUTIVE_SPACES, (line_of_file.length() - TWO_CONSECUTIVE_SPACES.length())) != std::string::npos)
        {
          two_consecutive_trailing_spaces_found_count += 1;
          cout << "Two consecutive trailing spaces were found on line " << current_line_number << "." << endl;
          modified_line_of_file_with_two_consecutive_trailing_spaces = line_of_file.erase((line_of_file.length() - TWO_CONSECUTIVE_SPACES.length()),  TWO_CONSECUTIVE_SPACES.length());
          line_of_file = modified_line_of_file_with_two_consecutive_trailing_spaces;
        }
        // Adding inequality signs to the beginning and end of plain URLs
        if (line_of_file.find(URL_COMPONENT_1) != std::string::npos && line_of_file.find(URL_COMPONENT_2) != std::string::npos && line_of_file.find(URL_COMPONENT_3) == std::string::npos && line_of_file.rfind("<", 0) == std::string::npos && line_of_file.find(">", 0) == std::string::npos)
        {
          plain_url_found_count += 1;
          cout << "A plain URL was found on line " << current_line_number << "." << endl;
          // Adding inequality signs to beginning and end of the current line to change plain URL into Markdown automatic link
          modified_line_of_file_with_plain_url = "<" + line_of_file + ">";
          line_of_file = modified_line_of_file_with_plain_url;
        }
        // Adding string elements to “markdown_converted_file_contents” vector
        markdown_converted_file_contents.push_back(line_of_file);
      }
      
      link_conversion_file.close();
      link_conversion_file.open(link_conversion_filename, ios::in | ios::out);
      
      // Adding two consecutive trailing spaces to lines meeting specific criteria: do not add two consecutive trailing spaces to lines followed by a blank line, or to blank lines. The temporary “modified_markdown_converted_file_contents” vector is used for this.
      for (int loop_counter = 0 ; loop_counter <= file_line_count ; loop_counter++)
      {
        if (!(markdown_converted_file_contents[loop_counter].empty() == false && markdown_converted_file_contents[loop_counter + 1].empty() == true) && markdown_converted_file_contents[loop_counter].empty() == false)
        {
          // cout << "Line " << loop_counter + 1 << endl;
          modified_markdown_converted_file_contents.push_back((markdown_converted_file_contents[loop_counter] + "  "));
        }
        else
          modified_markdown_converted_file_contents.push_back(markdown_converted_file_contents[loop_counter]);
      }
      
      // Clearing contents of “markdown_converted_file_contents” vector and adding string elements to it from temporary “modified_markdown_converted_file_contents” vector
      markdown_converted_file_contents.clear();
      for (int loop_counter = 0 ; loop_counter <= file_line_count ; loop_counter++)
        markdown_converted_file_contents.push_back(modified_markdown_converted_file_contents[loop_counter]);

      if (plain_url_found_count > 0)
      {
        cout << plain_url_found_count << " plain URLs were changed in " << link_conversion_filename << ". " << two_consecutive_trailing_spaces_found_count << " lines had two consecutive trailing spaces removed in " << link_conversion_filename << "." << endl;
        // Iteration through string elements of a vector, overwriting existing contents of text file with contents of vector.
        for (vector<string>::const_iterator loop_counter = markdown_converted_file_contents.begin() ; loop_counter != markdown_converted_file_contents.end() ; loop_counter++)
          link_conversion_file << *loop_counter << "\n";
      }
      else
        cout << "No plain URLs were found." << endl;
      
      // Clearing contents of “markdown_converted_file_contents” vector
      markdown_converted_file_contents.clear();
    }
    else
      cout << "Something went wrong.";
    
    // Closing a file
    link_conversion_file.close();
    
    cout << "Modify another file?" << endl;
    user_continue_choice = continue_or_exit_program();
  } while (toupper(user_continue_choice) == 'Y');

  return 0;
}

char continue_or_exit_program()
{
  // User input that gives that the user a chance to exit.
  
  // Variable declaration
  char user_continue_choice;
  
  cout << "Enter “Y” to do so, or “N” to exit:";
  cin >> user_continue_choice;
  // Input validation with while-loop construct: the value must be “Y” or “N”.
  while (toupper(user_continue_choice) != 'Y' && toupper(user_continue_choice) != 'N')
  {
    cout << "Invalid input: the value must be “Y” or “N”.\nEnter “Y” to do so, or “N” to exit:";
    cin >> user_continue_choice;
  }
  
  return user_continue_choice;
}
