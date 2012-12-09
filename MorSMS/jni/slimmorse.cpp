#include<jni.h>
#include<string.h>
#include<cstring>
#include<vector>
#include<stdlib.h>
#include<sstream> 
//#include<iostream> // DEBUGGING
//#include<fstream> // DEBUGGING

using namespace std ; 

// c++ code

char makeupper(char input) ; // convert lower to upper case 
//void morse(char input, vector<string> &vec) ; // morse symbol // DEBUGGING
void sigdur(char input, vector<int> &vec, int unit) ; // signal duration
string msg; // global string from java jstring
int unit ; // vibration unit
int delay ; // initial delay length
// static int sz ; // global size of return string // DEBUGGING

// function called from java
char * translate()
{


// 5 elements of morse code 
// dit (short) : (.) ; one unit on
// dah (long)  : (-) ; three units on 
// inter-character pause ; one unit off
// inter-word pause ; three units off
// inter-word pause ; seven units off

// PROGRAM OVERVIEW : 
// for (i = 0 : length(msg) - 1 ) read in characters
// translate lower to upper case ; do nothing if already upper
// only print single spaces between words  
// translate parsed txtmessage to signal duration and morse symbols
// look through most common letters first
// convert the string to an array of ints, then to an array of individual characters 

// DEBUGGING
// output two kinds of files
// 1. morse translation : vector<string> mvec -> (mcode.txt) 
// 2. pattern for android  : vector<int> signal -> (vibsig.txt) 


//string msg ; // text message input // DEBUGGING
vector<char> cvec ; // vector of translatable characters 
vector<int> signal ; // vibration signal 
//signal.push_back (0) ; // first entry is 0 (play immediately) 

// pause for four seconds 
signal.push_back (delay) ; // first entry is 4000 (pause for four seconds) 

//vector<string> mvec ; // morse code symbols // DEBUGGING
int txtlen ; // length of txt message
char ltr ; // current letter
int index = 0 ; // for counting index of cvec
bool pcheck = 0 ; // check if a space has been pushed 
bool empty = 1 ; // check if the message is has no translatable content  
int startindex ; // index where the phrase begins 

//  DEBUGGING
// open output text files 

//ofstream mcode ;
//ofstream vibsig ;
//mcode.open("mcode.txt", ios::trunc) ; 
//vibsig.open("vibsig.txt", ios::trunc) ; 

//cin.clear() ; // clear the buffer
//cout << "Enter a text message\n" ; 
//getline(cin,msg) ; 
//cout << "Input message -> " << msg << endl ; 
//cout << "Length of message is " << msg.length() << " characters\n" ; 

txtlen = msg.length() ; 

//  DEBUGGING
//changed to input parameter 
//int unit = 60 ; // ms
//int unit ;
//cout << "Enter the duration of a short ON (ms)\n" ;
//cin >> unit ;
//cout << "\n" ; 

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
//   exit(0) ; // completely empty (non-translatable) input, leave the program //  DEBUGGING 
     char * nulloutp = new char[2]; // silence if no output
     nulloutp[0] = '0' ; 
     nulloutp[1] = '\0' ;
     return nulloutp ; // return a silent signal
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
  // cout << "char # " << index << " value: " << *j << endl ; // DEBUGGING


  //morse(*j,mvec) ; // convert to morse symbols // DEBUGGING
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

// DEBUGGING
// write morse symbols to mcode.txt
//for (vector<string>::iterator j = mvec.begin() ; j != mvec.end() ; ++j) 
//{
//    mcode << *j << endl ; // print to a file 
//    // print code to screen ( for debugging ) 
//    if ( *j == " " ) 
//    {
//      cout << *j << "   **     " ; // inter-word symbol 
//    } 
//    else 
//    {
//      cout << *j << " & " ;  // inter-letter symbol 
//    }
//    //
//}
//    cout << "\n" ; 


// write vibration signal to vibsig.txt //  DEBUGGING
// convert to array of chars for output to java

string pstring ;
stringstream out ; 
vector<char> charvec ;
for (vector<int>::iterator j = signal.begin() ; j != signal.end() ; ++j) 
{
      // DEBUGGING
      //   vibsig << *j << endl ; // for printing to a file 

      // convert from int to individual characters
      out << (*j) ; 
      pstring = out.str() ; 
      out.str(string()) ; // clear the string stream
      
      for ( int ii = 0 ; ii < pstring.length() ; ii++) 
      { 
          charvec.push_back(static_cast<char>(pstring[ii])) ; 
      }
      charvec.push_back('\n') ; 
      pstring.erase() ; 

}

// DEBUGGING
//mcode.close() ; 
//vibsig.close() ; 

// put charvec into a cstring
char *output = new char[( charvec.size() + 1 ) ] ;
int kk = 0 ; 
for (vector<char>::iterator j = charvec.begin() ; j != charvec.end() ; ++j)
{
    output[kk] = (*j) ; 
    kk++ ; 
}

output[kk] = '\0' ; // end with null terminator
//sz = kk ; // size of output character array // DEBUGGING

return output; // return to java 
}

char makeupper(char input)  // if input is lower case 
{
  char converted ; 
  converted = static_cast<char>('A' + (input - 'a')) ;
  return converted ; 
}

