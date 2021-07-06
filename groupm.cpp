#include "groupm.h"

#define RAZN 57
//#define RAZMNAME 57*57*57*57+57*57*57+57*57+57
#define RAZMNAME 188500

int groupm::read_mas(const char*name, int num)
{
	FILE *fp;
	if (!(fp=fopen(name,"r"))) { printf("err file\n");return -1; }

    char sname[1234];
	int sphone;
	int sgroup;
	
	//printf("%d\n",RAZMNAME);
	//printf("%d\n",('a'-'A')*RAZN*RAZN*RAZN+('a'-'A')*RAZN*RAZN+('a'-'A')*RAZN+'a'-'A');
	//printf("%d\n",('a'-'A')*RAZN*RAZN*RAZN+('a'-'A')*RAZN*RAZN+('a'-'A')*RAZN+'b'-'A');
	
	//int i=0;	
	while(fscanf(fp,"%s%d%d",sname,&sphone,&sgroup)==3)
	{
		insert(sname,sphone,sgroup,num);
		//printf("&&&%d\n",i);
		//i++;
	}
	//printf("vse\n");
	fclose(fp);
	return 0;
	
}

void groupm::insert(char*name,int phone,int group,int num)
{
	list_node *current=head;
	if(mas[group-100])
	{
		current=mas[group-100]->insert(name,phone,group);
		if(!current)return;
		current->next=head;
		if(head)
			head->prev=current;		
		head=current;
		masphone(current);
		masname(current);
	}
	else
	{
		mas[group-100]=new list();
		mas[group-100]->mod=num;
		mas[group-100]->hash_name= new list_node*[RAZMNAME];
		for(int i=0; i<RAZMNAME;i++)mas[group-100]->hash_name[i]=0;

		mas[group-100]->hash_phone= new list_node*[mas[group-100]->mod];
		for(int i=0;i<mas[group-100]->mod;i++)mas[group-100]->hash_phone[i]=0;
		
		current=mas[group-100]->insert(name,phone,group);
		current->next=head;
		if(head)
			head->prev=current;	
		head=current;
		
		masphone(current);
		masname(current);
	}
}

int groupm::masname(list_node*a)
{
	int k=poiskvmasname(a);
	
	if(hash_name[k])
	{
		list_node *m=hash_name[k];
		
		a->down_n=m;
		m->up_n=a;
		hash_name[k]=a;
	}
	else
		hash_name[k]=a;
	
	a->place=k;
	
	return 0;
}

int groupm::poiskvmasname(list_node*a)
{
	//return (a->name.get()[0]-'A')*RAZN+a->name.get()[1]-'A';	
	return (a->name.get()[0]-'A')*RAZN*RAZN+(a->name.get()[1]-'A')*RAZN+(a->name.get()[2]-'A');
}

int groupm::poiskvmasname(command*a)
{
	return (a->name.get()[0]-'A')*RAZN*RAZN+(a->name.get()[1]-'A')*RAZN+(a->name.get()[2]-'A');
	//return (a->name.get()[0]-'A')*RAZN+a->name.get()[1]-'A';	
}

void groupm::masphone(list_node*a)
{
	int k=poiskvmasphoneinsert(a);
	
	if(hash_phone[k])
	{
		list_node *m=hash_phone[k];
		
		a->down_p=m;
		m->up_p=a;
		hash_phone[k]=a;
	}
	else
		hash_phone[k]=a;
	
	a->modphone=k;
}

int groupm::poiskvmasphoneinsert(list_node*a)
{
	int num=a->phone;
	return num%mod;
	
	/*int sum=0,num=a->phone;
	
	while(num)
	{
		sum+=num%10;
		num=num/10;
	}
	return sum%mod;*/
	
}

int groupm::poiskvmasphoneinsert(command*a)
{
	int num=a->phone;
	return num%mod;
	
	/*int sum=0,num=a->phone;
	
	while(num)
	{
		sum+=num%10;
		num=num/10;
	}
	return sum%mod;*/
	
}

void groupm::print_mas()
{
	printf("___________________________________GROUP:\n");
	for(int i=0;i<900;i++)
	{
		if(mas[i])
		{
			mas[i]->print_list_mas();
			printf("++++++++++++++++++++++++++++++++\n");
		}
	}
	
	/*printf("__________________________________PHONE:\n");
	int i;//kol1=0,kol2=0;
	list_node*m;
	
	for(i=0;i<mod;i++)
	{
		if(hash_phone[i])
		{
			//kol2=0;
			//if(kol1>3)return;
			m=hash_phone[i];
			while(m)
			{
				//if(kol2>3)break;
				fprintf(stdout,"%s %d %d %d\n",m->name.get(),m->phone,m->group, m->modphone);
				m=m->down_p;
				//kol2++;
			}	
			printf("_________________________________\n");	
			//kol1++;			
		}
	}*/
	int i;//kol1=0,kol2=0;
	list_node*m;
	printf("__________________________________NAME:\n");
	for(i=0;i<RAZMNAME;i++)
	{
		if(hash_name[i])
		{
			//kol2=0;
			//if(kol1>3)return;
			m=hash_name[i];
			while(m)
			{
				//if(kol2>3)break;
				fprintf(stdout,"%s %d %d (%d)\n",m->name.get(),m->phone,m->group,m->place);
				m=m->down_n;
				//kol2++;
			}	
			printf("_________________________________\n");	
			//kol1++;			
		}
	}
}

void groupm::read_file(FILE * fp, FILE * bf)
{
	char buf[LEN];
	char t[8];
	int k;
	int alf[256];
	char * word[LEN];
    (void)bf;
	t[0]=' ';  t[1]='(';  t[2]='(';  t[3]='\n';  t[4]='\t';
	t[5]=',';  t[6]=';';  t[7]=0;
	make_alfavit(t,alf);
    int res=0;
	
	while( fgets(buf,LEN,fp) )
	{
		command help;
		res=help.parse(buf,word,alf,t);
		if (res>=0)
		{ 
			//printf("RESULT:\n");
			k=help.work(this);
			if(k==0)return;
		}
	}
}

int * groupm::make_alfavit(char * t, int * alf)
{
	int i=0;
    for (i=0;i<(int)strlen(t);i++)
	{
		alf[(unsigned int)t[i]]=1;
	} 
	return alf;
}

