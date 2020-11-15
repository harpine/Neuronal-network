#include <tclap/CmdLine.h>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <time.h>
#include <map>
#include <string>
#include <algorithm>

// * Default parameter values *

#define _END_TIME_ 500
#define _DELTA_T_ .5
#define _NB_ 10000
#define _PERC_ .5
#define _LAMB_ 10
#define _INT_ 8 // TODO: decide what will be the default parameter
#define _DISCHARGE_T_ 30
#define _OUTFILE_ "outfile"
#define _PATH_OUTFILE_ "../"
#define _PATH_TEST_ "test/"

// *text messages *

#define _TIME_TEXT_ "Simulation end time"
#define _NEURON_NUMBER_ "Number of neuron in simulation"
#define _PERCENT_ACTIVE_ "Percentage of activatory neurons"
#define _LAMBDA_ "Mean connectivity between the neurons"
#define _INTENSITY_ "Mean intensity of a connection"
#define _PRGRM_TEXT_ "Neuron simulation"
#define _CFILE_TEXT_ "Configuration file name"
#define _OFILE_TEXT_ "Output file name"