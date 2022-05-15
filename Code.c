#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TRUE 1
				
typedef struct NODE{
	char Name[100];
	int pCount;
	int meetCount;			//the linked list to save data of each person in a csv file row
	int minCount;
	struct NODE *next;
      	}rowData;

rowData *sortpCount(rowData *head);		//prototype of the function to sort participant count list
rowData *sortmeetCount(rowData *head);		//prototype of the function to sort meetings attended count list
rowData *sortminCount(rowData *head);		//prototype of the function to sort total minutes list

void printChartpCount_S(rowData *poin);         //prototype of the function to print SCALED participant count chart
void printChartmeetCount_S(rowData *poin);	//prototype of the function to print SCALED meeting count chart
void printChartminCount_S(rowData *poin);	//prototype of the function to print SCALED total minutes list
void printChartmeetCount_N_S(rowData *poin);	//prototype of the function to print NON SCALED meeting count chart
void printChartpCount_N_S(rowData *poin);	//prototype of the function to print NON SCALED participant count chart
void printChartminCount_N_S(rowData *poin);	//prototype of the function to print NON SCALED total minutes list

int nameLen(rowData *poin);			//prototype of the function to find the length of the lengthiest name in the list
int numofdig(int num);				//prototype of the function to find the number of digits in a number
int totalpCount(rowData *poin);			//prototype of the function to find the total number of particiapnts in every row in every file
int totalminCount(rowData *poin);		//prototype of the function to find the total minutes in every row in every file

rowData *head , *newnode, *temp, *comp;

int var=10;					//global variable to find the value after argument -l and default value is set to zero
int max=0;	  				//global variable assigned to take up the length of the lengthiest name
int totmeet=0;					//global variable to find number of nodes created to read each data or total number of meetings
int tot;					//global variable to find the total of particpants or minutes

