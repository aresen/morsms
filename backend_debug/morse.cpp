#include<iostream>
#include<string.h>
#include<vector>
#include<fstream>
#include<stdlib.h>
using namespace std ; 

// c++ code

char makeupper(char input) ; // convert lower to upper case 
void morse(char input, vector<string> &vec) ; // morse symbol
void sigdur(char input, vector<long> &vec, int unit) ; // signal duration

int main() {


// 5 elements of morse code 
// dit (short) : (.) ; one unit on
// dah (long)  : (-) ; three units on 
// inter-symbol pause ; one unit off
// inter-character pause ; three units off
// inter-word pause ; seven units off

// PROGRAM OVERVIEW : 
// for (i = 0 : length(msg) - 1 ) read in characters
// translate lower to upper case ; do nothing if already upper
// only print single spaces between words  
// translate parsed txtmessage to signal duration and morse symbols
// look through most common letters first
// output two kinds of files
// 1. morse translation : vector<string> signal -> (mcode.txt) 
// 2. pattern for android  : vector<long> mvec -> (vibsig.txt) 


string msg ; // text message input
vector<char> cvec ; // vector of translatable characters 
vector<long> signal ; // vibration signal 
signal.push_back (0) ; // first entry is 0 (play immediately) 
vector<string> mvec ; // morse code symbols
int txtlen ; // length of txt message
char ltr ; // current letter
int index = 0 ; // for counting index of cvec
bool pcheck = 0 ; // check if a space has been pushed 
bool empty = 1 ; // check if the message is has no translatable content  
int startindex ; // index where the phrase begins 

// open output text files 
ofstream mcode ;
ofstream vibsig ;
mcode.open("mcode.txt", ios::trunc) ; 
vibsig.open("vibsig.txt", ios::trunc) ; 

cin.clear() ; // clear the buffer
cout << "Enter a text message\n" ; 
getline(cin,msg) ; 
cout << "Input message -> " << msg << endl ; 
cout << "Length of message is " << msg.length() << " characters\n" ; 
txtlen = msg.length() ; 

//changed to input parameter 
//const int unit = 60 ; // ms
int unit ;
cout << "Enter the duration of a short ON (ms)\n" ;
cin >> unit ;
cout << "\n" ; 
int mp = 3*unit ; // only medium and long pause used in main, the rest are defined in sigdur 
int lp = 7*unit ; 


// check the input to prevent a segfault
for ( int i = 0 ; i < txtlen ; i++ ) 
{
    if ( ((msg[i] >=48) && (msg[i]<=57)) || ((msg[i] >=65) && (msg[i]<=90)) || ((msg[i] >=97) && (msg[i]<=122 )) ) // if a translatable, non-space charcter exists 
    {
       empty = 0 ; 
    }
}

if ( empty == 1 ) 
{
   exit(0) ; // completely empty (non-translatable) input, leave the program
} 

for (int i = 0 ; i < txtlen ; i++) 
{  

    if ( i==0) // remove any initial spaces 
    {
       while ( (msg[i] == 32 ) || ( msg[i] < 48 ) || ( ( msg[i] > 57) && (msg[i] <65 ) ) || ( (msg[i] > 90) && (msg[i] < 97) ) || ( msg[i] > 122) ) 
       // while the beginning of the phrase is a space or untranslatable
       {
             i++  ;
       }
             
       startindex = i ; 

    }

    ltr = msg[i] ;  

    // ignore characters that are not contained in a-z or A-Z or are spaces
    if ( ((ltr >=48) && (ltr<=57)) || ((ltr >=65) && (ltr<=90)) || (ltr==32) ) 
    // if the letter is 0-9 or A-Z or is a space 
    {
       if ( (ltr==32) && (i!= txtlen) ) // condense multiple spaces into one
       {
          if ( (msg[i+1] != 32) && (((msg[i+1] >=48) && (msg[i+1]<=57)) || ((msg[i+1] >=65) && (msg[i+1]<=90)) || (msg[i+1] >=97) && (msg[i+1]<=122))  && (((msg[i-1] >=48) && (msg[i-1]<=57)) || ((msg[i-1] >=65) && (msg[i-1]<=90)) || (msg[i-1] >=97) && (msg[i-1]<=122)) || pcheck == 0 )    
          // if the next letter and previous letter are translatable characters, or a space has not been pushed, push a space
          {
             cvec.push_back (ltr) ; 
             pcheck = 1 ; 
          }
       }
       else
       {
          cvec.push_back (ltr) ; // if ltr is not a space 
          pcheck = 0 ; 
       }
    } 
    else if  ((ltr >=97) && (ltr<=122))
    // if the letter is lowercase 
    { 
       ltr = makeupper(ltr) ; 
       cvec.push_back (ltr) ; 
       pcheck = 0 ;
    } 

    if (cvec[startindex] == 32) // if a space ends up first, get rid of it 
    {
       cvec.pop_back() ; 
    } 

}


for (vector<char>::iterator j = cvec.begin() ; j != cvec.end() ; ++j) 
{
  cout << "char # " << index << " value: " << *j << endl ; 


  morse(*j,mvec) ; // convert to morse symbols
  sigdur(*j,signal,unit) ; // convert to vibration on / off durations 
  // after index 0 , odd indices are ON and even are OFF 

  if (index != ( cvec.size() - 1 ) )
  {
      if (*(j+1) != (int) 32) // add inter-letter space
      {
         if (*j != (int) 32 ) // don't add if you are on the space character 
         {
            signal.push_back (mp) ; // inter-letter pause            
         }
      }
  } 

  index++ ;
}


  if (cvec[index - 1] != (int) 32 ) 
  { 
     signal.push_back (lp) ; // end with a long pause 
  }


// write morse symbols to mcode.txt
for (vector<string>::iterator j = mvec.begin() ; j != mvec.end() ; ++j) 
{
    mcode << *j << endl ; 
    // print code to screen ( for debugging ) 
    if ( *j == " " ) 
    {
      cout << *j << "   **     " ;  // inter-word symbol
    } 
    else 
    {
      cout << *j << " & " ; // inter-letter symbol
    }
    //
}
    cout << "\n" ; 

// make output as a string


//string strsig ; // output the vibration signal as a string
int sz = signal.size() ; 
int *output = new int[sz] ; 
int kk = 0 ;
// write vibration signal to vibsig.txt 
for (vector<long>::iterator j = signal.begin() ; j != signal.end() ; ++j) 
{
    vibsig << *j << endl ; 
    //output[kk] = static_cast<int>(*j) ; 
    //cout << output[kk] << endl ; 
    kk++ ;
}

mcode.close() ; 
vibsig.close() ; 

return 0 ; 
} 