void groupm::select(command * f)
{
	int i;
	list_node * current;
	if (f->c_name==LIKE)
	{
		char * words[LEN];
		char buf[LEN];
		int kol=0;
		int param=liker(f->name.get(),words,buf,&kol);
		switch(f->order)
		{
			case 100://name
			{
				for (current=head; current != NULL; current=current->next)
				{
					if (comp_like(current->name.get(),words,param,kol)==0)
						fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);			
				}
				break;
			}
			case 101://name group
			{
				if (f->oper==AND)
				{
					for (current=head; current != NULL; current=current->next)
					{
						if ((comp_like(current->name.get(),words,param,kol)==0)&&(comp_num(current->group,f->group,f->c_group)==0) )
							fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
					}
				}
				else
				{
					for (current=head; current != NULL; current=current->next)
					{
						if ((comp_like(current->name.get(),words,param,kol)==0) || (comp_num(current->group,f->group,f->c_group)==0) )
							fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
					}
				}
				break;
			}
			case 110://name phone
			{
				if (f->oper==AND)
				{
					for (current=head; current != NULL; current=current->next)
					{
						if ((comp_like(current->name.get(),words,param,kol)==0) && (comp_num(current->phone,f->phone,f->c_phone)==0) )
							fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
					}
				}
				else
				{
					for (current=head; current != NULL; current=current->next)
					{
						if ((comp_like(current->name.get(),words,param,kol)==0) || (comp_num(current->phone,f->phone,f->c_phone)==0) )
							fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
					}
				}
				break;
			}
		}
	}
	else
	{
		switch(f->order)
		{
			case 100://name
			{							
				list_node*m;
				
				//int k=(f->name.get()[0]-'A')*RAZN+f->name.get()[1]-'A';
				int k=poiskvmasname(f);
				switch(f->	c_name)
				{
					case EQ:
					{
						m=hash_name[k];
						while(m)
						{
							if(strcmp(m->name.get(),f->name.get())==0)
								fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
							m=m->down_n;
						}
						break;
					}
					case NE:
					{
						for(i=0;i<k;i++)
						{
							m=hash_name[i];
							while(m)
							{
								fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
								m=m->down_n;
							}
						}
						m=hash_name[k];
						while(m)
						{
							if(strcmp(m->name.get(),f->name.get())!=0)
								fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
							m=m->down_n;
						}
						for(i=k+1;i<RAZMNAME;i++)
						{
							m=hash_name[i];
							while(m)
							{
								fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
								m=m->down_n;
							}
						}
						break;
					}
					case LT:
					{
						for(i=0;i<k;i++)
						{
							m=hash_name[i];
							while(m)
							{
								fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
								m=m->down_n;
							}
						}
						
						m=hash_name[k];
						while(m)
						{
							if(strcmp(m->name.get(),f->name.get())<0)
								fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
							m=m->down_n;
						}
						
						break;
					}
					case GT:
					{
						for(i=k+1;i<RAZMNAME;i++)
						{
							m=hash_name[i];
							while(m)
							{
								fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
								m=m->down_n;
							}
						}
						
						m=hash_name[k];
						while(m)
						{
							if(strcmp(m->name.get(),f->name.get())>0)
								fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
							m=m->down_n;
						}
						break;
					}
					case LE:
					{
						for(i=0;i<k;i++)
						{
							m=hash_name[i];
							while(m)
							{
								fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
								m=m->down_n;
							}
						}
						
						m=hash_name[k];
						while(m)
						{
							if(strcmp(m->name.get(),f->name.get())<=0)
								fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
							m=m->down_n;
						}
						break;
					}
					case GE:
					{
						for(i=k+1;i<RAZMNAME;i++)
						{
							m=hash_name[i];
							while(m)
							{
								fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
								m=m->down_n;
							}
						}
						
						m=hash_name[k];
						while(m)
						{
							if(strcmp(m->name.get(),f->name.get())>=0)
								fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
							m=m->down_n;
						}
						break;
					}
					case LIKE:
					{
						break;
					}
					case COND_NONE:
					{
						break;
					}
					
				}
				break;
			}
			case 101://name group
			{
				if (f->oper==AND)
				{
					list_node*m;
					
					//int k=(f->name.get()[0]-'A')*RAZN+f->name.get()[1]-'A';
					int k=poiskvmasname(f);
					switch(f->	c_name)
					{
						case EQ:
						{
							for(int t=0;t<900;t++)
							{
								if(mas[t] && comp_num(t+100,f->group,f->c_group)==0)
								{
									m=mas[t]->hash_name[k];
									while(m)
									{
										if(strcmp(m->name.get(),f->name.get())==0)	
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										m=m->down_name2;
									}
								}
							}
							break;
						}
						case NE:
						{
							for(int t=0;t<900;t++)
							{
								if(mas[t] && comp_num(t+100,f->group,f->c_group)==0)
								{
									for(i=0;i<k;i++)
									{
										m=mas[t]->hash_name[i];
										while(m)
										{
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
											m=m->down_name2;
										}
									}
									m=mas[t]->hash_name[k];
									while(m)
									{
										if(strcmp(m->name.get(),f->name.get())!=0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										m=m->down_name2;
									}
									for(i=k+1;i<RAZMNAME;i++)
									{
										m=mas[t]->hash_name[i];
										while(m)
										{
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
											m=m->down_name2;
										}
									}
								}
							}								
							break;
						}
						case LT:
						{
							for(int t=0;t<900;t++)
							{
								if(mas[t] && comp_num(t+100,f->group,f->c_group)==0)
								{
									for(i=0;i<k;i++)
									{
										m=mas[t]->hash_name[i];
										while(m)
										{
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
											m=m->down_name2;
										}
									}
									
									m=mas[t]->hash_name[k];
									while(m)
									{
										if(strcmp(m->name.get(),f->name.get())<0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										m=m->down_name2;
									}
								}
							}							
							break;
						}
						case GT:
						{
							for(int t=0;t<900;t++)
							{
								if(mas[t] && comp_num(t+100,f->group,f->c_group)==0)
								{
									for(i=k+1;i<RAZMNAME;i++)
									{
										m=mas[t]->hash_name[i];
										while(m)
										{
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
											m=m->down_name2;
										}
									}
									
									m=mas[t]->hash_name[k];
									while(m)
									{
										if(strcmp(m->name.get(),f->name.get())>0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										m=m->down_name2;
									}
								}
							}
							break;
						}
						case LE:
						{
							for(int t=0;t<900;t++)
							{
								if(mas[t] && comp_num(t+100,f->group,f->c_group)==0)
								{
									for(i=0;i<k;i++)
									{
										m=mas[t]->hash_name[i];
										while(m)
										{
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
											m=m->down_name2;
										}
									}
									
									m=mas[t]->hash_name[k];
									while(m)
									{
										if(strcmp(m->name.get(),f->name.get())<=0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										m=m->down_name2;
									}
								}
							}
							break;
						}
						case GE:
						{
							for(int t=0;t<900;t++)
							{
								if(mas[t] && comp_num(t+100,f->group,f->c_group)==0)
								{
									for(i=k+1;i<RAZMNAME;i++)
									{
										m=mas[t]->hash_name[i];
										while(m)
										{
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
											m=m->down_name2;
										}
									}
									
									m=mas[t]->hash_name[k];
									while(m)
									{
										if(strcmp(m->name.get(),f->name.get())>=0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										m=m->down_name2;
									}
								}
							}
							break;
						}
						case LIKE:
						{
							
							break;
						}
						case COND_NONE:
						{
							break;
						}
						
					}
					break;		
				}
				else
				{
					list_node*m;
					
					//int k=(f->name.get()[0]-'A')*RAZN+f->name.get()[1]-'A';
					int k=poiskvmasname(f);
					switch(f->	c_name)
					{
						case EQ:
						{
							m=hash_name[k];
							while(m)
							{
								if(strcmp(m->name.get(),f->name.get())==0)
									if(comp_num(m->group,f->group,f->c_group)!=0)
										fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
								m=m->down_n;
							}
							break;
						}
						case NE:
						{
							for(i=0;i<k;i++)
							{
								m=hash_name[i];
								while(m)
								{
									if(comp_num(m->group,f->group,f->c_group)!=0)
										fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_n;
								}
							}
							
							m=hash_name[k];
							while(m)
							{
								if(strcmp(m->name.get(),f->name.get())!=0)
									if(comp_num(m->group,f->group,f->c_group)!=0)
										fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
								m=m->down_n;
							}

							for(i=k+1;i<RAZMNAME;i++)
							{
								m=hash_name[i];
								while(m)
								{
									if(comp_num(m->group,f->group,f->c_group)!=0)
										fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_n;
								}
							}
							break;
						}
						case LT:
						{
							for(i=0;i<k;i++)
							{
								m=hash_name[i];
								while(m)
								{
									if(comp_num(m->group,f->group,f->c_group)!=0)
										fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_n;
								}
							}
							
							m=hash_name[k];
							while(m)
							{
								if(strcmp(m->name.get(),f->name.get())<0)
									if(comp_num(m->group,f->group,f->c_group)!=0)
										fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
								m=m->down_n;
							}
							
							break;
						}
						case GT:
						{
							for(i=k+1;i<RAZMNAME;i++)
							{
								m=hash_name[i];
								while(m)
								{
									if(comp_num(m->group,f->group,f->c_group)!=0)
										fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_n;
								}
							}
							
							m=hash_name[k];
							while(m)
							{
								if(strcmp(m->name.get(),f->name.get())>0)
									if(comp_num(m->group,f->group,f->c_group)!=0)
										fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
								m=m->down_n;
							}
							break;
						}
						case LE:
						{
							for(i=0;i<k;i++)
							{
								m=hash_name[i];
								while(m)
								{
									if(comp_num(m->group,f->group,f->c_group)!=0)
										fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_n;
								}
							}
							
							m=hash_name[k];
							while(m)
							{
								if(strcmp(m->name.get(),f->name.get())<=0)
									if(comp_num(m->group,f->group,f->c_group)!=0)
										fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
								m=m->down_n;
							}
							break;
						}
						case GE:
						{
							for(i=k+1;i<RAZMNAME;i++)
							{
								m=hash_name[i];
								while(m)
								{
									if(comp_num(m->group,f->group,f->c_group)!=0)
										fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_n;
								}
							}
							
							m=hash_name[k];
							while(m)
							{
								if(strcmp(m->name.get(),f->name.get())>=0)
									if(comp_num(m->group,f->group,f->c_group)!=0)
										fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
								m=m->down_n;
							}
							break;
						}
						case LIKE:
						{
							break;
						}
						case COND_NONE:
						{
							break;
						}
						
					}
					
					switch(f->c_group)
					{
						case EQ:
						{
							if(mas[f->group-100])
							{
								for(current=mas[f->group-100]->head;current!=NULL;current=current->down_group)
									fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
							}
							break;
						}
						case NE:
						{
							for(int t=0;t < (f->group-100);t++)
							{
								if(mas[t])
								{
									for(current=mas[t]->head;current!=NULL;current=current->down_group)
										fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
								}
							}
							for(int t=(f->group-100)+1;t < 900;t++)
							{
								if(mas[t])
								{
									for(current=mas[t]->head;current!=NULL;current=current->down_group)
										fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
								}
							}
							break;
						}
						case LT:
						{
							for(int t=0;t < (f->group-100);t++)
							{
								if(mas[t])
								{
									for(current=mas[t]->head;current!=NULL;current=current->down_group)
										fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
								}
							}
							break;
						}
						case GT:
						{
							for(int t=(f->group-100)+1;t < 900;t++)
							{
								if(mas[t])
								{
									for(current=mas[t]->head;current!=NULL;current=current->down_group)
										fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
								}
							}
							break;
						}
						case LE:
						{
							for(int t=0;t <= (f->group-100);t++)
							{
								if(mas[t])
								{
									for(current=mas[t]->head;current!=NULL;current=current->down_group)
										fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
								}
							}
							break;
						}
						case GE:
						{
							for(int t=(f->group-100);t < 900;t++)
							{
								if(mas[t])
								{
									for(current=mas[t]->head;current!=NULL;current=current->down_group)
										fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
								}
							}
							break;
						}
						case COND_NONE:
						{
							break;
						}
						case LIKE:
						{
							break;
						}
														
					}
					
				}
				break;
			}
			case 110://name phone
			{	
				if (f->oper==AND)
				{
					list_node*m;
					if(f->c_phone==EQ)
					{
						//int k=(f->name.get()[0]-'A')*RAZN+f->name.get()[1]-'A';
						int k=poiskvmasname(f);
						/*int sum=0,num=f->phone;
		
						while(num)
						{
							sum+=num%10;
							num=num/10;
						}
						int pok=sum%mod;*/
						int pok=poiskvmasphoneinsert(f);
						
						switch(f->	c_name)
						{
							case EQ:
							{
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())==0)	
										if(m->modphone==pok)
											if(m->phone==f->phone)
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
					
									m=m->down_n;
								}
								break;
							}
							case NE:
							{
								for(i=0;i<k;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(m->modphone==pok)
											if(m->phone==f->phone)
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										m=m->down_n;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())!=0)
									{
										if(m->modphone==pok)
											if(m->phone==f->phone)
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									}
									m=m->down_n;
								}
								
								for(i=k+1;i<RAZMNAME;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(m->modphone==pok)
											if(m->phone==f->phone)
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										m=m->down_n;
									}
								}								
								break;
							}
							case LT:
							{
								for(i=0;i<k;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(m->modphone==pok)
											if(m->phone==f->phone)
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										m=m->down_n;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())<0)
										if(m->modphone==pok)
											if(m->phone==f->phone)
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_n;
								}
								
								break;
							}
							case GT:
							{
								for(i=k+1;i<RAZMNAME;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(m->modphone==pok)
											if(m->phone==f->phone)
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										m=m->down_n;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())>0)
										if(m->modphone==pok)
											if(m->phone==f->phone)
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_n;
								}
								break;
							}
							case LE:
							{
								for(i=0;i<k;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(m->modphone==pok)
											if(m->phone==f->phone)
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										m=m->down_n;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())<=0)
										if(m->modphone==pok)
											if(m->phone==f->phone)
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_n;
								}
								break;
							}
							case GE:
							{
								for(i=k+1;i<RAZMNAME;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(m->modphone==pok)
											if(m->phone==f->phone)
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										m=m->down_n;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())>=0)
										if(m->modphone==pok)
											if(m->phone==f->phone)
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_n;
								}
								break;
							}
							case LIKE:
							{
								break;
							}
							case COND_NONE:
							{
								break;
							}
							
						}
					}
					else
					{
						list_node*m;
						int k=poiskvmasname(f);
						//int k=(f->name.get()[0]-'A')*RAZN+f->name.get()[1]-'A';
						switch(f->	c_name)
						{
							case EQ:
							{
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())==0)	
										if(comp_num(m->phone,f->phone,f->c_phone)==0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_n;
								}
								break;
							}
							case NE:
							{
								for(i=0;i<k;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(comp_num(m->phone,f->phone,f->c_phone)==0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										m=m->down_n;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())!=0)
										if(comp_num(m->phone,f->phone,f->c_phone)==0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_n;
								}
								
								for(i=k+1;i<RAZMNAME;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(comp_num(m->phone,f->phone,f->c_phone)==0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										m=m->down_n;
									}
								}
								break;
							}
							case LT:
							{
								for(i=0;i<k;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(comp_num(m->phone,f->phone,f->c_phone)==0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										m=m->down_n;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())<0)
										if(comp_num(m->phone,f->phone,f->c_phone)==0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_n;
								}
								
								break;
							}
							case GT:
							{
								for(i=k+1;i<RAZMNAME;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(comp_num(m->phone,f->phone,f->c_phone)==0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										m=m->down_n;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())>0)
										if(comp_num(m->phone,f->phone,f->c_phone)==0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_n;
								}
								break;
							}
							case LE:
							{
								for(i=0;i<k;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(comp_num(m->phone,f->phone,f->c_phone)==0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										m=m->down_n;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())<=0)
										if(comp_num(m->phone,f->phone,f->c_phone)==0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_n;
								}
								break;
							}
							case GE:
							{
								for(i=k+1;i<RAZMNAME;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(comp_num(m->phone,f->phone,f->c_phone)==0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										m=m->down_n;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())>=0)
										if(comp_num(m->phone,f->phone,f->c_phone)==0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_n;
								}
								break;
							}
							case LIKE:
							{								
								break;
							}
							case COND_NONE:
							{
								break;
							}
							
						}
						
					}
								
				}
				else
				{
					list_node*m;
					
					//int k=(f->name.get()[0]-'A')*RAZN+f->name.get()[1]-'A';
					int k=poiskvmasname(f);
					/*int sum=0,num=f->phone;
		
						while(num)
						{
							sum+=num%10;
							num=num/10;
						}
						int pok=sum%mod;*/
						int pok=poiskvmasphoneinsert(f);
					if(f->c_phone==EQ)
					{
						switch(f->	c_name)
						{
							case EQ:
							{
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())==0)
									{
										if(m->modphone==pok)
										{
											if(m->phone!=f->phone)
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										}
										else
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										
									}
									m=m->down_n;
								}
								break;
							}
							case NE:
							{
								for(i=0;i<k;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(m->modphone==pok)
										{
											if(m->phone!=f->phone)
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										}
										else
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										
										m=m->down_n;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())!=0)
									{
										if(m->modphone==pok)
										{
											if(m->phone!=f->phone)
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										}
										else
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									}
									m=m->down_n;
								}
								
								for(i=k+1;i<RAZMNAME;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(m->modphone==pok)
										{
											if(m->phone!=f->phone)
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										}
										else
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										
										m=m->down_n;
									}
								}
								break;
							}
							case LT:
							{
								for(i=0;i<k;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(m->modphone==pok)
										{
											if(m->phone!=f->phone)
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										}
										else
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										
										m=m->down_n;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())<0)
									{
										if(m->modphone==pok)
										{
											if(m->phone!=f->phone)
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										}
										else
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									}
									m=m->down_n;
								}
								
								break;
							}
							case GT:
							{
								for(i=k+1;i<RAZMNAME;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(m->modphone==pok)
										{
											if(m->phone!=f->phone)
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										}
										else
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										
										m=m->down_n;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())>0)
									{
										if(m->modphone==pok)
										{
											if(m->phone!=f->phone)
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										}
										else
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									}
									m=m->down_n;
								}
								break;
							}
							case LE:
							{
								for(i=0;i<k;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(m->modphone==pok)
										{
											if(m->phone!=f->phone)
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										}
										else
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										
										m=m->down_n;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())<=0)
									{
										if(m->modphone==pok)
										{
											if(m->phone!=f->phone)
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										}
										else
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									}
									m=m->down_n;
								}
								break;
							}
							case GE:
							{
								for(i=k+1;i<RAZMNAME;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(m->modphone==pok)
										{
											if(m->phone!=f->phone)
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										}
										else
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										
										m=m->down_n;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())>=0)
									{
										if(m->modphone==pok)
										{
											if(m->phone!=f->phone)
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										}
										else
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									}	
									m=m->down_n;
								}
								break;
							}
							case LIKE:
							{								
								break;
							}
							case COND_NONE:
							{
								break;
							}
							
						}
						
						m=hash_phone[pok];
						while(m)
						{
							if(m->phone==f->phone)
								fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
							m=m->down_p;
						}							
					}
					else
					{
						list_node*m;
					
						//int k=(f->name.get()[0]-'A')*RAZN+f->name.get()[1]-'A';
						int k=poiskvmasname(f);
						switch(f->	c_name)
						{
							case EQ:
							{
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())==0)
										if(comp_num(m->phone,f->phone,f->c_phone)!=0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_n;
								}
								break;
							}
							case NE:
							{
								for(i=0;i<k;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(comp_num(m->phone,f->phone,f->c_phone)!=0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										m=m->down_n;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())!=0)
										if(comp_num(m->phone,f->phone,f->c_phone)!=0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_n;
								}
								
								for(i=k+1;i<RAZMNAME;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(comp_num(m->phone,f->phone,f->c_phone)!=0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										m=m->down_n;
									}
								}
								break;
							}
							case LT:
							{
								for(i=0;i<k;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(comp_num(m->phone,f->phone,f->c_phone)!=0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										m=m->down_n;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())<0)
										if(comp_num(m->phone,f->phone,f->c_phone)!=0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_n;
								}
								
								break;
							}
							case GT:
							{
								for(i=k+1;i<RAZMNAME;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(comp_num(m->phone,f->phone,f->c_phone)!=0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										m=m->down_n;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())>0)
										if(comp_num(m->phone,f->phone,f->c_phone)!=0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_n;
								}
								break;
							}
							case LE:
							{
								for(i=0;i<k;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(comp_num(m->phone,f->phone,f->c_phone)!=0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										m=m->down_n;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())<=0)
										if(comp_num(m->phone,f->phone,f->c_phone)!=0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_n;
								}
								break;
							}
							case GE:
							{
								for(i=k+1;i<RAZMNAME;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(comp_num(m->phone,f->phone,f->c_phone)!=0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										m=m->down_n;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())>=0)
										if(comp_num(m->phone,f->phone,f->c_phone)!=0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_n;
								}
								break;
							}
							case LIKE:
							{								
								break;
							}
							case COND_NONE:
							{
								break;
							}
							
							
						}
						for (current=head; current != NULL; current=current->next)
						{
							if (comp_num(current->phone,f->phone,f->c_phone)==0)
								fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
						}
					}
					
				}
				break;
			}
			case 10://phone
			{
				list_node*m;
				/*int sum=0,num=f->phone;
	
				while(num)
				{
					sum+=num%10;
					num=num/10;
				}
				int k=sum%mod;*/
				
				int k=poiskvmasphoneinsert(f);
				
				switch(f->c_phone)
				{
					case EQ:
					{
						m=hash_phone[k];
						while(m)
						{
							if(m->phone==f->phone)
								fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
							m=m->down_p;
						}
						break;
					}
					case NE:
					{
						for(i=0;i<k;i++)
						{
							m=hash_phone[i];
							while(m)
							{
								fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
								m=m->down_p;
							}
						}
						
						m=hash_phone[k];
						while(m)
						{
							if(m->phone!=f->phone)
								fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
							m=m->down_p;
						}
						
						for(i=k+1;i<mod;i++)
						{
							m=hash_phone[i];
							while(m)
							{
								fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
								m=m->down_p;
							}
						}
						
						break;
					}
					case LT:
					{
						for (current=head; current != NULL; current=current->next)
						{
							if (current->phone < f->phone)
								fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
						}
						break;
					}
					case GT:
					{
						for (current=head; current != NULL; current=current->next)
						{
							if (current->phone > f->phone)
								fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
						}
						break;
					}
					case LE:
					{
						for (current=head; current != NULL; current=current->next)
						{
							if (current->phone <= f->phone)
								fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
						}
						break;
					}
					case GE:
					{
						for (current=head; current != NULL; current=current->next)
						{
							if (current->phone >= f->phone)
								fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
						}
						break;
					}
					case COND_NONE:
					{
						break;
					}
					case LIKE:
					{
						break;
					}

				}
				break;
			}
			case 11://phone group
			{
				list_node * m;
				int pok=poiskvmasphoneinsert(f);
				if (f->oper==AND)
				{	
					switch(f->c_group)
					{
						case EQ:
						{
							int t=f->group-100;
							if(mas[t] )
							{
								if(f->c_phone==EQ)
								{
									m=mas[t]->hash_phone[pok];
									//printf("((((%s %d %d\n",m->name.get(),m->phone,m->group);
									while(m)
									{
										if(m->phone==f->phone)	
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										m=m->down_phone;
									}
								}
								else
								{
									if(f->c_phone==NE)
									{
										for(i=0;i<pok;i++)
										{
											m=mas[t]->hash_phone[i];
											while(m)
											{
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
												m=m->down_phone;
											}
										}
										
										m=mas[t]->hash_phone[pok];
										while(m)
										{
											if(m->phone!=f->phone)
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
											m=m->down_phone;
										}
										
										for(i=pok+1;i<mod;i++)
										{
											m=mas[t]->hash_phone[i];
											while(m)
											{
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
												m=m->down_phone;
											}
										}
									}
									else
									{
										for(current=mas[t]->head;current!=NULL;current=current->down_group)
											if(comp_num(current->phone,f->phone,f->c_phone)==0)
												fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
											
									}
								}
							}								
							break;
						}
						case NE:
						{
							for(int t=0;t < (f->group-100);t++)
							{
								if(mas[t] )
								{
									if(f->c_phone==EQ)
									{
										m=mas[t]->hash_phone[pok];
										//printf("((((%s %d %d\n",m->name.get(),m->phone,m->group);
										while(m)
										{
											if(m->phone==f->phone)	
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
											m=m->down_phone;
										}
									}
									else
									{
										if(f->c_phone==NE)
										{
											for(i=0;i<pok;i++)
											{
												m=mas[t]->hash_phone[i];
												while(m)
												{
													fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
													m=m->down_phone;
												}
											}
											
											m=mas[t]->hash_phone[pok];
											while(m)
											{
												if(m->phone!=f->phone)
													fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
												m=m->down_phone;
											}
											
											for(i=pok+1;i<mod;i++)
											{
												m=mas[t]->hash_phone[i];
												while(m)
												{
													fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
													m=m->down_phone;
												}
											}
										}
										else
										{
											for(current=mas[t]->head;current!=NULL;current=current->down_group)
												if(comp_num(current->phone,f->phone,f->c_phone)==0)
													fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
												
										}
									}
								}
							}
							for(int t=(f->group-100)+1;t < 900;t++)
							{
								if(mas[t] )
								{
									if(f->c_phone==EQ)
									{
										m=mas[t]->hash_phone[pok];
										//printf("((((%s %d %d\n",m->name.get(),m->phone,m->group);
										while(m)
										{
											if(m->phone==f->phone)	
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
											m=m->down_phone;
										}
									}
									else
									{
										if(f->c_phone==NE)
										{
											for(i=0;i<pok;i++)
											{
												m=mas[t]->hash_phone[i];
												while(m)
												{
													fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
													m=m->down_phone;
												}
											}
											
											m=mas[t]->hash_phone[pok];
											while(m)
											{
												if(m->phone!=f->phone)
													fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
												m=m->down_phone;
											}
											
											for(i=pok+1;i<mod;i++)
											{
												m=mas[t]->hash_phone[i];
												while(m)
												{
													fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
													m=m->down_phone;
												}
											}
										}
										else
										{
											for(current=mas[t]->head;current!=NULL;current=current->down_group)
												if(comp_num(current->phone,f->phone,f->c_phone)==0)
													fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
												
										}
									}
								}
							}
							
							break;
						}
						case LT:
						{
							for(int t=0;t < (f->group-100);t++)
							{
								if(mas[t] )
								{
									if(f->c_phone==EQ)
									{
										m=mas[t]->hash_phone[pok];
										//printf("((((%s %d %d\n",m->name.get(),m->phone,m->group);
										while(m)
										{
											if(m->phone==f->phone)	
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
											m=m->down_phone;
										}
									}
									else
									{
										if(f->c_phone==NE)
										{
											for(i=0;i<pok;i++)
											{
												m=mas[t]->hash_phone[i];
												while(m)
												{
													fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
													m=m->down_phone;
												}
											}
											
											m=mas[t]->hash_phone[pok];
											while(m)
											{
												if(m->phone!=f->phone)
													fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
												m=m->down_phone;
											}
											
											for(i=pok+1;i<mod;i++)
											{
												m=mas[t]->hash_phone[i];
												while(m)
												{
													fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
													m=m->down_phone;
												}
											}
										}
										else
										{
											for(current=mas[t]->head;current!=NULL;current=current->down_group)
												if(comp_num(current->phone,f->phone,f->c_phone)==0)
													fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
												
										}
									}
								}
							}
							break;
						}
						case GT:
						{
							for(int t=(f->group-100)+1;t < 900;t++)
							{
								if(mas[t] )
								{
									if(f->c_phone==EQ)
									{
										m=mas[t]->hash_phone[pok];
										//printf("((((%s %d %d\n",m->name.get(),m->phone,m->group);
										while(m)
										{
											if(m->phone==f->phone)	
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
											m=m->down_phone;
										}
									}
									else
									{
										if(f->c_phone==NE)
										{
											for(i=0;i<pok;i++)
											{
												m=mas[t]->hash_phone[i];
												while(m)
												{
													fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
													m=m->down_phone;
												}
											}
											
											m=mas[t]->hash_phone[pok];
											while(m)
											{
												if(m->phone!=f->phone)
													fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
												m=m->down_phone;
											}
											
											for(i=pok+1;i<mod;i++)
											{
												m=mas[t]->hash_phone[i];
												while(m)
												{
													fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
													m=m->down_phone;
												}
											}
										}
										else
										{
											for(current=mas[t]->head;current!=NULL;current=current->down_group)
												if(comp_num(current->phone,f->phone,f->c_phone)==0)
													fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
												
										}
									}
								}

							}
							break;
						}
						case LE:
						{
							for(int t=0;t <= (f->group-100);t++)
							{
								if(mas[t] )
								{
									if(f->c_phone==EQ)
									{
										m=mas[t]->hash_phone[pok];
										//printf("((((%s %d %d\n",m->name.get(),m->phone,m->group);
										while(m)
										{
											if(m->phone==f->phone)	
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
											m=m->down_phone;
										}
									}
									else
									{
										if(f->c_phone==NE)
										{
											for(i=0;i<pok;i++)
											{
												m=mas[t]->hash_phone[i];
												while(m)
												{
													fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
													m=m->down_phone;
												}
											}
											
											m=mas[t]->hash_phone[pok];
											while(m)
											{
												if(m->phone!=f->phone)
													fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
												m=m->down_phone;
											}
											
											for(i=pok+1;i<mod;i++)
											{
												m=mas[t]->hash_phone[i];
												while(m)
												{
													fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
													m=m->down_phone;
												}
											}
										}
										else
										{
											for(current=mas[t]->head;current!=NULL;current=current->down_group)
												if(comp_num(current->phone,f->phone,f->c_phone)==0)
													fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
												
										}
									}
								}								
							}
							break;
						}
						case GE:
						{
							for(int t=(f->group-100);t < 900;t++)
							{
								if(mas[t] )
								{
									if(f->c_phone==EQ)
									{
										m=mas[t]->hash_phone[pok];
										//printf("((((%s %d %d\n",m->name.get(),m->phone,m->group);
										while(m)
										{
											if(m->phone==f->phone)	
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
											m=m->down_phone;
										}
									}
									else
									{
										if(f->c_phone==NE)
										{
											for(i=0;i<pok;i++)
											{
												m=mas[t]->hash_phone[i];
												while(m)
												{
													fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
													m=m->down_phone;
												}
											}
											
											m=mas[t]->hash_phone[pok];
											while(m)
											{
												if(m->phone!=f->phone)
													fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
												m=m->down_phone;
											}
											
											for(i=pok+1;i<mod;i++)
											{
												m=mas[t]->hash_phone[i];
												while(m)
												{
													fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
													m=m->down_phone;
												}
											}
										}
										else
										{
											for(current=mas[t]->head;current!=NULL;current=current->down_group)
												if(comp_num(current->phone,f->phone,f->c_phone)==0)
													fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
												
										}
									}
								}

							}
							break;
						}
						case COND_NONE:
						{
							break;
						}
						case LIKE:
						{
							break;
						}

					}
					
				}
				else
				{
					list_node*m;
					//int sum=0,num=f->phone;
		
					/*while(num)
					{
						sum+=num%10;
						num=num/10;
					}
					int k=sum%mod;*/
					
					int k=poiskvmasphoneinsert(f);
					
					switch(f->c_phone)
					{
						case EQ:
						{
							for(int t=0;t<900;t++)
							{
								if(mas[t])
								{
									if(comp_num(t+100,f->group,f->c_group)==0)
										for(current=mas[t]->head;current!=NULL;current=current->down_group)
											fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
									else
									{
										m=mas[t]->hash_phone[k];
										while(m)
										{
											if(m->phone==f->phone)
											{
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
											}
											m=m->down_phone;
										}
									}
								}
							}
							break;
						}
						case NE:
						{
							for(int t=0;t<900;t++)
							{
								if(mas[t])
								{
									if(comp_num(t+100,f->group,f->c_group)==0)
										for(current=mas[t]->head;current!=NULL;current=current->down_group)
											fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
									else
									{									
										for(i=0;i<k;i++)
										{
											m=mas[t]->hash_phone[i];
											while(m)
											{
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
												m=m->down_phone;
											}
										}
										m=mas[t]->hash_phone[k];
										while(m)
										{
											if(m->phone!=f->phone)
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
											m=m->down_phone;
										}
										for(i=k+1;i<mod;i++)
										{
											m=mas[t]->hash_phone[i];
											while(m)
											{
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
												m=m->down_phone;
											}
										}
										
									}
								}
							}								
							break;
						}
						case LT:
						{
							for(int t=0;t<900;t++)
							{
								if(mas[t])
								{
									if(comp_num(t+100,f->group,f->c_group)==0)
										for(current=mas[t]->head;current!=NULL;current=current->down_group)
											fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
									else
									{
										for(current=mas[t]->head;current!=NULL;current=current->down_group)
										{
											if(current->phone < f->phone)
												fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
										}
									}
								}
							}
							break;
						}
						case GT:
						{
							for(int t=0;t<900;t++)
							{
								if(mas[t])
								{
									if(comp_num(t+100,f->group,f->c_group)==0)
										for(current=mas[t]->head;current!=NULL;current=current->down_group)
											fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
									else
									{
										for(current=mas[t]->head;current!=NULL;current=current->down_group)
										{
											if(current->phone > f->phone)
												fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
										}
									}
								}
							}
							break;
						}
						case LE:
						{
							for(int t=0;t<900;t++)
							{
								if(mas[t])
								{
									if(comp_num(t+100,f->group,f->c_group)==0)
										for(current=mas[t]->head;current!=NULL;current=current->down_group)
											fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
									else
									{
										for(current=mas[t]->head;current!=NULL;current=current->down_group)
										{
											if(current->phone <= f->phone)
												fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
										}
									}
								}
							}
							break;
						}
						case GE:
						{
							for(int t=0;t<900;t++)
							{
								if(mas[t])
								{
									if(comp_num(t+100,f->group,f->c_group)==0)
										for(current=mas[t]->head;current!=NULL;current=current->down_group)
											fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
									else
									{
										for(current=mas[t]->head;current!=NULL;current=current->down_group)
										{
											if(current->phone >= f->phone)
												fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
										}
									}
								}
							}
							break;
						}
						case COND_NONE:
						{
							break;
						}
						case LIKE:
						{
							break;
						}

					}
				}
				break;
			}
			case 1://group
			{
				switch(f->c_group)
				{
					case EQ:
					{
						if(mas[f->group-100])
						{
							for(current=mas[f->group-100]->head;current!=NULL;current=current->down_group)
								fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
						}
						break;
					}
					case NE:
					{
						for(int t=0;t < (f->group-100);t++)
						{
							if(mas[t])
							{
								for(current=mas[t]->head;current!=NULL;current=current->down_group)
									fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
							}
						}
						for(int t=(f->group-100)+1;t < 900;t++)
						{
							if(mas[t])
							{
								for(current=mas[t]->head;current!=NULL;current=current->down_group)
									fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
							}
						}
						break;
					}
					case LT:
					{
						for(int t=0;t < (f->group-100);t++)
						{
							if(mas[t])
							{
								for(current=mas[t]->head;current!=NULL;current=current->down_group)
									fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
							}
						}
						break;
					}
					case GT:
					{
						for(int t=(f->group-100)+1;t < 900;t++)
						{
							if(mas[t])
							{
								for(current=mas[t]->head;current!=NULL;current=current->down_group)
									fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
							}
						}
						break;
					}
					case LE:
					{
						for(int t=0;t <= (f->group-100);t++)
						{
							if(mas[t])
							{
								for(current=mas[t]->head;current!=NULL;current=current->down_group)
									fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
							}
						}
						break;
					}
					case GE:
					{
						for(int t=(f->group-100);t < 900;t++)
						{
							if(mas[t])
							{
								for(current=mas[t]->head;current!=NULL;current=current->down_group)
									fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
							}
						}
						break;
					}
					case COND_NONE:
					{
						break;
					}
					case LIKE:
					{
						break;
					}
				}
				break;
			}
			case 0:
			{
				for (current=head; current != NULL; current=current->next)
				{
					fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
				}
				break;
			}
		}
	}

}