// DEBUGGING
//void morse(char input, vector<string> &vec)  // return morse code symbol
//{
//
//     if (input == 'E') 
//     {
//        vec.push_back (".") ;
//     } 
//     else if (input == 'T') 
//     {
//        vec.push_back ("-")  ;   
//     }
//     else if (input == 'A') 
//     {
//        vec.push_back (". -") ;     
//     }
//     else if (input == 'O') 
//     {
//        vec.push_back ("- - -") ;     
//     }
//     else if (input == 'I') 
//     {
//        vec.push_back (". .") ; 
//     }
//     else if (input == 'N') 
//     {
//        vec.push_back ("- .") ;   
//     }
//     else if (input == 'S') 
//     {
//        vec.push_back (". . .") ;     
//     }
//     else if (input == 'H') 
//     {
//        vec.push_back (". . . .") ;     
//     }
//     else if (static_cast<int>(input) ==  32)  // space character 
//     {
//        vec.push_back (" ") ;    
//     }
//     else if (input == 'R') 
//     {
//        vec.push_back (". - .") ;     
//     }
//     else if (input == 'D') 
//     {
//        vec.push_back ("- . .") ;    
//     }
//     else if (input == 'L') 
//     {
//        vec.push_back (". - . .") ;     
//     }
//     else if (input == 'C') 
//     {
//        vec.push_back ("- . - .") ;   
//     }
//     else if (input == 'U') 
//     {
//        vec.push_back (". . -") ;    
//     }
//     else if (input == 'M') 
//     {
//        vec.push_back ("- -") ;    
//     }
//     else if (input == 'W') 
//     {
//        vec.push_back (". - -") ;     
//     }
//     else if (input == 'F') 
//     {
//        vec.push_back (". . - .") ;     
//     }
//     else if (input == 'G') 
//     {
//        vec.push_back ("- - .") ;    
//     }
//     else if (input == 'Y') 
//     {
//        vec.push_back ("- . - -") ;     
//     }
//     else if (input == 'P') 
//     {
//        vec.push_back (". - - .") ;   
//     }
//     else if (input == 'B') 
//     {
//        vec.push_back ("- . . .") ;    
//     }
//     else if (input == 'V') 
//     {
//        vec.push_back (". . . -") ;    
//     }
//     else if (input == 'K') 
//     {
//        vec.push_back ("- . -") ;    
//     }
//     else if (input == 'J') 
//     {
//        vec.push_back (". - - -") ;    
//     }
//     else if (input == 'X') 
//     {
//        vec.push_back ("- . . -") ;    
//     }
//     else if (input == 'Q') 
//     {
//        vec.push_back ("- - . -") ;    
//     }
//     else if (input == 'Z') 
//     {
//        vec.push_back ("- - . .") ;    
//     }
//     else if (input == '0') 
//     {
//        vec.push_back ("- - - - -") ;    
//     }
//     else if (input == '1') 
//     {
//        vec.push_back (". - - - -") ;    
//     }
//     else if (input == '2') 
//     {
//        vec.push_back (". . - - -") ;    
//     }
//     else if (input == '3') 
//     {
//        vec.push_back (". . . - -") ;    
//     }
//     else if (input == '4') 
//     {
//        vec.push_back (". . . . -") ;    
//     }
//     else if (input == '5') 
//     {
//        vec.push_back (". . . . .") ;    
//     }
//     else if (input == '6') 
//     {
//        vec.push_back ("- . . . .") ;    
//     }
//     else if (input == '7') 
//     {
//        vec.push_back ("- - . . .") ;    
//     }
//     else if (input == '8') 
//     {
//        vec.push_back ("- - - . .") ;    
//     }
//     else if (input == '9') 
//     {
//        vec.push_back ("- - - - .") ;    
//     }
//} 

void sigdur(char input, vector<int> &vec, int unit)  // return vibration signal for a letter
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
        vec.push_back (dah) ;
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

int main() {
return 0 ;
}  // nothing to see here

// to debug as a c++ file, comment out <jni.h> , uncomment <iostream>,
// comment out the extern c {} section 
// comment out the above main()
// uncomment the static int sz declaration near the beginning of the file
// and uncomment the sz = kk line located near the end of the translate
// function. Use the following main()

//int main() {

//msg.assign("sos") ;
//cout << "input message >> "  << msg << endl ;
//cout << "vibration sequence >> " << endl ; 
//unit = 60 ;
//char *outp = translate() ;

//for ( int i = 0 ; i < sz ; i++ )
//{
//  cout << outp[i] ;
//}

//return 0 ;
//}





// c code
extern "C" {
    jstring Java_com_ec_morsms_VibrationService_trans( JNIEnv * env, jobject obj, jstring msg_in, jint unit_in, jint delay_in )

    {
    	 const char * ms= (env)->GetStringUTFChars(msg_in,NULL);
    	 msg.assign(ms) ; // assign ms to string object
    	 unit = unit_in ; // input vibration unit 
         delay = delay_in ; // input vibration delay 
    	 return env->NewStringUTF(translate()) ;
    } 

    jstring Java_com_ec_morsms_Charts_trans( JNIEnv * env, jobject obj, jstring msg_in, jint unit_in, jint delay_in )

        {
             const char * ms= (env)->GetStringUTFChars(msg_in,NULL);
             msg.assign(ms) ; // assign ms to string object
             unit = unit_in ; // input vibration unit
             delay = delay_in ; // input vibration delay
             return env->NewStringUTF(translate()) ;
        }
}





