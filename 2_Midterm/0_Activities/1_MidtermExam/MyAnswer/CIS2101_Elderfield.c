/***************************************************************************
 * Name: Zeus Elderfield        //Lastname, Firstname [CIS 2101 group #]   *
 * Date: March 11, 2024                                                    *
 *                                                                         *
 *                                                                         *
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUMPROGRAMS 4
#define YEARLEVELS 4
#define MAXSTUDS 100

//Data Structure Definition
typedef struct{
    char fName[64];
    char mi;
    char lName[32];
}studName;

typedef unsigned char personalInfo;
/*Given 8 bits: 0000 0000
 
 Bits
 8    = Status:            0 - Inactive, 1 - Active
 7    = Nationality:       0 - Filipino, 1 - Foreigner
 6    = Enrollment Status: 0 - Regular, 1 - Irregular
 5    = Gender:            0 - Male, 1 - Female
 3-4  = Year Level:        00 - 1st, 01 - 2nd, 10 - 3rd, 11 - 4th
 1-2  = Program:           00 - CS, 01 - IT, 10 - IS, 11 - MATH
 
 For example:
 1001 1001 would represent an Active Regular 3rd Year Filipino Female IT Student
*/

typedef struct{
    char idNum[9];
    studName name;
    personalInfo info;
}student;

typedef struct{
    student studs[MAXSTUDS];
    int numStuds;
}arrListStud;



typedef struct studNode{
    student stud;
    struct studNode* next;
}studNode, *studLL;

typedef studLL studDict[YEARLEVELS];

typedef struct{
    studDict programStuds;
    int studCtr;               /* refers to the total number of students in the PROGRAM. */
}dcismNode;

typedef dcismNode dcismDict[NUMPROGRAMS];

typedef struct{
    char studID[9];
    studName sName;
}studRec;

typedef struct{
    studRec studs[MAXSTUDS];
    int count;
}sNode, *studSet;               /* array representation of a Set of studRecs */

//Function Prototypes
//-----Problem #1 Prototypes-----
arrListStud populateStudentList(void); // Reads the file containing student records and returns student 
                                       //   records to the calling function
                                       // PARTIAL CODE is provided

void generateStudentFile(void);   //Creates a file of student records
char* getProgram(personalInfo I);  //Returns the string equivalent of the program (BSCS, BSIT, BSIS, BSMATH)
                                   //  of the provided personalInfo. 
                                   
int yearLevelHash(personalInfo I);     //Returns the year level 
                                   
void displayArrListStud(arrListStud A); //Displays ID, Complete name, Program (Course) and year

//------Problem #2 Prototypes
void initDCISMDict(dcismDict D);        //Initializes the given dcismDict to be empty
void convertToDCISMDict(dcismDict D, arrListStud SL); //Inserts the LIST of students in arrListStud
                                                      //  to their proper place in the dcismDict
void displayStudLL(studLL SL) ;        // Displays the contents of a given studLL.
                                       // PARTIAL CODE is provided 

void displayDCISMDict(dcismDict D);     //Displays all the students in the dcismDict by program and year level.
                                        // PARTIAL CODE is provided;  Calls displayStudLL().

//------Problem #3 Prototypes

studSet* removeInactiveStudents(dcismDict D);   //Given dcismDict D, the function deletes student records
                                               //  that have the status "inactive" and place in an array of studSets
                                               // Deleted students will be stored in proper array of studSets
															  //   based on their program (course).
															  // Array of studSets will be returned to the calling function 
															  		    
void displayStudSets(studSet* S);             // Displays the ID, Firstname and Lastname of inactive students 
                                              //    for each program.
																			                         
/************************************************************************************
 * READ ME FIRST before ANSWERING                                                   *
 *   0)  CHANGE the name of the file to:  CIS2101_YourlastNameXX.c                  *
                                     XX is the first 2 letters of your firstname    *
 *   1)  To facilitate the checking of the machine problem, follow the instructions *
 *       in each PROBLEM #.                                                         *
 *   2)  To accomplish the task for each PROBLEM, a series of function calls may be *
 *       necessary.                                                                 *  
 *   3)  Write you answer BELOW THE COMMENTS. DO NOT DELETE COMMENTS                *
 *   4)  Uncomment or copy the print statement in each PROBLEM#  if the task is     *
 *       completed.                                                                 *
 ***********************************************************************************/                         