void groupm::delete_n(command * f)
{
	list_node * a;
	list_node *current;
	int i;
	if (f->c_name==LIKE)
	{
		char * words[LEN];
		char buf[LEN];
		int kol=0;
		int param=liker(f->name.get(),words,buf,&kol);
		switch(f->order)
		{
			case 100:
			{
				for (current=head; current != NULL; )
				{
					if (comp_like(current->name.get(),words,param,kol)==0)
					{
						a=current;
		                current=current->next;
						delete_current( a );
					}
                    else
                    {
                        current=current->next;
                    }	
				}
				break;
			}
			case 101:
			{
				if (f->oper==AND)
				{
					for (current=head; current != NULL; )
					{
						if ((comp_like(current->name.get(),words,param,kol)==0)&&(comp_num(current->group,f->group,f->c_group)==0) )
						{
							a=current;
				            current=current->next;
							delete_current( a );
						}
		                else
		                {
		                    current=current->next;
		                }
					}
				}
				else
				{
					for (current=head; current != NULL;)
					{
						if ((comp_like(current->name.get(),words,param,kol)==0) || (comp_num(current->group,f->group,f->c_group)==0) )
						{
							a=current;
				            current=current->next;
							delete_current( a );
						}
		                else
		                {
		                    current=current->next;
		                }
					}
				}
				break;
			}
			case 110:
			{
				if (f->oper==AND)
				{
					for (current=head; current != NULL; )
					{
						if ((comp_like(current->name.get(),words,param,kol)==0) && (comp_num(current->phone,f->phone,f->c_phone)==0) )
						{
							a=current;
				            current=current->next;
							delete_current( a );
						}
		                else
		                {
		                    current=current->next;
		                }
					}
				}
				else
				{
					for (current=head; current != NULL; )
					{
						if ((comp_like(current->name.get(),words,param,kol)==0) || (comp_num(current->phone,f->phone,f->c_phone)==0) )
						{
							a=current;
				            current=current->next;
							delete_current( a );
						}
		                else
		                {
		                    current=current->next;
		                }
					}
				}
				break;
			}
		}
	}
	else
	{
		switch(f->order)
		{
			case 100://name
			{
				list_node*m;
				
				//int k=(f->name.get()[0]-'A')*RAZN+f->name.get()[1]-'A';
				int k=poiskvmasname(f);
				switch(f->	c_name)
				{
					case EQ:
					{
						m=hash_name[k];
						while(m)
						{
							if(strcmp(m->name.get(),f->name.get())==0)
							{
								a=m;
								m=m->down_n;
								delete_current(a);
							}
							else
								m=m->down_n;
						}
						break;
					}
					case NE:
					{
						for(i=0;i<k;i++)
						{
							m=hash_name[i];
							while(m)
							{
								a=m;
								m=m->down_n;
								delete_current(a);
							}
						}
						m=hash_name[k];
						while(m)
						{
							if(strcmp(m->name.get(),f->name.get())!=0)
							{
								a=m;
								m=m->down_n;
								delete_current(a);
							}
							else
								m=m->down_n;
						}
						for(i=k+1;i<RAZMNAME;i++)
						{
							m=hash_name[i];
							while(m)
							{
								a=m;
								m=m->down_n;
								delete_current(a);
							}
						}
						break;
					}
					case LT:
					{
						for(i=0;i<k;i++)
						{
							m=hash_name[i];
							while(m)
							{
								a=m;
								m=m->down_n;
								delete_current(a);
							}
						}
						
						m=hash_name[k];
						while(m)
						{
							if(strcmp(m->name.get(),f->name.get())<0)
							{
								a=m;
								m=m->down_n;
								delete_current(a);
							}
							else
								m=m->down_n;
						}
						
						break;
					}
					case GT:
					{
						for(i=k+1;i<RAZMNAME;i++)
						{
							m=hash_name[i];
							while(m)
							{
								a=m;
								m=m->down_n;
								delete_current(a);
							}
						}
						
						m=hash_name[k];
						while(m)
						{
							if(strcmp(m->name.get(),f->name.get())>0)
							{
								a=m;
								m=m->down_n;
								delete_current(a);
							}
							else
								m=m->down_n;
						}
						break;
					}
					case LE:
					{
						for(i=0;i<k;i++)
						{
							m=hash_name[i];
							while(m)
							{
								a=m;
								m=m->down_n;
								delete_current(a);
							}
						}
						
						m=hash_name[k];
						while(m)
						{
							if(strcmp(m->name.get(),f->name.get())<=0)
							{
								a=m;
								m=m->down_n;
								delete_current(a);
							}
							else
								m=m->down_n;
						}
						break;
					}
					case GE:
					{
						for(i=k+1;i<RAZMNAME;i++)
						{
							m=hash_name[i];
							while(m)
							{
								a=m;
								m=m->down_n;
								delete_current(a);
							}
						}
						
						m=hash_name[k];
						while(m)
						{
							if(strcmp(m->name.get(),f->name.get())>=0)
							{
								a=m;
								m=m->down_n;
								delete_current(a);
							}
							else
								m=m->down_n;
						}
						break;
					}
					case LIKE:
					{
						break;
					}
					case COND_NONE:
					{
						break;
					}
					
				}
				break;
			}
			case 101://name group
			{
				if (f->oper==AND)
				{
					list_node *m;
					//int k=(f->name.get()[0]-'A')*RAZN+f->name.get()[1]-'A';
					int k=poiskvmasname(f);
					switch(f->	c_name)
					{
						case EQ:
						{
							for(int t=0;t<900;t++)
							{
								if(mas[t] && comp_num(t+100,f->group,f->c_group)==0)
								{
									m=mas[t]->hash_name[k];
									while(m)
									{
										if(strcmp(m->name.get(),f->name.get())==0)
										{									
												a=m;
												m=m->down_name2;
												delete_current(a);
										}
										else
											m=m->down_name2;
									}
								}
							}
							break;
						}
						case NE:
						{
							for(int t=0;t<900;t++)
							{
								if(mas[t] && comp_num(t+100,f->group,f->c_group)==0)
								{
									for(i=0;i<k;i++)
									{
										if(!mas[t])break;
										m=mas[t]->hash_name[i];
										while(m)
										{
											a=m;
											m=m->down_name2;
											delete_current(a);
											
										}
									}
									if(!mas[t])break;
									m=mas[t]->hash_name[k];
									while(m)
									{
										if(strcmp(m->name.get(),f->name.get())!=0)
										{
											a=m;
											m=m->down_name2;
											delete_current(a);
										}
										else
											m=m->down_name2;
									}
									for(i=k+1;i<RAZMNAME;i++)
									{
										if(!mas[t])break;
										m=mas[t]->hash_name[i];
										while(m)
										{
											a=m;
											m=m->down_name2;
											delete_current(a);	
										}
									}									
								}
							}								
							break;
						}
						case LT:
						{
							for(int t=0;t<900;t++)
							{
								if(mas[t] && comp_num(t+100,f->group,f->c_group)==0)
								{
									for(i=0;i<k;i++)
									{
										if(mas[t])
										{
											m=mas[t]->hash_name[i];
											while(m)
											{
												a=m;
												m=m->down_name2;
												delete_current(a);
											}
										}
									}
									if(mas[t])
									{
										m=mas[t]->hash_name[k];
										while(m)
										{
											if(strcmp(m->name.get(),f->name.get())<0)
											{
												a=m;
												m=m->down_name2;
												delete_current(a);
											}
											else
												m=m->down_name2;
										}
									}
								}
							}
							
							break;
						}
						case GT:
						{
							for(int t=0;t<900;t++)
							{
								if(mas[t] && comp_num(t+100,f->group,f->c_group)==0)
								{
									for(i=k+1;i<RAZMNAME;i++)
									{
										if(!mas[t])break;
										m=mas[t]->hash_name[i];
										while(m)
										{
											a=m;
											m=m->down_name2;
											delete_current(a);
										}
									}
									if(mas[t])
									{
										m=mas[t]->hash_name[k];
										while(m)
										{
											if(strcmp(m->name.get(),f->name.get())>0)
											{
												a=m;
												m=m->down_name2;
												delete_current(a);
											}
											else
												m=m->down_name2;
										}
									}
								}
							}
							break;
						}
						case LE:
						{
							for(int t=0;t<900;t++)
							{
								if(mas[t] && comp_num(t+100,f->group,f->c_group)==0)
								{
									for(i=0;i<k;i++)
									{
										if(!mas[t])break;
										m=mas[t]->hash_name[i];
										while(m)
										{
											a=m;
											m=m->down_name2;
											delete_current(a);
										}
									}
									if(mas[t])
									{
										m=mas[t]->hash_name[k];
										while(m)
										{
											if(strcmp(m->name.get(),f->name.get())<=0)
											{
												a=m;
												m=m->down_name2;
												delete_current(a);
											}
											else
												m=m->down_name2;
										}
									}
								}
							}
							break;
						}
						case GE:
						{
							for(int t=0;t<900;t++)
							{
								if(mas[t] && comp_num(t+100,f->group,f->c_group)==0)
								{
									for(i=k+1;i<RAZMNAME;i++)
									{
										if(!mas[t])break;
										m=mas[t]->hash_name[i];
										while(m)
										{
											a=m;
											m=m->down_name2;
											delete_current(a);
										}
									}
									if(mas[t])
									{
										m=mas[t]->hash_name[k];
										while(m)
										{
											if(strcmp(m->name.get(),f->name.get())>=0)
											{
												a=m;
												m=m->down_name2;
												delete_current(a);
											}
											else
												m=m->down_name2;
										}
									}
								}
							}
							break;
						}
						case LIKE:
						{							
							break;
						}
						case COND_NONE:
						{
							break;
						}
						
					}
					break;		
				}
				else
				{
					list_node*m;
					
					//int k=(f->name.get()[0]-'A')*RAZN+f->name.get()[1]-'A';
					int k=poiskvmasname(f);
					switch(f->	c_name)
					{
						case EQ:
						{
							m=hash_name[k];
							while(m)
							{
								if(strcmp(m->name.get(),f->name.get())==0)
								{
									if(comp_num(m->group,f->group,f->c_group)!=0)
									{
										a=m;
										m=m->down_n;
										delete_current(a);
									}
									else
										m=m->down_n;
								}
								else
									m=m->down_n;
							}
							break;
						}
						case NE:
						{
							for(i=0;i<k;i++)
							{
								m=hash_name[i];
								while(m)
								{
									if(comp_num(m->group,f->group,f->c_group)!=0)
									{
										a=m;
										m=m->down_n;
										delete_current(a);
									}
									else
										m=m->down_n;
								}
							}
							
							m=hash_name[k];
							while(m)
							{
								if(strcmp(m->name.get(),f->name.get())!=0)
								{
									if(comp_num(m->group,f->group,f->c_group)!=0)
									{
										a=m;
										m=m->down_n;
										delete_current(a);
									}
									else
										m=m->down_n;
								}
								else
									m=m->down_n;
							}

							for(i=k+1;i<RAZMNAME;i++)
							{
								m=hash_name[i];
								while(m)
								{
									if(comp_num(m->group,f->group,f->c_group)!=0)
									{
										a=m;
										m=m->down_n;
										delete_current(a);
									}
									else
										m=m->down_n;
								}
							}
							break;
						}
						case LT:
						{
							for(i=0;i<k;i++)
							{
								m=hash_name[i];
								while(m)
								{
									if(comp_num(m->group,f->group,f->c_group)!=0)
									{
										a=m;
										m=m->down_n;
										delete_current(a);
									}
									else
										m=m->down_n;
								}
							}
							
							m=hash_name[k];
							while(m)
							{
								if(strcmp(m->name.get(),f->name.get())<0)
								{
									if(comp_num(m->group,f->group,f->c_group)!=0)
									{
										a=m;
										m=m->down_n;
										delete_current(a);
									}
									else
										m=m->down_n;
								}
								else
									m=m->down_n;
							}							
							break;
						}
						case GT:
						{
							for(i=k+1;i<RAZMNAME;i++)
							{
								m=hash_name[i];
								while(m)
								{
									if(comp_num(m->group,f->group,f->c_group)!=0)
									{
										a=m;
										m=m->down_n;
										delete_current(a);
									}
									else
										m=m->down_n;
								}
							}
							
							m=hash_name[k];
							while(m)
							{
								if(strcmp(m->name.get(),f->name.get())>0)
								{
									if(comp_num(m->group,f->group,f->c_group)!=0)
									{
										a=m;
										m=m->down_n;
										delete_current(a);
									}
									else
										m=m->down_n;
								}
								else
									m=m->down_n;
							}
							break;
						}
						case LE:
						{
							for(i=0;i<k;i++)
							{
								m=hash_name[i];
								while(m)
								{
									if(comp_num(m->group,f->group,f->c_group)!=0)
									{
										a=m;
										m=m->down_n;
										delete_current(a);
									}
									else
										m=m->down_n;
								}
							}
							
							m=hash_name[k];
							while(m)
							{
								if(strcmp(m->name.get(),f->name.get())<=0)
								{
									if(comp_num(m->group,f->group,f->c_group)!=0)
									{
										a=m;
										m=m->down_n;
										delete_current(a);
									}
									else
										m=m->down_n;
								}
								else
									m=m->down_n;
							}
							break;
						}
						case GE:
						{
							for(i=k+1;i<RAZMNAME;i++)
							{
								m=hash_name[i];
								while(m)
								{
									if(comp_num(m->group,f->group,f->c_group)!=0)
									{
										a=m;
										m=m->down_n;
										delete_current(a);
									}
									else
										m=m->down_n;
								}
							}
							
							m=hash_name[k];
							while(m)
							{
								if(strcmp(m->name.get(),f->name.get())>=0)
								{
									if(comp_num(m->group,f->group,f->c_group)!=0)
									{
										a=m;
										m=m->down_n;
										delete_current(a);
									}
									else
										m=m->down_n;
								}
								else
									m=m->down_n;
							}
							break;
						}
						case LIKE:
						{
							break;
						}
						case COND_NONE:
						{
							break;
						}
						
					}
					
					switch(f->c_group)
					{
						case EQ:
						{
							if(mas[f->group-100])
							{
								for(current=mas[f->group-100]->head;current!=NULL;)
								{
									a=current;
									current=current->down_group;
									delete_current(a);
								}
							}
							break;
						}
						case NE:
						{
							for(int t=0;t < (f->group-100);t++)
							{
								if(mas[t])
								{
									for(current=mas[t]->head;current!=NULL;)
									{
										a=current;
										current=current->down_group;
										delete_current(a);
									}
								}
							}
							for(int t=(f->group-100)+1;t < 900;t++)
							{
								if(mas[t])
								{
									for(current=mas[t]->head;current!=NULL;)
									{
										a=current;
										current=current->down_group;
										delete_current(a);
									}
								}
							}
							break;
						}
						case LT:
						{
							for(int t=0;t < (f->group-100);t++)
							{
								if(mas[t])
								{
									for(current=mas[t]->head;current!=NULL;)
									{
										a=current;
										current=current->down_group;
										delete_current(a);
									}
								}
							}
							break;
						}
						case GT:
						{
							for(int t=(f->group-100)+1;t < 900;t++)
							{
								if(mas[t])
								{
									for(current=mas[t]->head;current!=NULL;)
									{
										a=current;
										current=current->down_group;
										delete_current(a);
									}
								}
							}
							break;
						}
						case LE:
						{
							for(int t=0;t <= (f->group-100);t++)
							{
								if(mas[t])
								{
									for(current=mas[t]->head;current!=NULL;)
									{
										a=current;
										current=current->down_group;
										delete_current(a);
									}
								}
							}
							break;
						}
						case GE:
						{
							for(int t=(f->group-100);t < 900;t++)
							{
								if(mas[t])
								{
									for(current=mas[t]->head;current!=NULL;)
									{
										a=current;
										current=current->down_group;
										delete_current(a);
									}
								}
							}
							break;
						}
						case COND_NONE:
						{
							break;
						}
						case LIKE:
						{
							break;
						}
														
					}
					
				}
				break;
			}
			case 110://name phone
			{
				if (f->oper==AND)
				{
					list_node*m;
					if(f->c_phone==EQ)
					{
						//int k=(f->name.get()[0]-'A')*RAZN+f->name.get()[1]-'A';
						int k=poiskvmasname(f);
						/*int sum=0,num=f->phone;
		
						while(num)
						{
							sum+=num%10;
							num=num/10;
						}
						int pok=sum%mod;*/
						int pok=poiskvmasphoneinsert(f);
						
						switch(f->	c_name)
						{
							case EQ:
							{
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())==0)	
									{
										if(m->modphone==pok)
										{
											if(m->phone==f->phone)
											{
												a=m;
												m=m->down_n;
												delete_current(a);
											}
											else
												m=m->down_n;
										}
										else
											m=m->down_n;
									}
									else
										m=m->down_n;
								}
								break;
							}
							case NE:
							{
								for(i=0;i<k;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(m->modphone==pok)
										{
											if(m->phone==f->phone)
											{
												a=m;
												m=m->down_n;
												delete_current(a);
											}
											else
												m=m->down_n;
										}
										else
											m=m->down_n;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())!=0)
									{
										if(m->modphone==pok)
										{
											if(m->phone==f->phone)
											{
												a=m;
												m=m->down_n;
												delete_current(a);
											}
											else
												m=m->down_n;
										}
										else
											m=m->down_n;
									}
									else
										m=m->down_n;
								}
								
								for(i=k+1;i<RAZMNAME;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(m->modphone==pok)
										{
											if(m->phone==f->phone)
											{
												a=m;
												m=m->down_n;
												delete_current(a);
											}
											else
												m=m->down_n;
										}
										else
											m=m->down_n;
									}
								}								
								break;
							}
							case LT:
							{
								for(i=0;i<k;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(m->modphone==pok)
										{
											if(m->phone==f->phone)
											{
												a=m;
												m=m->down_n;
												delete_current(a);
											}
											else
												m=m->down_n;
										}
										else
											m=m->down_n;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())<0)
									{
										if(m->modphone==pok)
										{
											if(m->phone==f->phone)
											{
												a=m;
												m=m->down_n;
												delete_current(a);
											}
											else
												m=m->down_n;
										}
										else
											m=m->down_n;
									}
									else
										m=m->down_n;
								}
								
								break;
							}
							case GT:
							{
								for(i=k+1;i<RAZMNAME;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(m->modphone==pok)
										{
											if(m->phone==f->phone)
											{
												a=m;
												m=m->down_n;
												delete_current(a);
											}
											else
												m=m->down_n;
										}
										else
											m=m->down_n;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())>0)
									{
										if(m->modphone==pok)
										{
											if(m->phone==f->phone)
											{
												a=m;
												m=m->down_n;
												delete_current(a);
											}
											else
												m=m->down_n;
										}
										else
											m=m->down_n;
									}
									else
										m=m->down_n;
								}
								break;
							}
							case LE:
							{
								for(i=0;i<k;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(m->modphone==pok)
										{
											if(m->phone==f->phone)
											{
												a=m;
												m=m->down_n;
												delete_current(a);
											}
											else
												m=m->down_n;
										}
										else
											m=m->down_n;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())<=0)
									{
										if(m->modphone==pok)
										{
											if(m->phone==f->phone)
											{
												a=m;
												m=m->down_n;
												delete_current(a);
											}
											else
												m=m->down_n;
										}
										else
											m=m->down_n;
									}
									else
										m=m->down_n;
								}
								break;
							}
							case GE:
							{
								for(i=k+1;i<RAZMNAME;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(m->modphone==pok)
										{
											if(m->phone==f->phone)
											{
												a=m;
												m=m->down_n;
												delete_current(a);
											}
											else
												m=m->down_n;
										}
										else
											m=m->down_n;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())>=0)
									{
										if(m->modphone==pok)
										{
											if(m->phone==f->phone)
											{
												a=m;
												m=m->down_n;
												delete_current(a);
											}
											else
												m=m->down_n;
										}
										else
											m=m->down_n;
									}
									else
										m=m->down_n;
								}
								break;
							}
							case LIKE:
							{
								break;
							}
							case COND_NONE:
							{
								break;
							}
							
						}
					}
					else
					{
						list_node*m;
						
						///int k=(f->name.get()[0]-'A')*RAZN+f->name.get()[1]-'A';
						int k=poiskvmasname(f);
						switch(f->	c_name)
						{
							case EQ:
							{
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())==0)	
									{
										if(comp_num(m->phone,f->phone,f->c_phone)==0)
										{
											a=m;
											m=m->down_n;
											delete_current(a);
										}
										else
											m=m->down_n;
									}
									else
										m=m->down_n;
								}
								break;
							}
							case NE:
							{
								for(i=0;i<k;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(comp_num(m->phone,f->phone,f->c_phone)==0)
										{
											a=m;
											m=m->down_n;
											delete_current(a);
										}
										else
											m=m->down_n;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())!=0)
									{
										if(comp_num(m->phone,f->phone,f->c_phone)==0)
										{
											a=m;
											m=m->down_n;
											delete_current(a);
										}
										else
											m=m->down_n;
									}
									else
										m=m->down_n;
								}
								
								for(i=k+1;i<RAZMNAME;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(comp_num(m->phone,f->phone,f->c_phone)==0)
										{
											a=m;
											m=m->down_n;
											delete_current(a);
										}
										else
											m=m->down_n;
									}
								}
								break;
							}
							case LT:
							{
								for(i=0;i<k;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(comp_num(m->phone,f->phone,f->c_phone)==0)
										{
											a=m;
											m=m->down_n;
											delete_current(a);
										}
										else
											m=m->down_n;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())<0)
									{
										if(comp_num(m->phone,f->phone,f->c_phone)==0)
										{
											a=m;
											m=m->down_n;
											delete_current(a);
										}
										else
											m=m->down_n;
									}
									else
										m=m->down_n;
								}
								
								break;
							}
							case GT:
							{
								for(i=k+1;i<RAZMNAME;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(comp_num(m->phone,f->phone,f->c_phone)==0)
										{
											a=m;
											m=m->down_n;
											delete_current(a);
										}
										else
											m=m->down_n;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())>0)
									{
										if(comp_num(m->phone,f->phone,f->c_phone)==0)
										{
											a=m;
											m=m->down_n;
											delete_current(a);
										}
										else
											m=m->down_n;
									}
									else
										m=m->down_n;
								}
								break;
							}
							case LE:
							{
								for(i=0;i<k;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(comp_num(m->phone,f->phone,f->c_phone)==0)
										{
											a=m;
											m=m->down_n;
											delete_current(a);
										}
										else
											m=m->down_n;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())<=0)
									{
										if(comp_num(m->phone,f->phone,f->c_phone)==0)
										{
											a=m;
											m=m->down_n;
											delete_current(a);
										}
										else
											m=m->down_n;
									}
									else
										m=m->down_n;
								}
								break;
							}
							case GE:
							{
								for(i=k+1;i<RAZMNAME;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(comp_num(m->phone,f->phone,f->c_phone)==0)
										{
											a=m;
											m=m->down_n;
											delete_current(a);
										}
										else
											m=m->down_n;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())>=0)
									{
										if(comp_num(m->phone,f->phone,f->c_phone)==0)
										{
											a=m;
											m=m->down_n;
											delete_current(a);
										}
										else
											m=m->down_n;
									}
									else
										m=m->down_n;
								}
								break;
							}
							case LIKE:
							{								
								break;
							}
							case COND_NONE:
							{
								break;
							}
							
						}
						
					}
								
				}
				else
				{
					list_node*m;
					
					//int k=(f->name.get()[0]-'A')*RAZN+f->name.get()[1]-'A';
					int k=poiskvmasname(f);
					/*int sum=0,num=f->phone;
		
						while(num)
						{
							sum+=num%10;
							num=num/10;
						}
						int pok=sum%mod;*/
						int pok=poiskvmasphoneinsert(f);
					if(f->c_phone==EQ)
					{
						switch(f->	c_name)
						{
							case EQ:
							{
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())==0)
									{
										if(m->modphone==pok)
										{
											if(m->phone!=f->phone)
											{
												a=m;
												m=m->down_n;
												delete_current(a);
											}
											else
												m=m->down_n;
										}
										else
										{
											a=m;
											m=m->down_n;
											delete_current(a);
										}										
									}
									else
										m=m->down_n;
								}
								break;
							}
							case NE:
							{
								for(i=0;i<k;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(m->modphone==pok)
										{
											if(m->phone!=f->phone)
											{
												a=m;
												m=m->down_n;
												delete_current(a);
											}
											else
												m=m->down_n;
										}
										else
										{
											a=m;
											m=m->down_n;
											delete_current(a);
										}
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())!=0)
									{
										if(m->modphone==pok)
										{
											if(m->phone!=f->phone)
											{
												a=m;
												m=m->down_n;
												delete_current(a);
											}
											else
												m=m->down_n;
										}
										else
										{
											a=m;
											m=m->down_n;
											delete_current(a);
										}
									}
									else
										m=m->down_n;
								}
								
								for(i=k+1;i<RAZMNAME;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(m->modphone==pok)
										{
											if(m->phone!=f->phone)
											{
												a=m;
												m=m->down_n;
												delete_current(a);
											}
											else
												m=m->down_n;
										}
										else
										{
											a=m;
											m=m->down_n;
											delete_current(a);
										}
									}
								}
								break;
							}
							case LT:
							{
								for(i=0;i<k;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(m->modphone==pok)
										{
											if(m->phone!=f->phone)
											{
												a=m;
												m=m->down_n;
												delete_current(a);
											}
											else
												m=m->down_n;
										}
										else
										{
											a=m;
											m=m->down_n;
											delete_current(a);
										}
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())<0)
									{
										if(m->modphone==pok)
										{
											if(m->phone!=f->phone)
											{
												a=m;
												m=m->down_n;
												delete_current(a);
											}
											else
												m=m->down_n;
										}
										else
										{
											a=m;
											m=m->down_n;
											delete_current(a);
										}
									}
									else
										m=m->down_n;
								}
								
								break;
							}
							case GT:
							{
								for(i=k+1;i<RAZMNAME;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(m->modphone==pok)
										{
											if(m->phone!=f->phone)
											{
												a=m;
												m=m->down_n;
												delete_current(a);
											}
											else
												m=m->down_n;
										}
										else
										{
											a=m;
											m=m->down_n;
											delete_current(a);
										}
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())>0)
									{
										if(m->modphone==pok)
										{
											if(m->phone!=f->phone)
											{
												a=m;
												m=m->down_n;
												delete_current(a);
											}
											else
												m=m->down_n;
										}
										else
										{
											a=m;
											m=m->down_n;
											delete_current(a);
										}
									}
									else
										m=m->down_n;
								}
								break;
							}
							case LE:
							{
								for(i=0;i<k;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(m->modphone==pok)
										{
											if(m->phone!=f->phone)
											{
												a=m;
												m=m->down_n;
												delete_current(a);
											}
											else
												m=m->down_n;
										}
										else
										{
											a=m;
											m=m->down_n;
											delete_current(a);
										}
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())<=0)
									{
										if(m->modphone==pok)
										{
											if(m->phone!=f->phone)
											{
												a=m;
												m=m->down_n;
												delete_current(a);
											}
											else
												m=m->down_n;
										}
										else
										{
											a=m;
											m=m->down_n;
											delete_current(a);
										}
									}
									else
										m=m->down_n;
								}
								break;
							}
							case GE:
							{
								for(i=k+1;i<RAZMNAME;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(m->modphone==pok)
										{
											if(m->phone!=f->phone)
											{
												a=m;
												m=m->down_n;
												delete_current(a);
											}
											else
												m=m->down_n;
										}
										else
										{
											a=m;
											m=m->down_n;
											delete_current(a);
										}
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())>=0)
									{
										if(m->modphone==pok)
										{
											if(m->phone!=f->phone)
											{
												a=m;
												m=m->down_n;
												delete_current(a);
											}
											else
												m=m->down_n;
										}
										else
										{
											a=m;
											m=m->down_n;
											delete_current(a);
										}
									}	
									else
										m=m->down_n;
								}
								break;
							}
							case LIKE:
							{								
								break;
							}
							case COND_NONE:
							{
								break;
							}
							
						}
						
						m=hash_phone[pok];
						while(m)
						{
							if(m->phone==f->phone)
							{
								a=m;
								m=m->down_p;
								delete_current(a);
							}
							else
								m=m->down_p;
						}							
					}
					else
					{
						list_node*m;
					
						//int k=(f->name.get()[0]-'A')*RAZN+f->name.get()[1]-'A';
						int k=poiskvmasname(f);
						switch(f->	c_name)
						{
							case EQ:
							{
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())==0)
									{
										if(comp_num(m->phone,f->phone,f->c_phone)!=0)
										{
											a=m;
											m=m->down_n;
											delete_current(a);
										}
										else
											m=m->down_n;
									}
									else
										m=m->down_n;
								}
								break;
							}
							case NE:
							{
								for(i=0;i<k;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(comp_num(m->phone,f->phone,f->c_phone)!=0)
										{
											a=m;
											m=m->down_n;
											delete_current(a);
										}
										else
											m=m->down_n;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())!=0)
									{
										if(comp_num(m->phone,f->phone,f->c_phone)!=0)
										{
											a=m;
											m=m->down_n;
											delete_current(a);
										}
										else
											m=m->down_n;
									}
									else
										m=m->down_n;
								}
								
								for(i=k+1;i<RAZMNAME;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(comp_num(m->phone,f->phone,f->c_phone)!=0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										m=m->down_n;
									}
								}
								break;
							}
							case LT:
							{
								for(i=0;i<k;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(comp_num(m->phone,f->phone,f->c_phone)!=0)
										{
											a=m;
											m=m->down_n;
											delete_current(a);
										}
										else
											m=m->down_n;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())<0)
									{
										if(comp_num(m->phone,f->phone,f->c_phone)!=0)
										{
											a=m;
											m=m->down_n;
											delete_current(a);
										}
										else
											m=m->down_n;
									}
									else
										m=m->down_n;
								}
								
								break;
							}
							case GT:
							{
								for(i=k+1;i<RAZMNAME;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(comp_num(m->phone,f->phone,f->c_phone)!=0)
										{
											a=m;
											m=m->down_n;
											delete_current(a);
										}
										else
											m=m->down_n;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())>0)
									{
										if(comp_num(m->phone,f->phone,f->c_phone)!=0)
										{
											a=m;
											m=m->down_n;
											delete_current(a);
										}
										else
											m=m->down_n;
									}
									else
										m=m->down_n;
								}
								break;
							}
							case LE:
							{
								for(i=0;i<k;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(comp_num(m->phone,f->phone,f->c_phone)!=0)
										{
											a=m;
											m=m->down_n;
											delete_current(a);
										}
										else
											m=m->down_n;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())<=0)
									{
										if(comp_num(m->phone,f->phone,f->c_phone)!=0)
										{
											a=m;
											m=m->down_n;
											delete_current(a);
										}
										else
											m=m->down_n;
									}
									else
										m=m->down_n;
								}
								break;
							}
							case GE:
							{
								for(i=k+1;i<RAZMNAME;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(comp_num(m->phone,f->phone,f->c_phone)!=0)
										{
											a=m;
											m=m->down_n;
											delete_current(a);
										}
										else
											m=m->down_n;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())>=0)
									{
										if(comp_num(m->phone,f->phone,f->c_phone)!=0)
										{
											a=m;
											m=m->down_n;
											delete_current(a);
										}
										else
											m=m->down_n;
									}
									else
										m=m->down_n;
								}
								break;
							}
							case LIKE:
							{								
								break;
							}
							case COND_NONE:
							{
								break;
							}
							
							
						}
						for (current=head; current != NULL; current=current->next)
						{
							if (comp_num(current->phone,f->phone,f->c_phone)==0)
							{
								a=m;
								m=m->next;
								delete_current(a);
							}
							else
								current=current->next;
						}
					}
					
				}
				break;
			}
			case 10://phone
			{
					list_node*m;
				/*int sum=0,num=f->phone;
	
				while(num)
				{
					sum+=num%10;
					num=num/10;
				}
				int k=sum%mod;*/
				int k=poiskvmasphoneinsert(f);
				
				switch(f->c_phone)
				{
					case EQ:
					{
						m=hash_phone[k];
						while(m)
						{
							if(m->phone==f->phone)
							{
								a=m;
								m=m->down_p;
								delete_current(a);
							}
							else
								m=m->down_p;
						}
						break;
					}
					case NE:
					{
						for(i=0;i<k;i++)
						{
							m=hash_phone[i];
							while(m)
							{
								a=m;
								m=m->down_p;
								delete_current(a);
							}
						}
						
						m=hash_phone[k];
						while(m)
						{
							if(m->phone!=f->phone)
							{
								a=m;
								m=m->down_p;
								delete_current(a);
							}
							else
								m=m->down_p;
						}
						
						for(i=k+1;i<mod;i++)
						{
							m=hash_phone[i];
							while(m)
							{
								a=m;
								m=m->down_p;
								delete_current(a);
							}
						}
						
						break;
					}
					case LT:
					{
						for (current=head; current != NULL; )
						{
							if (current->phone < f->phone)
							{
								a=current;
								current=current->next;
								delete_current(a);
							}
							else
								current=current->next;
						}
						break;
					}
					case GT:
					{
						for (current=head; current != NULL;)
						{
							if (current->phone > f->phone)
							{
								a=current;
								current=current->next;
								delete_current(a);
							}
							else
								current=current->next;
						}
						break;
					}
					case LE:
					{
						for (current=head; current != NULL;)
						{
							if (current->phone <= f->phone)
							{
								a=current;
								current=current->next;
								delete_current(a);
							}
							else
								current=current->next;
						}
						break;
					}
					case GE:
					{
						for (current=head; current != NULL;)
						{
							if (current->phone >= f->phone)
							{
								a=current;
								current=current->next;
								delete_current(a);
							}
							else
								current=current->next;
						}
						break;
					}
					case COND_NONE:
					{
						break;
					}
					case LIKE:
					{
						break;
					}

				}
				break;
			}
			case 11://phone group
			{
				list_node*m;
				if (f->oper==AND)
				{	
					int pok=poiskvmasphoneinsert(f);
					switch(f->c_group)
					{
						case EQ:
						{
							int t=f->group-100;
							if(mas[t] )
							{
								if(f->c_phone==EQ)
								{
									m=mas[t]->hash_phone[pok];
									//printf("((((%s %d %d\n",m->name.get(),m->phone,m->group);
									while(m)
									{
										if(m->phone==f->phone)	
										{
											a=m;
											m=m->down_phone;
											delete_current(a);
										}
										else
											m=m->down_phone;
									}
								}
								else
								{
									if(f->c_phone==NE)
									{
										for(i=0;i<pok;i++)
										{
											m=mas[t]->hash_phone[i];
											while(m)
											{
												a=m;
												m=m->down_phone;
												delete_current(a);
											}
										}
										
										m=mas[t]->hash_phone[pok];
										while(m)
										{
											if(m->phone!=f->phone)
											{
												a=m;
												m=m->down_phone;
												delete_current(a);
											}
											else
												m=m->down_phone;
										}
										
										for(i=pok+1;i<mod;i++)
										{
											m=mas[t]->hash_phone[i];
											while(m)
											{
												a=m;
												m=m->down_phone;
												delete_current(a);
											}
										}
									}
									else
									{
										for(current=mas[f->group-100]->head;current!=NULL;)
										{
											if(comp_num(current->phone,f->phone,f->c_phone)==0)
											{
												a=current;
												current=current->down_group;
												delete_current(a);
											}
											else
												current=current->down_group;
										}
									}
								}
							}								
							break;
						}
						case NE:
						{
							for(int t=0;t < (f->group-100);t++)
							{
								if(mas[t] )
								{
									if(f->c_phone==EQ)
									{
										m=mas[t]->hash_phone[pok];
										//printf("((((%s %d %d\n",m->name.get(),m->phone,m->group);
										while(m)
										{
											if(m->phone==f->phone)	
											{
												a=m;
												m=m->down_phone;
												delete_current(a);
											}
											else
												m=m->down_phone;
										}
									}
									else
									{
										if(f->c_phone==NE)
										{
											for(i=0;i<pok;i++)
											{
												m=mas[t]->hash_phone[i];
												while(m)
												{
													a=m;
													m=m->down_phone;
													delete_current(a);
												}
											}
											
											m=mas[t]->hash_phone[pok];
											while(m)
											{
												if(m->phone!=f->phone)
												{
													a=m;
													m=m->down_phone;
													delete_current(a);
												}
												else
													m=m->down_phone;
											}
											
											for(i=pok+1;i<mod;i++)
											{
												m=mas[t]->hash_phone[i];
												while(m)
												{
													a=m;
													m=m->down_phone;
													delete_current(a);
												}
											}
										}
										else
										{
											for(current=mas[f->group-100]->head;current!=NULL;)
											{
												if(comp_num(current->phone,f->phone,f->c_phone)==0)
												{
													a=current;
													current=current->down_group;
													delete_current(a);
												}
												else
													current=current->down_group;
											}
										}
									}
								}
							}
							for(int t=(f->group-100)+1;t < 900;t++)
							{
								if(mas[t] )
								{
									if(f->c_phone==EQ)
									{
										m=mas[t]->hash_phone[pok];
										//printf("((((%s %d %d\n",m->name.get(),m->phone,m->group);
										while(m)
										{
											if(m->phone==f->phone)	
											{
												a=m;
												m=m->down_phone;
												delete_current(a);
											}
											else
												m=m->down_phone;
										}
									}
									else
									{
										if(f->c_phone==NE)
										{
											for(i=0;i<pok;i++)
											{
												m=mas[t]->hash_phone[i];
												while(m)
												{
													a=m;
													m=m->down_phone;
													delete_current(a);
												}
											}
											
											m=mas[t]->hash_phone[pok];
											while(m)
											{
												if(m->phone!=f->phone)
												{
													a=m;
													m=m->down_phone;
													delete_current(a);
												}
												else
													m=m->down_phone;
											}
											
											for(i=pok+1;i<mod;i++)
											{
												m=mas[t]->hash_phone[i];
												while(m)
												{
													a=m;
													m=m->down_phone;
													delete_current(a);
												}
											}
										}
										else
										{
											for(current=mas[f->group-100]->head;current!=NULL;)
											{
												if(comp_num(current->phone,f->phone,f->c_phone)==0)
												{
													a=current;
													current=current->down_group;
													delete_current(a);
												}
												else
													current=current->down_group;
											}
										}
									}
								}
							}
							
							break;
						}
						case LT:
						{
							for(int t=0;t < (f->group-100);t++)
							{
								if(mas[t] )
								{
									if(f->c_phone==EQ)
									{
										m=mas[t]->hash_phone[pok];
										//printf("((((%s %d %d\n",m->name.get(),m->phone,m->group);
										while(m)
										{
											if(m->phone==f->phone)	
											{
												a=m;
												m=m->down_phone;
												delete_current(a);
											}
											else
												m=m->down_phone;
										}
									}
									else
									{
										if(f->c_phone==NE)
										{
											for(i=0;i<pok;i++)
											{
												m=mas[t]->hash_phone[i];
												while(m)
												{
													a=m;
													m=m->down_phone;
													delete_current(a);
												}
											}
											
											m=mas[t]->hash_phone[pok];
											while(m)
											{
												if(m->phone!=f->phone)
												{
													a=m;
													m=m->down_phone;
													delete_current(a);
												}
												else
													m=m->down_phone;
											}
											
											for(i=pok+1;i<mod;i++)
											{
												m=mas[t]->hash_phone[i];
												while(m)
												{
													a=m;
													m=m->down_phone;
													delete_current(a);
												}
											}
										}
										else
										{
											for(current=mas[f->group-100]->head;current!=NULL;)
											{
												if(comp_num(current->phone,f->phone,f->c_phone)==0)
												{
													a=current;
													current=current->down_group;
													delete_current(a);
												}
												else
													current=current->down_group;
											}
										}
									}
								}
							}
							break;
						}
						case GT:
						{
							for(int t=(f->group-100)+1;t < 900;t++)
							{
								if(mas[t] )
								{
									if(f->c_phone==EQ)
									{
										m=mas[t]->hash_phone[pok];
										//printf("((((%s %d %d\n",m->name.get(),m->phone,m->group);
										while(m)
										{
											if(m->phone==f->phone)	
											{
												a=m;
												m=m->down_phone;
												delete_current(a);
											}
											else
												m=m->down_phone;
										}
									}
									else
									{
										if(f->c_phone==NE)
										{
											for(i=0;i<pok;i++)
											{
												m=mas[t]->hash_phone[i];
												while(m)
												{
													a=m;
													m=m->down_phone;
													delete_current(a);
												}
											}
											
											m=mas[t]->hash_phone[pok];
											while(m)
											{
												if(m->phone!=f->phone)
												{
													a=m;
													m=m->down_phone;
													delete_current(a);
												}
												else
													m=m->down_phone;
											}
											
											for(i=pok+1;i<mod;i++)
											{
												m=mas[t]->hash_phone[i];
												while(m)
												{
													a=m;
													m=m->down_phone;
													delete_current(a);
												}
											}
										}
										else
										{
											for(current=mas[f->group-100]->head;current!=NULL;)
											{
												if(comp_num(current->phone,f->phone,f->c_phone)==0)
												{
													a=current;
													current=current->down_group;
													delete_current(a);
												}
												else
													current=current->down_group;
											}
										}
									}
								}
							}
							break;
						}
						case LE:
						{
							for(int t=0;t <= (f->group-100);t++)
							{
								if(mas[t] )
								{
									if(f->c_phone==EQ)
									{
										m=mas[t]->hash_phone[pok];
										//printf("((((%s %d %d\n",m->name.get(),m->phone,m->group);
										while(m)
										{
											if(m->phone==f->phone)	
											{
												a=m;
												m=m->down_phone;
												delete_current(a);
											}
											else
												m=m->down_phone;
										}
									}
									else
									{
										if(f->c_phone==NE)
										{
											for(i=0;i<pok;i++)
											{
												m=mas[t]->hash_phone[i];
												while(m)
												{
													a=m;
													m=m->down_phone;
													delete_current(a);
												}
											}
											
											m=mas[t]->hash_phone[pok];
											while(m)
											{
												if(m->phone!=f->phone)
												{
													a=m;
													m=m->down_phone;
													delete_current(a);
												}
												else
													m=m->down_phone;
											}
											
											for(i=pok+1;i<mod;i++)
											{
												m=mas[t]->hash_phone[i];
												while(m)
												{
													a=m;
													m=m->down_phone;
													delete_current(a);
												}
											}
										}
										else
										{
											for(current=mas[f->group-100]->head;current!=NULL;)
											{
												if(comp_num(current->phone,f->phone,f->c_phone)==0)
												{
													a=current;
													current=current->down_group;
													delete_current(a);
												}
												else
													current=current->down_group;
											}
										}
									}
								}
							}
							break;
						}
						case GE:
						{
							for(int t=(f->group-100);t < 900;t++)
							{
								if(mas[t] )
								{
									if(f->c_phone==EQ)
									{
										m=mas[t]->hash_phone[pok];
										//printf("((((%s %d %d\n",m->name.get(),m->phone,m->group);
										while(m)
										{
											if(m->phone==f->phone)	
											{
												a=m;
												m=m->down_phone;
												delete_current(a);
											}
											else
												m=m->down_phone;
										}
									}
									else
									{
										if(f->c_phone==NE)
										{
											for(i=0;i<pok;i++)
											{
												m=mas[t]->hash_phone[i];
												while(m)
												{
													a=m;
													m=m->down_phone;
													delete_current(a);
												}
											}
											
											m=mas[t]->hash_phone[pok];
											while(m)
											{
												if(m->phone!=f->phone)
												{
													a=m;
													m=m->down_phone;
													delete_current(a);
												}
												else
													m=m->down_phone;
											}
											
											for(i=pok+1;i<mod;i++)
											{
												m=mas[t]->hash_phone[i];
												while(m)
												{
													a=m;
													m=m->down_phone;
													delete_current(a);
												}
											}
										}
										else
										{
											for(current=mas[f->group-100]->head;current!=NULL;)
											{
												if(comp_num(current->phone,f->phone,f->c_phone)==0)
												{
													a=current;
													current=current->down_group;
													delete_current(a);
												}
												else
													current=current->down_group;
											}
										}
									}
								}
							}
							break;
						}
						case COND_NONE:
						{
							break;
						}
						case LIKE:
						{
							break;
						}

					}
					
			
			
			
			
			
			
			
			
			
			
					/*switch(f->c_group)
					{
						case EQ:
						{
							for(current=mas[f->group-100]->head;current!=NULL;)
							{
								if(comp_num(current->phone,f->phone,f->c_phone)==0)
								{
									a=current;
									current=current->down_group;
									delete_current(a);
								}
								else
									current=current->down_group;
							}
							break;
						}
						case NE:
						{
							for(int t=0;t < (f->group-100);t++)
							{
								if(mas[t])
								{
									for(current=mas[t]->head;current!=NULL;)
									{
										if(comp_num(current->phone,f->phone,f->c_phone)==0)
										{
											a=current;
											current=current->down_group;
											delete_current(a);
										}
										else
											current=current->down_group;
									}
								}
							}
							for(int t=(f->group-100)+1;t < 900;t++)
							{
								if(mas[t])
								{
									for(current=mas[t]->head;current!=NULL;)
									{
										if(comp_num(current->phone,f->phone,f->c_phone)==0)
										{
											a=current;
											current=current->down_group;
											delete_current(a);
										}
										else
											current=current->down_group;
									}
								}
							}
							
							break;
						}
						case LT:
						{
							for(int t=0;t < (f->group-100);t++)
							{
								if(mas[t])/////////////////////////
								{
									for(current=mas[t]->head;current!=NULL;)
									{
										if(comp_num(current->phone,f->phone,f->c_phone)==0)
										{
											a=current;
											current=current->down_group;
											delete_current(a);
										}
										else
											current=current->down_group;
									}
								}
							}
							break;
						}
						case GT:
						{
							for(int t=(f->group-100)+1;t < 900;t++)
							{
								if(mas[t])
								{
									for(current=mas[t]->head;current!=NULL;)
									{
										if(comp_num(current->phone,f->phone,f->c_phone)==0)
										{
											a=current;
											current=current->down_group;
											delete_current(a);
										}
										else
											current=current->down_group;
									}
								}
							}
							break;
						}
						case LE:
						{
							for(int t=0;t <= (f->group-100);t++)
							{
								if(mas[t])
								{
									for(current=mas[t]->head;current!=NULL;)
									{
										if(comp_num(current->phone,f->phone,f->c_phone)==0)
										{
											a=current;
											current=current->down_group;
											delete_current(a);
										}
										else
											current=current->down_group;
									}
								}
							}
							break;
						}
						case GE:
						{
							for(int t=(f->group-100);t < 900;t++)
							{
								if(mas[t])
								{
									for(current=mas[t]->head;current!=NULL;)
									{
										if(comp_num(current->phone,f->phone,f->c_phone)==0)
										{
											a=current;
											current=current->down_group;
											delete_current(a);
										}
										else
											current=current->down_group;
									}
								}
							}
							break;
						}
						case COND_NONE:
						{
							break;
						}
						case LIKE:
						{
							break;
						}

					}
					*/
				}
				else
				{
					list_node*m;
					//int sum=0,num=f->phone;
		
					/*while(num)
					{
						sum+=num%10;
						num=num/10;
					}
					int k=sum%mod;*/
					int k=poiskvmasphoneinsert(f);
					
					switch(f->c_phone)
					{
						case EQ:
						{
							for(int t=0;t<900;t++)
							{
								if(mas[t])
								{
									if(comp_num(t+100,f->group,f->c_group)==0)
									{
										for(current=mas[t]->head;current!=NULL;)
										{
											a=current;
											current=current->down_group;
											delete_current(a);
										}
									}
									else
									{
										m=mas[t]->hash_phone[k];
										while(m)
										{
											if(m->phone==f->phone)
											{
												a=m;
												m=m->down_phone;
												delete_current(a);
											}
											else
												m=m->down_phone;
										}
									}
								}
							}
							break;
						}
						case NE:
						{
							for(int t=0;t<900;t++)
							{
								if(mas[t])
								{
									if(comp_num(t+100,f->group,f->c_group)==0)
									{
										for(current=mas[t]->head;current!=NULL;)
										{
											a=current;
											current=current->down_group;
											delete_current(a);
										}
									}
									else
									{									
										for(i=0;i<k;i++)
										{
											if(!mas[t])break;
											m=mas[t]->hash_phone[i];
											while(m)
											{
												a=m;
												m=m->down_phone;
												delete_current(a);
											}
										}
										if(mas[t])
										{
											m=mas[t]->hash_phone[k];
											while(m)
											{
												if(m->phone!=f->phone)
												{
													a=m;
													m=m->down_phone;
													delete_current(a);
												}
												else
													m=m->down_phone;
											}
										}
										for(i=k+1;i<mod;i++)
										{
											if(!mas[t])break;
											m=mas[t]->hash_phone[i];
											while(m)
											{
												a=m;
												m=m->down_phone;
												delete_current(a);
											}
										}
										
									}
								}
							}								
							break;
						}
						case LT:
						{
							for(int t=0;t<900;t++)
							{
								if(mas[t])
								{
									if(comp_num(t+100,f->group,f->c_group)==0)
									{
										for(current=mas[t]->head;current!=NULL;)
										{
											a=current;
											current=current->down_group;
											delete_current(a);
										}
									}
									else
									{
										for(current=mas[t]->head;current!=NULL;)
										{
											if(current->phone < f->phone)
											{
												a=current;
												current=current->down_group;
												delete_current(a);
											}
											else
												current=current->down_group;
										}
									}
								}
							}
							break;
						}
						case GT:
						{
							for(int t=0;t<900;t++)
							{
								if(mas[t])
								{
									if(comp_num(t+100,f->group,f->c_group)==0)
									{
										for(current=mas[t]->head;current!=NULL;)
										{
											a=current;
											current=current->down_group;
											delete_current(a);
										}
									}
									else
									{
										for(current=mas[t]->head;current!=NULL;)
										{
											if(current->phone > f->phone)
											{
												a=current;
												current=current->down_group;
												delete_current(a);
											}
											else
												current=current->down_group;
										}
									}
								}
							}
							break;
						}
						case LE:
						{
							for(int t=0;t<900;t++)
							{
								if(mas[t])
								{
									if(comp_num(t+100,f->group,f->c_group)==0)
									{
										for(current=mas[t]->head;current!=NULL;)
										{
											a=current;
											current=current->down_group;
											delete_current(a);
										}
									}
									else
									{
										for(current=mas[t]->head;current!=NULL;)
										{
											if(current->phone <= f->phone)
											{
												a=current;
												current=current->down_group;
												delete_current(a);
											}
											else
												current=current->down_group;
										}
									}
								}
							}
							break;
						}
						case GE:
						{
							for(int t=0;t<900;t++)
							{
								if(mas[t])
								{
									if(comp_num(t+100,f->group,f->c_group)==0)
									{
										for(current=mas[t]->head;current!=NULL;)
										{
											a=current;
											current=current->down_group;
											delete_current(a);
										}
									}
									else
									{
										for(current=mas[t]->head;current!=NULL;)
										{
											if(current->phone >= f->phone)
											{
												a=current;
												current=current->down_group;
												delete_current(a);
											}
											else
												current=current->down_group;
										}
									}
								}
							}
							break;
						}
						case COND_NONE:
						{
							break;
						}
						case LIKE:
						{
							break;
						}

					}
				}
				break;
			}
			case 1://group
			{
		        switch(f->c_group)
				{
					case EQ:
					{
						if(mas[f->group-100])
						{
							for(current=mas[f->group-100]->head;current!=NULL;)
							{
								a=current;
								current=current->down_group;
								delete_current(a);
							}
						}
						break;
					}
					case NE:
					{
						for(int t=0;t < (f->group-100);t++)
						{
							if(mas[t])
							{
								for(current=mas[t]->head;current!=NULL;)
								{
									a=current;
									current=current->down_group;
									delete_current(a);
								}
							}
						}
						for(int t=(f->group-100)+1;t < 900;t++)
						{
							if(mas[t])
							{
								for(current=mas[t]->head;current!=NULL;)
								{
									a=current;
									current=current->down_group;
									delete_current(a);
								}
							}
						}
						break;
					}
					case LT:
					{
						for(int t=0;t < (f->group-100);t++)
						{
							if(mas[t])
							{
								for(current=mas[t]->head;current!=NULL;)
								{
									a=current;
									current=current->down_group;
									delete_current(a);
								}
							}
						}
						break;
					}
					case GT:
					{
						for(int t=(f->group-100)+1;t < 900;t++)
						{
							if(mas[t])
							{
								for(current=mas[t]->head;current!=NULL;)
								{
									a=current;
									current=current->down_group;
									delete_current(a);
								}
							}
						}
						break;
					}
					case LE:
					{
						for(int t=0;t <= (f->group-100);t++)
						{
							if(mas[t])
							{
								for(current=mas[t]->head;current!=NULL;)
								{
									a=current;
									current=current->down_group;
									delete_current(a);
								}
							}
						}
						break;
					}
					case GE:
					{
						for(int t=(f->group-100);t < 900;t++)
						{
							if(mas[t])
							{
								for(current=mas[t]->head;current!=NULL;)
								{
									a=current;
									current=current->down_group;
									delete_current(a);
								}
							}
						}
						break;
					}
					case COND_NONE:
					{
						break;
					}
					case LIKE:
					{
						break;
					}
				}
				break;
			}
			case 0:
			{
				for (current=head; current != NULL; )
				{
					a=current;
	                current=current->next;
					delete_current( a ); 
				}	
			}
		}
	}
}

