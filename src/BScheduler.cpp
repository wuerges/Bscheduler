

#include "BScheduler.h"

int getIndexNthOk(bool *ok, int sz, int n){
    if (n <0 || n >=sz)
        return -1;

    int i;

    for(i=0; i < sz;i++)
        if (ok[i])
            if (n == 0)
                return i;
            else
                n--;

    return -1;
}
void printIntVector(char* n, int * v, int sz){

    int i;

    printf("%s",n);
    for(i=0; i < sz;i++)
        printf("v[%d]=%d ",i,v[i]);
    printf("\n");
}
void printBoolVector(char* n, bool * ok, int sz){
    int i;

    printf("%s",n);
    for(i=0; i < sz;i++)
        if (ok[i])
            printf("ok[%d]=true ",i);
        else
            printf("ok[%d]=false ",i);
    printf("\n");
}
void copySlot(Slot & sl1, Slot sl2) {

    int i;

    sl1.codisc = sl2.codisc;
    sl1.partdisc = sl2.partdisc;
    sl1.sz = sl2.sz;
    sl1.tpused = sl2.tpused;
    sl1.nprofs = sl2.nprofs;
    sl1.profs = new int [DEFAULMAXNUMBERPROFESSORSBYSUBJECT];
    for (i=0; i < sl1.nprofs; i++)
        sl1.profs[i] = sl2.profs[i];
}
void printCentralizedString(FILE* f, int sz, char *str) {

    int i;
    int t = strlen(str);
    if (t > sz) t = sz;

    int b1 = (sz - t)/2;
    int b2 = (sz - t - b1);

    for (i=0; i < b1; i++) fprintf(f," ");
    for (i=0; i < t; i++)fprintf(f,"%c", str[i]);
    for (i=0; i < b2; i++) fprintf(f," ");
}
void removeFromVector(int n, int sz, int * v) {
    int i;

    if (!v)
        return;

    for (i=n; i < sz-1; i++)
        v[i] = v[i+1];
}
bool memberIntVector(int v, int n, int * p) {
    int i;

    if (!p)
        return false;

    for (i=0; i < n; i++)
        if (v == p[i])
            return true;
    return false;
}
bool memberCharVector(char * v, int n, char* * p) {
    int i;

    if (!p)
        return false;

    for (i=0; i < n; i++)
        if (strcmp(v,p[i])==0)
            return true;
    return false;
}
bool includeIntVector(int &n1, int &n2, int *&p, int v) {
    int i;

    int * aux;

    if (!p) {
        p = new int[DEFAULMAXNUMBEROFROOMS];
        p[0] = v;
        n1++;
        n2 = DEFAULMAXNUMBEROFROOMS;
        return true;
    } else if (n1 == n2) {
        aux = new int[n2];
        for (int i=0; i < n2; i++)
            aux[i] = p[i];
        delete [] p;
        p = new int[n2+DEFAULMAXNUMBEROFROOMS];
        for (int i=0; i < n2; i++)
            p[i] = aux[i];
        delete [] aux;
        p[n2] = v;
        n1++;
        n2 = n2+DEFAULMAXNUMBEROFROOMS;
        return true;
    } else {
        p[n1] = v;
        n1++;
        return true;
    }

}
bool includeCharVector(int &n1, int &n2, char * *&p, char * v) {
    int i;

    char ** aux;

    if (!p) {
        p = new char *[DEFAULTNUMBEROFSEMESTERS];
        p[0] = new char[strlen(v)+1];
        strcpy(p[0],v);
        n1++;
        n2 = DEFAULTNUMBEROFSEMESTERS;
        return true;
    } else if (n1 == n2) {
        aux = new char *[n2+DEFAULTNUMBEROFSEMESTERS];
        for (int i=0; i < n2; i++)
            aux[i] = p[i];
        aux[n2]=new char[strlen(v)+1];
        strcpy(aux[n2],v);
        delete [] p;
        p = aux;
        n1++;
        n2 = n2+DEFAULTNUMBEROFSEMESTERS;
        return true;
    } else {
        p[n1] = new char[strlen(v)+1];
        strcpy(p[n1],v);
        n1++;
        return true;
    }

}
bool deletePeriodVector(int n, Period * p) {
    int i;

    if (!p)
        return false;

    for (i=0; i < n; i++)
        delete p[i].slots;
    delete [] p;
    return true;
}
bool deleteShiftVector(int n, Shift * p) {
    int i;

    if (!p)
        return false;

    for (i=0; i < n; i++){
        delete p[i].name;
        deletePeriodVector(p[i].np, p[i].per);
    }
    delete p;
    return true;
}
bool deleteRoomScheduleVector(int n, RoomSchedule * p) {
    int i;

    if (!p)
        return false;

    for (i=0; i < n; i++)
        delete p[i].sched;
    delete p;
    return true;
}
bool deleteProfessorVector(int n, Professor *p) {
    int i;

    if (!p)
        return false;

    for (i=0; i < n; i++) {
        delete [] p[i].name;
        delete [] p[i].disc;
        delete [] p[i].toavoid;
    }
    delete [] p;
    return true;
}
bool deleteSemScheduleVector(int n, SemSchedule * p) {
    int i;

    if (!p)
        return false;

    for (i=0; i < n; i++){
        delete []  p[i].title;
        deleteRoomScheduleVector(p[i].nrooms, p[i].roomavail);
    }
    delete [] p;
    return true;
}
bool deleteDiscPartVector(int n, DiscPart * p) {
    int i;

    if (!p)
        return false;

    for (i=0; i < n; i++){
        delete p[i].profs;
    }
    delete [] p;
    return true;
}
bool deleteSubjectVector(int n, Subject * p) {
    int i;

    if (!p)
        return false;

    for (i=0; i < n; i++){
        deleteDiscPartVector(p[i].npart,p[i].part);
    }
    delete [] p;
    return true;
}
bool deleteSlotVector(int n, Slot * p) {
    int i;

    if (!p)
        return false;

    for (i=0; i < n; i++)
        delete [] p[i].profs;
    delete [] p;
    return true;
}
GAProblemDefinition::GAProblemDefinition(FILE* f1, FILE* f2): nline(0), nchar(0), schedsz(0), ndayweek(0), nshifts(0),
	          shif(NULL), nrooms(0), rooms(NULL), nprofs(0), prof(NULL), nsem(0), sched(NULL), weights(NULL), maxweights(0),
	          semavail(NULL), nsub(0), nsubpart(0), subj(NULL), infile(f1), logfile(f2) {

        read();
        print();
}
GAProblemDefinition::~GAProblemDefinition(){
    if (shif)
        deleteShiftVector(nshifts,shif);
    if (rooms)
        delete [] rooms;
    deleteProfessorVector(nprofs, prof);
    if (semavail)
        deleteSemScheduleVector(nsem,semavail);
    if (subj)
        deleteSubjectVector(nsub,subj);
}
bool GAProblemDefinition::testAvailabilty(int &s, int &t, int &n) {

    int i,j;
    int avail[DEFAULTMAXNUMBEROFHOURSBYSLOT];

    for (i=0; i < nsem; i++) {
        for(j=0; j < DEFAULTMAXNUMBEROFHOURSBYSLOT; j++)
            avail[j] = semavail[i].slotavail[j];
        for(j=DEFAULTMAXNUMBEROFHOURSBYSLOT-1; j >0; j--)
            if (avail[j] < semavail[i].slotreq[j]) {
                s = i;
                t = j+1;
                n = semavail[i].slotreq[j] - avail[j];
                return false;
            } else {
                avail[j-1] += avail[j] - semavail[i].slotreq[j];
                avail[j] = 0;
            }
        if (avail[0] < semavail[i].slotreq[0]){
            s = i;
            t = 1;
            n = semavail[i].slotreq[0] - avail[0];
            return false;
        }
    }

    return true;
 }
ProfCredit * GAProblemDefinition::inicializeProfCredit(){
#if DEBUG_MODE == 1
    fprintf(stderr,">>>>> Entering inicializeProfCredit: Parameters: void\n");
#endif // DEBUG_MODE

    int i, j;

    ProfCredit * pc = new ProfCredit[nprofs];

    for(i=0; i < nprofs; i++) {
        pc[i].cod = i;
        pc[i].crednok = 0;
        pc[i].credok = 0;
        pc[i].np = prof[i].ndp;
        pc[i].used = new int[prof[i].ndp];
        for(j=0; j < prof[i].ndp; j++){
            pc[i].used[j] = false;
            pc[i].crednok += subj[prof[i].disc[j].cod].part[prof[i].disc[j].part].cred;
        }
    }

#if DEBUG_MODE == 1
    fprintf(stderr,"<<<<< Leaving inicializeProfCredit: Result: %p\n",pc);
#endif // DEBUG_MODE
    return pc;
};
SubjCredit * GAProblemDefinition::inicializeSubjCredit(){
#if DEBUG_MODE == 1
    fprintf(stderr,">>>>> Entering inicializeSubjCredit: Parameters: void\n");
#endif // DEBUG_MODE

    int i, j;

    SubjCredit * sc = new SubjCredit[nsub];

    for(i=0; i < nsub; i++) {
        sc[i].cod = i;
        sc[i].np = subj[i].npart;
        sc[i].used = new int[subj[i].npart];
        for(j=0; j < subj[i].npart; j++)
            sc[i].used[j] =false;
    }

#if DEBUG_MODE == 1
    fprintf(stderr,"<<<<< Leaving inicializeSubjCredit: Result: %p\n", sc);
#endif // DEBUG_MODE
    return sc;
};

Part GAProblemDefinition::getProfessorSubject(int p, int n) {
    Part su;
    su.cod=-1;
    su.part=0;

    if (p < 0 || p >= nprofs)
        return su;
    if (n < 0 || n >= prof[p].ndp)
        return su;

    return prof[p].disc[n];
}

int GAProblemDefinition::getSubjectIndexForProfessor(int n, Part p){
#if DEBUG_MODE == 1
    fprintf(stderr,">>>>> Entering getSubjectIndexForProfessor: Parameters: n=%d p=%d\n",n,p);
#endif // DEBUG_MODE
    int i;

    for(i=0; i < prof[n].ndp; i++)
        if (prof[n].disc[i].cod == p.cod && prof[n].disc[i].part == p.part)
        return i;
};