int main(int argc, char *argv[]){
	char *files[100];			//local variable to store file name
	int count=0;				//local variable to count number of files initially set to zero

	int x1=0,x2=0,x3=0;			//local variable to check whether which argument is executed all three variables are initailly ste to zero
	int lineCount=1;			//local variable to find the number of nodes in the linked list initially set to one
      	head = NULL;				//rowdata type pointer variable initially set to NULL
        if(argc==1){
        	printf("No input files were given\nusage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n",argv[0]);
                return -1;
        }

	for (int j=1;j<=argc-1;j++){ 			//loop to iterate for number of arguments entered execution file excluded
		for(int k=1;k<=argc-1;k++){ 		//in -m , -p , -t  if two arguments are  entered at the same time then following error message is executed
			if(((strcmp(argv[j],"-m"))==0 && (strcmp(argv[k],"-t"))==0) || ((strcmp(argv[j],"-m"))==0 && (strcmp(argv[k],"-p"))==0) || ((strcmp(argv[j],"-p"))==0 && (strcmp(argv[k],"-t"))==0)){
    				printf("Cannot plot multiple parameters in same graph.\nusage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n",argv[0]);
				return -1;
			}
		}

		if((strcmp(argv[j],"-l"))==0){ 		//if an argument of -l is entered the folllowing block is executed
			if(argc<=j+1){ 			//if -l is entered at the end of an argument then print the following error message
    				printf("Not enough options for [-l]\nusage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n",argv[0]);
    				return -1;
			}

			for(int k=0 ; k<strlen(argv[j+1]);k++){ 	//to check whether the argument entered after -l is a numeric value
    				if((argv[j+1][0]=='-')&& k==0){ 	//if the  argument after -l contains a - as the first element then the next iteration is called
        				continue;
   		 		}		
    				if(!isdigit(argv[j+1][k])){ 	//if the rest does not contain a digit then the following error message is printed
					printf("Invalid option for [-l]\nusage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n",argv[0]);
        				return -1;
    				}
	
			}	
                        if(atoi(argv[j+1])<0){     //if the condition after -l is - then it is considered as a negative number so following error message is executed

                                printf("Invalid option(negative) for [-l]\nusage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n",argv[0]);
                                return -1;

                        }else if(atoi(argv[j+1])==0){
                                return -1;
                        }
		
			var=atoi(argv[j+1]); 	//else var variable is assigned with the value after -l by converting it to an integer
			continue;

		}else if((strcmp(argv[j],"-m"))==0){ 
 			continue;

		}else if((strcmp(argv[j],"-p"))==0){
			continue;

                }else if((strcmp(argv[j],"-t"))==0){
                        continue;

		}else if(strcmp(argv[j],"--scaled")==0){
    			continue;

		}else if(argv[j][0]=='-'){ 	//if an invalid argument or flag is give then the following error message is printed			
			printf("Invalid option [-%s]\nusage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n",argv[j],argv[0]);
    			return -1;

		}else{ 		//all other arguments are considered as files

    			if(strcmp(argv[j-1],"-l")==0){ 	//this is given inorder to avoid considering the number entered after -l to be considered as a file 
        			continue;
    			}
			files[count]=(char*)malloc(sizeof(strlen(argv[j]))); 	//dynamic memory is allocated to store the file names
                        strcpy(files[count],argv[j]); 				//names of the files are copied
			count++;
	
		}
		int z=0;

		while(z!=count){		//to check each file name if its fall into the conditions
                	char file_in[100];
                	strcpy(file_in,files[z]);	
			char *ret;
			char ch[4] = ".csv";
			ret = strstr(file_in,ch);	//checking whether the file contains .csv in  its name

                        if(ret==NULL){
                                printf("Only .csv files should be given as inputs.\n");
                                return-1;
                        }

                        if(strncmp(ret,ch,4)!=0){
                                printf("Only .csv files should be given as inputs.\n");
                                return -1;

                        }else{
                                z++;
                                continue;
                        }
		}
	}

	if(var==0){     //if the value entered is zero then the program is ended
            	return 0;
        }

	if (count==0){ 		//if no files are given following code block is executed
    		printf("No input files were given\nusage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n",argv[0]);
    		return 0;
	}

	for(int m = 0;m<=count-1;m++){			//loop to open each files
		FILE *filepointer= fopen(files[m],"r");

		if(filepointer ==NULL){			//if the file cannot be open then the following error message is executed
			printf("Cannot open one or more given files\n");
			return 0;
		}
	}

	for(int n = 0;n<=count-1;){		//loop to open each files
		FILE *filepointer= fopen(files[n],"r");
		char line[1000];
		while(fgets(line, sizeof(line), filepointer)){		//to read each line in file
                        newnode = (rowData*)malloc(sizeof(rowData));	//dynamic memory for to store each line
                        newnode ->next = 0;
                        totmeet++;
			char *token;
			int sum=0;
                        char time[50];
                        char *hour,*min;
			newnode->meetCount=1;
                        token = strtok(line, ",");			//to sperate name from a row
                        int i_hour,i_min;
                        strcpy(newnode->Name,token);
                        token = strtok(NULL,",");			//to seperate participant count from a row
                        newnode->pCount = atoi(token);
                        token = strtok(NULL,",");			//to seperate time from a row
                        strcpy(time,token);
                        hour = strtok(time,":");			//to seperate hour from time
                        min = strtok(NULL,":");				//to seperate minute from time
                        i_hour = atoi(hour);				//to convert hour string to an integer
                        i_min = atoi(min);				//to covert minute string to an integer
                        newnode ->minCount = i_hour*60 +i_min;		//to covert hour to minute and adding minute to add and assigning it to minCount
			totmeet=totmeet+sum;	
			if(head == 0){
                                head =temp = newnode;
                        }else{
				comp =head;
				while(comp!=NULL){
					if(strcmp(comp->Name,newnode->Name)==0){	//checking whether the newnode name is already in the linked list if it's true then the following code is executed
						comp->pCount=comp->pCount+newnode->pCount;	
						comp->minCount=comp->minCount+newnode->minCount;
						comp->meetCount = comp->meetCount +1;
						free(newnode);
						break;
					}
					comp = comp -> next;	//newnode is created
				}
				if(comp==NULL){
					temp ->next = newnode;
					temp = newnode;
					lineCount++;
				}
			}
			sum++;
		}
		fclose(filepointer);
		n++;
	}

        for (int j=1;j<=argc-1;j++){ //if scaled option is given in any of the arguments the scaled version of the chart is printed

           	if((strcmp(argv[j],"-m"))==0){		//if -m is entered as an argument then following block is executed
                      	sortmeetCount(head);
			x1++;
			break;
              	}else if((strcmp(argv[j],"-p"))==0){	//if -p is entered as an argument then following block is executed
                   	sortpCount(head);
			x2++;
			break;

            	}else if((strcmp(argv[j],"-t"))==0){	//if -t is entered as an argument then following block is executed
                     	sortminCount(head);
			x3++;
			break;
               	}
        }

	if(x1 == 0 && x2 == 0 && x3 == 0){
                sortmeetCount(head);
	}

	if(var>lineCount){

		var = lineCount;
	}
	max = nameLen(head);
	int z;
        for(int j=1;j<=argc-1;j++){
                z = strcmp(argv[j],"--scaled");
                if(z==0){
                        break;
                }
        }
       	if((x2==0 && x3==0) && z==0 && var!=0){		//if -m and --scaled entered as arguments and if var!=0 then following block is executed
              	printChartmeetCount_S(head);
              	return -1;
        }else if(x2==1 && z==0 && var!=0){		//if -p and --scaled entered as arguments and if var!=0 then following block is executed
             	printChartpCount_S(head);
              	return -1;
        }else if(x3==1 && z==0 && var!=0){		//if -t and --scaled entered as arguments and if var!=0 then following block is executed
		printChartminCount_S(head);
            	 return -1;
        }else if((x2==0 && x3==0) && z!=0 && var!=0){	//if -m is entered as an argument and var!=0 then following block is executed
		tot = totmeet;
		printChartmeetCount_N_S(head);
		return -1;
	}else if(x2==1 && z!=0 && var!=0){		//if -p is entered as an argument and var!=0 then following block is executed
		tot = totalpCount(head);
                printChartpCount_N_S(head);
                return -1;
        }else if(x3==1 && z!=0 && var!=0){		//if -t is entered as an argument and var!=0 then following block is executed
		tot = totalminCount(head);
                printChartminCount_N_S(head);
                return -1;
	}	
	return 0;
}