void groupm::perest(list_node*a)
{
	if(a->up_name2)
	{
		if(a->down_name2)
		{
			a->up_name2->down_name2=a->down_name2;
			a->down_name2->up_name2=a->up_name2;
		}
		else
		{
			a->up_name2->down_name2=NULL;
		}
	}
	else
	{
		if(a->down_name2)
		{
			mas[a->group-100]->hash_name[a->place]=a->down_name2;
			a->down_name2->up_name2=NULL;
		}
		else
			mas[a->group-100]->hash_name[a->place]=NULL;
	}
	return;
}

void groupm::perestphone(list_node*a)
{
	if(a->up_phone)
	{
		if(a->down_phone)
		{
			a->up_phone->down_phone=a->down_phone;
			a->down_phone->up_phone=a->up_phone;
		}
		else
		{
			a->up_phone->down_phone=NULL;
		}
	}
	else
	{
		if(a->down_phone)
		{
			mas[a->group-100]->hash_phone[a->modphone]=a->down_phone;
			a->down_phone->up_phone=NULL;
		}
		else
			mas[a->group-100]->hash_phone[a->modphone]=NULL;
	}
	return;
}

void groupm::perestgroup(list_node*a)
{
	if(a->up_group)
	{
		if(a->down_group)
		{
			a->up_group->down_group=a->down_group;
			a->down_group->up_group=a->up_group;
		}
		else
		{
			a->up_group->down_group=NULL;
		}
	}
	else
	{
		if(a->down_group)
		{
			mas[a->group-100]->head=a->down_group;
			a->down_group->up_group=NULL;
		}
		else
		{
			delete []mas[a->group-100]->hash_name;
			delete []mas[a->group-100]->hash_phone;
			delete mas[a->group-100];
			mas[a->group-100]=NULL;
		}
	}	
}

