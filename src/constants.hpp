#include <tclap/CmdLine.h>
#include <stdexcept>
#include <iostream>
#include <fstream>

// * Default parameter values *

#define _END_TIME_ 15
#define _DELTA_T_ .5
#define _NB_ 20
#define _PERC_ .5
#define _LAMB_ 4
#define _INT_ 2 // TODO: decide what will be the default parameter
#define _DISCHARGE_T_ 30

// *text messages *

#define _TIME_TEXT_ "Simulation end time"
#define _NEURON_NUMBER_ "Number of neuron in simulation"
#define _PERCENT_ACTIVE_ "Percentage of activatory neurons"
#define _LAMBDA_ "Mean connectivity between the neurons"
#define _INTENSITY_ "Mean intensity of a connection"
#define _PRGRM_TEXT_ "Neuron simulation"
#define _OFILE_TEXT_ "Output file name"
