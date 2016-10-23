//Harprabh Sangha
//hsswx7

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <time.h>

#include "log.h"

void displayHelpMesg();

int main(int argc, char **argv)
{
  int c; //This is for the Switch statement for using getopt
  int x = 42;
  char *filename = "logfile.txt";
  int hflag =0;
  int hepflag =  0; // flags for each command for customized messages
  int nflag = 0;
  int lflag = 0;
  int nempty = 0; 
  char *exe = argv[0]; //getting the executable name

  static struct option long_options[] = 
  { 
    {"help", no_argument, 0, 'p'},
    { 0,     0          , 0,  0 } 
  };
  int long_index = 0;

  while((c = getopt_long_only(argc, argv, "hpn:l:", long_options, &long_index)) != -1)
  {
    switch (c)
    {
      case 'h':
        hflag = 1;
        nempty = 1; 
	if (hepflag ==0) {displayHelpMesg();}
      break;
      
      case 'p':
        //printf("help used \n");
       hepflag = 1;
       nempty = 1;
       if (hflag ==0) {displayHelpMesg();}
      break;
      
      case 'n':
        nflag = 1;
        nempty = 1;
        printf ("X changed to %s\n", optarg);
        x = atoi(optarg);
      break;
     
      case 'l':
        if (optopt == 'n')
        {
          printf("Please enter a valid filename.");
          return 0;
        }
        printf("Log file name changed to: %s\n", optarg);
        lflag = 1;
        nempty = 1;
	filename = optarg;
      break;
      
      case '?':
        if (optopt == 'l')
        {
          printf("Command -l requires filename. Ex: -lfilename.txt | -l filename.txt.\n");
        }
        else if (optopt == 'n')
        {
          printf("Commands -n requirest int value. Ex: -n213| -n 2132\n");
        }
        else
        {
          printf("You have used an invalid command, please use -h or -help for command options, closing program.\n"); 
        }
      return 0;
	  
      default :
        if (optopt == 'l')
        {
          lflag = 1;
          nempty = 1; 
          //perror("Error: ");
          printf ("Please enter filename after -l \n");
        }
	else if (optopt == 'n')
        { 
          printf ("Please enter integer x after -n \n");
	  nflag = 1;
          nempty = 1;
        }
        printf("Running Program without Commands.");
      break;
    }
  }
  if ((nempty == 0) &&argv[optind] == NULL || argv[optind + 1] == NULL)
  {
    printf("Running program without commands. Please use -h or -help for commands options.\n");
  }

  
  
  input_msg ("hello world");
  clearlog();
  input_msg ("World Wants to say Hello back but professor wants to run each function atleast twice, so your alone.\n");
  clearlog(); // running it atleast time
  
  /*
  hflag   //-h flag
  hepflag //-help flag 
  nflag   // -n x flag 
  lflag   // -l flag
  */
  
  if (hflag || hepflag || nflag || lflag)
  {
	  if (nflag)
	  {
		  char input = x;
		  if (x < 42)
		  {
			  input_msg("x is too small to be the number of time the professor died in Dark Souls.");
			  input_msg ("YOU DIED");
		  }
		  else if (x == 42)
		  {
			 input_msg("Answer to Life Answered, Computer will self distruct....Soon....");
		  }
		  else if (x > 42)
		  {
			if (x > 100)
			{
			  if(x > 150 && x < 200)
			  {
				input_msg ("Nighty Night :)");
			  }
			  else
			  {
				 input_msg("Incorrect number of times the player died in Dark Souls, please add 100 more."); 
			  }
			  
			}
			else 
			{
				input_msg("X changed without rational consent.");
				input_msg("X is to still too small to calcualte the chances of survivle in Dark Souls.");
			}
		  }
	  }
	  else 
	  {
		  input_msg ("X not changed.");
	  }
	  
	  
	  if (hepflag || hflag)
	  {  
		  if (hflag && hepflag)
		  {
			  input_msg ("User called help twice, assume they did not read the README.");
		  }
		  else
		  {
			 input_msg("Help message was called, Please make program easier to use."); 
			 //savelog(filename ,exe); 	
		  }
	  }
	  else
	  {
		input_msg ("Help not used, Hooray!");   
	  }
	  
	  if (lflag)
	  {
		input_msg("Filename changed, Hopefully user read README for instructions.");  
	  }
  }	  
  else  
  {
	  input_msg("No commands chosen, program not fully used.");
  }
  
  savelog(filename ,exe); // saving to the log
  clearlog(); // running it atleast time


  return 0;
}

void displayHelpMesg()
{
  printf (" -h or -help  : shows steps on how to use the program \n");
  printf (" -n x        : changes the value of x \n");
  printf (" -l filename : change the log file name \n\n");
}
