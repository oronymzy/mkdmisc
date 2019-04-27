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
// https://stackoverflow.com/questions/3867890/count-character-occurrences-in-a-string/3871346#3871346
// https://stackoverflow.com/questions/5468346/how-to-get-the-element-in-vector-using-the-specified-position-in-c/5468388#5468388
// https://stackoverflow.com/questions/2624232/how-to-change-a-particular-element-of-a-c-stl-vector/2624242#2624242
// https://stackoverflow.com/questions/25225948/how-to-check-if-a-file-exists-in-c-with-fstreamopen/25225993#25225993

#include <algorithm> // Required for the *count* function template.
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
  const string COLON_FOLLOWED_BY_TWO_SLASHES = "://";
  const string DOT_CHARACTER = ".";

  // Vector definition
  vector<string> markdown_converted_file_contents;
  vector<string> modified_markdown_converted_file_contents; // Temporary vector
  
  // Variable declaration
  int file_line_count;
  int space_character_count;
  int trailing_space_addition_count;
  string link_conversion_filename;
  string one_or_more_consecutive_space_characters;
  char user_continue_choice;
  string line_of_file;
  int plain_url_found_count;
  int trailing_space_removal_count;
  bool plain_url_found; // Flag variable
  bool plain_url_found_at_least_once; // Flag variable
  bool trailing_space_found; // Flag variable
  bool trailing_space_found_at_least_once; // Flag variable
  int current_line_number;
  int current_index_number;
  string modified_line_of_file_with_plain_url; // Temporary variable
  
  cout << "This program modifies a file to change any plain URLs into Markdown automatic hyperlinks." << endl;

  fstream link_conversion_file;

  do
  {
    // User input
    cout << "Enter a filename: ";
    cin >> link_conversion_filename;
    
    // Opening a file for input
    link_conversion_file.open(link_conversion_filename, ios::in);
    
    // Input validation with while-loop construct: it must be possible for the file referred to by the filename to be opened.
    while (link_conversion_file.fail())
    {
      cout << "Invalid filename: “" << link_conversion_filename << "” cannot be opened. Enter a filename: ";
      cin >> link_conversion_filename;
      // Opening a file for input
      link_conversion_file.close();
      link_conversion_file.open(link_conversion_filename, ios::in);
    }
    
    // Setting the file line count to zero
    file_line_count = 0;
    
    // Setting the space character count to zero
    space_character_count = 0;
    
    // Calculation of the file's line count
    while (std::getline(link_conversion_file, line_of_file))
    {
      file_line_count += 1;
    }
    
    link_conversion_file.close();
    link_conversion_file.open(link_conversion_filename, ios::in | ios::out);

    if (file_line_count == 1)
    {
      std::getline(link_conversion_file, line_of_file);
      
      // Setting flag variables to false
      plain_url_found = false;
      trailing_space_found = false;

      // Determining the number of space characters in a line
      space_character_count = std::count(line_of_file.begin(), line_of_file.end(), ' ');

      // Setting the number of space characters to zero
      one_or_more_consecutive_space_characters = "";
      // Creating a string made up of space characters with a length equal to the number of space characters in a line
      if (space_character_count >= 1)
      {
        for (int loop_counter = 0 ; loop_counter < space_character_count ; loop_counter++)
          one_or_more_consecutive_space_characters += " ";
      }
      
      // Determining if a line has a plain URL
      if (line_of_file.find(COLON_FOLLOWED_BY_TWO_SLASHES) != std::string::npos && line_of_file.find(DOT_CHARACTER) != std::string::npos && (space_character_count == 0 || (space_character_count >= 1 && line_of_file.find(one_or_more_consecutive_space_characters) == (line_of_file.length() - space_character_count))) && line_of_file.rfind("<", 0) == std::string::npos && line_of_file.find(">", 0) == std::string::npos)
      {
        plain_url_found = true;
        // Determining if a line has any trailing spaces
        if (line_of_file.find(one_or_more_consecutive_space_characters) == (line_of_file.length() - space_character_count))
        {
          trailing_space_found = true;
          // Removing any trailing spaces from a line
          modified_line_of_file_with_plain_url = line_of_file.substr(0, line_of_file.size() - space_character_count);
          line_of_file = modified_line_of_file_with_plain_url;
        }
      // Adding inequality signs to beginning and end of the current line to change plain URL into Markdown automatic link
      line_of_file = "<" + line_of_file + ">";

      link_conversion_file.close();
      link_conversion_file.open(link_conversion_filename, ios::out);
      
      // Overwriting existing contents of text file with contents of 'line_of_file' variable
      link_conversion_file << line_of_file;
      }
      
      // Informational output for user
      cout << "The file contains only one line.";
      if (plain_url_found == true && trailing_space_found == true && space_character_count == 1)
        cout << " A plain URL was changed into an automatic link, and " << space_character_count << " trailing space was removed." << endl;
      else if (plain_url_found == true && trailing_space_found == true && space_character_count > 1)
        cout << " A plain URL was changed into an automatic link, and " << space_character_count << " trailing spaces were removed." << endl;
      else if (plain_url_found == true && trailing_space_found == false)
        cout << " A plain URL was changed into an automatic link. No trailing spaces were found." << endl;
      else if (plain_url_found == false)
        cout << " A plain URL was not found, and no changes were made to the file." << endl;
      else
        cout << " Something went wrong." << endl;
    }
    else if (file_line_count > 1)
    {
      // Setting variable values to zero
      plain_url_found_count = 0;
      current_line_number = 0;
      current_index_number = 0;
      trailing_space_addition_count = 0;
      trailing_space_removal_count = 0;
      
      // Setting flag variables to false
      plain_url_found_at_least_once = false;
      trailing_space_found_at_least_once = false;

      // Iteration through each line of a text file, adding all lines to a vector as string elements, unaltered
      while (std::getline(link_conversion_file, line_of_file))
      {
        // Adding string elements to “markdown_converted_file_contents” vector
        markdown_converted_file_contents.push_back(line_of_file);
      }
      
      link_conversion_file.close();
      link_conversion_file.open(link_conversion_filename, ios::in | ios::out);

      // Iteration through each line of a text file, detecting any plain URLs and changing them into Markdown automatic links. All lines are added to a vector as string elements, regardless of whether they were changed or not.
      while (std::getline(link_conversion_file, line_of_file))
      {
        current_line_number += 1;

        // Setting flag variables to false
        plain_url_found = false;
        trailing_space_found = false;
        
        // Set variable referring to index number, which starts with zero, as opposed to the current line number, which starts with one
        current_index_number = current_line_number - 1;

        // Determining the number of space characters in a line
        space_character_count = std::count(line_of_file.begin(), line_of_file.end(), ' ');

        // Setting the number of space characters to zero
        one_or_more_consecutive_space_characters = "";
        // Creating a string made up of space characters with a length equal to the number of space characters in a line
        if (space_character_count >= 1)
        {
          for (int loop_counter = 0 ; loop_counter < space_character_count ; loop_counter++)
            one_or_more_consecutive_space_characters += " ";
        }
        
        // Determining if a line has a plain URL
        if (line_of_file.find(COLON_FOLLOWED_BY_TWO_SLASHES) != std::string::npos && line_of_file.find(DOT_CHARACTER) != std::string::npos && (space_character_count == 0 || (space_character_count >= 1 && line_of_file.find(one_or_more_consecutive_space_characters) == (line_of_file.length() - space_character_count))) && line_of_file.rfind("<", 0) == std::string::npos && line_of_file.find(">", 0) == std::string::npos)
        {
          plain_url_found_count += 1;
          plain_url_found = true;
          plain_url_found_at_least_once = true;
          // Determining if a line has any trailing spaces
          if (line_of_file.find(one_or_more_consecutive_space_characters) == (line_of_file.length() - space_character_count))
          {
            trailing_space_found = true;
            trailing_space_found_at_least_once = true;
            // Removing any trailing spaces from a line
            modified_line_of_file_with_plain_url = line_of_file.substr(0, line_of_file.size() - space_character_count);
            trailing_space_removal_count += space_character_count;
            line_of_file = modified_line_of_file_with_plain_url;
          }
        }
        // Adding string elements to “markdown_converted_file_contents” vector
        markdown_converted_file_contents.at(current_index_number) = line_of_file;

        // Adding inequality signs to beginning and end of the current line if it is a plain URL, changing the plain URL into a Markdown automatic link. Also adding two consecutive trailing spaces to lines meeting specific criteria: do not add two consecutive trailing spaces to lines followed by a blank line, or to blank lines. The temporary “modified_markdown_converted_file_contents” vector is used for this.
        if (plain_url_found == true && markdown_converted_file_contents[current_index_number + 1].empty() == false)
        {
          trailing_space_addition_count += 2;
          line_of_file = "<" + line_of_file + ">  ";
        }
        else if (plain_url_found == true)
          line_of_file = "<" + line_of_file + ">";
        modified_markdown_converted_file_contents.push_back(line_of_file);
      }
      
      link_conversion_file.close();
      link_conversion_file.open(link_conversion_filename, ios::in | ios::out);
      
      // Clearing contents of “markdown_converted_file_contents” vector and adding string elements to it from temporary “modified_markdown_converted_file_contents” vector
      markdown_converted_file_contents.clear();
      for (int loop_counter = 0 ; loop_counter < file_line_count ; loop_counter++)
        markdown_converted_file_contents.push_back(modified_markdown_converted_file_contents[loop_counter]);

      if (plain_url_found_count > 0)
      {
        // Iteration through string elements of a vector, overwriting existing contents of text file with contents of vector.
        for (vector<string>::const_iterator loop_counter = markdown_converted_file_contents.begin() ; loop_counter != markdown_converted_file_contents.end() ; loop_counter++)
          link_conversion_file << *loop_counter << "\n";
      }
      
      // Informational output for user
      cout << "The file contains " << file_line_count << " lines.";
      if (plain_url_found_at_least_once == true && trailing_space_found_at_least_once == true && trailing_space_addition_count != 0)
      {
        if (plain_url_found_count == 1)
          cout << " 1 plain URL was changed into an automatic link";
        else if (plain_url_found_count > 1)
          cout << " " << plain_url_found_count << " plain URLs were changed into automatic links";
        
        if (trailing_space_removal_count == 1)
          cout << ", 1 trailing space was removed";
        else if (trailing_space_removal_count > 1)
          cout << ", " << trailing_space_removal_count << " trailing spaces were removed";
        
        cout << ", and " << trailing_space_addition_count << " trailing spaces were added." << endl;
      }
      else if (plain_url_found_at_least_once == true && trailing_space_found_at_least_once == true && trailing_space_addition_count == 0)
      {
        if (plain_url_found_count == 1)
          cout << " 1 plain URL was changed into an automatic link";
        else if (plain_url_found_count > 1)
          cout << " " << plain_url_found_count << " plain URLs were changed into automatic links";
        
        if (trailing_space_removal_count == 1)
          cout << ", and 1 trailing space was removed.";
        else if (trailing_space_removal_count > 1)
          cout << ", and " << trailing_space_removal_count << " trailing spaces were removed.";
        else
          cout << ".";
        
        cout << " No trailing spaces were added." << endl;
      }
      else if (plain_url_found_at_least_once == true && trailing_space_found_at_least_once == false && trailing_space_addition_count != 0)
      {
        if (plain_url_found_count == 1)
          cout << " 1 plain URL was changed into an automatic link.";
        else if (plain_url_found_count > 1)
          cout << " " << plain_url_found_count << " plain URLs were changed into automatic links.";
        
        cout << " No trailing spaces were removed.";
        
        cout << " " << trailing_space_addition_count << " trailing spaces were added." << endl;
      }
      else if (plain_url_found_at_least_once == true && trailing_space_found_at_least_once == false && trailing_space_addition_count == 0)
      {
        if (plain_url_found_count == 1)
          cout << " 1 plain URL was changed into an automatic link.";
        else if (plain_url_found_count > 1)
          cout << " " << plain_url_found_count << " plain URLs were changed into automatic links.";
        
        cout << " No trailing spaces were removed or added." << endl;
      }
      else if (plain_url_found_at_least_once == false && trailing_space_found_at_least_once == false && trailing_space_addition_count == 0)
        cout << " No plain URLs were found, and no changes were made to the file." << endl;
      else
        cout << " Something went wrong." << endl;
      
      // Clearing contents of “markdown_converted_file_contents” vector
      markdown_converted_file_contents.clear();
    }
    else
      cout << "Something went wrong." << endl;
    
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