char makeupper(char input)  // if input is lower case 
{
  char converted ; 
  converted = static_cast<char>('A' + (input - 'a')) ;
  return converted ; 
}


void morse(char input, vector<string> &vec)  // return morse code symbol
{

     if (input == 'E') 
     {
        vec.push_back (".") ;
     } 
     else if (input == 'T') 
     {
        vec.push_back ("-")  ;   
     }
     else if (input == 'A') 
     {
        vec.push_back (". -") ;     
     }
     else if (input == 'O') 
     {
        vec.push_back ("- - -") ;     
     }
     else if (input == 'I') 
     {
        vec.push_back (". .") ; 
     }
     else if (input == 'N') 
     {
        vec.push_back ("- .") ;   
     }
     else if (input == 'S') 
     {
        vec.push_back (". . .") ;     
     }
     else if (input == 'H') 
     {
        vec.push_back (". . . .") ;     
     }
     else if (static_cast<int>(input) ==  32)  // space character 
     {
        vec.push_back (" ") ;    
     }
     else if (input == 'R') 
     {
        vec.push_back (". - .") ;     
     }
     else if (input == 'D') 
     {
        vec.push_back ("- . .") ;    
     }
     else if (input == 'L') 
     {
        vec.push_back (". - . .") ;     
     }
     else if (input == 'C') 
     {
        vec.push_back ("- . - .") ;   
     }
     else if (input == 'U') 
     {
        vec.push_back (". . -") ;    
     }
     else if (input == 'M') 
     {
        vec.push_back ("- -") ;    
     }
     else if (input == 'W') 
     {
        vec.push_back (". - -") ;     
     }
     else if (input == 'F') 
     {
        vec.push_back (". . - .") ;     
     }
     else if (input == 'G') 
     {
        vec.push_back ("- - .") ;    
     }
     else if (input == 'Y') 
     {
        vec.push_back ("- . - -") ;     
     }
     else if (input == 'P') 
     {
        vec.push_back (". - - .") ;   
     }
     else if (input == 'B') 
     {
        vec.push_back ("- . . .") ;    
     }
     else if (input == 'V') 
     {
        vec.push_back (". . . -") ;    
     }
     else if (input == 'K') 
     {
        vec.push_back ("- . -") ;    
     }
     else if (input == 'J') 
     {
        vec.push_back (". - - -") ;    
     }
     else if (input == 'X') 
     {
        vec.push_back ("- . . -") ;    
     }
     else if (input == 'Q') 
     {
        vec.push_back ("- - . -") ;    
     }
     else if (input == 'Z') 
     {
        vec.push_back ("- - . .") ;    
     }
     else if (input == '0') 
     {
        vec.push_back ("- - - - -") ;    
     }
     else if (input == '1') 
     {
        vec.push_back (". - - - -") ;    
     }
     else if (input == '2') 
     {
        vec.push_back (". . - - -") ;    
     }
     else if (input == '3') 
     {
        vec.push_back (". . . - -") ;    
     }
     else if (input == '4') 
     {
        vec.push_back (". . . . -") ;    
     }
     else if (input == '5') 
     {
        vec.push_back (". . . . .") ;    
     }
     else if (input == '6') 
     {
        vec.push_back ("- . . . .") ;    
     }
     else if (input == '7') 
     {
        vec.push_back ("- - . . .") ;    
     }
     else if (input == '8') 
     {
        vec.push_back ("- - - . .") ;    
     }
     else if (input == '9') 
     {
        vec.push_back ("- - - - .") ;    
     }
} 

