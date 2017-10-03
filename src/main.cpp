#include "BScheduler.h"

// -population=100 -chromosome = 10 -crossover=0.5 -mutation=0.1 -genlimitlower=-10 -genlimitupper=10 -generations=10000 -maxnoimprovement=100
//template<> float Chromosome<float>::computeFitness() {
//
//	fitness = 0;
//
//	if (chromsz < 1 || chrom == NULL)
//		return -1;
//
//    int i = 0;
//	float sum1 = 0;
//	for (i = 0; i < chromsz/2; i++)
//		sum1 += chrom[i];
//	float sum2 = 0;
//	for (; i  < chromsz; i++)
//		sum2 += chrom[i];
//    int j= chromsz/4;
//    int k = chromsz * 3 / 4;
//
//	fitness = (sum1 - sum2) + chrom[j] - chrom[k] * chrom[k];
//
//	fitness /= 100.25;
//
//	return fitness;
//};

float *weight = NULL;
float *profit = NULL;
float cap=0, tot=0;
float * readWeights(int sz){
    FILE * f = NULL;

    char * fname = putPath(getWorkingDirectory(), "knapsack.dat");
    f = fopen(fname,"r");
    if (!f) {
        printf("Nao consegui abrir arquivo: %s \n", fname);
        exit(EXIT_FAILURE);
    }
    int n;
    fscanf(f,"%f %f %d",&cap, &tot, &n);
     if (n <= 0) {
        printf("Arquivo vazio: %s \n", fname);
        exit(EXIT_FAILURE);
    }
     if (n != sz) {
        printf("Arquivo incompativel com entrada: (%d =/= %d)\n", n,sz);
        exit(EXIT_FAILURE);
    }
   float * aux = new float[n];
   profit = new float[n];
   int i;
   for (i=0; i < n; i++)
    fscanf(f,"%f %f", &aux[i], &profit[i]);
   return aux;
}

// -population=1000 -chromosome = 10 -crossover=0.5 -mutation=0.1 -genlimitlower=0 -genlimitupper=1 -generations=10000 -maxnoimprovement=100
//template<> float Chromosome<int>::computeFitness() {
//
//
//	if (chromsz < 1 || chrom == NULL)
//		return -1;
//
//    if (weight == NULL) {
//       weight = readWeights(chromsz);
//    }
//
//	fitness = 0;
//
//
//    int i;
//    float sum =0;
//	for (i = 0; i < chromsz; i++)
//         if (chrom[i] > 0)
//            sum += weight[i];
//
//
//   if (sum > cap)
//        fitness  = 1 - (sum - cap) / (tot - cap);
//    else
//        fitness = sum / cap;
//
//	return fitness;
//};
//template<> float Chromosome<int>::computeFitness() {
//
//	fitness = 0;
//
//	if (chromsz < 1 || chrom == NULL)
//		return -1;
//
//	int sum = 0;
//	for (int i = 0; i < chromsz; i++)
//		sum += chrom[i];
//
//	fitness = (float)sum / chromsz;
//
//	return fitness;
//};

int main(int argc, char ** argv) {


	GeneticAlgorithm <int> * genalg = NULL;

	genalg = new GeneticAlgorithm<int>(DEFAULTINTLIMITLOWER,DEFAULTINTLIMITUPPER, true);

	if (argc > 1) {
		bool oklow = false, okupp = false;

		float low = getCommandLineParameter<int>(
					argc,
					argv,
					NAME_OPTIONALSPACE_EQUAL_OPTIONALSPACE_VALUE_CLPARAM,
					"-genlimitlower",
					oklow
				);
		float upp = getCommandLineParameter<int>(
					argc,
					argv,
					NAME_OPTIONALSPACE_EQUAL_OPTIONALSPACE_VALUE_CLPARAM,
					"-genlimitupper",
					okupp
				);
//	GeneticAlgorithm <int> * genalg = NULL;
//
//	genalg = new GeneticAlgorithm<int>(DEFAULTINTLIMITLOWER,DEFAULTINTLIMITUPPER, false);
//
//	if (argc > 1) {
//		bool oklow = false, okupp = false;
//
//		int low = getCommandLineParameter<int>(
//					argc,
//					argv,
//					NAME_OPTIONALSPACE_EQUAL_OPTIONALSPACE_VALUE_CLPARAM,
//					"-genlimitlower",
//					oklow
//				);
//		int upp = getCommandLineParameter<int>(
//					argc,
//					argv,
//					NAME_OPTIONALSPACE_EQUAL_OPTIONALSPACE_VALUE_CLPARAM,
//					"-genlimitupper",
//					okupp
//				);
		if(oklow && okupp)
			genalg->setGenLimits(low,upp);
	};

	char * infile = NULL;
	char * outfile = NULL;

	infile = getCommandLineParameter<char *>(
					argc,
					argv,
					NAME_OPTIONALSPACE_EQUAL_OPTIONALSPACE_VALUE_CLPARAM,
					"-inputfile"
				);

	if (infile != NULL)
		genalg->read(outfile);
	else
		genalg->initializePopulation(
					getCommandLineParameter<int>(
						argc,
						argv,
						NAME_OPTIONALSPACE_EQUAL_OPTIONALSPACE_VALUE_CLPARAM,
						"-population"
					),
					getCommandLineParameter<int>(
						argc,
						argv,
						NAME_OPTIONALSPACE_EQUAL_OPTIONALSPACE_VALUE_CLPARAM,
						"-chromosome"
					),
					getCommandLineParameter<float>(
						argc,
						argv,
						NAME_OPTIONALSPACE_EQUAL_OPTIONALSPACE_VALUE_CLPARAM,
						"-crossover"
					),
					getCommandLineParameter<float>(
						argc,
						argv,
						NAME_OPTIONALSPACE_EQUAL_OPTIONALSPACE_VALUE_CLPARAM,
						"-mutation"
					)
				);

    int maxgen = getCommandLineParameter<int>(
                    argc,
                    argv,
                    NAME_OPTIONALSPACE_EQUAL_OPTIONALSPACE_VALUE_CLPARAM,
                    "-generations"
                 );
    int maxnoimprov = getCommandLineParameter<int>(
                    argc,
                    argv,
                    NAME_OPTIONALSPACE_EQUAL_OPTIONALSPACE_VALUE_CLPARAM,
                    "-maxnoimprovement"
                 );
   float mindif = getCommandLineParameter<float>(
                    argc,
                    argv,
                    NAME_OPTIONALSPACE_EQUAL_OPTIONALSPACE_VALUE_CLPARAM,
                    "-mindif"
                 );

    maxgen = max(0,maxgen);

    float bestfit=0;

    if (maxnoimprov == 0)
        bestfit = genalg->runForNGenerations(maxgen);
    else
        bestfit = genalg->runTillNoImprovement(maxnoimprov,maxgen);

    printf("\n\nBest fitness = %f\n", bestfit);

    genalg->getBestChromosome()->print();
    genalg->print();

	outfile = getCommandLineParameter<char *>(
					argc,
					argv,
					NAME_OPTIONALSPACE_EQUAL_OPTIONALSPACE_VALUE_CLPARAM,
					"-outputfile"
				);



	genalg->save(outfile);

	delete genalg;

	getchar();

	return 1;
}