rowData *sortpCount(rowData *poin){		//prototype of the function to sort participant count list

int te;
rowData *x,*y,*z;
char na[100];
for(x=poin;x->next!=NULL;x=x->next){
        z=poin;

        for(y=poin;z->next!=NULL;y=y->next){
                if(y->pCount<y->next->pCount){		//comparing the first not with the next node if it's true swapping both
                        te = y->pCount;
                        strcpy(na,y->Name);
                        y->pCount = y->next->pCount;
                        strcpy(y->Name,y->next->Name);
                        y->next->pCount = te;
                        strcpy(y->next->Name,na);
                }
                z=z->next;

        }
}


return head;
}

rowData *sortmeetCount(rowData *poin){		//prototype of the function to sort meetings attended count list
int in;
rowData *x,*y,*z;
char na[100];
for(x=poin;x->next!=NULL;x=x->next){
        z=poin;
        for(y=poin;z->next!=NULL;y=y->next){
                if(y->meetCount<y->next->meetCount){		//comparing the first not with the next node if it's true swapping both
                        in = y->meetCount;
                        strcpy(na,y->Name);
                        y->meetCount = y->next->meetCount;
                        strcpy(y->Name,y->next->Name);
                        y->next->meetCount = in;
                        strcpy(y->next->Name,na);
                }
                z=z->next;
        }
}

return head;
}

rowData *sortminCount(rowData *poin){		//prototype of the function to sort total minutes list

int co;
rowData *x,*y,*z;
char na[100];
for(x=poin;x->next!=NULL;x=x->next){
	z=poin;
        for(y=poin;z->next!=NULL;y=y->next){		
                if(y->minCount<y->next->minCount){		//comparing the first not with the next node if it's true swapping both
                        co = y->minCount;
                        strcpy(na,y->Name);
                        y->minCount = y->next->minCount;
                        strcpy(y->Name,y->next->Name);
                        y->next->minCount = co;
                        strcpy(y->next->Name,na);
                }
                z=z->next;
        }
}

return head;

}

void printChartpCount_S(rowData *poin){		//prototype of the function to print SCALED participant count chart

        rowData *p=poin;
        float m=p->pCount;
        float n;
	printf("\n");
        while(var>0){
		n=p->pCount;
                for(int j=0;j<3;j++){ 		//loop to repeat thrice
                        if(j==1){ 		//when the second iteration process is happening(second sub row)
                                printf(" %s",p->Name); 			//first the charachter is printed
                                for(int i=0;i<(max+1)-strlen(p->Name);i++){ 	//then according to the scaling algorithm number of boxes are printed

                                        printf(" ");

                                }
                                printf("\u2502");
                                for(int i=1;i<=(int)((n/m)*(80-(max+3+numofdig(p->pCount))));i++){
                                        printf("\u2591");
                                }
                                printf("%i\n",p->pCount);
                        }else{
                                for(int i=0;i<max+2;i++){
                                        printf(" ");
                                }
                                printf("\u2502");
                                for(int i=0;i<(int)((n/m)*(80-(max+3+numofdig(p->pCount))));i++){
                                        printf("\u2591");
                                }
                                printf("\n");
                        }
                }
                for(int i=0;i<max+2;i++){
                        printf(" ");
                }
                printf("\u2502");
                printf("\n");
                p=p->next;

                var--;
        }
        for(int i=0;i<max+2;i++){
                printf(" ");
        }
        printf("\u2514");
        for(int i=0;i<80-(max+3);i++){
                printf("\u2500");
        }
        printf("\n");
}