void groupm::perest_name_global(list_node*a)
{
	if(a->up_n)
	{
		if(a->down_n)
		{
			a->up_n->down_n=a->down_n;
			a->down_n->up_n=a->up_n;
		}
		else
		{
			a->up_n->down_n=NULL;
		}
	}
	else
	{
		if(a->down_n)
		{
			hash_name[a->place]=a->down_n;
			a->down_n->up_n=NULL;
		}
		else
			hash_name[a->place]=NULL;
	}
	return;
}

void groupm::perest_phone_global(list_node*a)
{
	if(a->up_p)
	{
		if(a->down_p)
		{
			a->up_p->down_p=a->down_p;
			a->down_p->up_p=a->up_p;
		}
		else
		{
			a->up_p->down_p=NULL;
		}
	}
	else
	{
		if(a->down_p)
		{
			hash_phone[a->modphone]=a->down_p;
			a->down_p->up_p=NULL;
		}
		else
			hash_phone[a->modphone]=NULL;
	}
	return;
}

void groupm::delete_current(list_node *a)
{	
	if ( (a==head)&&(a->next==NULL) )
	{
		delete []mas[a->group-100]->hash_name;
		delete []mas[a->group-100]->hash_phone;
		delete mas[a->group-100];
		mas[a->group-100]=NULL;
		hash_name[a->place]=NULL;
		hash_phone[a->modphone]=NULL;
		delete a;
		head=NULL;
	}
	else
	{
		if (a==head)
		{
			head=a->next;
			head->prev=0;
			
			perest(a);
			perestphone(a);
			perestgroup(a);
			perest_name_global(a);
			perest_phone_global(a);
            delete a;
		}
		else
		{	
			if (a->next==NULL)
			{
				a->prev->next=0;
				
				perest(a);
				perestphone(a);
				perestgroup(a);
				perest_name_global(a);
				perest_phone_global(a);
                delete a;
			}
			else
			{
				a->prev->next=a->next;
				a->next->prev=a->prev;
				
				perest(a);
				perestphone(a);
				perestgroup(a);
				perest_name_global(a);
				perest_phone_global(a);
                delete a;
			}
		}
	}
}