int main(void)
{
   /*-------------------------------------------------------------------------
    * 	Problem #1  :: 1) Populate the list by calling populateStudentList  *
    *                   2) Calls displayArrListStud()                        *
    *------------------------------------------------------------------------*/	
   printf("\n\n\nProblem #1:: ");
   printf("\n------------\n");
    arrListStud A = populateStudentList();
    displayArrListStud(A);
   
    /*-------------------------------------------------------------------------
    * 	Problem #2  :: 1) Call initDCISMDict()                               *
    *                   2) Call convertToDCISMDict()                          *
    *                   3) Call displayDCISMDict()                            *
	 *-------------------------------------------------------------------------*/	
    dcismDict D;    
   printf("\n\n\nProblem #2:: ");
   printf("\n------------\n");
   
   initDCISMDict(D);
   convertToDCISMDict(D, A);
   displayDCISMDict(D);
    
  
    /*-------------------------------------------------------------------------
    * 	Problem #3  :: 1) Call removeInactiveStudents() passing dcismDict in *
    *                          problem #2                                     *
    *                   2) Call displayDCISMDict(D);                          *
    *                   3) Call displayStudSets(inactive);                    *
	 *-------------------------------------------------------------------------*/	  
    printf("\n\n\nProblem #3:: ");
    printf("\n------------\n");
	studSet* S = removeInactiveStudents(D);
	displayDCISMDict(D);
	displayStudSets(S); 
    
    return 0;
}                                  
                                       

/*****************************************************************************************
 *  Functions for Problem # 1                                                            *
 *****************************************************************************************/      
 //-----------------------------------------------------------------------------------------
// populateStudentList(). The function will read a file containing student records and   
// returns the student records to the calling function in the form of an arrListStud..
//
// PARTIAL CODE is provide.
//-----------------------------------------------------------------------------------------
arrListStud populateStudentList(void)
{
    FILE* fp;
    student* studs;
    int dataCount;
   
    arrListStud retVal = {.numStuds = 0};
    
    if((fp = fopen("students.bin", "rb"))== NULL){
        puts("Unsuccessful in opening students.txt");
    }else{
        fseek(fp, 0, 2);
        dataCount = (int) ftell(fp) / sizeof(student);
        studs = (student*) malloc (sizeof(student) * dataCount);
        if(studs != NULL){
            fseek(fp, 0, 0);
            fread(studs, sizeof(student), dataCount, fp);
        }
        
		//Put your CODE here
        int x;
        for (x = 0; x < MAXSTUDS && x < dataCount; ++x) {
            retVal.studs[x] = studs[x];
            retVal.numStuds++;
        }
        fclose (fp);
         
    }

    return retVal;
}

//-----------------------------------------------------------------------------------------
// getProgram(). Return the string equivalent of the program of the provided personalInfo.
//-----------------------------------------------------------------------------------------
char* getProgram(personalInfo I)
{
  //Write your code here   
    char tempProgram[5];

    int p = I & 3;

    if(p == 0) { // 00
        strcpy(tempProgram, "CS");
    }
    else if(p == 1) { // 01
        strcpy(tempProgram, "IT");
    }
    else if(p == 2) {
        strcpy(tempProgram, "IS");
    }
    else {
        strcpy(tempProgram, "MATH");
    }

    char *retVal = (char*)malloc(sizeof(char) * (strlen(tempProgram) + 1));

    if(retVal != NULL) {
        strcpy(retVal, tempProgram);
    }

    return retVal;
}

//-----------------------------------------------------------------------------------------
// programHash(). Returns the integer equivalent of the bits that represent a student's program.
//-----------------------------------------------------------------------------------------
int yearLevelHash(personalInfo I)
{
     //Write your code here
    return (I & 12) >> 2;
}



