/***************************** License **********************************

 Copyright (C) 2013 by Jose Carlos Bins Filho josebins@gmail.com

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

************************************************************************/

#if !defined(_BScheduler_H_)
#define _BScheduler_H_

#include "BSchedulerDefaults.h"
#include "BList.h"
#include "BCommandLine.h"
#include "BFile.h"


//#define DEBUG_MODE 1

inline bool randomValue(bool lower = DEFAULTBOOLEANLIMITLOWER, bool upper = DEFAULTBOOLEANLIMITUPPER)
                {if ((float)rand() / RAND_MAX >= 0.5) return true; else return false;};
inline int randomValue(int lower = DEFAULTINTLIMITLOWER, int upper = DEFAULTINTLIMITUPPER)
//                {return min(lower + (int)((float)rand() / RAND_MAX * (upper - lower + 1)),upper);};
                {float r = (float)rand() / RAND_MAX;
                 return min(lower + (int)(r * (upper - lower + 1)),upper);};
inline float randomValue(float lower= DEFAULTFLOATLIMITLOWER, float upper = DEFAULTFLOATLIMITUPPER)
                {return  (lower + (float)rand() / RAND_MAX * (upper - lower));};
inline char randomValue(char lower = DEFAULTCHARLIMITLOWER, char upper = DEFAULTCHARLIMITUPPER)
                {return  (char)min((int)(lower + (float)rand() / RAND_MAX * (upper - lower + 1)),upper);};

void printCentralizedString(FILE*, int, char *);
void removeFromVector(int, int, int *);
bool memberIntVector(int, int, int *);
bool memberCharVector(char *, int, char**);
bool includeIntVector(int &, int &, int *&, int, int);
bool includeCharVector(int &, int &, char **&, char *);
char * getDayName(int);

typedef struct {
    int crednok;
    int credok;
    int cod;
    int np;
    int *used;
} ProfCredit;
typedef struct {
    int cod;
    int np;
    int *used;
    int *nas;
} SubjCredit;
typedef struct {
    int cod;
    int part;
} Part;
typedef struct {
    bool tpused;
    int sz;
    int codisc;
    int partdisc;
    int nprofs;
    int *profs;
} Slot;
void copySlot(Slot &, Slot);
bool deleteSlotVector(int, Slot *);
typedef struct {
    char* name;
    int nta;
    int * toavoid;
    int ndp;
    Part *disc;
} Professor;
bool deleteProfessorVector(int, Professor*);
typedef struct {
    int room;
    int * sched;
} RoomSchedule;
bool deleteRoomScheduleVector(int, RoomSchedule *);
typedef struct {
    char *title;
    int nrooms;
    RoomSchedule * roomavail;
    int slotavail[DEFAULTMAXNUMBEROFHOURSBYSLOT];
    int slotreq[DEFAULTMAXNUMBEROFHOURSBYSLOT];
} SemSchedule;
bool deleteSemScheduleVector(int, SemSchedule *);
typedef struct {
    int cred;
    int nprofs;
    int * profs;
} DiscPart;
bool deleteDiscPartVector(int, DiscPart *);
typedef struct {
    int n;
    bool * ok;
} Check;
typedef struct {
    char *title;
    int cred;
    int sem;
    int npart;
    DiscPart * part;
} Subject;
bool deleteSubjectVector(int, Subject *);
typedef struct {
    int sz;
    int np;
    int *slots;
} Period;
bool deletePeriodVector(int, Period *);
typedef struct {
    char*name;
    int np;
    Period * per;
} Shift;
bool deleteShiftVector(int, Shift *);