int groupm::cmp(list_node * a,command * f)
{
	if (a->group==f->group)
	{
		if (a->phone==f->phone)
		{
			if (strcmp(a->name.get(),f->name.get())==0)
			{
				return -1;
			}
			else return 0;
		}
		else return 0;
	}
	else return 0;
}

int groupm::comp_name(list_node * a, char * b, cond_type c_name )
{
	int k=(b[0]-'A')*RAZN*RAZN*RAZN+(b[1]-'A')*RAZN*RAZN+(b[2]-'A')*RAZN+b[3]-'A';
	switch(c_name)
	{
		case EQ:
		{
			if(k==a->place)
			{
				if(strcmp(a->name.get(),b)==0)return 0;
			}
			break;
		}
		case NE:
		{
			if(k==a->place)
			{
				if(strcmp(a->name.get(),b)!=0)return 0;
			}
			else
				return 0;
			
			break;
		}
		case LT:
		{
			if (k==a->place)
			{
				if(strcmp(b,a->name.get())>0)return 0;
			}
			else
			{
				if(k > a->place)return 0;
			}
			break;
		}
		case GT:
		{
			if (k==a->place)
			{
				if(strcmp(b,a->name.get())<0)return 0;
			}
			else
			{
				if(k < a->place)return 0;
			}
			break;
		}
		case LE:
		{
			if (k==a->place)
			{
				if(strcmp(b,a->name.get())>=0)return 0;
			}
			else
			{
				if(k > a->place)return 0;
			}
			break;
		}
		case GE:
		{
			if (k==a->place)
			{
				if(strcmp(b,a->name.get())<=0)return 0;
			}
			else
			{
				if(k < a->place)return 0;
			}
			break;
		}
		case LIKE:
		{
			
			break;
		}
        case COND_NONE:
        {
            break;
        }
		
	}
	return 1;
}