void printChartmeetCount_S(rowData *poin){		//prototype of the function to print SCALED meeting count chart

	rowData *p=poin;
        float m=p->meetCount;
        float n;
        printf("\n");

        while(var>0){
                n=p->meetCount;
                for(int j=0;j<3;j++){ 	//loop to repeat thrice
                        if(j==1){ 	// when the second iteration process is happening(second sub row)
                                printf(" %s",p->Name); 	//first the charachter is printed
                                for(int i=0;i<(max+1)-strlen(p->Name);i++){ //then according to the scaling algorithm number of boxes are printed
                                        printf(" ");
                                }
                                printf("\u2502");
                                for(int i=1;i<=(int)((n/m)*(80-(max+3+numofdig(p->meetCount))));i++){

                                        printf("\u2591");
                                }
                                printf("%i\n",p->meetCount);
                        }else{
                                for(int i=0;i<max+2;i++){
                                        printf(" ");
                                }
                                printf("\u2502");
                                for(int i=0;i<(int)((n/m)*(80-(max+3+numofdig(p->meetCount))));i++){

                                        printf("\u2591");
                                }
                                printf("\n");
                        }
                }
                for(int i=0;i<max+2;i++){
                        printf(" ");
                }
                printf("\u2502");
                printf("\n");
                p=p->next;
                var--;
        }
        for(int i=0;i<max+2;i++){
                printf(" ");
        }
        printf("\u2514");
        for(int i=0;i<80-(max+3);i++){
                printf("\u2500");
        }
        printf("\n");
}


void printChartminCount_S(rowData *poin){		//prototype of the function to print SCALED total minutes list

        rowData *p=poin;

        float m=p->minCount;
        float n;
	printf("\n");
        while(var>0){
		n=p->minCount;
                for(int j=0;j<3;j++){ 		//loop to repeat thrice
                        if(j==1){ 		// when the second iteration process is happening(second sub row)
                                printf(" %s",p->Name); //first the charachter is printed


                                for(int i=0;i<(max+1)-strlen(p->Name);i++){ 	//then according to the scaling algorithm number of boxes are printed

                                        printf(" ");

                                }
                                printf("\u2502");
                                for(int i=1;i<=(int)((n/m)*(80-(max+3+numofdig(p->minCount))));i++){

                                        printf("\u2591");
                                }
                                printf("%i\n",p->minCount);
                        }else{
                                for(int i=0;i<max+2;i++){
                                        printf(" ");
                                }
                                printf("\u2502");
                                for(int i=0;i<(int)((n/m)*(80-(max+3+numofdig(p->minCount))));i++){

                                        printf("\u2591");
                                }
                                printf("\n");
                        }
                }
                for(int i=0;i<max+2;i++){
                        printf(" ");
                }
                printf("\u2502");
                printf("\n");
                p=p->next;

                var--;
        }
        for(int i=0;i<max+2;i++){
                printf(" ");
        }
        printf("\u2514");
        for(int i=0;i<80-(max+3);i++){
                printf("\u2500");
        }
        printf("\n");
}

/*instructions are similar to that of printing a scaled word chart , only difference is  the algorithm for non scaled is given here*/

void printChartpCount_N_S(rowData *poin){ 		//prototype of the function to print NON SCALED meeting count chart

        rowData *p=poin;
      
        float n;
	printf("\n");
        while(var>0){
                n=p->pCount;

                for(int j=0;j<3;j++){
                        if(j==1){
                                printf(" %s",p->Name);
                                for(int i=0;i<(max+1)-strlen(p->Name);i++){
                                        printf(" ");
                                }
                                printf("\u2502");

                                for(int i=0;i<(int)((n/tot)*(80-(max+3+numofdig(p->pCount))));i++){

                                        printf("\u2591");
                                }
                                printf("%i\n",p->pCount);
                        }else{
                                for(int i=0;i<max+2;i++){
                                        printf(" ");
                                }

                                printf("\u2502");
                                for(int i=0;i<(int)((n/tot)*(80-(max+3+numofdig(p->pCount))));i++){


                                        printf("\u2591");
                                }
                                printf("\n");
                        }
                }
                for(int i=0;i<max+2;i++){
                        printf(" ");
                }

                printf("\u2502");
                printf("\n");
                p=p->next;
                var--;
        }
        for(int i=0;i<max+2;i++){
                printf(" ");
        }

        printf("\u2514");
        for(int i=0;i<80-(max+3);i++){
                printf("\u2500");
        }
        printf("\n");
}