//---------------------------------------------------------------------------------------------
// displayArrListStud(). Displays the ID, Firstname, Lastname, Program (course) and year level.
//  Calls getProgram() and yearLevelHash() to determine the Program and year level.
//
//  PARTIAL CODE is provided
//-----------------------------------------------------------------------------------------
void displayArrListStud(arrListStud A)
{
   int x;
   
   printf("%-10s", "Id Number");
   printf("%-10s", "fName");
   printf("%-10s", "lName");
   printf("%-10s", "Program");      //Program and Year should be included in the display, though
   printf("%-10s", "Year");         //   it is not included in the sample display.
     
   //Write your code here.  
   char *temp ;
    for(x = 0; x < A.numStuds; x++) {
    	printf("\n%-10s", A.studs[x].idNum);
	   printf("%-10s", A.studs[x].name.fName);
	   printf("%-10s", A.studs[x].name.lName);
	   
	   temp = getProgram(A.studs[x].info);
	   printf("%-10s", temp);      //Program and Year should be included in the display, though
	   free(temp);
	   
	   printf("%-10d", yearLevelHash(A.studs[x].info) + 1); 
	}
}


/*****************************************************************************************
 *  Functions for Problem # 2                                                            *
 *****************************************************************************************/      
//-----------------------------------------------------------------------------------------
// programHash(). Returns the integer equivalent of the bits that represent a student's program.
//-----------------------------------------------------------------------------------------
int programHash(personalInfo I)
{
     //Write your code
     return (I & 3);
}


//-----------------------------------------------------------------------------------------
// insertStudLL(). Inserts into the sorted studSet based on the student's ID number.
//  All elements in the studLL should be unique. The function will return 1 if the insert was successful and 0 if not.
//-----------------------------------------------------------------------------------------

int insertStudLL(studLL* SL, student S)
{
     //Write your code
     studLL *trav;
     
     
     for(trav = SL; *trav != NULL && strcmp((*trav)->stud.idNum, S.idNum) < 0; trav = &(*trav)->next) {}
	 
	 if(*trav == NULL || strcmp((*trav)->stud.idNum, S.idNum) != 0) {
	 	studLL temp = (studLL) malloc(sizeof(struct studNode));
	 	if(temp != NULL) {
	 		temp->stud = S;
	 		temp->next = *trav;
	 		*trav = temp;
		 }
		 else {
		 	return 0;
		 }
	 }
	 
	 return (*trav == NULL || strcmp((*trav)->stud.idNum, S.idNum) != 0) ? 1 : 0;
}


//-----------------------------------------------------------------------------------------
// displayStudLL(). The function will display the contents of a given studLL.
//-----------------------------------------------------------------------------------------
void displayStudLL(studLL SL)
{
    if(SL != NULL){
      //  printf("\nYear %d\n\n",    );        //Complete the code and Uncomment
        printf("\n%-10s", "Id Number");
        printf("%-10s", "fName");
        printf("%-10s", "lName");
        printf("%-10s", "Program");
        printf("%-10s", "Year");
        printf("%-10s", "Gender");
        printf("%-15s", "Enrollment");
        printf("%-15s", "Nationality");
        printf("%-10s\n", "Status");
        
        //Write your code here 
        studLL curr;
        
        for(curr = SL; curr != NULL; curr = curr->next) {
        	printf("%-10s", curr->stud.idNum);
	        printf("%-10s", curr->stud.name.fName);
	        printf("%-10s", curr->stud.name.lName);
	        
	        char *temp = getProgram(curr->stud.info);
	        printf("%-10s", temp);
	        free(temp);
	        
	        printf("%-10d", yearLevelHash(curr->stud.info) + 1);
	        
	        int g = (curr->stud.info & 16) >> 4;
	        int e = (curr->stud.info & 32) >> 5;
	        int n = (curr->stud.info & 64) >> 6;
	        int s = (curr->stud.info & 128) >> 7;
	        
	        printf("%-10s", (g == 0) ? "Male" : "Female" );
	        printf("%-15s", (e == 0) ? "Regular" : "Irregular");
	        printf("%-15s", (n == 0) ? "Filipino" : "Foreigner");
	        printf("%-10s\n", (s == 0) ? "Inactive" : "Active");
		}
    }
}

//-----------------------------------------------------------------------------------------
// initDCISMDict(). The function will initialize the given  dcismDict to be empty
//-----------------------------------------------------------------------------------------
void initDCISMDict(dcismDict D)
{
     //Write your code here
     int i, j;
    for(i = 0; i < NUMPROGRAMS; i++) {
        D[i].studCtr = 0;
        for(j = 0; j < YEARLEVELS; j++) {
            D[i].programStuds[j] = NULL;
            D[i].studCtr = 0;
        }
    }
}


