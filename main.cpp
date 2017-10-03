//#include <iosintream>

#include "BScheduler.h"

int main(int argc, char ** argv) {


// Genetoc Algorithm parameters and their flags
    bool okin = false,
         okout = false,
         oklog = false,
         okpop = false,
         okgen= false,
         oknoimp = false,
         okmincross = false,
         oktmut = false;
    char * inputname = NULL;
    char * outputname = NULL;
    char * logname = NULL;
    int pop = 0;
    int maxgen = 0;
    int maxnoimp = 0;
    float mincross = 0;
    float tmut = 0;

	GeneticAlgorithm * genalg = NULL;

	if (argc > 1) {

		 inputname = getCommandLineParameter<char *>(
					argc,
					argv,
					NAME_OPTIONALSPACE_EQUAL_OPTIONALSPACE_VALUE_CLPARAM,
					"-in",
					okin
				);
		 outputname = getCommandLineParameter<char *>(
					argc,
					argv,
					NAME_OPTIONALSPACE_EQUAL_OPTIONALSPACE_VALUE_CLPARAM,
					"-out",
					okout
				);
		  logname = getCommandLineParameter<char *>(
					argc,
					argv,
					NAME_OPTIONALSPACE_EQUAL_OPTIONALSPACE_VALUE_CLPARAM,
					"-log",
					oklog
				);
          pop = getCommandLineParameter<int>(
                    argc,
					argv,
					NAME_OPTIONALSPACE_EQUAL_OPTIONALSPACE_VALUE_CLPARAM,
					"-population",
					okpop
				);
          maxgen = getCommandLineParameter<int>(
                    argc,
					argv,
					NAME_OPTIONALSPACE_EQUAL_OPTIONALSPACE_VALUE_CLPARAM,
					"-maxgenerations",
					okgen
				);
          maxnoimp = getCommandLineParameter<int>(
                    argc,
					argv,
					NAME_OPTIONALSPACE_EQUAL_OPTIONALSPACE_VALUE_CLPARAM,
					"-maxnoimprov",
					oknoimp
				);
          mincross = getCommandLineParameter<float>(
                    argc,
					argv,
					NAME_OPTIONALSPACE_EQUAL_OPTIONALSPACE_VALUE_CLPARAM,
					"-mincrossover",
					okmincross
				);
          tmut = getCommandLineParameter<float>(
                    argc,
					argv,
					NAME_OPTIONALSPACE_EQUAL_OPTIONALSPACE_VALUE_CLPARAM,
					"-taxmutation",
					oktmut
				);
	} else {
        fprintf(stderr,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        fprintf(stderr,"ERROR: No Parameters!\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        getchar();
        exit(EXIT_FAILURE);
	}

	if (!okin) {
        fprintf(stderr,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        fprintf(stderr,"ERROR: No input File!\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        getchar();
        exit(EXIT_FAILURE);
	}
	if (!okout) {
        fprintf(stderr,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        fprintf(stderr,"WARNING: No output File!\nDefault output is %s!\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n",DEFAULTOUTPUTFILE);
        outputname = new char [DEFAULTNAMESIZE];
        strcpy(outputname,DEFAULTOUTPUTFILE);
	}
	if (!oklog) {
        fprintf(stderr,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        fprintf(stderr,"WARNING: No Log File!\nLog on screen!\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        logname = NULL;
	}
	if (!okpop) {
        fprintf(stderr,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        fprintf(stderr,"WARNING: No population set!\nDefault population = %d!\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n", DEFAULTPOPULATIONSIZE);
        pop = DEFAULTPOPULATIONSIZE;
	}
	if (!okgen) {
        fprintf(stderr,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        fprintf(stderr,"WARNING: No maximum number of generations set!\nDefault maximum generations  = %d!\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n", DEFAULTMAXOFGENERATIONS);
        maxgen = DEFAULTMAXOFGENERATIONS;
	}
	if (!oknoimp) {
        fprintf(stderr,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        fprintf(stderr,"WARNING: No maximum number of generations without improvement set!\nDefault maximum generations without improvement = %d!\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n", DEFAULTMAXOFGENERATIONSWITHOUTIMPROVEMENT);
        maxnoimp = DEFAULTMAXOFGENERATIONSWITHOUTIMPROVEMENT;
	}
	if (!okmincross) {
        fprintf(stderr,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        fprintf(stderr,"WARNING: No minimum percentage of cross over set!\nDefault minimum percentage of cross over = %f!\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n", DEFAULTMINCROSSOVERPERCENTAGE);
        mincross = DEFAULTMINCROSSOVERPERCENTAGE;
	}
	if (!oktmut) {
        fprintf(stderr,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        fprintf(stderr,"WARNING: No percentage of mutation set!\nDefault percentage of mutation = %f!\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n", DEFAULTMUTATIONPERCENTAGE);
        tmut = DEFAULTMUTATIONPERCENTAGE;
	}

	genalg = new GeneticAlgorithm(inputname, outputname, logname);

	genalg->initializePopulation( pop, mincross, tmut);

    float bestfit=0;

    if (oknoimp == 0)
        bestfit = genalg->runTillNoImprovement(maxnoimp,maxgen);
    else
        bestfit = genalg->runForNGenerations(maxgen);
    printf("\n\nBest fitness = %f\n", bestfit);

    genalg->getBestChromosome()->print();
    genalg->print();

	genalg->save();

	delete genalg;

	getchar();

	return 0;
}