void printChartmeetCount_N_S(rowData *poin){ 		//prototype of the function to print NON SCALED participant count chart
	
        rowData *p=poin;
        float n;
        printf("\n");
        while(var>0){
                n=p->meetCount;

                for(int j=0;j<3;j++){
                        if(j==1){
                                printf(" %s",p->Name);
                                for(int i=0;i<(max+1)-strlen(p->Name);i++){
                                        printf(" ");
                                }
                                printf("\u2502");

                                for(int i=0;i<(int)((n/tot)*(80-(max+3+numofdig(p->meetCount))));i++){


                                        printf("\u2591");
                                }
                                printf("%i\n",p->meetCount);
                        }else{
                                for(int i=0;i<max+2;i++){
                                        printf(" ");
                                }

                                printf("\u2502");
                                for(int i=0;i<(int)((n/tot)*(80-(max+3+numofdig(p->meetCount))));i++){

                                        printf("\u2591");
                                }
                                printf("\n");
                        }
                }
                for(int i=0;i<max+2;i++){
                        printf(" ");
                }

                printf("\u2502");
                printf("\n");
                p=p->next;
                var--;
        }
        for(int i=0;i<max+2;i++){
                printf(" ");
        }

        printf("\u2514");
        for(int i=0;i<80-(max+3);i++){
                printf("\u2500");
        }
        printf("\n");
}


void printChartminCount_N_S(rowData *poin){ 		//prototype of the function to print NON SCALED total minutes list

        rowData *p=poin;
        float n;
	printf("\n");
        while(var>0){
                n=p->minCount;

                for(int j=0;j<3;j++){
                        if(j==1){
                                printf(" %s",p->Name);
                                for(int i=0;i<(max+1)-strlen(p->Name);i++){
                                        printf(" ");
                                }
                                printf("\u2502");

                                for(int i=0;i<(int)((n/tot)*(80-(max+3+numofdig(p->minCount))));i++){

                                        printf("\u2591");
                                }
                                printf("%i\n",p->minCount);
                        }else{
                                for(int i=0;i<max+2;i++){
                                        printf(" ");
                                }

                                printf("\u2502");
                                for(int i=0;i<(int)((n/tot)*(80-(max+3+numofdig(p->minCount))));i++){
                                        printf("\u2591");
                                }
                                printf("\n");
                        }
                }
                for(int i=0;i<max+2;i++){
                        printf(" ");
                }

                printf("\u2502");
                printf("\n");
                p=p->next;
                var--;
        }
        for(int i=0;i<max+2;i++){
                printf(" ");
        }

        printf("\u2514");
        for(int i=0;i<80-(max+3);i++){
                printf("\u2500");
        }
        printf("\n");
}


int nameLen(rowData *poin){		//prototype of the function to find the length of the lengthiest name in the list

        temp=poin;
        int max_ret;
        max_ret=strlen(temp->Name);
        for(int z=var;z>1;z--){
                if(max_ret<strlen(temp->next->Name)){

                        max_ret=strlen(temp->next->Name);
                }
                temp=temp->next;
        }
        return max_ret;
}

int numofdig(int num){			//prototype of the function to find the number of digits in a number
	int dig=1;
        while(num>10){
                num = num/10;
                dig++;
        }
        return dig;
}

int totalpCount(rowData *poin){		//prototype of the function to find the total number of particiapnts in every row in every file
        poin=head;
	int totalp=0;
        while(poin!=NULL){
                totalp = totalp + poin->pCount;
                poin = poin ->next;
        }
	return totalp;
}

int totalminCount(rowData *poin){	//prototype of the function to find the total minutes in every row in every file
        poin=head;
        int totalmin=0;
        while(poin!=NULL){
                totalmin = totalmin + poin->minCount;
                poin = poin ->next;
        }
        return totalmin;
}

