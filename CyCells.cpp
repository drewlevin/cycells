#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>

#include "tissue.h"
#include "history.h"
#include "fileDef.h"
#include "fileInit.h"
#include "cells.h"

int main(int argc, char *argv[])
{
  Tissue *tissue;
  FileDef def_parser;
  FileInit init_parser;
  History *history;    // Holds aggregate sim data
  int t = 0;
  int n = 0;

  char def[256] = "";
  char init[256] = "";
  char hist[256] = "";
  int dur = -1;
  int step = 1;
  int disp = 100;
  int seed = -1;

  bool success = true;
  int argi = 1;
  
  if (argc < 2)
  {
    success = false;
    cerr << "Please add arguments" << endl;
  }

  while (argi < argc && success)
  {
    if (!strcmp("-init", argv[argi]))
    {
      if (argi + 1 < argc)
      {
        strcpy(init, argv[++argi]);
        argi++;
      }
      else 
      {
        cerr << "-init: Missing filename" << endl;
        success = false;
      }
    }
    else if (!strcmp("-def", argv[argi]) && argi+1 < argc)
    {
      if (argi + 1 < argc)
      {
        strcpy(def, argv[++argi]);
        argi++;
      }
      else
      {
        cerr << "-def: Missing filename" << endl;
        success = false;
      }
    }
    else if (!strcmp("-dur", argv[argi]) && argi+1 < argc)
    {      
      if (argi + 1 < argc)
      {
        dur = atoi(argv[++argi]);
        argi++;
      }
      else
      {
        cerr << "-dur: Missing amount" << endl;
        success = false;
      }
    }
    else if (!strcmp("-step", argv[argi]) && argi+1 < argc)
    {
      if (argi + 1 < argc)
      {
        step = atoi(argv[++argi]);       
        argi++;
      }
      else
      {
        cerr << "-step: Missing amount" << endl;
        success = false;
      }
    }
    else if (!strcmp("-disp", argv[argi]) && argi+1 < argc)
    {
      if (argi + 1 < argc)
      {
        disp = atoi(argv[++argi]);       
        argi++;
      }
      else
      {
        cerr << "-disp: Missing amount" << endl;
        success = false;
      }
    }
    else if (!strcmp("-seed", argv[argi]) && argi+1 < argc)
    {
      if (argi + 1 < argc)
      {
        seed = atoi(argv[++argi]);
        argi++;
      }
      else
      {
        cerr << "-seed: Missing value" << endl;
        success = false;
      }
    }
    else if (!strcmp("-hist", argv[argi]) && argi+1 < argc)
    {
      if (argi + 1 < argc)
      {
        strcpy(hist, argv[++argi]);
        argi++;
      }
      else
      {
        cerr << "-hist: Missing filename" << endl;
        success = false;
      }
    }
    else
    {
      cerr << "Unrecognized flag" << endl;
      success = false;
    }
  }    

  if (success && strcmp(def, "") && strcmp(init, "") && dur > 0)
  {
	  tissue = new Tissue();

    def_parser.defineFromFile(tissue, def);
    init_parser.initFromFile(tissue, init);

    if (seed != -1)
      tissue->setSeed(seed);

    history = new History(*tissue, 0);
    history->sample(*tissue);

    while (t < dur)
    {
      tissue->update(step);  
      history->sample(*tissue);
      t = int(tissue->getTime());
      
      n = int((t+step)/step);   // Number of steps taken
      if (disp > 0)
        if ((n % disp) == 0)
          printf("Time: %d\n", t+step);
    }

    if (strcmp(hist, "")) 
    {
      ofstream outfile(hist);
    	outfile << *history;
    	outfile.close();		
    }
  }
  else
  {
    if (!strcmp(def, ""))
      cerr << "Model not defined.  Use -def <file> to choose a definition file." << endl;
    if (!strcmp(init, ""))
      cerr << "Model not initialized.  Use -init <file> to choose an init file." << endl;
    if (dur <= 0)
      cerr << "Duration not defined or set to a non-positive value.  Set with -dur <value>" << endl;
  }

  return 0;
}

