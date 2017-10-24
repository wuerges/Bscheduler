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

#if !defined(_BGADEFAULTS_H_)
#define _BGADEFAULTS_H_

#include "BCommandLine.h"
#include "BFunctions.h"
#include "BFile.h"
#include "BSort.h"
#include "BList.h"
#include <time.h>
#include <stdio.h>

#define MAXVALUEDIFFERENCECONSIDEREDEQUAL          0.001
#define CLEANGROUPSATEACHGENERATION                 true
#define ONLYONECOPY                                 true
#define DEFAULTPOPULATIONSIZE                        100
#define DEFAULTCHROMOSOMETYPE                       bool
#define DEFAULTCHROMOSOMESIZE                         50
#define DEFAULTMAXOFGENERATIONS		               10000
#define DEFAULTMAXOFGENERATIONSWITHOUTIMPROVEMENT    100
#define DEFAULTMINCROSSOVERPERCENTAGE		           0.3
#define DEFAULTMUTATIONPERCENTAGE	  	               0.1
#define DEFAULTINTLIMITLOWER                     INT_MIN
#define DEFAULTINTLIMITUPPER                     INT_MAX
#define DEFAULTFLOATLIMITLOWER                         0.0
#define DEFAULTFLOATLIMITUPPER                         1.0
#define DEFAULTBOOLEANLIMITLOWER                   false
#define DEFAULTBOOLEANLIMITUPPER                    true
#define DEFAULTCHARLIMITLOWER                   CHAR_MIN
#define DEFAULTCHARLIMITUPPER                   CHAR_MAX
#define DEFAULTFILENAME                       "Schedule"
#define DEFAULTEXTENSIONNAME                       "html"
#define DEFAULTEXECUTIONLOGFILE       "ExecutionLog.log"
#define DEFAULTOUTPUTFILE                 "Schedule.html"
#define DEFAULTNAMESIZE                              128
#define DEFAULTNUMBERSIZE                             24
#define DEFAULTMAXNUMBEROFCLASSESBYPROFESSOR          12
#define DEFAULTNUMBEROFSEMESTERS                      10
#define DEFAULMAXNUMBERPROFESSORSBYSUBJECT             3
#define DEFAULMAXNUMBEROFCLASSESBYSUBJECT              3
#define DEFAULMAXNUMBEROFROOMS                        10
#define DEFAULMAXNUMBEROFSLOTSBYSUBJECT               20
#define DEFAULTCROSSOVERSELECTION                      0
#define DEFAULTVALUEFORFORBIDSCHEDULE                  0
#define DEFAULTVALUEFORFORBIDSCHEDULEMARK             'X'
#define DEFAULTVALUEFORAVOIDSCHEDULE                   1
#define DEFAULTVALUEFORAVOIDSCHEDULEMARK              '#'
#define DEFAULTVALUEFORNEUTRALSCHEDULE                 2
#define DEFAULTVALUEFORNEUTRALSCHEDULEMARK            '*'
#define DEFAULTVALUEFORPREFEREDSCHEDULE                3
#define DEFAULTVALUEFORPREFEREDSCHEDULEMARK           '.'
#define DEFAULTVALUEFOROCCUPIEDSCHEDULE                4
#define DEFAULTVALUEFOROCCUPIEDSCHEDULEMARK           'o'
#define DEFAULTVALUEFORERRORSCHEDULE                   5
#define DEFAULTVALUEFORERRORSCHEDULEMARK              'e'
#define DEFAULTMAXNUMBEROFHOURSBYSLOT                  5
#define DEFAULTSCHEDULESTRINGSIZE                      13

#endif