int GAProblemDefinition::getSubjectPartProf(int d, int p, int i) {
#if DEBUG_MODE == 1
    fprintf(stderr,">>>>> Entering getSubjectPartProf: Parameters: disc=%d part=%d ind=%d\n",d,p,i);
#endif // DEBUG_MODE

     if (d < 0 || d >= nsub) return 0;
     if (p < 0 || p >= subj[d].npart) return 0;
     if (i < 0 || i >= subj[d].part[p].nprofs) return 0;

     int aux = subj[d].part[p].profs[i];

#if DEBUG_MODE == 1
    fprintf(stderr,"<<<<< Leaving getSubjectPartProf: Result: prof=%d\n",aux);
#endif // DEBUG_MODE
     return aux;
};
int * GAProblemDefinition::getSubjectPartProfs(int d, int p) {
#if DEBUG_MODE == 1
    fprintf(stderr,">>>>> Entering getSubjectPartProfs: Parameters: disc=%d part=%d\n",d,p);
#endif // DEBUG_MODE

     if (d < 0 || d >= nsub) return 0;
     if (p < 0 || p >= subj[d].npart) return 0;

#if DEBUG_MODE == 1
    fprintf(stderr,"<<<<< Leaving getSubjectPartProfs: Result: np=%d\n",subj[d].part[p].nprofs);
#endif // DEBUG_MODE
     return subj[d].part[p].profs;
};
int GAProblemDefinition::getSubjectPartNumberofProfs(int d, int p) {
#if DEBUG_MODE == 1
    fprintf(stderr,">>>>> Entering getSubjectPartNumberofProfs: Parameters: disc=%d part=%d\n",d,p);
#endif // DEBUG_MODE

     if (d < 0 || d >= nsub) return 0;
     if (p < 0 || p >= subj[d].npart) return 0;

#if DEBUG_MODE == 1
    fprintf(stderr,"<<<<< Leaving getSubjectPartNumberofProfs: Result: np=%d\n",subj[d].part[p].nprofs);
#endif // DEBUG_MODE
     return subj[d].part[p].nprofs;
};
int GAProblemDefinition::getSlotSize(int sl) {
#if DEBUG_MODE == 1
    fprintf(stderr,">>>>> Entering getSlotSize: Parameters: sl=%d\n",sl);
#endif // DEBUG_MODE

   if (sl < 0 || sl >= tablesz) {
        fprintf(stderr,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        fprintf(stderr,"ERRO >> Invalid slot !\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        return 0;
    }
#if DEBUG_MODE == 1
    fprintf(stderr,"<<<<< Leaving getSlotSize: Result: %d\n",sched[sl].sz);
#endif // DEBUG_MODE
    return sched[sl].sz;
}
Slot * GAProblemDefinition::cloneScheduleModel() {
#if DEBUG_MODE == 1
    fprintf(stderr,">>>>> Entering cloneScheduleModel: Parameters: void\n");
#endif // DEBUG_MODE

    Slot * aux = new Slot[tablesz];

    int i,j;

    for(i=0; i < tablesz; i++) {
        aux[i].tpused = sched[i].tpused;
        aux[i].sz = sched[i].sz;
        aux[i].codisc = sched[i].codisc;
        aux[i].partdisc = sched[i].partdisc;
        aux[i].nprofs = sched[i].nprofs;
        aux[i].profs = new int [DEFAULMAXNUMBERPROFESSORSBYSUBJECT];
    }

#if DEBUG_MODE == 1
    fprintf(stderr,"<<<<< Leaving makeAllRoomScheduleByModel: Result: to large to show\n");
#endif // DEBUG_MODE

   return aux;
}
int GAProblemDefinition::getProfessorCode(char *namep) {
    if (namep == NULL) {
        fprintf(stderr,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        fprintf(stderr,"ERRO >> Invalid professor name !\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        return -1;
    }

    int i;

    for (i=0; i < nprofs; i++)
        if (strcmp(namep,prof[i].name)==0)
            return i;

    fprintf(stderr,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    fprintf(stderr,"ERRO >> Could not find professor name %s !\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n",namep);
    return -1;
}
char *  GAProblemDefinition::getProfessorName(int code) {
    if (code < 0 || code > nprofs-1) {
        fprintf(stderr,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        fprintf(stderr,"ERRO >> Invalid professor code %d !\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n", code);
        return NULL;
    }

    return prof[code].name;
}
char *  GAProblemDefinition::getProfessorsNickName(int n, int sz, int *p) {

    int i,j,k;
    int t = (sz-n+1)/n;

    char * nick = new char[DEFAULTNAMESIZE];
    k=0;
    for(i=0; i < n; i++) {
        for(j=0; j < t; j++) {
            if (prof[p[i]].name[j] == '\0') break;
            nick[k++] = prof[p[i]].name[j];
        }

        if (i < n-1)
            nick[k++] = '/';
    }
    nick[k]='\0';

   return nick;
}
int GAProblemDefinition::getSubjectCode(char *namep) {
    if (namep == NULL) {
        fprintf(stderr,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        fprintf(stderr,"ERRO >> Invalid subject title !\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        return -1;
    }

    int i;

    for (i=0; i < nsub; i++)
        if (strcmp(namep,subj[i].title)==0)
            return i;

    fprintf(stderr,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    fprintf(stderr,"ERRO >> Could not subject title %s !\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n",namep);
    return -1;
}
char *  GAProblemDefinition::getSubjectTitle(int code) {
    if (code < 0 || code > nsub-1) {
        fprintf(stderr,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        fprintf(stderr,"ERRO >> Invalid subject code %d !\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n", code);
        return NULL;
    }

    return subj[code].title;
}
int GAProblemDefinition::getSemesterCode(char *namep) {
    if (namep == NULL){
        fprintf(stderr,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        fprintf(stderr,"ERRO >> Invalid semestr title !\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        return -1;
    }

    int i;

    for (i=0; i < nsem; i++)
        if (strcmp(namep,semavail[i].title)==0)
            return i;

   fprintf(stderr,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    fprintf(stderr,"ERRO >> Could not find semester title %s !\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n",namep);
   return -1;
}
char *  GAProblemDefinition::getSemesterName(int code) {
    if (code < 0 || code > nsem-1)
        return NULL;


    return semavail[code].title;
}
int GAProblemDefinition::getRoomCode(int n) {
    int i;

    for (i=0; i < nrooms; i++)
        if (rooms[i] == n)
            return i;

   fprintf(stderr,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
   fprintf(stderr,"ERRO >> Could not find room code %s !\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n",n);
   return -1;
}
int  GAProblemDefinition::getRoomNumber(int code) {
    if (code < 0 && code >= nrooms){
        fprintf(stderr,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        fprintf(stderr,"ERRO >> Invalid Room Code !\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        return -1;
    }

     return rooms[code];
}
int  GAProblemDefinition::getSemesterSlotSize(int code) {
    if (code < 0 || code >=30)
        return -1;

    int i,j,k;

    for (i=0; i < nshifts; i++)
        for(j=0; j < shif[i].np; j++)
            for(k=0; k < shif[i].per[j].np; k++)
                if (shif[i].per[j].slots[k] == code)
                    return shif[i].per[j].sz;

    return -1;
}

bool GAProblemDefinition::cleanBuffer() {
    int c;

    c = getc(infile);
    while (true) {
        if (c == EOF)
            return false;
        else if (isalnum(c)){
            ungetc(c, infile);
            return true;
        } else {
            nchar++;
            if (c == '\n)') {
                nline++;
                nchar = 0;
            } else if(c == '%') {
                while (c != '\n') c= getc(infile);
            } else c = getc(infile);
        }
    }
}

bool GAProblemDefinition::readInt(int & num) {

    cleanBuffer();
    char number[DEFAULTNUMBERSIZE+1];

    int i=0;
    bool ok = true;
    for(i=0; i < DEFAULTNUMBERSIZE && ok; i++){
        number[i] = getc(infile);
        if (!isdigit(number[i])){
            ok = false;
            ungetc(number[i],infile);
            number[i] = '\0';
            if (i==0)  {
                fprintf(stderr,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                fprintf(stderr,"ERROR: Could not read Int value!\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            }
        }
    }
    num = atoi(number);

}
bool GAProblemDefinition::readFloat(float & num) {

    cleanBuffer();
    char number[DEFAULTNUMBERSIZE+1];

    int i=0;
    bool ok = true;
    bool dot = false;
    for(i=0; i < DEFAULTNUMBERSIZE && ok; i++){
        number[i] = getc(infile);
        if (!isdigit(number[i]))
            if (!number[i] == '.' || dot) {
                ok = false;
                ungetc(number[i],infile);
                number[i] = '\0';
                if (i==0)  {
                    fprintf(stderr,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                    fprintf(stderr,"ERROR: Could not read float value!\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                }
            } else dot = true;
    }
    num = atof(number);

}
bool GAProblemDefinition::readString(char * & str) {

    char aux[DEFAULTNAMESIZE];
    cleanBuffer();
    fscanf(infile,"%s",aux);
    str = new char[strlen(aux)+1];
    strcpy(str,aux);
}
bool GAProblemDefinition::read() {

	if (infile == NULL)
		return false;

    int i,j,k;
    int n,s,t, r;

    char  * aux = new char[DEFAULTNAMESIZE];

    int naux = 0;

    readInt(ndayweek);
    readInt(nshifts);
    shif = new Shift[nshifts];
    schedsz = 0;
    for(i=0; i <  nshifts; i++) {
        readString(aux);
        shif[i].name = new char[strlen(aux)+1];
        strcpy(shif[i].name, aux);
        readInt(shif[i].np);
        schedsz += shif[i].np;
        shif[i].per = new Period[shif[i].np];
        for(j=0; j <  shif[i].np; j++) {
            readInt(shif[i].per[j].sz);
            readInt(shif[i].per[j].np);
            shif[i].per[j].slots = new int[shif[i].per[j].np];
            for(k=0; k < shif[i].per[j].np; k++)
                readInt(shif[i].per[j].slots[k]);
        }
    }
    schedsz = schedsz * ndayweek;

    readInt(nprofs);

	prof = new Professor[nprofs];

	for (i=0; i < nprofs; i++) {
        prof[i].toavoid = new int[schedsz];
        prof[i].disc = new Part[DEFAULTMAXNUMBEROFCLASSESBYPROFESSOR];
        prof[i].ndp = 0;
        for (j=0; j < DEFAULTMAXNUMBEROFCLASSESBYPROFESSOR; j++) {
            prof[i].disc[j].cod = -1;
            prof[i].disc[j].part = -1;
        }
        for (j=0; j < schedsz; j++)
            prof[i].toavoid[j] = DEFAULTVALUEFORNEUTRALSCHEDULE;
		readString(prof[i].name);
		readInt(n);
		prof[i].nta = n;
        for (j=0; j < n; j++) {
            readInt(s);
            prof[i].toavoid[s] = DEFAULTVALUEFORAVOIDSCHEDULE;
        }
    }

	readInt(nsem);

	semavail = new SemSchedule [nsem];

	for (i=0; i < nsem; i++) {
 		readString( semavail[i].title);
 		readInt( semavail[i].nrooms);
 		semavail[i].roomavail = new RoomSchedule[semavail[i].nrooms];
 		for(j=0; j < DEFAULTMAXNUMBEROFHOURSBYSLOT; j++){
            semavail[i].slotavail[j]=0;
            semavail[i].slotreq[j]=0;
 		}
        for (k=0; k < semavail[i].nrooms; k++) {
            semavail[i].roomavail[k].sched = new int[schedsz];
            for (j=0; j < schedsz; j++)
                semavail[i].roomavail[k].sched[j] = DEFAULTVALUEFORFORBIDSCHEDULE;
            readInt(r);
            if (!memberIntVector(r, nrooms, rooms))
                includeIntVector(nrooms,naux,rooms,r);
            semavail[i].roomavail[k].room = getRoomCode(r);
            readInt(n);
            for (j=0; j < n; j++) {
                readInt( s);
                semavail[i].roomavail[k].sched[s] = DEFAULTVALUEFORPREFEREDSCHEDULE;
                semavail[i].slotavail[getSemesterSlotSize(s) -1]++;
            }
            readInt(n);
            for (j=0; j < n; j++) {
                readInt( s);
                semavail[i].roomavail[k].sched[s] = DEFAULTVALUEFORNEUTRALSCHEDULE;
            }
        }
    }

	readInt( nsub);

	subj = new Subject[nsub];

    nsubpart = 0;
	for (i=0; i < nsub; i++) {
 		readString( subj[i].title);
 		readInt( subj[i].cred);
 		readString(aux);
 		subj[i].sem = getSemesterCode(aux);
 		readInt( subj[i].npart);
 		nsubpart+= subj[i].npart;
        subj[i].part = new DiscPart [subj[i].npart];
        for (k=0; k < subj[i].npart; k++) {
            readInt( subj[i].part[k].cred);
            semavail[subj[i].sem].slotreq[subj[i].part[k].cred-1]++;
            readInt( subj[i].part[k].nprofs);
            subj[i].part[k].profs = new int[subj[i].part[k].nprofs];
            for (j=0; j < subj[i].part[k].nprofs; j++) {
                readString(aux);
                subj[i].part[k].profs[j] = getProfessorCode(aux);
                prof[subj[i].part[k].profs[j]].disc[prof[subj[i].part[k].profs[j]].ndp].cod = i;
                prof[subj[i].part[k].profs[j]].disc[prof[subj[i].part[k].profs[j]].ndp].part = k;
                prof[subj[i].part[k].profs[j]].ndp++;

            }
        }
    }

    readInt(nw);
    weights = new float[nw];
    for (i=0; i < nw; i++)
        readFloat(weights[i]);

    maxweights = nsubpart/2*weights[0];
    for(i=0; i< nprofs; i++)
        maxweights = maxweights + prof[i].nta * weights[1];
    for(i=0; i <  nshifts; i++)
        for(j=0; j <  shif[i].np; j++)
            if(shif[i].per[j].sz == 3)
                maxweights = maxweights + shif[i].per[j].np * weights[2];

    tablesz = nrooms * schedsz;

    sched = new Slot[tablesz];

    int x=0;
    for(i=0; i <  tablesz; i++) {
        sched[i].tpused = false;
        sched[i].sz = 0;
        sched[i].codisc = -1;
        sched[i].partdisc = 0;
        sched[i].nprofs=0;
        sched[i].profs = new int [DEFAULMAXNUMBERPROFESSORSBYSUBJECT];
    }
   for(i=0; i <  nshifts; i++)
        for(j=0; j <  shif[i].np; j++)
            for(k=0; k < shif[i].per[j].np; k++)
                sched[shif[i].per[j].slots[k]].sz = shif[i].per[j].sz;

    if (!testAvailabilty(s,t,n)){
        fprintf(stderr,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        fprintf(stderr,"ERROR: Not enough slots for semesters!\n\tSemester %d:%s missing %d slot(s) of size %d.\n",s,
                getSemesterName(s), n,t);
        fprintf(stderr,"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        getchar();
        exit(EXIT_FAILURE);
	}

    delete aux;

	return true;
};
void GAProblemDefinition::printMainDefinition(){
    int i,j,k;

    fprintf(logfile,"Semana = %d Turnos = %d\n", ndayweek, nshifts);
    for(i=0; i <  nshifts; i++) {
        fprintf(logfile,"\tT= %d:%s Np = %d\n", i, shif[i].name, shif[i].np);
        for(j=0; j <  shif[i].np; j++) {
            fprintf(logfile,"\t\tP= %d sz = %d nh=%d ", j, shif[i].per[j].sz, shif[i].per[j].np);
            for(k=0; k < shif[i].per[j].np; k++)
                fprintf(logfile,"H= %d ", shif[i].per[j].slots[k]);
            fprintf(logfile,"\n");
        }
    }
}
void GAProblemDefinition::printAllSubjectData(){
    int i;

	fprintf(logfile, "NSubj=%d\n", nsub);
	for (i=0; i < nsub; i++)
       printSubjectData(i);
 }
void GAProblemDefinition::printSubjectData(int n){
    int i,j;

    fprintf(logfile,"Subject= %d:%s Cred=%d Sem=%s DiscParts=%d ",
                n,subj[n].title, subj[n].cred,
                getSemesterName(subj[n].sem), subj[n].npart);
    for (i=0; i < subj[n].npart; i++) {
        fprintf(logfile,"DiscPart #%d cred = %d profs= %d ",i,
                subj[n].part[i].cred, subj[n].part[i].nprofs);
        for (int j=0; j < subj[n].part[i].nprofs; j++)
            fprintf(logfile,"%s ",getProfessorName(subj[n].part[i].profs[j]));
    }
    fprintf(logfile,"\n");
}
void GAProblemDefinition::printAllSemesterData(){
    int i;

	fprintf(logfile, "Nsem=%d\n", nsem);
	for (i=0; i < nsem; i++)
        printSemesterData(i);
 }
void GAProblemDefinition::printSemesterData(int n){
    int i;

    fprintf(logfile,"Semestre: %s Avail=%d/%d/%d/%d/%d Req=%d/%d/%d/%d/%d Rooms = %d ",semavail[n].title,
            semavail[n].slotavail[0], semavail[n].slotavail[1], semavail[n].slotavail[2],
            semavail[n].slotavail[3], semavail[n].slotavail[4], semavail[n].slotreq[0],
            semavail[n].slotreq[1], semavail[n].slotreq[2], semavail[n].slotreq[3],
            semavail[n].slotreq[4], semavail[n].nrooms);
    for (int i=0; i < semavail[n].nrooms; i++) {
            fprintf(logfile,"Room %d : %d\n", i, semavail[n].roomavail[i].room);
            fprintf(logfile,"Tabela Horarios\n");
            printSchedule(logfile,semavail[n].roomavail[i].sched);
    }
}
void GAProblemDefinition::printAllProfessorData(){
    int i;

    fprintf(logfile, "Nprofs= %d\n", nprofs);
	for (i=0; i < nprofs; i++)
        printProfessorData(i);
}
void GAProblemDefinition::printProfessorData(int n){
    int i;
	fprintf(logfile,"Prof=%d:%s\n",n, prof[n].name);
    fprintf(logfile,"Tabela Preferencias\n");
    printSchedule(logfile,prof[n].toavoid);
    fprintf(stderr,"Subjects:\n");
    for (i=0; i < prof[n].ndp; i++)
        fprintf(stderr,"\tD=%s C=%d P=%d C=%d\n",getSubjectTitle(prof[n].disc[i].cod),
                prof[n].disc[i].cod, prof[n].disc[i].part,subj[prof[n].disc[i].cod].part[prof[n].disc[i].part].cred);
}
void GAProblemDefinition::printWeights(){
    int i;

    for(i=0; i < nw; i++)
        fprintf(logfile,"W[%d]=%f ", i, weights[i]);
    fprintf(logfile,"\n");
    fprintf(logfile,"MaxW = %f\n", maxweights);
}
void GAProblemDefinition::printSchedule(FILE *f, int *sched){

    int i,j,k;

    for (int i=0; i < 3; i++) {
        for (int j=0; j < 2; j++) {
            for (int k=0; k < 5; k++) {
                switch (sched[i*10+k*2+j]) {
                case DEFAULTVALUEFORFORBIDSCHEDULE: fprintf(f,"%c", DEFAULTVALUEFORFORBIDSCHEDULEMARK);
                        break;
                case DEFAULTVALUEFORAVOIDSCHEDULE: fprintf(f,"%c", DEFAULTVALUEFORAVOIDSCHEDULEMARK);
                        break;
                case DEFAULTVALUEFORNEUTRALSCHEDULE: fprintf(f,"%c", DEFAULTVALUEFORNEUTRALSCHEDULEMARK);
                        break;
                case DEFAULTVALUEFORPREFEREDSCHEDULE: fprintf(f,"%c", DEFAULTVALUEFORPREFEREDSCHEDULEMARK);
                        break;
                case DEFAULTVALUEFOROCCUPIEDSCHEDULE: fprintf(f,"%c", DEFAULTVALUEFOROCCUPIEDSCHEDULEMARK);
                        break;
                default: fprintf(f,"%c", DEFAULTVALUEFORERRORSCHEDULEMARK);
                }
            }
            fprintf(f,"\n");
        }
    }
};
bool GAProblemDefinition::print() {

	if (logfile == NULL)
		return false;

    printMainDefinition();
    printWeights();
//    printScheduleModel();
 	printAllProfessorData();
    printAllSemesterData();
    printAllSubjectData();

	return true;
};

Chromosome::Chromosome(GAProblemDefinition *p, bool fill): pd(p), chrom(NULL), chromsz(0), fitness(0), pcred(NULL), scred(NULL){

#if DEBUG_MODE == 1
    fprintf(stderr,">>>>> Entering Chromosome: Parameters: def =%p fill=%d\n",(GAProblemDefinition*)p, fill);
#endif // DEBUG_MODE

    if (pd == NULL)
        return;


    chromsz = pd->getTableSize();
    schedsz = pd->getRoomScheduleSize();
    chromrooms = chromsz / schedsz;
    logfile = pd->getLogFile();
    pcred = pd->inicializeProfCredit();
    scred = pd->inicializeSubjCredit();



	if (chromsz < 1)
		return;

    chrom = pd->cloneScheduleModel();

    if (fill)
        fillChromossome();

#if DEBUG_MODE == 1
    fprintf(logfile,"<<<<< Leaving Chromosome: Result: void\n");
#endif // DEBUG_MODE
}
bool Chromosome::fillChromossome() {
#if DEBUG_MODE == 1
    fprintf(stderr,">>>>> Entering fillChromossome: Parameters: void\n");
#endif // DEBUG_MODE

    int i, j, sc;
    Part su;
    bool ok = false;

    int nsubpart = pd->getNumberDiscPartsOfSubjects();
    while (!ok) {
        ok = true;
        for (i=0; i < nsubpart; i++) {
            su = selecionaSubject();
            sc = selecionaSchedule(su);
            if (sc == -1)
                sc = swapSchedule(su);
            if (sc == -1) {
                ok = false;
                break;
            };
            if(chrom[sc].tpused)
                printf("---------- Unexpected error -----------\n");
            chrom[sc].codisc = su.cod;
            chrom[sc].partdisc = su.part;
            chrom[sc].tpused = true;
            chrom[sc].nprofs = pd->getSubjectPartNumberofProfs(su.cod, su.part);
            for(j=0; j < chrom[sc].nprofs; j++)
                chrom[sc].profs[j] = pd->getSubjectPartProf(su.cod, su.part, j);
            markSubjectAsUsed(su);
        }
        if (!ok) {
            deleteChrom();
            chrom = pd->cloneScheduleModel();
            pcred = pd->inicializeProfCredit();
            scred = pd->inicializeSubjCredit();
        }
    }

    printf("Chromosome ok!\n");

#if DEBUG_MODE == 1
    fprintf(logfile,"<<<<< Leaving fillChromossome: Result: true\n");
#endif // DEBUG_MODE
    return true;
}
bool Chromosome::markSubjectAsUsed(Part su){
#if DEBUG_MODE == 1
    fprintf(stderr,">>>>> Entering markSubjectAsUsed: Parameters: Cod=%d Part=%d\n", su.cod, su.part);
#endif // DEBUG_MODE

    if (su.cod < 0 || su.cod >= pd->getNumberSubjects()) return false;
    if (su.part < 0 || su.part >= scred[su.cod].np) return false;

    int i, p, ind,cred;
    int np = pd->getSubjectPartNumberofProfs(su.cod,su.part);

    for(i=0; i < np; i++) {
        p = pd->getSubjectPartProf(su.cod,su.part,i);
        ind = pd->getSubjectIndexForProfessor(p, su);
        pcred[p].used[ind] = true;
 //       printf("marcar prof=%s disc=%s used=%d\n", pd->getProfessorName(p), pd->getSubjectTitle(pd->getProfessorSubject(p,ind).cod), pcred[p].used[ind]);
        cred = pd->getSubjectPartCred(su);
        pcred[p].crednok -= cred;
        pcred[p].credok += cred;
    }

    scred[su.cod].used[su.part] = true;

//    printAvailableProfessorAll();

#if DEBUG_MODE == 1
    fprintf(stderr,"<<<<< Leaving markSubjectAsUsed: Result: true\n");
#endif // DEBUG_MODE
    return true;
};
bool Chromosome::unmarkSubjectAsUsed(Part su){
#if DEBUG_MODE == 1
    fprintf(stderr,">>>>> Entering unmarkSubjectAsUsed: Parameters: Cod=%d Part=%d\n", su.cod, su.part);
#endif // DEBUG_MODE

    if (su.cod < 0 || su.cod >= pd->getNumberSubjects()) return false;
    if (su.part < 0 || su.part >= scred[su.cod].np) return false;

    int i, p, ind,cred;
    int np = pd->getSubjectPartNumberofProfs(su.cod,su.part);

    for(i=0; i < np; i++) {
        p = pd->getSubjectPartProf(su.cod,su.part,i);
        ind = pd->getSubjectIndexForProfessor(p, su);
        pcred[p].used[ind] = false;
//        printf("desmarcar prof=%s disc=%s used=%d\n", pd->getProfessorName(p), pd->getSubjectTitle(pd->getProfessorSubject(p,ind).cod), pcred[p].used[ind]);
        cred = pd->getSubjectPartCred(su);
        pcred[p].crednok += cred;
        pcred[p].credok -= cred;
    }

    scred[su.cod].used[su.part] = false;

//    printAvailableProfessorAll();

#if DEBUG_MODE == 1
    fprintf(stderr,"<<<<< Leaving unmarkSubjectAsUsed: Result: true\n");
#endif // DEBUG_MODE
    return true;
};
int Chromosome::getBusiestProfessor(){
    int i;

    int maxcred = 0,
        nummax = 0,
        n,
        np;

    np = pd->getNumberOfProfessors();
    for (i=0; i < np; i ++)
        if (pcred[i].crednok > maxcred) {
            maxcred = pcred[i].crednok;
            nummax = 1;
        } else if (pcred[i].crednok == maxcred)
            nummax++;

    n = randomValue(1,nummax);

//    printf("nummax=%d maxcred = %d\n", nummax, maxcred);
    for(i=0; i < np; i++) {
        if (pcred[i].crednok == maxcred)
            if (n == 1)
               return i;
            else
               n--;
    }

    fprintf(stderr,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    fprintf(stderr,"ERRO >> Could not find busiest professor !\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    getchar();
    exit(EXIT_FAILURE);

}
Part Chromosome::selecionaSubject(){
#if DEBUG_MODE == 1
    fprintf(stderr,">>>>> Entering selecionaSubject: Parameters: void\n");
#endif // DEBUG_MODE

    int p;

    p = getBusiestProfessor();

//    printf("%s\n", pd->getProfessorName(p));

//    for (int j=0; j < pcred[p].np; j++) {
//        printf("disc[%d]=%d - used[%d]=%d\n", j, pd->getProfessorSubject(p,j).cod, j, pcred[p].used[j]);
//    }
    int i = getUnusedDisc(pcred[p].np, pcred[p].used);
    Part aux = pd->getProfessorSubject(p,i);

#if DEBUG_MODE == 1
    fprintf(stderr,"<<<<< Leaving selecionaSubject: Result: Cod = %d Part = %d\n", aux.cod, aux.part);
#endif // DEBUG_MODE
    return aux;
};
bool Chromosome::testSubject(Part su){

    if (su.cod < 0 || su.cod >= pd->getNumberSubjects())
        return false;
    if (su.part < 0 || su.part >= pd->getSubjectNumberOfDiscParts(su.cod))
        return false;

     return !scred[su.cod].used[su.part];

}
int Chromosome::getUnusedDisc(int n, int * used){
    int i;


    for (i=0; i < n; i ++)
        if (!used[i])
            return i;

    fprintf(stderr,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    fprintf(stderr,"ERRO >> Could not find Unused Disc for professor!\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    getchar();
    exit(EXIT_FAILURE);
}
Chromosome::~Chromosome() {
#if DEBUG_MODE == 1
    fprintf(stderr,">>>>> Entering ~Chromosome: Parameters: void\n");
#endif // DEBUG_MODE
	if (chromsz == 0 || chrom == NULL)
		return;

    if (chrom)
        deleteChrom();
	chrom = NULL;

#if DEBUG_MODE == 1
    fprintf(logfile,"<<<<< Leaving ~Chromosome: Result: void\n");
#endif // DEBUG_MODE

}
void Chromosome::deleteChrom() {
#if DEBUG_MODE == 1
    fprintf(stderr,">>>>> Entering deleteChrom: Parameters: void\n");
#endif // DEBUG_MODE

	if (chrom == NULL)
		return;

    int i;

    deleteSlotVector(chromsz,chrom);
	chrom = NULL;
#if DEBUG_MODE == 1
    fprintf(logfile,"<<<<< Leaving deleteChrom: Result: void\n");
#endif // DEBUG_MODE
}
float Chromosome::computeFitness(){
#if DEBUG_MODE == 1
    fprintf(stderr,">>>>> Entering computeFitness: Parameters: \n");
#endif // DEBUG_MODE

    int i;
    int nw0,nw1,nw2,w0, w1, w2;
    float mw;
    w0 = pd->getWeights(0);
    w1 = pd->getWeights(1);
    w2 = pd->getWeights(2);
    mw = pd->getMaxWeights();

    nw0=nw1=nw2=0;
    for (i=0; i<chromsz; i++) {
        if (chrom[i].tpused) {
            if (testFourPeriods(i,chrom[i].nprofs, chrom[i].profs))
                nw0++;
            if (!testProfessorPreferences(i,chrom[i].nprofs, chrom[i].profs))
                nw1++;
            if (!testSubjectSize(i,chrom[i].codisc, chrom[i].partdisc))
                nw2++;
        }

    }
    fitness = 1 - (nw0*w0+nw1+w1+nw2+w2)/mw;

#if DEBUG_MODE == 1
    fprintf(logfile,"<<<<< Leaving computeFitness: Result: fitness=%f\n", fitness);
#endif // DEBUG_MODE
    return fitness;
}
void Chromosome::forceSubject(int sc, Part su){
#if DEBUG_MODE == 1
    fprintf(stderr,">>>>> Entering forceSchedule: Parameters: slot = %d cod = %d part = %d \n", sc, su.cod, su.part);
#endif // DEBUG_MODE

    int i;


    chrom[sc].codisc = su.cod;
    chrom[sc].partdisc = su.part;
    chrom[sc].tpused = true;
    chrom[sc].nprofs = pd->getSubjectPartNumberofProfs(su.cod, su.part);
    for(i=0; i < chrom[sc].nprofs; i++)
        chrom[sc].profs[i] = pd->getSubjectPartProf(su.cod, su.part, i);
    markSubjectAsUsed(su);


#if DEBUG_MODE == 1
    fprintf(logfile,"<<<<< Leaving forceSchedule: Result: void\n");
#endif // DEBUG_MODE
}
int * Chromosome::getAvailableSlots(Part su, int &ns){
#if DEBUG_MODE == 1
    fprintf(stderr,">>>>> Entering getAvailableSlots: Parameters: cod=%d part=%d\n", su.cod, su.part);
#endif // DEBUG_MODE

    int i, j;

    int *aux = new int[chromsz];

    int s = pd->getSubjectSemester(su.cod);
    int c = pd->getSubjectPartCred(su);
    int n = pd->getSemesterNumberOfRooms(s);
    int r;
    int ** sched = new int *[n];

    ns=0;
    for (i=0; i < n; i++) {
        r = pd->getSemesterRoom(s,i);
        sched[i] = pd->getSemesterRoomShedule(s,i);
 //       printIntVector("Schedule ", sched[i],schedsz);
        for (j=0; j < schedsz; j++)
            if ((sched[i][j] == DEFAULTVALUEFORAVOIDSCHEDULE ||
                 sched[i][j] == DEFAULTVALUEFORNEUTRALSCHEDULE ||
                 sched[i][j] == DEFAULTVALUEFORPREFEREDSCHEDULE) &&
                 !chrom[r*schedsz+j ].tpused)
                 aux[ns++] = r*schedsz+j;
    }
    delete [] sched;

#if DEBUG_MODE == 1
    fprintf(stderr,"<<<<< Leaving getAvailableSlots: Result: n=%d\n",ns);
#endif // DEBUG_MODE
     return aux;
};
int * Chromosome::getUsedSlots(Part su, int &ns){
#if DEBUG_MODE == 1
    fprintf(stderr,">>>>> Entering getUsedSlots: Parameters: P=%p cod=%d part=%d\n", pd, su.cod, su.part);
#endif // DEBUG_MODE

    int i, j;

    int *aux = new int[chromsz];

    int s = pd->getSubjectSemester(su.cod);
    int c = pd->getSubjectPartCred(su);
    int n = pd->getSemesterNumberOfRooms(s);
    int r;
    int ** sched = new int *[n];

    ns=0;
    for (i=0; i < n; i++) {
        r = pd->getSemesterRoom(s,i);
        sched[i] = pd->getSemesterRoomShedule(s,i);
//        printIntVector("Schedule ", sched[i],schedsz);
        for (j=0; j < schedsz; j++)
            if ((sched[i][j] == DEFAULTVALUEFORAVOIDSCHEDULE ||
                 sched[i][j] == DEFAULTVALUEFORNEUTRALSCHEDULE ||
                 sched[i][j] == DEFAULTVALUEFORPREFEREDSCHEDULE) &&
                 chrom[r*schedsz+j ].tpused)
                  aux[ns++] = r*schedsz+j;
    }
    delete [] sched;

#if DEBUG_MODE == 1
    fprintf(stderr,"<<<<< Leaving getUsedSlots: Result: n=%d\n",ns);
#endif // DEBUG_MODE
     return aux;
};
bool Chromosome::sameProfessor(int slot, int prof){
#if DEBUG_MODE == 1
    fprintf(stderr,">>>>> Entering sameProfessor: Parameters: slot = %d prof = %d \n", slot, prof);
#endif // DEBUG_MODE


    int i,j,s;



    for (i=0; i < chromrooms; i++){
        s = i*schedsz+slot;
        if (chrom[s].tpused)
            for (j=0; j < chrom[s].nprofs; j++)
                if (chrom[s].profs[j] == prof)
                    return true;
    }

#if DEBUG_MODE == 1
    fprintf(stderr,"<<<<< Leaving getUsedSlots: Result: false\n");
#endif // DEBUG_MODE
    return false;
}
bool Chromosome::testConflict00(int prof, int slot){
#if DEBUG_MODE == 1
    fprintf(stderr,">>>>> Entering testConflict00: Parameters: prof = %d slot = %d \n", prof, slot);
#endif // DEBUG_MODE

    int s = slot % schedsz;

    if (sameProfessor(s,prof))
        return false;
    return true;
}
bool Chromosome::testConflict01(int prof, int slot){
#if DEBUG_MODE == 1
    fprintf(stderr,">>>>> Entering testConflict01: Parameters: prof = %d slot = %d\n", prof, slot);
#endif // DEBUG_MODE

    int s = slot % schedsz;

    switch (s) {
        case 21:
        case 23:
        case 25:
        case 27: if (sameProfessor(s-19,prof))
                    return false;
                 return true;
        case  2:
        case  4:
        case  6:
        case  8: if (sameProfessor(s+19,prof))
                    return false;
                 return true;
       default:  return true;
    }
}
bool Chromosome::testConflict02(int prof, int slot){
#if DEBUG_MODE == 1
    fprintf(stderr,">>>>> Entering testConflict02: Parameters: prof = %d slot = %d\n", prof, slot);
#endif // DEBUG_MODE

    int s = slot % schedsz;

    switch (s) {
        case 20:
        case 22:
        case 24:
        case 26:
        case 28: if (sameProfessor(s-20,prof) || sameProfessor(s-19,prof))
                    return false;
                 return true;
        case 21:
        case 23:
        case 25:
        case 27:
        case 29: if (sameProfessor(s-21,prof) || sameProfessor(s-20,prof))
                    return false;
                 return true;
        case  0:
        case  2:
        case  4:
        case  6:
        case  8: if (sameProfessor(s+20,prof) || sameProfessor(s+21,prof))
                    return false;
                 return true;
        case  1:
        case  3:
        case  5:
        case  7:
        case  9: if (sameProfessor(s+19,prof) || sameProfessor(s+20,prof))
                    return false;
                 return true;
        default: return true;
    }
}
bool Chromosome::testFourPeriods(int slot, int np, int * profs){
#if DEBUG_MODE == 1
    fprintf(stderr,">>>>> Entering testFourPeriods: Parameters: slot = %d np=%d profs = %p\n", slot, np, profs);
#endif // DEBUG_MODE

    int s = slot % schedsz;
    int i;
    for (i=0; i < np; i++) {
        if (testConflict03(s, profs[i]))
            return false;
    }

#if DEBUG_MODE == 1
    fprintf(stderr,"<<<<< Leaving testFourPeriods: Result: true\n");
#endif // DEBUG_MODE
    return true;
}
bool Chromosome::testProfessorPreferences(int slot, int np, int * profs){
#if DEBUG_MODE == 1
    fprintf(stderr,">>>>> Entering testProfessorPreferences: Parameters: slot = %d np=%d profs = %p\n", slot, np, profs);
#endif // DEBUG_MODE

    int s = slot % schedsz;
    int i,n;
    int * toavoid;
    for (i=0; i < np; i++) {
        toavoid = pd->getProfessorSlotsToAvoid(profs[i],n);
        if (toavoid[s] == DEFAULTVALUEFORAVOIDSCHEDULE)
            return false;
    }

#if DEBUG_MODE == 1
    fprintf(stderr,"<<<<< Leaving testProfessorPreferences: Result: true\n");
#endif // DEBUG_MODE
    return true;
}
bool Chromosome::testSubjectSize(int slot, int cod, int p){
#if DEBUG_MODE == 1
    fprintf(stderr,">>>>> Entering testSubjectSize: Parameters: slot = %d cod=%d p=%d\n", slot, cod,p);
#endif // DEBUG_MODE

    Part su;
    su.cod = cod;
    su.part = p;
    int aux1 = pd->getSlotSize(slot % schedsz);
    int aux2 = pd->getSubjectPartCred(su);
    if (pd->getSlotSize(slot % schedsz) != pd->getSubjectPartCred(su))
            return false;

#if DEBUG_MODE == 1
    fprintf(stderr,"<<<<< Leaving testSubjectSize: Result: true\n");
#endif // DEBUG_MODE
    return true;
}
bool Chromosome::testConflict03(int slot, int prof){
#if DEBUG_MODE == 1
    fprintf(stderr,">>>>> Entering testConflict03: Parameters: slot = %d prof = %d\n", slot, prof);
#endif // DEBUG_MODE

    int s = slot % schedsz;

    int s1 = s % 2;

    if (s1 == 1 && sameProfessor(s-1,prof))
        return false;

#if DEBUG_MODE == 1
    fprintf(stderr,"<<<<< Leaving testConflict03: Parameters: Result = true\n");
#endif // DEBUG_MODE
    return true;
}
bool Chromosome::testSchedule(int s, Part su){
#if DEBUG_MODE == 1
    fprintf(stderr,">>>>> Entering testSchedule: Parameters: s=%d cod=%d part=%d\n", s, su.cod, su.part);
#endif // DEBUG_MODE

    int np = pd->getSubjectPartNumberofProfs(su.cod, su.part);
    int * profs = pd->getSubjectPartProfs(su.cod, su.part);

    int i;
    for (i=0; i < np; i++) {
        if (!testConflict00(profs[i], s))
            return false;
        if (!testConflict01(profs[i], s))
            return false;
        if (!testConflict02(profs[i], s))
            return false;
    }

#if DEBUG_MODE == 1
    fprintf(stderr,"<<<<< Leaving testSchedule: Result: true\n");
#endif // DEBUG_MODE
    return true;
}
int Chromosome::selecionaSchedule(Part su){
#if DEBUG_MODE == 1
    fprintf(stderr,">>>>> Entering selecionaSchedule: Parameters: cod = %d part=%d\n", su.cod,su.part);
#endif // DEBUG_MODE

    int aux;

    int n;
    int * slots = getAvailableSlots(su, n);

    bool ok = false;

    while (n > 0 && !ok) {
            aux = randomValue(0,n-1);
            if (aux >= n){
                fprintf(stderr,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                fprintf(stderr,"ERROR: In random Generation!\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                exit(EXIT_FAILURE);
            }
            if (testSchedule(slots[aux],su))
                ok = true;
            else {
                removeFromVector(aux, n, slots);
                n--;
            }
    }


    int ret = slots[aux];

    delete [] slots;

    if (!ok) return -1;

#if DEBUG_MODE == 1
    fprintf(stderr,"<<<<< Leaving selecionaSchedule: Result: slot=%d\n",ret);
#endif // DEBUG_MODE
     return ret;
};
bool * Chromosome::testSwap(int * slots, int n1, Part su, int &n2){
#if DEBUG_MODE == 1
    fprintf(stderr,">>>>> Entering testSwap: Parameters: slots=%p n=%d cod=%d part = %d\n", slots, n', su1.cod, su1.part);
#endif // DEBUG_MODE

    n2=0;
    if (slots == NULL || n1 == 0)
        return NULL;

    bool * ok = new bool[n1];

    int i;
    for(i=0; i < n1; i++)
        if (testSchedule(slots[i],su)) {
            ok[i] = true;
            n2++;
        } else
            ok[i] = false;
#if DEBUG_MODE == 1
    fprintf(stderr,"<<<<< Leaving testSwap: Result: ok=%p n=%d\n",acc,n2);
#endif // DEBUG_MODE
    return ok;
};
bool * Chromosome::testSwapExclude(int * slots, int n1, Part su, int ex, int &n2){
#if DEBUG_MODE == 1
    fprintf(stderr,">>>>> Entering testSwapExclude: Parameters: slots=%p n=%d cod=%d part = %d exc=%d\n", slots, n', su1.cod, su1.part,ex);
#endif // DEBUG_MODE

    n2=0;
    if (slots == NULL || n1 == 0)
        return NULL;

    bool * ok = new bool[n1];

    int i;
    for(i=0; i < n1; i++)
        if (slots[i] != ex && testSchedule(slots[i],su)) {
            ok[i] = true;
            n2++;
        } else
            ok[i] = false;
#if DEBUG_MODE == 1
    fprintf(stderr,"<<<<< Leaving testSwap: Result: ok=%p n=%d\n",acc,n2);
#endif // DEBUG_MODE
    return ok;
};
int Chromosome::swapSchedule(Part &su1){
#if DEBUG_MODE == 1
    fprintf(stderr,">>>>> Entering swapSchedule: Parameters: cod=%d part = %d\n", su1.cod, su1.part);
#endif // DEBUG_MODE


    fprintf(stderr,">>>>> trocando %s/%d\n", pd->getSubjectTitle(su1.cod), su1.part);

    Part su2,su3;

    print();

    int i, nu,ns,na,nt,nc,nl;
    int * usedsl = getUsedSlots(su1, nu);

    for (int x=0; x < nu; x++)
        printf("usedsl[%d] = %d\n", x, usedsl[x]);

    bool * sourcok = testSwap(usedsl,nu,su1,ns);

    for (int x=0; x < nu; x++)
        printf("sourcok[%d] = %d\n", x, sourcok[x]);

    if (ns == 0) {
        delete [] usedsl;
        delete [] sourcok;
        return -1;
    }

    nc = ns;
    bool * copyok = new bool [nu];
    for (i=0;i<nu;i++)
        copyok[i]=sourcok[i];

    bool * targok,
         * linkok;

    int * availsl = getAvailableSlots(su1, na);

    for (int x=0; x < na; x++)
        printf("availsl[%d] = %d\n", x, availsl[x]);

    int ind1, ind2, ind3;

    int source, target, link;
    target = -1;

    while(ns > 0) {
        ind1 = getIndexNthOk(sourcok,nu,randomValue(0,ns-1));
        source = usedsl[ind1];
        su2.cod = chrom[source].codisc;
        su2.part = chrom[source].partdisc;
        fprintf(stderr,"1 >>>>> por %s/%d\n", pd->getSubjectTitle(su2.cod), su2.part);
        targok = testSwap(availsl,na,su2,nt);
        if (nt > 0) {
            ind2 = getIndexNthOk(targok,na,randomValue(0,nt-1));
            target = availsl[ind2];
            forceSubject(source,su1);
            unmarkSubjectAsUsed(su2);
            fprintf(stderr,"2 >>>>> Feito\n");
            break;
        }
        delete [] targok;
        sourcok[ind1] = false;
        ns--;
    }

    if (target==-1) {
        sourcok = copyok;
        ns = nc;
        while(ns > 0) {
            ind1 = getIndexNthOk(sourcok,nu,randomValue(0,ns-1));
            source = usedsl[ind1];
            su3.cod = chrom[source].codisc;
            su3.part = chrom[source].partdisc;
            fprintf(stderr,"3 >>>>> por %s/%d\n", pd->getSubjectTitle(su3.cod), su3.part);
            linkok = testSwapExclude(usedsl,nu,su3,source,nl);
            if (nl > 0) {
                ind3 = getIndexNthOk(linkok,nu,randomValue(0,nl-1));
                link = usedsl[ind3];
                su2.cod = chrom[link].codisc;
                su2.part = chrom[link].partdisc;
                fprintf(stderr,"4 >>>>> se %s/%d\n", pd->getSubjectTitle(su2.cod), su2.part);
                targok = testSwap(availsl,na,su2,nt);
                if (nt > 0) {
                    ind2 = getIndexNthOk(targok,na,randomValue(0,nt-1));
                    target = availsl[ind2];
                    forceSubject(source,su1);
                    unmarkSubjectAsUsed(su3);
                    forceSubject(link,su3);
                    unmarkSubjectAsUsed(su2);
                    fprintf(stderr,"5 >>>>> Feito\n");
                    break;
                }
                delete [] targok;
                linkok[ind3]=false;
                nl--;
            }
            delete [] linkok;
            sourcok[ind1] = false;
            ns--;
        }
    }

    delete [] targok;
    delete [] sourcok;
    delete [] usedsl;
    delete [] availsl;

    if (target != -1)  {
        su1.cod = su2.cod;
        su1.part = su2.part;
    }

#if DEBUG_MODE == 1
    fprintf(stderr,"<<<<< Leaving swapSchedule: Result: slot=%d\n",target);
#endif // DEBUG_MODE
    return target;
};
void Chromosome::printAvailableProfessor(int n){
    int i;
    Part su;

    fprintf(stderr,"Prof=%d:%s Nok=%d Ok=%d T=%d ns=%d \n", n,
            pd->getProfessorName(n), pcred[n].crednok, pcred[n].credok,
            pcred[n].crednok+pcred[n].credok, pcred[n].np);
    for(i=0; i < pcred[n].np; i++) {
        su = pd->getProfessorSubject(n,i);
        fprintf(stderr,"\tSub=%d:%s Part=%d Used=%d\n", su.cod,
                    pd->getSubjectTitle(su.cod),
                    su.part, pcred[n].used[i]);
    }
}
void Chromosome::printAvailableProfessorAll(){
    int i;
    int np = pd->getNumberOfProfessors();
    for(i=0; i < np; i++)
        printAvailableProfessor(i);
}
void Chromosome::printProfessorSchedule(int prof){

	if (chromsz < 1 || chrom == NULL) {
		printf("Chromosome::print >> Error: Empty Chromosome\n");
		return;
	};
	if (prof < 0 || prof >= pd->getNumberOfProfessors()) {
		printf("Chromosome::print >> Error: Invalid Professor %d\n", prof);
		return;
	};

 	char aux[DEFAULTNAMESIZE];
	char * paux;

    int i,j,k,p;

    bool ok;

    Part * sched = new Part[schedsz];
    int * room = new int[schedsz];

    fprintf(logfile,"Professor %d:%s Schedule\n",prof,pd->getProfessorName(prof));
    for (int i=0; i < schedsz; i++) {
        sched[i].cod = -1;
        room[i] = -1;
    }
    for (int i=0; i < chromsz; i++)
        if (chrom[i].tpused) {
            ok = false;
            for (j=0; j < chrom[i].nprofs; j++)
                if (chrom[i].profs[j] == prof)
                    ok = true;
            if (ok) {
                sched[i%schedsz].cod = chrom[i].codisc;
                sched[i%schedsz].part = chrom[i].partdisc;
                room[i%schedsz] = i / schedsz;
            }
        }
    for (int i=0; i < 3; i++) {
        for (int j=0; j < 2; j++) {
            for (int k=0; k < 5; k++) {
                p = i*10+k*2+j;
                if (sched[p].cod == -1)
                    strcpy(aux,"-----");
                else
                    sprintf(aux,"%s/%d", pd->getSubjectTitle(sched[p].cod), sched[p].part);
                fprintf(logfile,"|");
                printCentralizedString(logfile,DEFAULTSCHEDULESTRINGSIZE,aux);
            }
            fprintf(logfile,"\n");
            for (int k=0; k < 5; k++){
                p = i*10+k*2+j;
                fprintf(logfile,"|");
                if (pd->getSubjectPartNumberofProfs(sched[p].cod, sched[p].part) == 0) {
                     strcpy(aux,"-----");
                     printCentralizedString(logfile,DEFAULTSCHEDULESTRINGSIZE,aux);
                } else {
                    paux = pd->getProfessorsNickName(pd->getSubjectPartNumberofProfs(sched[p].cod, sched[p].part), 13,
                                                     pd->getSubjectPartProfs(sched[p].cod, sched[p].part));
                    printCentralizedString(logfile,DEFAULTSCHEDULESTRINGSIZE, paux);
                    delete  [] paux;
                }
            }
            fprintf(logfile,"|\n");
            for (int k=0; k < 5; k++) {
                p = i*10+k*2+j;
                if (room[p] == -1)
                    strcpy(aux,"-----");
                else
                    sprintf(aux,"Room %d", pd->getRoomNumber(room[p]));
                fprintf(logfile,"|");
                printCentralizedString(logfile,DEFAULTSCHEDULESTRINGSIZE,aux);
            }
            fprintf(logfile,"\n");
       }
        fprintf(logfile,"\n");
    }
    };

void Chromosome::printRoom(int n) {

	if (chromsz < 1 || chrom == NULL) {
		printf("Chromosome::print >> Error: Empty Chromosome\n");
		return;
	};

	if (n < 0 || n >= chromrooms) {
		printf("Chromosome::print >> Error: Invalid Chromosome Room\n");
		return;
	};

	char aux[DEFAULTNAMESIZE];
	char * paux;

    int i,j,k,p,r;

    r = schedsz * n;

    fprintf(logfile,"Room %d Schedule - Chromossome from %d->%d\n",n,r,r+schedsz-1);
    for (int i=0; i < 3; i++) {
        for (int j=0; j < 2; j++) {
            for (int k=0; k < 5; k++) {
                p = r+i*10+k*2+j;
                if (chrom[p].codisc == -1)
                    strcpy(aux,"-----");
                else
                    sprintf(aux,"%s/%d", pd->getSubjectTitle(chrom[p].codisc), chrom[p].partdisc);
                fprintf(logfile,"|");

                printCentralizedString(logfile,DEFAULTSCHEDULESTRINGSIZE,aux);
           }
            fprintf(logfile,"\n");
            for (int k=0; k < 5; k++){
                p = r+i*10+k*2+j;
                fprintf(logfile,"|");
                if (chrom[p].nprofs == 0) {
                     strcpy(aux,"-----");
                     printCentralizedString(logfile,DEFAULTSCHEDULESTRINGSIZE,aux);
                } else {
                    paux = pd->getProfessorsNickName(chrom[p].nprofs, 13, chrom[p].profs);
                    printCentralizedString(logfile,DEFAULTSCHEDULESTRINGSIZE, paux);
                    delete  [] paux;
                }
            }
            fprintf(logfile,"|\n");
       }
        fprintf(logfile,"\n");
    }
}
void Chromosome::print() {

    int i,r;

    fprintf(logfile,"Chromossome\n");

    for (int i=0; i < chromrooms; i++)
        printRoom(i);
//    printProfessorsSchedules();

//	printf("   %f\n", fitness);
}
void Chromosome::printProfessorsSchedules() {

    int i,r;

    fprintf(logfile,"Professors\n");

    for (int i=0; i < pd->getNumberOfProfessors(); i++)
        printProfessorSchedule(i);

//	printf("   %f\n", fitness);
}
void Chromosome::fprint(FILE * f) {

	if (chromsz < 1 || chrom == NULL) {
		fprintf(f,"Chromosome::fprint(FILE * f) >> Error: Empty Chromosome\n");
		return;
	};

	int type = NULL;
	char format[10];
	strcpy(format,getOutputFormat(type));
	strcat(format," ");

	for (int i=0; i < chromsz; i++)
		fprintf(f, format, chrom[i]);

	fprintf(f, "   %f\n", fitness);
}
bool Chromosome::crossover(Chromosome * parent1, Chromosome * parent2) {

	if (chrom == NULL || parent1 == NULL || parent2 == NULL)
		return false;

    Slot * chrom1 = parent1->getChromosome();
    Slot * chrom2 = parent2->getChromosome();

    int i,j,k;
    Part su;
    int sc;

    int nsubpart = pd->getNumberDiscPartsOfSubjects();

    for (i=0; i < chromrooms; i+=2) {
        for (j=0; j < schedsz; j++) {
            k = i*schedsz+j;
            if (chrom1[k].tpused) {
                copySlot(chrom[k],chrom1[k]);
                su.cod = chrom2[k].codisc;
                su.part = chrom2[k].partdisc;
                markSubjectAsUsed(su);
                nsubpart--;
            }
        }
    }
    for (i=1; i < chromrooms; i+=2) {
        for (j=0; j < schedsz; j++) {
            k = i*schedsz+j;
            if (chrom2[k].tpused) {
                su.cod = chrom2[k].codisc;
                su.part = chrom2[k].partdisc;
                if (testSubject(su) && testSchedule(k,su)) {
                    copySlot(chrom[k],chrom2[k]);
                    markSubjectAsUsed(su);
                    nsubpart--;
                }
            }
        }
    }
    bool ok = true;
    for (i=1; i < nsubpart; i++) {
        su =  selecionaSubject();
        sc = selecionaSchedule(su);
        if (sc == -1)
            sc = swapSchedule(su);
        if (sc == -1) {
            ok = false;
            break;
        };
        if(chrom[sc].tpused)
            printf("---------- Unexpected error -----------\n");
        chrom[sc].codisc = su.cod;
        chrom[sc].partdisc = su.part;
        chrom[sc].tpused = true;
        chrom[sc].nprofs = pd->getSubjectPartNumberofProfs(su.cod, su.part);
        for(j=0; j < chrom[sc].nprofs; j++)
            chrom[sc].profs[j] = pd->getSubjectPartProf(su.cod, su.part, j);
        markSubjectAsUsed(su);
    }

    if (!ok)
        return false;

    computeFitness();
    return true;

}
void Chromosome::repair() {

    int i,j;
    int np,nl,n = pd->getNumberSubjects();
    Check * subck = new Check[n];
    int nprt = pd->getNumberDiscPartsOfSubjects();
    int * subplus = new int [nprt];
    int * subless = new int [nprt];

    print();

    for(i=0; i < n; i++) {
        subck[i].n = pd->getSubjectNumberOfDiscParts(i);
        subck[i].ok = new bool[subck[i].n];
        for(j=0; j < subck[i].n; j++)
            subck[i].ok[j] = false;
    }
    for(i=0; i < nprt; i++)
        subplus[i]=subless[i] = -1;

    np=nl=0;
    for(i=0; i < chromsz; i++) {
        if (chrom[i].tpused) {
            if (subck[chrom[i].codisc].ok[chrom[i].partdisc]) {
                printf("disc %d p=%d ja existe\n",chrom[i].codisc,chrom[i].partdisc);
                subplus[np] = i;
                np++;
            } else
                subck[chrom[i].codisc].ok[chrom[i].partdisc] = true;
        }
    }


    for(i=0; i < n; i++) {
        for(j=0; j < subck[i].n; j++)
            if (!subck[i].ok[j]) {
                printf("disc %d p=%d nao existe\n",i,j);
                subless[i];
                nl++;
        }

    }
}
bool Chromosome::mutate(int pos) {

    Part su;
    su.cod = chrom[pos].codisc;
    su.part = chrom[pos].partdisc;

    int sc = swapSchedule(su);
}
void Chromosome::mutate(float mutationrate) {

    if (logfile != NULL) {
        fprintf(logfile,">>> void Chromosome::mutate(float mutationrate)\n");
        fprintf(logfile,">>> this=%p mutationrate=%f\n",this,mutationrate);
        fprintf(logfile,">>> ");
        fprintf(logfile,"fitness = %f\n", fitness);
   }

	if (chrom == NULL)
		return;

    int nmut = 0;

    for (int i=0; i < chromsz; i++)
		if (randomValue((float)0.0, (float)1.0) <= mutationrate) {
            if(mutate(i))
                nmut++;
		}

    if (nmut > 0)
        computeFitness();

    if (logfile != NULL) {
        fprintf(logfile,"<<< ");
        fprintf(logfile,"fitness = %f\n", fitness);
        fprintf(logfile,"<<< void Chromosome::mutate(float mutationrate)\n");
  }
  }
Chromosome * Chromosome::clone() {
    Chromosome * x = new Chromosome(pd);
    x->copy(this);
    return x;
}
void Chromosome::copy(Chromosome  c) {

	if (chromsz == 0)
		return;

	for (int i=0; i < chromsz; i++)
		chrom[i] =  c.chrom[i];

	fitness = c.fitness;

}
void Chromosome::copy(Chromosome * c) {

    if (logfile != NULL) {
        fprintf(logfile,">>> void Chromosome::copy(Chromosome * c)\n");
        fprintf(logfile,">>> this=%p c=%p\n",this,c);
    }

	if (chromsz == 0)
		return;

	for (int i=0; i < chromsz; i++)
		chrom[i] =  c->chrom[i];

	fitness = c->fitness;

};
bool Chromosome::sameElements(Chromosome * c) {

    if (logfile != NULL) {
        fprintf(logfile,">>> void Chromosome::sameElements(Chromosome * c)\n");
        fprintf(logfile,">>> this=%p c=%p\n",this,c);
    }

	if (chromsz == 0)
		return false;

	return true;

};

GAPopulation::GAPopulation(int psz, float cross, float mut, FILE * f1, FILE * f2, FILE * f3):
                    pop(NULL), sibling(NULL), mutation(NULL), aux(NULL), roulete(NULL), pair(NULL),
                    chromsz(0), popsz(psz), crossperc(cross), mutationrate(mut), infile(f1),
                    outfile(f2), logfile(f3), probdef(NULL){

	if (popsz < 1)
		return;

	srand((int)(time(NULL)));

	probdef = new GAProblemDefinition(infile,logfile);

	pop = new Chromosome*[popsz];

	chromsz = probdef->getTableSize();

    for (int i=0; i < popsz; i++) {
        pop[i] = new Chromosome(probdef,true);
    }


};
GAPopulation::~GAPopulation() {

	if (popsz < 0)
		return;

	if (pop != NULL) {} {
        for (int i=0; i < popsz; i++)
            delete pop[i];
        delete [] pop;
        pop = NULL;
	}
	if (sibling != NULL) {} {
        for (int i=0; i < popsz; i++)
            delete sibling[i];
        delete [] sibling;
        sibling = NULL;
	}
	if (mutation != NULL) {} {
        for (int i=0; i < popsz; i++)
            delete mutation[i];
        delete [] mutation;
        mutation = NULL;
	}
	if (aux != NULL) {} {
        for (int i=0; i < popsz; i++)
            delete aux[i];
        delete [] aux;
        aux = NULL;
	}
	if (roulete != NULL) {} {
        delete [] roulete;
        roulete = NULL;
	}
	if (pair != NULL) {} {
        for (int i=0; i < popsz; i++)
            delete pair[i];
        delete [] pair;
        pair = NULL;
	}
};
void GAPopulation::mutate() {

	if (popsz <= 0 || pop == NULL)
		return;

   if (mutation == NULL) {
        mutation = new Chromosome *[popsz];
	for (int i=0; i < popsz; i++)
            mutation[i] = new Chromosome(probdef);

    }

	for (int i=0; i < popsz; i++) {
		mutation[i]->copy(pop[i]);
		mutation[i]->mutate(mutationrate);
		mutation[i]->computeFitness();
	}
};
void GAPopulation::print() {

	if (popsz <= 0 || chromsz <= 0 || pop == NULL)
		return;

	for (int i=0; i < popsz; i++)
		pop[i]->print();
};
void GAPopulation::fprint(FILE * f) {

	if (popsz <= 0 || chromsz <= 0 || pop == NULL)
		return;

	fprintf(f, "%d %d %f %f\n", popsz, chromsz, crossperc, mutationrate);

	for (int i=0; i < popsz; i++)
		pop[i]->fprint(f);
};
Slot * GAPopulation::getChromosome(int c, int &sz) {

	sz = 0;
	if (c < 0 || c >= popsz)
		return NULL;

	sz = pop[c]->getSize();
	return pop[c]->getChromosome();

};
float GAPopulation::computeFitness() {

	if (popsz <= 0)
		return 0;

    float sum = 0;

	for (int i=0; i < popsz; i++)
		sum += pop[i]->computeFitness();

    return sum / popsz;
};
float GAPopulation::averageFitness() {

	if (popsz <= 0)
		return 0;

    float sum = 0;

	for (int i=0; i < popsz; i++)
		sum += pop[i]->getFitness();

    return sum / popsz;
};
void GAPopulation::generateRouleteTable() {

	if (popsz <= 0)
		return;

	quickSort<Chromosome *>(pop, 0, popsz-1, DESCENDINGORDER);

	float min = pop[popsz-1]->getFitness();
	float max = pop[0]->getFitness();

	if (max == min)
        return;

	float sz = max - min;

	float sum = 0;
	for (int i=0; i < popsz; i++)
		sum += (pop[i]->getFitness()- min)/sz;

    if (roulete == NULL)
        roulete = new float [popsz+1];

	roulete[0] = 0;

	for (int i=0; i < popsz; i++)
        roulete[i+1] = roulete[i] + (pop[i]->getFitness()- min)/sz/sum;
    roulete[popsz]=1.0;
};
void GAPopulation::pairIndividuals() {


    float p;
    int liminf,limsup;

    if (pair == NULL) {
        pair = new int *[popsz];
        for (int i = 0; i < popsz; i++)
            pair[i] = new int[2];
    }

    for (int i = 0; i < popsz; i++) {
        p = (float)rand() / RAND_MAX;
        liminf=0; limsup=popsz;
        if (!linearIntervalSearch(p, roulete, liminf, limsup, ASCENDINGORDER)) {
            printf("ERROR >> UNKNOWN ERROR\n");
            getchar();
        }
        pair[i][0]=liminf;
        pair[i][1]=pair[i][0];
        while (pair[i][1] == pair[i][0]) {
            p = (float)rand() / RAND_MAX;
            liminf=0; limsup=popsz;
            if (!linearIntervalSearch(p, roulete, liminf, limsup, ASCENDINGORDER)){
                printf("ERROR >> UNKNOWN ERROR\n");
                getchar();
            }
            pair[i][1] = liminf;
        }
    }



};
void GAPopulation::crossover() {

    if (sibling == NULL) {
        sibling = new Chromosome *[popsz];
        for (int i=0; i < popsz; i++)
            sibling[i] = new Chromosome(probdef);

    }

	for (int i=0; i < popsz; i++) {
		if (!sibling[i]->crossover(pop[pair[i][0]],pop[pair[i][1]]))
            if (!sibling[i]->crossover(pop[pair[i][1]],pop[pair[i][0]]))
                sibling[i]->fillChromossome();
		sibling[i]->computeFitness();
	}
};

void GAPopulation::selectBest() {

	if (popsz <= 0 || sibling == NULL)
		return;

    if (aux == NULL) {
        aux = new Chromosome *[popsz];
        for (int i = 0; i < popsz; i++)
            aux[i] = new Chromosome();
    }

	quickSort<Chromosome *>(sibling, 0, popsz-1, DESCENDINGORDER);
	quickSort<Chromosome *>(mutation, 0, popsz-1, DESCENDINGORDER);

	int n = 0;
	int i = 0,j = 0, k=0;
	while (n < popsz) {
       if (pop[i]->operator>=(sibling[j]) && pop[i]->operator>=(mutation[k])) {
            aux[n++]->copy(pop[i]);
            if (ONLYONECOPY  &&  pop[i]->operator==(sibling[j]) && pop[i]->sameElements(sibling[j]))
                j++;
            if (ONLYONECOPY  && pop[i]->operator==(mutation[k]) && pop[i]->sameElements(mutation[k]))
                k++;
            i++;
        } else if (sibling[j]->operator>=(mutation[k])) {
            aux[n++]->copy(sibling[j]);
            if (ONLYONECOPY  && sibling[j]->operator==(mutation[k]) && sibling[j]->sameElements(mutation[k]))
                k++;
            j++;
        } else
            aux[n++]->copy(mutation[k++]);
	}

	for (i=0; i < popsz; i++)
        pop[i]->copy(aux[i]);

};
void GAPopulation::selectSiblings() {

	if (popsz <= 0 || sibling == NULL)
		return;

    if (aux == NULL) {
        aux = new Chromosome *[popsz];
        for (int i = 0; i < popsz; i++)
            aux[i] = new Chromosome();
    }

	quickSort<Chromosome *>(sibling, 0, popsz-1, DESCENDINGORDER);
	quickSort<Chromosome *>(mutation, 0, popsz-1, DESCENDINGORDER);

	int n = 0;
	int i = 0, j = 0, k=0;
	while (n < popsz) {
        if (sibling[j]->operator>=(mutation[k])) {
            aux[n++]->copy(sibling[j]);
            if (ONLYONECOPY  && sibling[j]->operator==(mutation[k]) && sibling[j]->sameElements(mutation[k]))
                k++;
            j++;
        } else {
            aux[n++]->copy(mutation[k++]);
        };
	}

	for (i=0; i < popsz; i++)
        pop[i]->copy(aux[i]);

};

GeneticAlgorithm::GeneticAlgorithm(char * f1, char * f2, char * f3): genpop(NULL), infile(NULL), outfile(NULL), logfile(NULL){

    if (f1) {
        infile = fopen(f1,"r");
        if (!infile) {
            fprintf(stderr,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            fprintf(stderr,"ERROR: Could not open input File to read!\nInputfile = %s\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n",f1);
            getchar();
            exit(EXIT_FAILURE);
        }
    }
    if (f2) {
        outfile = fopen(f2,"w");
        if (!outfile) {
            fprintf(stderr,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            fprintf(stderr,"ERROR: Could not open output File to write!\nOutputfile = %s\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n",f2);
            getchar();
            exit(EXIT_FAILURE);
        }
    }
    if (f3) {
        logfile = fopen(f3,"w");
        if (!logfile) {
            fprintf(stderr,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            fprintf(stderr,"ERROR: Could not open log File to write!\nLogfile = %s\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n",f3);
            getchar();
            exit(EXIT_FAILURE);
        }
    } else
        logfile = stderr;
}
GeneticAlgorithm::~GeneticAlgorithm() {

	if (genpop == NULL)
		return;

    delete genpop;

    fclose(logfile);
    fclose(outfile);
    fclose(infile);
}

bool GeneticAlgorithm::initializePopulation(int psz, float cross, float mut) {

	genpop = new GAPopulation(psz, cross, mut, infile, outfile, logfile);
	return true;
};
void GeneticAlgorithm::save(char * fname) {

	if (!initialized())
		return;

	FILE * f = NULL;
	char * fullname = NULL;
	char * filename = NULL;
	time_t timer;
	struct tm * date;

	if (fname == NULL) {
		filename = new char[100];
		timer = time(NULL);
		date = localtime(&timer);
	} else
		filename = fname;

	f = fopen(fullname, "w");

	if (f == NULL)
		return;


	genpop->fprint(f);

	fclose(f);

};
void GeneticAlgorithm::print() {

	if (!initialized())
		return;

	genpop->print();
};
bool GeneticAlgorithm::initialized() {

	if (genpop != NULL)
        return true;

	return false;
};


float GeneticAlgorithm::computeFitness() {

	if (!initialized())
		return 0;

	return genpop->computeFitness();

};
float GeneticAlgorithm::nextGeneration() {

	if (!initialized())
		return 0;

    genpop->computeFitness();
	genpop->generateRouleteTable();
    genpop->pairIndividuals();
    genpop->crossover();
    genpop->mutate();
    switch(DEFAULTCROSSOVERSELECTION) {
        case 1: genpop->selectBest();
                break;
        case 0:
        default: genpop->selectSiblings();
    }
    return genpop->averageFitness();

};

bool GeneticAlgorithm::read(char * fname) {

	if (fname == NULL)
		return false;

	if (initialized()) {
		fprintf(stderr, "ERROR >>> Genetic Algorithm already initialized!\n");
		return false;
	};

	FILE * f = NULL;
	char * fullname = NULL;

	f = fopen(fullname, "r");

	if (f == NULL)
		return false;

	fclose(f);

	return true;
};

float GeneticAlgorithm::runForNGenerations(int ng) {

    maxgen = ng;
    float oldfit=0,
          avgfit=0;
    int n = 0;
    while (n < maxgen) {
        avgfit = nextGeneration();
        if (avgfit > oldfit)
            oldfit = avgfit;
        printf("----- generations = %d --  avg fitness = %f ----\n", n,  avgfit);
        if (logfile)
            fprintf(logfile,"%d %f\n", n,  avgfit);

        n++;
    }

    return (getBestChromosome())->getFitness();

};
float GeneticAlgorithm::runTillNoImprovement(int nnip, int ng) {

    maxgen = ng;
    maxgennoimp = nnip;

    float oldfit=0,
          avgfit=0;
    int n=0,
        ni=0;
    while (n < maxgen && ni < maxgennoimp) {
        avgfit = nextGeneration();
        if (avgfit > oldfit) {
            oldfit = avgfit;
            ni = 0;
        } else
            ni++;
        printf("----- generations = %d -- last improvement = %d -- avg fitness = %f ----\n", n, n - ni, avgfit);
        if (logfile)
            fprintf(logfile,"%d %f\n", n,  avgfit);
        n++;
    }

    return (getBestChromosome())->getFitness();

};