int groupm::comp_num(int a, int b,cond_type r)
{
	int res=0;

	res=-a+b;
	switch(r)
	{
		case EQ:
		{
			if (res==0) return 0;
			break;
		}
		case NE:
		{
			if (res!=0) return 0;
			break;
		}
		case LT:
		{
			if (res>0) return 0;
			break;
		}
		case GT:
		{
			if (res<0) return 0;
			break;
		}
		case LE:
		{
			if (res>=0) return 0;
			break;
		}
		case GE:
		{
			if (res<=0) return 0;
			break;
		}
		case COND_NONE:
		{
			break;
		}
		case LIKE:
		{
			break;
		}

	}
	
	return 1;
}

int groupm::liker(char *b, char ** words, char * buf, int * kol)
{
	for (int y=0;y<1233;y++)
		buf[y]=0;
	char a[1234];
	for (int y=0;y<1233;y++)
		a[y]=0;
	strcpy(a,b);
	//printf("%s\n",a);
	int len=strlen(b);
	int i=0;
	int l=2;
	int param=0;
	if (a[0]=='%')
	{
		param=10;/// в начале %
		if (a[len-1]=='%')
		{
			while ( (a[len-l]=='\\')&&(a[len-l]!=0) )
				l++;
			if (l%2==0) param=11;//в начале и конце %
		}
	}
	else
	{
		if (a[len-1]=='%')
			param=1;//в конце %
		else param=0;// нигде
	}
	
	while (a[i]=='%')
		i++;
	if (a[i] == 0) return 1;
	int j=0;
	
	for(;a[i];i++)
	{
		if (a[i]=='\\')
		{
			if (a[i+1]=='\\') i++;
			else  {  if (a[i+1]=='%') i++;  }
		}
		else  {  if (a[i]=='%') a[i]=0;  }
		
		buf[j]=a[i];
		j++;
	}
	buf[j]=0;
	len=j;
	j=0;
	int k=0;
	//printf("00000\n");
	while(j<len)
	{
		words[k]=buf+j;
		//printf("%s\n",words[k]);
		k++;
		while(buf[j]!=0)
			j++;
		if (j>=len) break;
		while (j< len && buf[j]==0)
			j++;
	
	}
	*kol=k;
	return param;
}

int groupm::comp_like(char * comm, char ** words, int param, int am)
{
	
	char * s1=strstr(comm,words[0]);
	if (s1==NULL) {  return -1; }
	if ((s1-comm)!=0)
	{
		if (!( (param==11)||(param==10)) ) { return -1; }
	}
	
	char * s2=strlast(comm,words[am-1]);
	if (s2==NULL) {  return -1; }
	if ((s2+strlen(words[am-1]))[0]!=0)
	{
		if (!( (param==11)||(param==1)) ) { return -1; }
	}
	char *s;
	comm=comm+strlen(words[0]);
	int i=0;
	//printf("!@#\n");
	for (i=1;i<am;i++)
	{
		if (comm==NULL) { return -1; }
		if (s2-comm<0) { return -1; }
		s=strstr(comm,words[i]);
		if (s==NULL) { return -1; }
		comm=comm+strlen(words[i]);
	}
	return 0;
}

char * groupm::strlast(char * a, char * b)
{
	char * s=NULL;
	int  t=0;
	while (strstr(a+t,b)!=NULL)
	{
		s=strstr(a+t,b);
		t=s-a+1;
	}
	return s;
	
}