class GAProblemDefinition {
public:
	/// Constructor
	GAProblemDefinition(FILE*, FILE* =NULL);
	bool read();
    bool print();
	///// Default Destructor
	~GAProblemDefinition();
	int getSemesterNumberOfRooms(int i)  { if (i < 0 || i >= nsem) return 0; else return semavail[i].nrooms;};
	int * getSemesterRoomShedule(int i, int j)  { if (i < 0 || i >= nsem) return NULL; if (j < 0 || j >= semavail[i].nrooms) return NULL;
	                              else return semavail[i].roomavail[j].sched;};
	int getSemesterCode(char* =NULL);
	int getSemesterRoom(int i, int j){ if (i < 0 || i >= nsem) return -1; if (j < 0 || j >= semavail[i].nrooms) return -1;
	                    else return semavail[i].roomavail[j].room;};
	char * getSemesterName(int = -1);
	int getRoomCode(int);
	int getRoomNumber(int);
	int getSubjectCode(char* =NULL);
	char * getSubjectTitle(int = -1);
	int getNumberOfProfessors() { return nprofs;};
	int getProfessorCode(char* =NULL);
	Part getProfessorSubject(int p, int n);
	int * getProfessorSlotsToAvoid(int p, int &n);
	char * getProfessorName(int = -1);
    char * getProfessorsNickName(int n, int sz, int *profs);
    int getTableSize() { return tablesz;};
    int getNumberDiscPartsOfSubjects() { return nsubpart;};
    int getNumberSubjects() { return nsub;};
    int getSubjectNumberOfDiscParts(int i) { if (i < 0 || i >= nsub) return 0; else return subj[i].npart;};
    int getWeights(int i) { if (i < 0 || i >= nw) return -1; else return weights[i];};
    int getMaxWeights() { return maxweights;};
    int * getSubjectPartProfs(int, int);
    int getSubjectPartNumberofProfs(int, int);
    int getSubjectPartProf(int, int, int);
    int getSubjectIndexForProfessor(int, Part);
    int getSubjectSemester(int s) { if (s < 0 || s >= nsub) return -1; else return subj[s].sem;};
    int getSubjectPartCred(Part s) { if (s.cod < 0 || s.cod >= nsub) return 0;if (s.part < 0 || s.part >= subj[s.cod].npart) return 0;
                                     else return subj[s.cod].part[s.part].cred;};
    int getSemesterSlotSize(int code);
    int getRoomScheduleSize() { return schedsz;};
    char * getShiftName(int i) { if (i < 0 || i >= nshifts || shif == NULL) return NULL;
                                 return shif[i].name;}
    int getNumberOfShifts() { return nshifts;}
    int getShiftNumberOfPeriods(int i) { if (i < 0 || i >= nshifts || shif == NULL) return 0;
                                 return shif[i].np;}
    int getSlotSize(int);
    FILE* getLogFile() { return logfile;};
    bool testAvailabilty(int&,int&,int&);
    Slot * cloneScheduleModel();
    ProfCredit *  inicializeProfCredit();
    SubjCredit * inicializeSubjCredit();
	void printSchedule(FILE*, int *);
	void printModelRoom(int);
	void printScheduleModel();
    void printAllProfessorData();
    void printProfessorData(int n);
    void printAllSemesterData();
    void printSemesterData(int n);
    void printAllSubjectData();
    void printSubjectData(int n);
    void printMainDefinition();
    void printWeights();
protected:
    int nline;
    int nchar;
    int tablesz;
    int schedsz;
    int ndayweek;
    int nshifts;
    Shift *shif;
	int nrooms;
	int *rooms;
	int nprofs;
	Professor * prof;
	int nsem;
    SemSchedule * semavail;
    Slot *sched;
    int nsub;
    int nsubpart;
    Subject * subj;
    int nw;
    float *weights;
 	float maxweights;
    FILE * infile;
    FILE * logfile;

    bool cleanBuffer();
    bool readInt(int &, char * name = NULL, bool = true);
    bool readFloat(float &);
    bool readString(char * &);

};

class Chromosome {
public:
	///// Default Constructor
    Chromosome(GAProblemDefinition * = NULL,bool=false);

