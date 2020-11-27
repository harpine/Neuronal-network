
# Neuronal network
***
Short description : This project aims to model a neuron network, implementing different types of neurons (each neuron has its specificities). The simulation must be launched from a terminal and the results can be observed with a Rasterplot command. Several different options can be entered by the user when executing the program, by writing the command line. It is fully documented with Doxygen and contains unit tests.
Project status : completed.

## Requirements
***
A list of technologies used within the project:
* [doxygen]: Version 1.9.0
* [cmake]: Version 3.10.2
* [googletest]: Version 1.10.0

## Installation
***
A little intro about the installation and steps to get appropriate result.
```
$ git clone https://gitlab.epfl.ch/sv_cpp_projects/team_9
$ mkdir build
$ cd build
$ cmake ..
$ make
$ ./neuron_network
$ Rscript ../Rasterplots.R spikes.txt 
```

### Options and default values
***
The command ./neuron_network -h make visible all possible options for the program, however default parameters are applied for all fields.
* -c (choice of having to supplementary output files)
* -m 'b' (model for neuron connection, b for basic)
* -o "" (output file name) Default values for all output files are defined later if no name file is given
* -i 8 (mean intensity of a connection)
* -l 10 (mean connectivity between the neurons)
* -r "" (repartition of all neuron types) If nothing is given, the parameter -p is used
* -p .5 (proportion of excitatory neurons in the network) If repartition is given, this parameter is unused.
* -n 10 000 (number of neurons in the network)
* -t 500 (time of simulation in ms)

### Author rights
***
This code was written by Aline Brunner, Florence Crozat, Justin Mapanao, Claire Payoux.

#### Logo rights
***
[neuronal network](https://www.freepng.fr/png-4j8gg0/)