void sigdur(char input, vector<long> &vec, int unit)  // return 
{

int dot = 1*unit ; // "."
int dah = 3*unit ; // "-"
int sp = 1*unit ; // inter-dit/dah pause
//int mp = 3*unit ; // inter-letter pause ; not needed in here
int lp = 7*unit ; // inter-word pause 

     if (input == 'E') 
     {
//      (".") ;
        vec.push_back (dot) ;
     } 
     else if (input == 'T') 
     {
//      ("-")  ;   
        vec.push_back (dah) ;
     }
     else if (input == 'A') 
     {
//     (". -") ;     
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
     }
     else if (input == 'O') 
     {
//      ("- - -") ;     
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
     }
     else if (input == 'I') 
     {
//      (". .") ; 
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
     }
     else if (input == 'N') 
     {
//      ("- .") ;   
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
     }
     else if (input == 'S') 
     {
//      (". . .") ;     
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
     }
     else if (input == 'H') 
     {
//      (". . . .") ;     
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
     }
     else if (static_cast<int>(input) ==  32)  // space character 
     {
//      (" ") ;    
        vec.push_back (lp) ;    
     }
     else if (input == 'R') 
     {
//      (". - .") ;     
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
     }
     else if (input == 'D') 
     {
//      ("- . .") ;    
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
     }
     else if (input == 'L') 
     {
//      (". - . .") ;     
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
     }
     else if (input == 'C') 
     {
//      ("- . - .") ;   
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
     }
     else if (input == 'U') 
     {
//      (". . -") ;    
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
     }
     else if (input == 'M') 
     {
//      ("- -") ;    
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
     }
     else if (input == 'W') 
     {
//      (". - -") ;     
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
     }
     else if (input == 'F') 
     {
//      (". . - .") ;     
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
     }
     else if (input == 'G') 
     {
//      ("- - .") ;    
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
     }
     else if (input == 'Y') 
     {
//      ("- . - -") ;     
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
     }
     else if (input == 'P') 
     {
//      (". - - .") ;   
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
     }
     else if (input == 'B') 
     {
//      ("- . . .") ;    
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
     }
     else if (input == 'V') 
     {
//      (". . . -") ;    
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
     }
     else if (input == 'K') 
     {
//      ("- . -") ;    
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
     }
     else if (input == 'J') 
     {
//      (". - - -") ;    
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
     }
     else if (input == 'X') 
     {
//      ("- . . -") ;    
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
     }
     else if (input == 'Q') 
     {
//      ("- - . -") ;    
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
     }
     else if (input == 'Z') 
     {
//      ("- - . .") ;    
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
     }
     else if (input == '0') 
     {
//      ("- - - - -") ;    
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
     }
     else if (input == '1') 
     {
//      (". - - - -") ;    
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
     }
     else if (input == '2') 
     {
//      (". . - - -") ;    
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
     }
     else if (input == '3') 
     {
//      (". . . - -") ;    
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
     }
     else if (input == '4') 
     {
//      (". . . . -") ;    
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
     }
     else if (input == '5') 
     {
//      (". . . . .") ;    
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
     }
     else if (input == '6') 
     {
//      ("- . . . .") ;    
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
     }
     else if (input == '7') 
     {
//      ("- - . . .") ;    
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
     }
     else if (input == '8') 
     {
//      ("- - - . .") ;    
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
     }
     else if (input == '9') 
     {
//      ("- - - - .") ;    
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dah) ;
        vec.push_back (sp) ;
        vec.push_back (dot) ;
     }
} 
