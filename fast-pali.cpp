//Karmvir Singh Dhaliwal
//30025474
//CPSC 457 T01

//Most of this code is copied from the slow-pali.cpp file we were given in this assignment.
//We are given clear permission in the assignment to freely reuse whatever code from this file we need.
#include <unistd.h>
#include <stdio.h>
#include <stdio.h>
#include <ctype.h>
#include <string>
#include <vector>
/////////////////////////////////////////////////////////
//This code was provided by Professor Federl for us to use. This code can be found at https://gitlab.com/cpsc457/public/longest-int-my-getchar
// He made clear in lecture we can use this code in our assignment so long as we cite it. 
char buffer[1024*1024]; // 1MB sotrage to hold results of read()
int buff_size = 0;      // stores how many characters are stored in buffer
int buff_pos = 0;       // position in bufffer[] where we extract next char

// returns the next char from stdin, or -1 on EOF
// returns characters stored in buffer[] until it is empty
// when buffer[] gets empty, it is replenished by calling read()
int
fast_read_one_character_from_stdin()
{
  // check if buffer[] is empty
  if( buff_pos >= buff_size) {
    // buffer is empty, let's replenish it
    buff_size = read( STDIN_FILENO, buffer, sizeof(buffer));
    // detect EOF
    if(buff_size <= 0) return -1;
    // reset position from where we'll return characters
    buff_pos = 0;
  }
  // return the next character from the buffer and update position
  return buffer[buff_pos++];
}
//end of the code used from the above cited source. 
/////////////////////////////////////////////////////////
// split string p_line into a vector of strings (words)
// the delimiters are 1 or more whitespaces
std::vector<std::string>
split( const std::string & p_line)
{
  auto line = p_line + " ";
  std::vector<std::string> res;
  bool in_str = false;
  std::string curr_word = "";
  for( auto c : line) {
    if( isspace(c)) {
      if( in_str)
        res.push_back(curr_word);
      in_str = false;
      curr_word = "";
    }
    else {
      curr_word.push_back(c);
      in_str = true;
    }
  }
  return res;
}

// reads in a line from STDIN using the function fast_read_one_character_from_stdin();
// reads until \n or EOF and result includes \n if present
// returns empty string on EOF
//this code was also taken from the cited source above, with modifications to fit my needs.
std::string
stdin_readline()
{
  std::string result;
  while(true) {
    int c = fast_read_one_character_from_stdin();
    if (c == -1) break;
    else{
      result.push_back(c);
    }
    if( c == '\n') break;
  }
  return result;
}
//end of code used from source 
// returns true if a word is palindrome
// palindrome is a string that reads the same forward and backward
//    after converting all characters to lower case
bool
is_palindrome( const std::string & s)
{
  for( size_t i = 0 ; i < s.size() / 2 ; i ++)
    if( tolower(s[i]) != tolower(s[s.size()-i-1]))
      return false;
  return true;
}

// returns the longest palindrome on standard input
// in case of ties for length, returns the first palindrome
// all input is broken into words, and each word is checked
// word is a sequence of characters separated by white space
// white space is whatever isspace() says it is
//    i.e. ' ', '\n', '\r', '\t', '\n', '\f'
std::string
get_longest_palindrome()
{
  std::string max_pali;
  while(1) {
    std::string line = stdin_readline();
    if( line.size() == 0) break;
    auto words = split( line);
    for( auto word : words) {
      if( word.size() <= max_pali.size()) continue;
      if( is_palindrome(word))
        max_pali = word;
    }
  }
  return max_pali;
}

int
main()
{
  std::string max_pali = get_longest_palindrome();
  printf("Longest palindrome: %s\n", max_pali.c_str());
  return 0;
}

