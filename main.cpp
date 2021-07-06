# include "list.h"
# include "command.h"
# include "groupm.h"



int main (int argc, char ** argv)
{
	//FILE*fp;
	//double t;
    if (argc!=3)
	{
		printf("Usage: %s record.txt mod \n",argv[0]);
		return -1;
	}
	
	//printf("%d",'z'-'A');
	
	char * name1=argv[1];
	//char * name_com=argv[2];
	int mod=atoi(argv[2]);
	groupm a(mod);
	
	/*int mod;
	printf("input mod\n");
	scanf("%d",&mod);*/
	
	double t2=clock();
	
	double t1=clock();
	//printf("DDD\n");
	
	a.read_mas(name1,mod);
	//printf("ffff\n");
	t1=clock()-t1;
	printf("Time read_list: %lf\n",t1/CLOCKS_PER_SEC);
  
	//
	
	/*printf("____________________________________GROUP:\n");
	a.print_mas();*/
	
	
	
	
	
	
	/*fp=fopen(name_com,"r");
	if (!fp) { printf("No such file\n"); return 2; }*/
	
	
	double t3=clock();
  	a.read_file(stdin,stdout);
	t3=clock()-t3;
	printf("Time comm: %lf\n",t3/CLOCKS_PER_SEC);
	printf("Time read_list: %lf\n",t1/CLOCKS_PER_SEC);
	
	
	t2=clock()-t2;
	printf("ALL TIME: %lf\n",t2/CLOCKS_PER_SEC);
	//a.delete_list();*/
	
	//fclose(fp);
	//printf("FFFFFF\n");
	return 0;
}