//-----------------------------------------------------------------------------------------
// convertToDCISMDict(). The function will go through list of students and insert them to their proper place in the dcismDict.
//-----------------------------------------------------------------------------------------
void convertToDCISMDict(dcismDict D, arrListStud SL)
{
     //Write your code here
     int i;
     
     for(i = 0; i < SL.numStuds; i++) {
     	int p = programHash(SL.studs[i].info);
     	int y = yearLevelHash(SL.studs[i].info);
     	
     	if(insertStudLL(&D[p].programStuds[y], SL.studs[i]) == 1) {
     		D[p].studCtr++;
		}
	 }
}



//-----------------------------------------------------------------------------------------
// displayDCISMDict(). The function will display all the students in the dcismDict by program and year level.
//-----------------------------------------------------------------------------------------
void displayDCISMDict(dcismDict D)
{
    int i, j;
    for(i = 0; i < NUMPROGRAMS; i++){
        for(j = 0; j < YEARLEVELS; j++){
        	printf("\n---------------------------------------------------------------------------------------------------------------\n%s %d Students", getProgram(i), j + 1);
             displayStudLL(D[i].programStuds[j]);
        }
    }
}

/*****************************************************************************************
 *  Functions for Problem # 3                                                            *
 *****************************************************************************************/      
//-----------------------------------------------------------------------------------------
// initStudSet(). The functions initialize an empty array of studSets that can accommodate the total number of programs.
//-----------------------------------------------------------------------------------------
studSet* initStudSet(void)
{
     //Write your code here
     studSet *ret = (studSet*)malloc(sizeof(studSet) * NUMPROGRAMS);
     
     if(ret != NULL) {
     	int i;
     	
     	for(i = 0; i < NUMPROGRAMS; i++) {
     		ret[i] = (studSet)malloc(sizeof(sNode));
     		ret[i]->count = 0;
		 }
	 }
	 
	 return ret;
}


//-----------------------------------------------------------------------------------------
// insertStudSet(). The function will insert the studRec into the studSet. Student will be inserted at the end of the set.
//-----------------------------------------------------------------------------------------
void insertStudSet(studSet S, studRec sRecord)
{
    //Write your code here
    if(S->count < MAXSTUDS) {
    	int i;
    	
    	for(i = 0; i < S->count && strcmp(S->studs[i].studID, sRecord.studID) != 0; i++) {}
    	
    	if(i == S->count) {
    		S->studs[S->count++] = sRecord;
		}
	}
}


//-----------------------------------------------------------------------------------------
// removeInactiveStudents(). The function will delete all student records that have the status "inactive".
// Deleted records will be stored in an array of studSets, such that each deleted student will be stored
// in its proper index in the array of studSets based on their program. Return the array of studSets to the calling function.
//-----------------------------------------------------------------------------------------
studSet* removeInactiveStudents(dcismDict D)
{
     //Write your code here
     studSet *S = initStudSet();
     
     int i, j;
     for(i = 0; i < NUMPROGRAMS; i++) {
     	for(j = 0; j < YEARLEVELS; j++) {
     		studLL *trav = &D[i].programStuds[j];
     		
     		while(*trav != NULL) {
     			int status = ((*trav)->stud.info & 128) >> 7;
     			if(status == 0) {
     				studRec temp;
     				temp.sName = (*trav)->stud.name;
     				strcpy(temp.studID, (*trav)->stud.idNum);
     				
     				insertStudSet(S[i], temp);
     				
     				studLL t = *trav;
     				*trav = t->next;
     				free(t);
				}
				else {
					trav = &(*trav)->next;
				}
			 }
		}
	 }
	 
	 return S;
}

 
 
/**********************************************************************************
 *  Displays the ID, Firstname and Lastname of inactive students for each program. *
 **********************************************************************************/
void displayStudSets(studSet* S)
{
     //Write your code 
     int i, j;
     
     for(i = 0; i < NUMPROGRAMS; i++) {
     	printf("\n\n%s\n", getProgram(i));
     	for(j = 0; j < S[i]->count; j++) {
     		printf("%10s", S[i]->studs[j].studID);
     		printf("%10s", S[i]->studs[j].sName.fName);
     		printf("%10s\n", S[i]->studs[j].sName.lName);
		 }
	 }
}


