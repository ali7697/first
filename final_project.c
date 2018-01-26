#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
struct node{
	char str[50];
	struct node *next;
};
time_t time_first,time_last;//save high score
char ch;//toye tabe tarif mikardam error stack midad
int num,firstnum,txt;
int choice;//2 ja estefade shode
int continu=1;
int k=1;
int yenegahbandige[100];
FILE *new_file[100];//???
FILE *fn;//esmha
double total_score[1000],max_total_score[1000];//1000 topics avalesham 0 mide   double
double sum_of_scores[80];//baraye top players
int topic_number;
double score_sum=0;
double high_sum_of_score[10];
char name[80];
char c[50][50];//topic names
char top_name[10][80];
struct node * list;
void tolink(void);//kalamat ro dakhele linked list mirize
struct node * create_node(char string[]);
void add_end(struct node *list,struct node * new_node);
char *get_word(struct node *list);
char new_topic_name[100][100];
int generated_topic_num;
int character_number(char *string);
void show_word(char *string);
void guess(char *string);
void draw_wrong_guess(int wrong_guess);
void menue();
void save(char name[]);
void topic_generator();
void show_top_players();
int main(void){
	menue();
	while(continu){
		tolink();
		score_sum=0;
		while(num){
			guess(get_word(&list));
		}
	}
	return 0;
}
void tolink(void){
	int a;
	int h;
	int j;
	char str[100];
	FILE *f;
	FILE *fp;
	k=1;
	f=fopen("AVAILABLE_TOPICS.txt","r");
	printf("Do you want to generate a new topic?\n1.Yes\n2.No\n");
	scanf("%d",&a);
	if(a==1)
		topic_generator();
	printf("Here are the topics , choose one :\n");
	//printf("1.Fruits\n2.Soccer players\n3.Programming languages\n4.Computer networks\n5.Video games\n");
	while(!feof(f)){//(fgets(c[k],50,f)!=NULL){
		fscanf(f,"%s",c[k]);
		printf("%d.%s\n",k,c[k]);
		k++;
	}
	fclose(f);
	/*if(a==1){
		for(a=1,j=6;a<=generated_topic_num;a++){
			printf("%d.%s\n",j,new_topic_name[a-1]);
		}
	}*/
	printf("Enter the number of topic :\n");
	scanf("%d",&topic_number);	
	fp=fopen(c[topic_number],"r");
	if(fp==NULL)
		printf("error\n");
	
	/*if(topic_number==1)
		fp=fopen("fruits.txt","r");
	else
		if(topic_number==2)
			fp=fopen("soccer_players.txt","r");
		else
			if(topic_number==3)
				fp=fopen("programming_languages.txt","r");
			else 
				if(topic_number==4)
					fp=fopen("computer_networks.txt","r");
				else
					if(topic_number==5)
						fp=fopen("video_games.txt","r");*/
	/*else{
		fp=fopen(new_topic_name[topic_number-6],"r");//-6 bekhatere j
		if(fp==NULL){
			printf("error\n");
		}
	}*/
	fscanf(fp,"%s",&str);
	list=create_node(str);
	num++;
	while(!feof(fp)){
		fscanf(fp,"%s",str);
		add_end(list,create_node(str));	
		num++;
	}
	num=num-1;
	firstnum=num;
	fclose(fp);
}
struct node * create_node(char string[]){
	struct node * nn;
	int i;
	nn = (struct node *) 
	malloc(sizeof(struct node));
	for(i=0;string[i]!='\0';i++){
		nn->str[i]=string[i];
	}
	nn->str[i]='\0';
	nn->next = NULL;
	return nn;
}
void add_end(struct node *list,struct node * new_node){
	struct node *current;
    for(current = list; current->next != NULL; current = current->next);
    current->next = new_node;
    new_node->next = NULL;
}
char * get_word(struct node **list/* *list */){//yeki migire va hazfesh mikone
	char a[]="a";
	int i,j;
	struct node *current;
	struct node *nod;
	struct node *temp;
	temp=create_node(a);
	temp->next=*list;//list
	srand(time(0));
	j=rand()%num;
	current=temp;
	if(j==0){
		nod=current->next;
		*list=current->next->next;
	}
	else{
	for(i=0;i<j;i++){
		current=current->next;
	}
	nod=current->next;
	if(j==num-1){//bara tomato akhari javab midads vali toi ravand javab nemide
		current->next=NULL;
	}
	else
		current->next=current->next->next;
	}
	num--;
	return nod->str;
}
int character_number(char *string){
	int i;
	for(i=0;string[i]!='\0';i++);
	return i;
}
void show_word(char *string){
	int i;
	for(i=0;i<character_number(string);i++){
		printf("_ ");
	}
	printf("\n");
}
void guess(char *string){
	char temp[50];
	int i,j,delta_t,saveorno;
	int ah=0;
	int negahban=1,wrong_guess,cnum;//character number
	double score=0;//score_sum=0;
	wrong_guess=0;
	if(num==firstnum-1)
		time_first=time(0);
	draw_wrong_guess(wrong_guess);
	show_word(string);
	for(i=0;i<30;i++)
		temp[i]='_';
	while(negahban){
		negahban=0;
		j=0;
		scanf("%s",&ch);
		if(ch=='Q'){
			printf("Do you want to save the game?\n");
			printf("1.Yes\n2.No\n");
			scanf("%d",&choice);
			if(choice==1){
				save(name);
			}
			exit(0);
		}
		for(i=0;string[i]!='\0';i++){
			if(ch==string[i]){
				j=1;
				break;
			}
		}
		if(j==0)
			wrong_guess++;
		draw_wrong_guess(wrong_guess);
		for(i=0;string[i]!='\0';i++){
			if(ch==string[i] && temp[i]=='_' ){
				printf("%c ",ch);
				temp[i]=ch;
			}
			else{
				if(temp[i]!='_'){
					printf("%c ",temp[i]);
				}
				else{
					printf("_ ");
					negahban=1;
				}
			}
		}
		if(wrong_guess==5){
			printf("\n");
			printf("\nscore is : 0\n");
			if(num==0){//emtiaz kolle topic
				time_last=time(0);
				delta_t=time_last-time_first;
				total_score[topic_number]=1.0*score_sum/delta_t;
				if(total_score[topic_number]>max_total_score[topic_number])
					max_total_score[topic_number]=total_score[topic_number];
				ah=1;
				printf("\nfinal score is : %lf\n",total_score[topic_number]);//sefr mide
				printf("Do you want to play again?\n1.Yes\n2.No\n");
				scanf("%d",&continu);
				if(continu==1){
					break;
				}
				if(continu==2){//save bad az payan
					printf("do you want to save the game?\n1.Yes\n2.No\n");
					scanf("%d",&saveorno);
					if(saveorno==1){
						save(name);
					}
					exit(0);
				}
			}
			else
				break;
		}
		///////////////
		//negahban=0;//??
		printf("\n");
	}
	if(wrong_guess<5){
		cnum=character_number(string);
		score=3*cnum-wrong_guess;
		score_sum+=score;
		printf("score is : %lf\n",score);
	}
	if(num==0 && ah==0){//emtiaz kolle topic
		time_last=time(0);
		delta_t=time_last-time_first;
		total_score[topic_number]=1.0*score_sum/delta_t;
		if(total_score[topic_number]>max_total_score[topic_number])
			max_total_score[topic_number]=total_score[topic_number];
		printf("\nfinal score is : %lf\n",total_score[topic_number]);//sefr mide
		printf("Do you want to play again?\n1.Yes\n2.No\n");
		scanf("%d",&continu);
		if(continu==2){//save bad az payan
			printf("do you want to save the game?\n1.Yes\n2.No\n");
			scanf("%d",&saveorno);
			if(saveorno==1){
				save(name);
			}
			exit(0);
		}
	}
	else
		printf("\nnext\n");
}	
void draw_wrong_guess(int wrong_guess){
	if(wrong_guess==0){
		printf("        +-----+\n");
		printf("        | . . |\n");
		printf("        |  |  |\n");
		printf("        | --- |\n");
		printf("        +-----+\n");
		printf("          | |  \n");
		printf("     +-----------+\n");
		printf("    /|-----------|\\ \n");
		printf("   / /-----------\\ \\ \n");
		printf("  / /|-----------|\\ \\  \n");
		printf("     |-----------|    \n");
		printf("     |-----------|    \n");
		printf("     |-----------|    \n");
		printf("     +-+-+-+-+-+-+    \n");
		printf("       | |   | |      \n");
		printf("       | |   | |      \n");
		printf("       | |   | |      \n");
		printf("       | |   | |      \n");
		printf("       | |   | |      \n");
		printf("/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\ \n");
		printf("////////////////////// \n");
		printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \n");
	}
	if(wrong_guess==1){
		printf("        +-----+\n");
		printf("        | o o |\n");
		printf("        |  |  |\n");
		printf("        | --- |\n");
		printf("        +-----+\n");
		printf("          | |  \n");
		printf("     +-----------+\n");
	    printf("    /|-----------|\\ \n");
		printf("   / /-----------\\ \\ \n");
		printf("  / /|-----------|\\ \\  \n");
		printf("     |-----------|    \n");
		printf("     |-----------|    \n");
		printf("     |-----------|    \n");
		printf("     +-+-+-+-+-+-+    \n");
		printf("/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\ \n");
		printf("////////////////////// \n");
		printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \n");
	}
	if(wrong_guess==2){
		printf("        +-----+\n");
		printf("        | 0 0 |\n");
		printf("        |  |  |\n");
		printf("        | --- |\n");
		printf("        +-----+\n");
		printf("          | |  \n");
		printf("     +-----------+\n");
		printf("    /|-----------|\\ \n");
		printf("   / /-----------\\ \\ \n");
		printf("  / /|-----------|\\ \\  \n");
		printf("/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\ \n");
		printf("////////////////////// \n");
		printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \n");
	}
	if(wrong_guess==3){
		printf("        +-----+\n");
		printf("        | o o |\n");
		printf("        |  |  |\n");
		printf("        | --- |\n");
		printf("        +-----+\n");
		printf("          | |  \n");
		printf("/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\ \n");
		printf("////////////////////// \n");
		printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \n");
	}
	if(wrong_guess==4){
		printf("        +-----+\n");
		printf("        | * * |\n");
		printf("        |  |  |\n");
		printf("/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\ \n");
		printf("////////////////////// \n");
		printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \n");
	}
	if(wrong_guess==5){
		printf("      Bye Bye ! ! !    \n");
		printf("/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\ \n");
		printf("////////////////////// \n");
		printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \n");
	}
}
void menue(){
	int i=1;
	int w=1;
	int s;
	char str[]=".txt";
	FILE *file;
	FILE *ff;
	printf("Welocome to Hangman!!!!!!!\n\n");
	printf("Please enter your name :\n");
	gets(name);
	strcat(name,str);
	printf("Enter a number to continue : \n");
	printf("1.Resume\n2.New game\n");
	scanf("%d",&choice);
	if(choice==1){
		txt=1;
		file=fopen(name,"r");
		if(file==NULL){
			printf("You have not played before.\n");
			exit(0);
		}
		ff=fopen("AVAILABLE_TOPICS.txt","r");
		while(!feof(ff)){
			fscanf(ff,"%s",c[w]);
			w++;
		}
		fclose(ff);
		while(!feof(file)){	
			fscanf(file,"%lf ",&max_total_score[i]);//high score zakhire mishe
			printf("your max total score in %s is : %lf \n",c[i],max_total_score[i]);
			i++;
		}
			//age in nabashe hame high score ha 0
		//}
		/*printf("your max total score in fruits is : %lf \n",max_total_score[1]);
		printf("your max total score in soccer players is : %lf \n",max_total_score[2]);
		printf("your max total score in programming languages is : %lf \n",max_total_score[3]);
		printf("your max total score in computer networks is : %lf \n",max_total_score[4]);
		printf("your max total score in video games is : %lf \n",max_total_score[5]);*/

	}
	if(choice==2){//to oon file high score taraf hamaro sefr mikone
		txt=1;
		//
		file=fopen(name,"r");
		if(file==NULL){
			fn=fopen("names.txt","a");
			fprintf(fn," %s",name);
			fclose(fn);
		}
		//fclose(file);
		file=fopen(name,"w");
		for(i=1;i<=6;i++){
			fprintf(file,"%Lf ",max_total_score[i]);
		}
	}
	fclose(file);
	printf("Do you want to see the top players?\n");
	printf("1.Yes\n2.No\n");
	scanf("%d",&s);
	if(s==1)
		show_top_players();
}
void save(char name[]){
	int i=1;
	char str[]=".txt";
	//struct node *current;
	FILE *fsave;
	if(txt==0)
		strcat(name,str);
	fsave=fopen(name,"w");
	/*for(current=list;current->next!=NULL;current=current->next){
		fprintf(fsave,"%s ",current->str);
	}*/
	fprintf(fsave,"%Lf ",max_total_score[i]);//jadid neveshte shod
	for(i=2;i<k;i++){//i 1 bood kardamesh 2
		//fwrite(&max_total_score[i],sizeof(double),1,fsave);
		fprintf(fsave," %Lf",max_total_score[i]);
	}
	fclose(fsave);
}
void topic_generator(){
	FILE *www;
	int r=1,i=0;
	char str[]=".txt";
	char word[50];
	www=fopen("AVAILABLE_TOPICS.txt","a");
	while(r==1){
		printf("Please enter the name of the new topic :\n");
		scanf("%s",new_topic_name[i]);
		strcat(new_topic_name[i],str);
		fprintf(www,"\n%s",new_topic_name[i]);
		new_file[i]=fopen(new_topic_name[i],"w");
		printf("Enter the words you want to add (enter E to end) :\n");
		while(1){
			scanf("%s",word);
			if(word[0]=='E' && word[1]=='\0' )
				break;
			fprintf(new_file[i],"%s ",word);
		}
		fclose(new_file[i]);
		printf("Do you want to add another topic?\n1.Yes\n2.No\n");
		scanf("%d",&r);
		i++;
	}
	generated_topic_num=i;
	fclose(www);
}
void show_top_players(){
	FILE *fesm;
	int i=0;
	int k=0;
	int w;
	int negahbantabe=0;
	int num;
	char esm[80][80];
	//[80][10]
	double sum_temp=0;//sum_of_score[80][80]
	//high some [10]
	fn=fopen("names.txt","r");
	while(!feof(fn)){
		fscanf(fn,"%s",esm[i]);
		fesm=fopen(esm[i],"r");
		if(fesm==NULL)
			printf("Error\n");//?????????????
		while(!feof(fesm)){
			fscanf(fesm,"%Lf",&sum_temp);
			//fread(&sum_temp,sizeof(double),1,fesm); 0 midad
			sum_of_scores[i]+=sum_temp;
		}
		fclose(fesm);
		i++;
	}
	num=i;
	fclose(fn);
	for(k=0;(k<10 && k<num);k++){
		for(i=0;i<num;i++){
			if(k==0){
				if(sum_of_scores[i]>=high_sum_of_score[k]){
				high_sum_of_score[k]=sum_of_scores[i];
				//strcpy(top_name[k],esm[i]);
				for(w=0;esm[i][w]!='\0';w++){
					top_name[k][w]=esm[i][w];
				}
				top_name[k][w]='\0';
				}
			}
			else
				if(sum_of_scores[i]>=high_sum_of_score[k]){// && sum_of_scores[i]<high_sum_of_score[k-1]/*sum_of_scores[i-1]*/){
					if(sum_of_scores[i]<high_sum_of_score[k-1]){
						high_sum_of_score[k]=sum_of_scores[i];
						//strcpy(top_name[k],esm[i]);
						for(w=0;esm[i][w]!='\0';w++){
							top_name[k][w]=esm[i][w];//error kheili ajib topname[k-1]edamesh ino mirize!!!!!!!

						}
						top_name[k][w]='\0';
					}
					else{
						if(sum_of_scores[i]==high_sum_of_score[k-1] && strcmp(esm[i],top_name[k-1])!=0 && yenegahbandige[i]==0){
							/*for(w=0;esm[i][w]!='\0' && top_name[k-1][w]!='\0';w++){
								if(esm[i][w]==top_name[k-1][w]){
									continue;
								}
								else{
									negahbantabe=1;
								}
							}
							if(negahbantabe==1){*/
							high_sum_of_score[k]=sum_of_scores[i];
							//strcpy(top_name[k],esm[i]);
							for(w=0;esm[i][w]!='\0';w++){
								top_name[k][w]=esm[i][w];
							}
							top_name[k][w]='\0';
					}
					}
			}
		}
		for(negahbantabe=1;negahbantabe<num;negahbantabe++){
			if(strcmp(top_name[k],esm[negahbantabe])==0){
				yenegahbandige[negahbantabe]=1;//emtiaz haye mosavi tekrari chap nakone
			}
		}
		printf("%s    %Lf\n",top_name[k],high_sum_of_score[k]);
	
	}
}