	///// Default Destructor
	~Chromosome();
	void print(bool = false);
	void hprint(FILE *, bool ini=true, bool end=true);
	void fprint(FILE *);
	///// Gets one gen from the current chromosome
	Slot * getChromosome() { return chrom;};
//	int gen (int p) {if (p >= 0 && p < chromsz) return chrom[p]; else return invalidChromosomeValue(type);}; ///< [in] Gen position
	int getSize() {return chromsz;};
	float getFitness() {return fitness;};
	float computeFitness();
	bool operator<(Chromosome x) { return (fitness < x.fitness);};
	bool operator<(Chromosome *x) { return (fitness < x->fitness);};
	bool operator>(Chromosome x) { return (fitness > x.fitness);};
	bool operator>(Chromosome *x) { return (fitness > x->fitness);};
	bool operator<=(Chromosome x) { return (fitness <= x.fitness);};
	bool operator<=(Chromosome *x) { return (fitness <= x->fitness);};
	bool operator>=(Chromosome x) { return (fitness >= x.fitness);};
	bool operator>=(Chromosome *x) { return (fitness >= x->fitness);};
	bool operator==(Chromosome x) { return (fitness == x.fitness);};
	bool operator==(Chromosome *x) { return (fitness == x->fitness);};
	bool crossover(Chromosome * parent1,Chromosome * parent2);
    bool fillChromossome();
	bool mutate( int);
	void mutate( float mut);
	void copy(Chromosome x);
	void copy(Chromosome * x);
	Chromosome * clone();
	bool sameElements(Chromosome *x);

protected:
    GAProblemDefinition * pd;
	ProfCredit * pcred;
	SubjCredit * scred;
	float fitness;
	int chromsz;
	int chromrooms;
	int schedsz;
//	SemSchedule * semsched;
	Slot *chrom;
	FILE * logfile;
    bool selecionaSlot(Part, int&);
    int * getAvailableSlots(Part, int &);
    int * getUsedSlots(Part, int &);
    bool testSchedule(int s, Part su);
    bool sameProfessor(int, int);
    bool testConflict00(int, int);
    bool testConflict01(int, int);
    bool testConflict02(int, int);
    bool testConflict03(int, int);
    bool testSwapSchedule(int s1, Part su1, int s2, Part su2);
    void deleteChrom();
    bool swapSlot(Part &, int&);
    void forceSubject(int sc, Part su);
    void printProfessorSchedule(int prof);
    void printProfessorsSchedules();
    bool testFourPeriods(int, int, int*);
    bool testProfessorPreferences(int, int, int*);
    bool testSubjectSize(int, int, int);
    bool * testSwap(int * slots, int n1, Part su, int &n2);
    bool * testSwapExclude(int * slots, int n1, Part su, int ex, int &n2);
    void repair();
    int getBusiestProfessor();
    bool getBusiestSubjectPart(Part &);
    bool markSubjectAsUsed(Part);
    bool unmarkSubjectAsUsed(Part);
    int getUnusedDisc(int n, int * used);
    Part selecionaSubject();
    void printRoomVerbose(int n);
    void printRoom(int n);
    void printAvailableProfessor(int);
    void printAvailableProfessorAll();
    bool testSubject(Part su);
    void printHTMLHeader(FILE * f);
    void printHTMLSchedule(FILE * f);
    void printHTMLId(int, FILE * f);
    void printHTMLFooter(FILE * f);
    void printHTMLRoom(int r, FILE * f);
    void printHTMLShift(int r, int s,  FILE * f);
    void printHTMLPeriod(int r, int s, int p, FILE * f);
    void resetAvailableSubjectSlots();

};

class GAPopulation {
public:
	/// Constructor
	GAPopulation(
		int psz,									///< [in] Population size
		float cross = DEFAULTMINCROSSOVERPERCENTAGE,	///< [in] Crossover percentaga
		float mut = DEFAULTMUTATIONPERCENTAGE,		///< [in] Mutation Percentage
        FILE * f1 = NULL,							///< [in] Input File
        FILE * f2 = NULL,							///< [in] Output file
        FILE * f3 = NULL							///< [in] Log file
    );
	bool read(FILE *);
    bool printData(FILE *);
	///// Default Destructor
	~GAPopulation();
	void print();
	void fprint(FILE*);
	Slot * getChromosome(int c, int &sz);
	int getPopulationSize() {return popsz;};
	float computeFitness();
	void generateRouleteTable();
	void pairIndividuals();
    void selectBest();
    void selectSiblings();
    void crossover();
    void mutate();
    float averageFitness();
	Chromosome * getBestChromosome() {return (pop == NULL) ? NULL : pop[0];};

protected:
    int chromsz;
	int popsz;
	GAProblemDefinition * probdef;
	float crossperc;
	float mutationrate;
	Chromosome ** pop;
	Chromosome ** sibling;
	Chromosome ** mutation;
	Chromosome ** aux;
	int **pair;
	float * roulete;
	FILE * infile;
	FILE * outfile;
	FILE * logfile;


};

class GeneticAlgorithm {
public:
	/// Default Constructor
	GeneticAlgorithm(char * f1, char * f2, char * f3);
	/// Constructor
	///// Default Destructor
	~GeneticAlgorithm();
	float runForNGenerations(int num = DEFAULTMAXOFGENERATIONS);
	float runTillNoImprovement(int numni = DEFAULTMAXOFGENERATIONSWITHOUTIMPROVEMENT, int numg = DEFAULTMAXOFGENERATIONS);
	bool initialized();
	bool initializePopulation(
		int psz,									///< [in] Population size
		float cross = DEFAULTMINCROSSOVERPERCENTAGE,	///< [in] Crossover percentaga
		float mut = DEFAULTMUTATIONPERCENTAGE		///< [in] Mutation Percentage
	);
	void print();
	bool read(
		char * fname								///< [in] Population size
	);
	bool initialize(
	);
	void save(char * fname = NULL);
	void saveHTML(char * fname = NULL);
	float computeFitness();
	float nextGeneration();
	Chromosome * getBestChromosome() {return (genpop == NULL) ? NULL : genpop->getBestChromosome();};

protected:
    int maxgen;
    int maxgennoimp;
	GAPopulation * genpop;
	FILE * infile;
	FILE * outfile;
	FILE * logfile;
};




#endif
