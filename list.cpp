# include "list.h"
# include "list_node.h"

#define RAZN 57
#define RAZMNAME 188500

int list::read_list(const char * name, int num)
{
    delete_list();
	FILE * fp;
	//int i;
	if (!(fp=fopen(name,"r"))) { return -1; }

        char sname[1234];
	int sphone;
	int sgroup;
	mod=num;
	hash_name= new list_node*[RAZMNAME];
	for(int i=0; i<RAZMNAME;i++) hash_name[i]=0;

	hash_phone= new list_node*[mod];
	for(int i=0;i<mod;i++)hash_phone[i]=0;
	
	
    while(fscanf(fp,"%s%d%d",sname,&sphone,&sgroup)==3)
		insert(sname,sphone,sgroup);
	
	
	return 0;
}

void list::delete_list()
{
	list_node *p=head;
	list_node *next;
	while (p!=NULL)
	{
		next=p->next;
                delete p;
		p=next;
		next=0;
	}
	next=0;
	p=0;
	
	delete []hash_name;
	delete []hash_phone;
	
	
}

list_node* list::insert(char * name, int phone, int group )//////
{
	int pok;
	current=head;
	
	list_node * node;
	node= new list_node();
	if (head == NULL)
	{
		node->init(name,phone,group);
		pok=mas(node);
		if(pok==1)
		{
			delete node;
			return 0;
		}
		masphone(node);
		head=node;
	}
	else
	{
		node->init(name,phone,group);
		pok=mas(node);
		if(pok==1)
		{
			delete node;
			return 0;
		}
		head->up_group=node;
		node->down_group=head;
		head=node;
		masphone(node);
	}
	
	return node;
}

void list::masphone(list_node*a)
{
	int k=poiskvmasphone(a);
	
	if(hash_phone[k])
	{
		list_node *m=hash_phone[k];
		
		a->down_phone=m;
		m->up_phone=a;
		hash_phone[k]=a;
	}
	else
		hash_phone[k]=a;
	
	a->modphone=k;
}

int list::poiskvmasphone(list_node*a)
{
	/*int sum=0,num=a->phone;
	
	while(num)
	{
		sum+=num%10;
		num=num/10;
	}
	return sum%mod;*/
	int num=a->phone;
	return num%mod;
}

void list::printmasphone()
{
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
				fprintf(stdout,"%s %d %d %d \n",m->name.get(),m->phone,m->group,m->modphone);
				m=m->down_phone;
				//kol2++;
			}	
			printf("_________________________________\n");	
			//kol1++;			
		}
	}
}

int list::mas(list_node*a)
{
	int k=poiskvmas(a);
	
	if(hash_name[k])
	{
		list_node *m=hash_name[k];
		
		while(m->down_name2)
		{
			if(strcmp(m->name.get(),a->name.get())==0 && m->phone==a->phone && m->group==a->group)
				return 1;
			
			m=m->down_name2;
		}
		if(strcmp(m->name.get(),a->name.get())==0 && m->phone==a->phone && m->group==a->group)
			return 1;
		m->down_name2=a;
		a->up_name2=m;
	}
	else
		hash_name[k]=a;
	
	a->place=k;
	
	return 0;
}

int list::poiskvmas(list_node*a)
{
	return (a->name.get()[0]-'A')*RAZN*RAZN+(a->name.get()[1]-'A')*RAZN+(a->name.get()[2]-'A');
	//return (a->name.get()[0]-'A')*RAZN+a->name.get()[1]-'A';	
}

void list::printmas()
{
	int i;//kol1=0,kol2=0;
	list_node*m;
	
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
				fprintf(stdout,"%s %d %d \n",m->name.get(),m->phone,m->group);
				m=m->down_name2;
				//kol2++;
			}	
			printf("_________________________________\n");	
			//kol1++;			
		}
	}
}

/*void list::perest(list_node*a)
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
			hash_name[a->place]=a->down_name2;
			a->down_name2->up_name2=NULL;
		}
		else
			hash_name[a->place]=NULL;
	}
	return;
}

void list::perestphone(list_node*a)
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
			hash_phone[a->modphone]=a->down_phone;
			a->down_phone->up_phone=NULL;
		}
		else
			hash_phone[a->modphone]=NULL;
	}
	return;
}

void list::delete_current(list_node *a)
{
	if ( (a==head)&&(a->next==NULL) )
	{
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
            delete a;
		}
		else
		{	
			if (a->next==NULL)
			{
				a->prev->next=0;
				perest(a);
				perestphone(a);
                delete a;
			}
			else
			{
				a->prev->next=a->next;
				a->next->prev=a->prev;
				perest(a);
				perestphone(a);
                delete a;
			}
		}
	}
}

int list::cmp(list_node * a,command * f)
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

void list::read_file(FILE * fp, FILE * bf)
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
			printf("RESULT:\n");
			k=help.work(this);
			if(k==0)return;
		}
	}
}

int * list::make_alfavit(char * t, int * alf)
{
	int i=0;
    for (i=0;i<(int)strlen(t);i++)
	{
		alf[(unsigned int)t[i]]=1;
	}
	return alf;
}*/

/*void list::select(command * f)
{
	int i;
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
				
				int k=(f->name.get()[0]-'A')*RAZN+f->name.get()[1]-'A';
				switch(f->	c_name)
				{
					case EQ:
					{
						m=hash_name[k];
						while(m)
						{
							if(strcmp(m->name.get(),f->name.get())==0)
								fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
							m=m->down_name2;
						}
						break;
					}
					case NE:
					{
						for(i=0;i<RAZN*RAZN+RAZN;i++)
						{
							if(i==k)
							{
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())!=0)
										fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_name2;
								}
							}
							else
							{
								m=hash_name[i];
								while(m)
								{
									fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_name2;
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
								fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
								m=m->down_name2;
							}
						}
						
						m=hash_name[k];
						while(m)
						{
							if(strcmp(m->name.get(),f->name.get())<0)
								fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
							m=m->down_name2;
						}
						
						break;
					}
					case GT:
					{
						for(i=k+1;i<RAZN*RAZN+RAZN;i++)
						{
							m=hash_name[i];
							while(m)
							{
								fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
								m=m->down_name2;
							}
						}
						
						m=hash_name[k];
						while(m)
						{
							if(strcmp(m->name.get(),f->name.get())>0)
								fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
							m=m->down_name2;
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
								m=m->down_name2;
							}
						}
						
						m=hash_name[k];
						while(m)
						{
							if(strcmp(m->name.get(),f->name.get())<=0)
								fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
							m=m->down_name2;
						}
						break;
					}
					case GE:
					{
						for(i=k+1;i<RAZN*RAZN+RAZN;i++)
						{
							m=hash_name[i];
							while(m)
							{
								fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
								m=m->down_name2;
							}
						}
						
						m=hash_name[k];
						while(m)
						{
							if(strcmp(m->name.get(),f->name.get())>=0)
								fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
							m=m->down_name2;
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
					
					int k=(f->name.get()[0]-'A')*RAZN+f->name.get()[1]-'A';
					switch(f->	c_name)
					{
						case EQ:
						{
							m=hash_name[k];
							while(m)
							{
								if(strcmp(m->name.get(),f->name.get())==0)	
									if(comp_num(m->group,f->group,f->c_group)==0)
										fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
								m=m->down_name2;
							}
							break;
						}
						case NE:
						{
							for(i=0;i<RAZN*RAZN+RAZN;i++)
							{
								if(i==k)
								{
									m=hash_name[k];
									while(m)
									{
										if(strcmp(m->name.get(),f->name.get())!=0)
											if(comp_num(m->group,f->group,f->c_group)==0)
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										m=m->down_name2;
									}
								}
								else
								{
									m=hash_name[i];
									while(m)
									{
										if(comp_num(m->group,f->group,f->c_group)==0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										m=m->down_name2;
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
									if(comp_num(m->group,f->group,f->c_group)==0)
										fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_name2;
								}
							}
							
							m=hash_name[k];
							while(m)
							{
								if(strcmp(m->name.get(),f->name.get())<0)
									if(comp_num(m->group,f->group,f->c_group)==0)
										fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
								m=m->down_name2;
							}
							
							break;
						}
						case GT:
						{
							for(i=k+1;i<RAZN*RAZN+RAZN;i++)
							{
								m=hash_name[i];
								while(m)
								{
									if(comp_num(m->group,f->group,f->c_group)==0)
										fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_name2;
								}
							}
							
							m=hash_name[k];
							while(m)
							{
								if(strcmp(m->name.get(),f->name.get())>0)
									if(comp_num(m->group,f->group,f->c_group)==0)
										fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
								m=m->down_name2;
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
									if(comp_num(m->group,f->group,f->c_group)==0)
										fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_name2;
								}
							}
							
							m=hash_name[k];
							while(m)
							{
								if(strcmp(m->name.get(),f->name.get())<=0)
									if(comp_num(m->group,f->group,f->c_group)==0)
										fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
								m=m->down_name2;
							}
							break;
						}
						case GE:
						{
							for(i=k+1;i<RAZN*RAZN+RAZN;i++)
							{
								m=hash_name[i];
								while(m)
								{
									if(comp_num(m->group,f->group,f->c_group)==0)
										fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_name2;
								}
							}
							
							m=hash_name[k];
							while(m)
							{
								if(strcmp(m->name.get(),f->name.get())>=0)
									if(comp_num(m->group,f->group,f->c_group)==0)
										fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
								m=m->down_name2;
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
					
					int k=(f->name.get()[0]-'A')*RAZN+f->name.get()[1]-'A';
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
								m=m->down_name2;
							}
							break;
						}
						case NE:
						{
							for(i=0;i<RAZN*RAZN+RAZN;i++)
							{
								if(i==k)
								{
									m=hash_name[k];
									while(m)
									{
										if(strcmp(m->name.get(),f->name.get())!=0)
											if(comp_num(m->group,f->group,f->c_group)!=0)
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										m=m->down_name2;
									}
								}
								else
								{
									m=hash_name[i];
									while(m)
									{
										if(comp_num(m->group,f->group,f->c_group)!=0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										m=m->down_name2;
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
									if(comp_num(m->group,f->group,f->c_group)!=0)
										fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_name2;
								}
							}
							
							m=hash_name[k];
							while(m)
							{
								if(strcmp(m->name.get(),f->name.get())<0)
									if(comp_num(m->group,f->group,f->c_group)!=0)
										fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
								m=m->down_name2;
							}
							
							break;
						}
						case GT:
						{
							for(i=k+1;i<RAZN*RAZN+RAZN;i++)
							{
								m=hash_name[i];
								while(m)
								{
									if(comp_num(m->group,f->group,f->c_group)!=0)
										fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_name2;
								}
							}
							
							m=hash_name[k];
							while(m)
							{
								if(strcmp(m->name.get(),f->name.get())>0)
									if(comp_num(m->group,f->group,f->c_group)!=0)
										fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
								m=m->down_name2;
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
									m=m->down_name2;
								}
							}
							
							m=hash_name[k];
							while(m)
							{
								if(strcmp(m->name.get(),f->name.get())<=0)
									if(comp_num(m->group,f->group,f->c_group)!=0)
										fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
								m=m->down_name2;
							}
							break;
						}
						case GE:
						{
							for(i=k+1;i<RAZN*RAZN+RAZN;i++)
							{
								m=hash_name[i];
								while(m)
								{
									if(comp_num(m->group,f->group,f->c_group)!=0)
										fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_name2;
								}
							}
							
							m=hash_name[k];
							while(m)
							{
								if(strcmp(m->name.get(),f->name.get())>=0)
									if(comp_num(m->group,f->group,f->c_group)!=0)
										fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
								m=m->down_name2;
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
						if (comp_num(current->group,f->group,f->c_group)==0)
							fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
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
						int k=(f->name.get()[0]-'A')*RAZN+f->name.get()[1]-'A';
						int sum=0,num=f->phone;
		
						while(num)
						{
							sum+=num%10;
							num=num/10;
						}
						int pok=sum%mod;
						
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
					
									m=m->down_name2;
								}
								break;
							}
							case NE:
							{
								for(i=0;i<RAZN*RAZN+RAZN;i++)
								{
									if(i==k)
									{
										m=hash_name[k];
										while(m)
										{
											if(strcmp(m->name.get(),f->name.get())!=0)
											{
												if(m->modphone==pok)
													if(m->phone==f->phone)
														fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
											}
											m=m->down_name2;
										}
									}
									else
									{
										m=hash_name[i];
										while(m)
										{
											if(m->modphone==pok)
												if(m->phone==f->phone)
													fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
											m=m->down_name2;
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
											if(m->phone==f->phone)
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										m=m->down_name2;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())<0)
										if(m->modphone==pok)
											if(m->phone==f->phone)
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_name2;
								}
								
								break;
							}
							case GT:
							{
								for(i=k+1;i<RAZN*RAZN+RAZN;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(m->modphone==pok)
											if(m->phone==f->phone)
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										m=m->down_name2;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())>0)
										if(m->modphone==pok)
											if(m->phone==f->phone)
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_name2;
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
										m=m->down_name2;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())<=0)
										if(m->modphone==pok)
											if(m->phone==f->phone)
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_name2;
								}
								break;
							}
							case GE:
							{
								for(i=k+1;i<RAZN*RAZN+RAZN;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(m->modphone==pok)
											if(m->phone==f->phone)
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										m=m->down_name2;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())>=0)
										if(m->modphone==pok)
											if(m->phone==f->phone)
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_name2;
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
						
						int k=(f->name.get()[0]-'A')*RAZN+f->name.get()[1]-'A';
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
									m=m->down_name2;
								}
								break;
							}
							case NE:
							{
								for(i=0;i<RAZN*RAZN+RAZN;i++)
								{
									if(i==k)
									{
										m=hash_name[k];
										while(m)
										{
											if(strcmp(m->name.get(),f->name.get())!=0)
												if(comp_num(m->phone,f->phone,f->c_phone)==0)
													fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
											m=m->down_name2;
										}
									}
									else
									{
										m=hash_name[i];
										while(m)
										{
											if(comp_num(m->phone,f->phone,f->c_phone)==0)
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
											m=m->down_name2;
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
										if(comp_num(m->phone,f->phone,f->c_phone)==0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										m=m->down_name2;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())<0)
										if(comp_num(m->phone,f->phone,f->c_phone)==0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_name2;
								}
								
								break;
							}
							case GT:
							{
								for(i=k+1;i<RAZN*RAZN+RAZN;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(comp_num(m->phone,f->phone,f->c_phone)==0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										m=m->down_name2;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())>0)
										if(comp_num(m->phone,f->phone,f->c_phone)==0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_name2;
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
										m=m->down_name2;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())<=0)
										if(comp_num(m->phone,f->phone,f->c_phone)==0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_name2;
								}
								break;
							}
							case GE:
							{
								for(i=k+1;i<RAZN*RAZN+RAZN;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(comp_num(m->phone,f->phone,f->c_phone)==0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										m=m->down_name2;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())>=0)
										if(comp_num(m->phone,f->phone,f->c_phone)==0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_name2;
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
					
					int k=(f->name.get()[0]-'A')*RAZN+f->name.get()[1]-'A';
					int sum=0,num=f->phone;
		
						while(num)
						{
							sum+=num%10;
							num=num/10;
						}
						int pok=sum%mod;
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
									m=m->down_name2;
								}
								break;
							}
							case NE:
							{
								for(i=0;i<RAZN*RAZN+RAZN;i++)
								{
									if(i==k)
									{
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
											m=m->down_name2;
										}
									}
									else
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
											
											m=m->down_name2;
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
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										}
										else
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										
										m=m->down_name2;
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
									m=m->down_name2;
								}
								
								break;
							}
							case GT:
							{
								for(i=k+1;i<RAZN*RAZN+RAZN;i++)
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
										
										m=m->down_name2;
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
									m=m->down_name2;
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
										
										m=m->down_name2;
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
									m=m->down_name2;
								}
								break;
							}
							case GE:
							{
								for(i=k+1;i<RAZN*RAZN+RAZN;i++)
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
										
										m=m->down_name2;
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
									m=m->down_name2;
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
							m=m->down_phone;
						}							
					}
					else
					{
						list_node*m;
					
						int k=(f->name.get()[0]-'A')*RAZN+f->name.get()[1]-'A';
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
									m=m->down_name2;
								}
								break;
							}
							case NE:
							{
								for(i=0;i<RAZN*RAZN+RAZN;i++)
								{
									if(i==k)
									{
										m=hash_name[k];
										while(m)
										{
											if(strcmp(m->name.get(),f->name.get())!=0)
												if(comp_num(m->phone,f->phone,f->c_phone)!=0)
													fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
											m=m->down_name2;
										}
									}
									else
									{
										m=hash_name[i];
										while(m)
										{
											if(comp_num(m->phone,f->phone,f->c_phone)!=0)
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
											m=m->down_name2;
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
										if(comp_num(m->phone,f->phone,f->c_phone)!=0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										m=m->down_name2;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())<0)
										if(comp_num(m->phone,f->phone,f->c_phone)!=0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_name2;
								}
								
								break;
							}
							case GT:
							{
								for(i=k+1;i<RAZN*RAZN+RAZN;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(comp_num(m->phone,f->phone,f->c_phone)!=0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										m=m->down_name2;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())>0)
										if(comp_num(m->phone,f->phone,f->c_phone)!=0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_name2;
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
										m=m->down_name2;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())<=0)
										if(comp_num(m->phone,f->phone,f->c_phone)!=0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_name2;
								}
								break;
							}
							case GE:
							{
								for(i=k+1;i<RAZN*RAZN+RAZN;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(comp_num(m->phone,f->phone,f->c_phone)!=0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										m=m->down_name2;
									}
								}
								
								m=hash_name[k];
								while(m)
								{
									if(strcmp(m->name.get(),f->name.get())>=0)
										if(comp_num(m->phone,f->phone,f->c_phone)!=0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_name2;
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
				int sum=0,num=f->phone;
	
				while(num)
				{
					sum+=num%10;
					num=num/10;
				}
				int k=sum%mod;
				
				switch(f->c_phone)
				{
					case EQ:
					{
						m=hash_phone[k];
						while(m)
						{
							if(m->phone==f->phone)
								fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
							m=m->down_phone;
						}
						break;
					}
					case NE:
					{
						for(i=0;i<mod;i++)
						{
							if(i==k)
							{
								m=hash_phone[k];
								while(m)
								{
									if(m->phone!=f->phone)
										fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_phone;
								}
							}
							else
							{
								m=hash_phone[i];
								while(m)
								{
									fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
									m=m->down_phone;
								}
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
				if (f->oper==AND)
				{				
					list_node*m;
					int sum=0,num=f->phone;
		
					while(num)
					{
						sum+=num%10;
						num=num/10;
					}
					int k=sum%mod;
					
					switch(f->c_phone)
					{
						case EQ:
						{
							m=hash_phone[k];
							while(m)
							{
								if(m->phone==f->phone)
								{
									if(comp_num(m->group,f->group,f->c_group)==0)
										fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
								}
								m=m->down_phone;
							}
							break;
						}
						case NE:
						{
							for(i=0;i<mod;i++)
							{
								if(i==k)
								{
									m=hash_phone[k];
									while(m)
									{
										if(m->phone!=f->phone)
											if(comp_num(m->group,f->group,f->c_group)==0)
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										m=m->down_phone;
									}
								}
								else
								{
									m=hash_phone[i];
									while(m)
									{
										if(comp_num(m->group,f->group,f->c_group)==0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										m=m->down_phone;
									}
								}
							}
							break;
						}
						case LT:
						{
							for (current=head; current != NULL; current=current->next)
							{
								if (current->phone < f->phone)
										if(comp_num(current->group,f->group,f->c_group)==0)
											fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
							}
							break;
						}
						case GT:
						{
							for (current=head; current != NULL; current=current->next)
							{
								if (current->phone > f->phone)
									if(comp_num(current->group,f->group,f->c_group)==0)
										fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
							}
							break;
						}
						case LE:
						{
							for (current=head; current != NULL; current=current->next)
							{
								if (current->phone <= f->phone)
									if(comp_num(current->group,f->group,f->c_group)==0)
										fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
							}
							break;
						}
						case GE:
						{
							for (current=head; current != NULL; current=current->next)
							{
								if (current->phone >= f->phone)
									if(comp_num(current->group,f->group,f->c_group)==0)
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
				}
				else
				{
					list_node*m;
					int sum=0,num=f->phone;
		
					while(num)
					{
						sum+=num%10;
						num=num/10;
					}
					int k=sum%mod;
					
					switch(f->c_phone)
					{
						case EQ:
						{
							m=hash_phone[k];
							while(m)
							{
								if(m->phone==f->phone)
								{
									if(comp_num(m->group,f->group,f->c_group)!=0)
										fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
								}
								m=m->down_phone;
							}
							break;
						}
						case NE:
						{
							for(i=0;i<mod;i++)
							{
								if(i==k)
								{
									m=hash_phone[k];
									while(m)
									{
										if(m->phone!=f->phone)
											if(comp_num(m->group,f->group,f->c_group)!=0)
												fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										m=m->down_phone;
									}
								}
								else
								{
									m=hash_phone[i];
									while(m)
									{
										if(comp_num(m->group,f->group,f->c_group)!=0)
											fprintf(stdout,"%s %d %d\n",m->name.get(),m->phone,m->group);
										m=m->down_phone;
									}
								}
							}
							break;
						}
						case LT:
						{
							for (current=head; current != NULL; current=current->next)
							{
								if (current->phone < f->phone)
									if(comp_num(current->group,f->group,f->c_group)!=0)
										fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
							}
							break;
						}
						case GT:
						{
							for (current=head; current != NULL; current=current->next)
							{
								if (current->phone > f->phone)
									if(comp_num(current->group,f->group,f->c_group)!=0)
										fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
							}
							break;
						}
						case LE:
						{
							for (current=head; current != NULL; current=current->next)
							{
								if (current->phone <= f->phone)
									if(comp_num(current->group,f->group,f->c_group)!=0)
										fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
							}
							break;
						}
						case GE:
						{
							for (current=head; current != NULL; current=current->next)
							{
								if (current->phone >= f->phone)
									if(comp_num(current->group,f->group,f->c_group)!=0)
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
					
					for (current=head; current != NULL; current=current->next)
					{
						if(comp_num(current->group,f->group,f->c_group)==0)
							fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
					}	
				}
				break;
			}
			case 1://group
			{
				for (current=head; current != NULL; current=current->next)
				{
					if (comp_num(current->group,f->group,f->c_group)==0)
						fprintf(stdout,"%s %d %d\n",current->name.get(),current->phone,current->group);
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

}*/

/*int list::comp_name(list_node * a, char * b, cond_type c_name )
{
	int k=(b[0]-'A')*RAZN+b[1]-'A';
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

int list::comp_num(int a, int b,cond_type r)
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

void list::delete_n(command * f)
{
	list_node * a;
	list_node*m;
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
				for (current=head; current != NULL; current=current->next)
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
					for (current=head; current != NULL; current=current->next)
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
					for (current=head; current != NULL; current=current->next)
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
					for (current=head; current != NULL; current=current->next)
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
					for (current=head; current != NULL; current=current->next)
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
				
				
				int k=(f->name.get()[0]-'A')*RAZN+f->name.get()[1]-'A';
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
								m=m->down_name2;
								delete_current(a);
							}
							else
								m=m->down_name2;
						}
						break;
					}
					case NE:
					{
						for(i=0;i<RAZN*RAZN+RAZN;i++)
						{
							if(i==k)
							{
								m=hash_name[k];
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
							}
							else
							{
								m=hash_name[i];
								while(m)
								{
									a=m;
									m=m->down_name2;
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
								a=m;
								m=m->down_name2;
								delete_current(a);
							}
						}
						
						m=hash_name[k];
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
						
						break;
					}
					case GT:
					{
						for(i=k+1;i<RAZN*RAZN+RAZN;i++)
						{
							m=hash_name[i];
							while(m)
							{
								a=m;
								m=m->down_name2;
								delete_current(a);
							}
						}
						
						m=hash_name[k];
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
								m=m->down_name2;
								delete_current(a);
							}
						}
						
						m=hash_name[k];
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
						break;
					}
					case GE:
					{
						for(i=k+1;i<RAZN*RAZN+RAZN;i++)
						{
							m=hash_name[i];
							while(m)
							{
								a=m;
								m=m->down_name2;
								delete_current(a);
							}
						}
						
						m=hash_name[k];
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
					
					int k=(f->name.get()[0]-'A')*RAZN+f->name.get()[1]-'A';
					switch(f->	c_name)
					{
						case EQ:
						{
							m=hash_name[k];
							while(m)
							{
								if(strcmp(m->name.get(),f->name.get())==0)
								{									
									if(comp_num(m->group,f->group,f->c_group)==0)
									{
										a=m;
										m=m->down_name2;
										delete_current(a);
									}
									else
										m=m->down_name2;
								}
								else
									m=m->down_name2;
							}
							break;
						}
						case NE:
						{
							for(i=0;i<RAZN*RAZN+RAZN;i++)
							{
								if(i==k)
								{
									m=hash_name[k];
									while(m)
									{
										if(strcmp(m->name.get(),f->name.get())!=0)
										{
											if(comp_num(m->group,f->group,f->c_group)==0)
											{
												a=m;
												m=m->down_name2;
												delete_current(a);
											}
											else
												m=m->down_name2;
										}
										else
											m=m->down_name2;
									}
								}
								else
								{
									m=hash_name[i];
									while(m)
									{
										if(comp_num(m->group,f->group,f->c_group)==0)
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
						case LT:
						{
							for(i=0;i<k;i++)
							{
								m=hash_name[i];
								while(m)
								{
									if(comp_num(m->group,f->group,f->c_group)==0)
									{
										a=m;
										m=m->down_name2;
										delete_current(a);
									}
									else
										m=m->down_name2;
								}
							}
							
							m=hash_name[k];
							while(m)
							{
								if(strcmp(m->name.get(),f->name.get())<0)
								{
									if(comp_num(m->group,f->group,f->c_group)==0)
									{
										a=m;
										m=m->down_name2;
										delete_current(a);
									}
									else
										m=m->down_name2;
								}
								else
									m=m->down_name2;
							}
							
							break;
						}
						case GT:
						{
							for(i=k+1;i<RAZN*RAZN+RAZN;i++)
							{
								m=hash_name[i];
								while(m)
								{
									if(comp_num(m->group,f->group,f->c_group)==0)
									{
										a=m;
										m=m->down_name2;
										delete_current(a);
									}
									else
										m=m->down_name2;
								}
							}
							
							m=hash_name[k];
							while(m)
							{
								if(strcmp(m->name.get(),f->name.get())>0)
								{
									if(comp_num(m->group,f->group,f->c_group)==0)
									{
										a=m;
										m=m->down_name2;
										delete_current(a);
									}
									else
										m=m->down_name2;
								}
								else
									m=m->down_name2;
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
									if(comp_num(m->group,f->group,f->c_group)==0)
									{
										a=m;
										m=m->down_name2;
										delete_current(a);
									}
									else
										m=m->down_name2;
								}
							}
							
							m=hash_name[k];
							while(m)
							{
								if(strcmp(m->name.get(),f->name.get())<=0)
								{
									if(comp_num(m->group,f->group,f->c_group)==0)
									{
										a=m;
										m=m->down_name2;
										delete_current(a);
									}
									else
										m=m->down_name2;
								}
								else
									m=m->down_name2;
							}
							break;
						}
						case GE:
						{
							for(i=k+1;i<RAZN*RAZN+RAZN;i++)
							{
								m=hash_name[i];
								while(m)
								{
									if(comp_num(m->group,f->group,f->c_group)==0)
									{
										a=m;
										m=m->down_name2;
										delete_current(a);
									}
									else
										m=m->down_name2;
								}
							}
							
							m=hash_name[k];
							while(m)
							{
								if(strcmp(m->name.get(),f->name.get())>=0)
								{
									if(comp_num(m->group,f->group,f->c_group)==0)
									{
										a=m;
										m=m->down_name2;
										delete_current(a);
									}
									else
										m=m->down_name2;
								}
								else
									m=m->down_name2;
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
					int k=(f->name.get()[0]-'A')*RAZN+f->name.get()[1]-'A';
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
										m=m->down_name2;
										delete_current(a);
									}
									else
										m=m->down_name2;
								}
								else
									m=m->down_name2;
							}
							break;
						}
						case NE:
						{
							for(i=0;i<RAZN*RAZN+RAZN;i++)
							{
								if(i==k)
								{
									m=hash_name[k];
									while(m)
									{
										if(strcmp(m->name.get(),f->name.get())!=0)
										{
											if(comp_num(m->group,f->group,f->c_group)!=0)
											{
												a=m;
												m=m->down_name2;
												delete_current(a);
											}
											else
												m=m->down_name2;
										}
										else
											m=m->down_name2;
									}
								}
								else
								{
									m=hash_name[i];
									while(m)
									{
										if(comp_num(m->group,f->group,f->c_group)!=0)
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
										m=m->down_name2;
										delete_current(a);
									}
									else
										m=m->down_name2;
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
										m=m->down_name2;
										delete_current(a);
									}
									else
										m=m->down_name2;
								}
								else
									m=m->down_name2;
							}
							
							break;
						}
						case GT:
						{
							for(i=k+1;i<RAZN*RAZN+RAZN;i++)
							{
								m=hash_name[i];
								while(m)
								{
									if(comp_num(m->group,f->group,f->c_group)!=0)
									{
										a=m;
										m=m->down_name2;
										delete_current(a);
									}
									else
										m=m->down_name2;
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
										m=m->down_name2;
										delete_current(a);
									}
									else
										m=m->down_name2;
								}
								else
									m=m->down_name2;
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
										m=m->down_name2;
										delete_current(a);
									}
									else
										m=m->down_name2;
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
										m=m->down_name2;
										delete_current(a);
									}
									else
										m=m->down_name2;
								}
								else
									m=m->down_name2;
							}
							break;
						}
						case GE:
						{
							for(i=k+1;i<RAZN*RAZN+RAZN;i++)
							{
								m=hash_name[i];
								while(m)
								{
									if(comp_num(m->group,f->group,f->c_group)!=0)
									{
										a=m;
										m=m->down_name2;
										delete_current(a);
									}
									else
										m=m->down_name2;
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
										m=m->down_name2;
										delete_current(a);
									}
									else
										m=m->down_name2;
								}
								else
									m=m->down_name2;
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
					
					for (current=head; current != NULL; )
					{
						if (comp_num(current->group,f->group,f->c_group)==0)
						{
							a=current;
		                    current=current->next;
							delete_current( a );
						}
		                else {
		                    current=current->next;
		                }
					}								
				}		
				break;
			}
			case 110://name phone
			{
				
				
				
				
				
				
				
				
				
				
				
				if (f->oper==AND)
				{
					if(f->c_phone==EQ)
					{
						int k=(f->name.get()[0]-'A')*RAZN+f->name.get()[1]-'A';
						int sum=0,num=f->phone;
		
						while(num)
						{
							sum+=num%10;
							num=num/10;
						}
						int pok=sum%mod;
						
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
												m=m->down_name2;
												delete_current(a);
											}
											else
												m=m->down_name2;
										}
										else
											m=m->down_name2;
									}
									else
										m=m->down_name2;
								}
								break;
							}
							case NE:
							{
								for(i=0;i<RAZN*RAZN+RAZN;i++)
								{
									if(i==k)
									{
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
														m=m->down_name2;
														delete_current(a);
													}
													else
														m=m->down_name2;
												}
												else
													m=m->down_name2;
											}
											else
												m=m->down_name2;
										}
									}
									else
									{
										m=hash_name[i];
										while(m)
										{
											if(m->modphone==pok)
											{
												if(m->phone==f->phone)
												{
													a=m;
													m=m->down_name2;
													delete_current(a);
												}
												else
													m=m->down_name2;
											}
											else
												m=m->down_name2;
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
											if(m->phone==f->phone)
											{
												a=m;
												m=m->down_name2;
												delete_current(a);
											}
											else
												m=m->down_name2;
										}
										else
											m=m->down_name2;
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
												m=m->down_name2;
												delete_current(a);
											}
											else
												m=m->down_name2;
										}
										else
											m=m->down_name2;
									}
									else
										m=m->down_name2;
								}
								
								break;
							}
							case GT:
							{
								for(i=k+1;i<RAZN*RAZN+RAZN;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(m->modphone==pok)
										{
											if(m->phone==f->phone)
											{
												a=m;
												m=m->down_name2;
												delete_current(a);
											}
											else
												m=m->down_name2;
										}
										else
											m=m->down_name2;
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
												m=m->down_name2;
												delete_current(a);
											}
											else
												m=m->down_name2;
										}
										else
											m=m->down_name2;
									}
									else
										m=m->down_name2;
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
												m=m->down_name2;
												delete_current(a);
											}
											else
												m=m->down_name2;
										}
										else
											m=m->down_name2;
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
												m=m->down_name2;
												delete_current(a);
											}
											else
												m=m->down_name2;
										}
										else
											m=m->down_name2;
									}
									else
										m=m->down_name2;
								}
								break;
							}
							case GE:
							{
								for(i=k+1;i<RAZN*RAZN+RAZN;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(m->modphone==pok)
										{
											if(m->phone==f->phone)
											{
												a=m;
												m=m->down_name2;
												delete_current(a);
											}
											else
												m=m->down_name2;
										}
										else
											m=m->down_name2;
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
												m=m->down_name2;
												delete_current(a);
											}
											else
												m=m->down_name2;
										}
										else
											m=m->down_name2;
									}
									else
										m=m->down_name2;
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
						
						int k=(f->name.get()[0]-'A')*RAZN+f->name.get()[1]-'A';
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
											m=m->down_name2;
											delete_current(a);
										}
										else
											m=m->down_name2;
									}
									else
										m=m->down_name2;
								}
								break;
							}
							case NE:
							{
								for(i=0;i<RAZN*RAZN+RAZN;i++)
								{
									if(i==k)
									{
										m=hash_name[k];
										while(m)
										{
											if(strcmp(m->name.get(),f->name.get())!=0)
											{
												if(comp_num(m->phone,f->phone,f->c_phone)==0)
												{
													a=m;
													m=m->down_name2;
													delete_current(a);
												}
												else
													m=m->down_name2;
											}
											else
												m=m->down_name2;
										}
									}
									else
									{
										m=hash_name[i];
										while(m)
										{
											if(comp_num(m->phone,f->phone,f->c_phone)==0)
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
											m=m->down_name2;
											delete_current(a);
										}
										else
											m=m->down_name2;
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
											m=m->down_name2;
											delete_current(a);
										}
										else
											m=m->down_name2;
									}
									else
										m=m->down_name2;
								}
								
								break;
							}
							case GT:
							{
								for(i=k+1;i<RAZN*RAZN+RAZN;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(comp_num(m->phone,f->phone,f->c_phone)==0)
										{
											a=m;
											m=m->down_name2;
											delete_current(a);
										}
										else
											m=m->down_name2;
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
											m=m->down_name2;
											delete_current(a);
										}
										else
											m=m->down_name2;
									}
									else
										m=m->down_name2;
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
											m=m->down_name2;
											delete_current(a);
										}
										else
											m=m->down_name2;
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
											m=m->down_name2;
											delete_current(a);
										}
										else
											m=m->down_name2;
									}
									else
										m=m->down_name2;
								}
								break;
							}
							case GE:
							{
								for(i=k+1;i<RAZN*RAZN+RAZN;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(comp_num(m->phone,f->phone,f->c_phone)==0)
										{
											a=m;
											m=m->down_name2;
											delete_current(a);
										}
										else
											m=m->down_name2;
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
											m=m->down_name2;
											delete_current(a);
										}
										else
											m=m->down_name2;
									}
									else
										m=m->down_name2;
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
					
					int k=(f->name.get()[0]-'A')*RAZN+f->name.get()[1]-'A';
					int sum=0,num=f->phone;
		
						while(num)
						{
							sum+=num%10;
							num=num/10;
						}
						int pok=sum%mod;
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
												m=m->down_name2;
												delete_current(a);
											}
											else
												m=m->down_name2;
										}
										else
										{
											a=m;
											m=m->down_name2;
											delete_current(a);
										}
									}
									else
										m=m->down_name2;
								}
								break;
							}
							case NE:
							{
								for(i=0;i<RAZN*RAZN+RAZN;i++)
								{
									if(i==k)
									{
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
														m=m->down_name2;
														delete_current(a);
													}
													else
														m=m->down_name2;
												}
												else
												{
													a=m;
													m=m->down_name2;
													delete_current(a);
												}
											}
											else
												m=m->down_name2;
										}
									}
									else
									{
										m=hash_name[i];
										while(m)
										{
											if(m->modphone==pok)
											{
												if(m->phone!=f->phone)
												{
													a=m;
													m=m->down_name2;
													delete_current(a);
												}
												else
													m=m->down_name2;
											}
											else
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
												m=m->down_name2;
												delete_current(a);
											}
											else
												m=m->down_name2;
										}
										else
										{
											a=m;
											m=m->down_name2;
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
												m=m->down_name2;
												delete_current(a);
											}
											else
												m=m->down_name2;
										}
										else
										{
											a=m;
											m=m->down_name2;
											delete_current(a);
										}
									}
									else
										m=m->down_name2;
								}
								
								break;
							}
							case GT:
							{
								for(i=k+1;i<RAZN*RAZN+RAZN;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(m->modphone==pok)
										{
											if(m->phone!=f->phone)
											{
												a=m;
												m=m->down_name2;
												delete_current(a);
											}
											else
												m=m->down_name2;
										}
										else
										{
											a=m;
											m=m->down_name2;
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
												m=m->down_name2;
												delete_current(a);
											}
											else
												m=m->down_name2;
										}
										else
										{
											a=m;
											m=m->down_name2;
											delete_current(a);
										}
									}
									else
										m=m->down_name2;
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
												m=m->down_name2;
												delete_current(a);
											}
											else
												m=m->down_name2;
										}
										else
										{
											a=m;
											m=m->down_name2;
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
												m=m->down_name2;
												delete_current(a);
											}
											else
												m=m->down_name2;
										}
										else
										{
											a=m;
											m=m->down_name2;
											delete_current(a);
										}
									}
									else
										m=m->down_name2;
								}
								break;
							}
							case GE:
							{
								for(i=k+1;i<RAZN*RAZN+RAZN;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(m->modphone==pok)
										{
											if(m->phone!=f->phone)
											{
												a=m;
												m=m->down_name2;
												delete_current(a);
											}
											else
												m=m->down_name2;
										}
										else
										{
											a=m;
											m=m->down_name2;
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
												m=m->down_name2;
												delete_current(a);
											}
											else
												m=m->down_name2;
										}
										else
										{
											a=m;
											m=m->down_name2;
											delete_current(a);
										}
									}
									else
										m=m->down_name2;
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
								m=m->down_phone;
								delete_current(a);
							}
							else
								m=m->down_phone;
						}							
					}
					else
					{
						list_node*m;
					
						int k=(f->name.get()[0]-'A')*RAZN+f->name.get()[1]-'A';
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
											m=m->down_name2;
											delete_current(a);
										}
										else
											m=m->down_name2;
									}
									else
										m=m->down_name2;
								}
								break;
							}
							case NE:
							{
								for(i=0;i<RAZN*RAZN+RAZN;i++)
								{
									if(i==k)
									{
										m=hash_name[k];
										while(m)
										{
											if(strcmp(m->name.get(),f->name.get())!=0)
											{
												if(comp_num(m->phone,f->phone,f->c_phone)!=0)
												{
													a=m;
													m=m->down_name2;
													delete_current(a);
												}
												else
													m=m->down_name2;
											}
											else
												m=m->down_name2;
										}
									}
									else
									{
										m=hash_name[i];
										while(m)
										{
											if(comp_num(m->phone,f->phone,f->c_phone)!=0)
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
											m=m->down_name2;
											delete_current(a);
										}
										else
											m=m->down_name2;
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
											m=m->down_name2;
											delete_current(a);
										}
										else
											m=m->down_name2;
									}
									else
										m=m->down_name2;
								}
								
								break;
							}
							case GT:
							{
								for(i=k+1;i<RAZN*RAZN+RAZN;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(comp_num(m->phone,f->phone,f->c_phone)!=0)
										{
											a=m;
											m=m->down_name2;
											delete_current(a);
										}
										else
											m=m->down_name2;
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
											m=m->down_name2;
											delete_current(a);
										}
										else
											m=m->down_name2;
									}
									else
										m=m->down_name2;
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
											m=m->down_name2;
											delete_current(a);
										}
										else
											m=m->down_name2;
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
											m=m->down_name2;
											delete_current(a);
										}
										else
											m=m->down_name2;
									}
									else
										m=m->down_name2;
								}
								break;
							}
							case GE:
							{
								for(i=k+1;i<RAZN*RAZN+RAZN;i++)
								{
									m=hash_name[i];
									while(m)
									{
										if(comp_num(m->phone,f->phone,f->c_phone)!=0)
										{
											a=m;
											m=m->down_name2;
											delete_current(a);
										}
										else
											m=m->down_name2;
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
											m=m->down_name2;
											delete_current(a);
										}
										else
											m=m->down_name2;
									}
									else
										m=m->down_name2;
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
						for (current=head; current != NULL; )
						{
							if (comp_num(current->phone,f->phone,f->c_phone)==0)
							{
								a=current;
								current=current->next;
								delete_current( a );
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
				int sum=0,num=f->phone;
	
				while(num)
				{
					sum+=num%10;
					num=num/10;
				}
				int k=sum%mod;
				
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
								m=m->down_phone;
								delete_current( a );
							}
							else
								m=m->down_phone;
						}
						break;
					}
					case NE:
					{
						for(i=0;i<mod;i++)
						{
							if(i==k)
							{
								m=hash_phone[k];
								while(m)
								{
									if(m->phone!=f->phone)
									{
										a=m;
										m=m->down_phone;
										delete_current( a );
									}
									else
										m=m->down_phone;
								}
							}
							else
							{
								m=hash_phone[i];
								while(m)
								{
									a=m;
									m=m->down_phone;
									delete_current( a );
								}
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
								delete_current( a );
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
								delete_current( a );
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
								delete_current( a );
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
								delete_current( a );
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
				if (f->oper==AND)
				{				
					list_node*m;
					int sum=0,num=f->phone;
		
					while(num)
					{
						sum+=num%10;
						num=num/10;
					}
					int k=sum%mod;
					
					switch(f->c_phone)
					{
						case EQ:
						{
							m=hash_phone[k];
							while(m)
							{
								if(m->phone==f->phone)
								{
									if(comp_num(m->group,f->group,f->c_group)==0)
									{
										a=m;
										m=m->down_phone;
										delete_current( a );
									}
									else
										m=m->down_phone;
								}
								else
									m=m->down_phone;
							}
							break;
						}
						case NE:
						{
							for(i=0;i<mod;i++)
							{
								if(i==k)
								{
									m=hash_phone[k];
									while(m)
									{
										if(m->phone!=f->phone)
										{
											if(comp_num(m->group,f->group,f->c_group)==0)
											{
												a=m;
												m=m->down_phone;
												delete_current( a );
											}
											else
												m=m->down_phone;
										}
										else
											m=m->down_phone;
									}
								}
								else
								{
									m=hash_phone[i];
									while(m)
									{
										if(comp_num(m->group,f->group,f->c_group)==0)
										{
											a=m;
											m=m->down_phone;
											delete_current( a );
										}
										else
											m=m->down_phone;
									}
								}
							}
							break;
						}
						case LT:
						{
							for (current=head; current != NULL;)
							{
								if (current->phone < f->phone)
								{
									if(comp_num(current->group,f->group,f->c_group)==0)
									{
										a=current;
										current=current->next;
										delete_current( a );
									}
									else
										current=current->next;
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
									if(comp_num(current->group,f->group,f->c_group)==0)
									{
										a=current;
										current=current->next;
										delete_current( a );
									}
									else
										current=current->next;
								}
								else
									current=current->next;
									
							}
							break;
						}
						case LE:
						{
							for (current=head; current != NULL; )
							{
								if (current->phone <= f->phone)
								{
									if(comp_num(current->group,f->group,f->c_group)==0)
									{
										a=current;
										current=current->next;
										delete_current( a );
									}
									else
										current=current->next;
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
									if(comp_num(current->group,f->group,f->c_group)==0)
									{
										a=current;
										current=current->next;
										delete_current( a );
									}
									else
										current=current->next;
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
				}
				else
				{
					list_node*m;
					int sum=0,num=f->phone;
		
					while(num)
					{
						sum+=num%10;
						num=num/10;
					}
					int k=sum%mod;
					
					switch(f->c_phone)
					{
						case EQ:
						{
							m=hash_phone[k];
							while(m)
							{
								if(m->phone==f->phone)
								{
									if(comp_num(m->group,f->group,f->c_group)!=0)
									{
										a=m;
										m=m->down_phone;
										delete_current( a );
									}
									else
										m=m->down_phone;
								}
								else
									m=m->down_phone;
							}
							break;
						}
						case NE:
						{
							for(i=0;i<mod;i++)
							{
								if(i==k)
								{
									m=hash_phone[k];
									while(m)
									{
										if(m->phone!=f->phone)
										{
											if(comp_num(m->group,f->group,f->c_group)!=0)
											{
												a=m;
												m=m->down_phone;
												delete_current( a );
											}
											else
												m=m->down_phone;
										}
										else
											m=m->down_phone;
									}
								}
								else
								{
									m=hash_phone[i];
									while(m)
									{
										if(comp_num(m->group,f->group,f->c_group)!=0)
										{
											a=m;
											m=m->down_phone;
											delete_current( a );
										}
										else
											m=m->down_phone;
									}
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
									if(comp_num(current->group,f->group,f->c_group)!=0)
									{
										a=current;
										current=current->next;
										delete_current( a );
									}
									else
										current=current->next;
								}
								else
									current=current->next;
							}
							break;
						}
						case GT:
						{
							for (current=head; current != NULL; )
							{
								if (current->phone > f->phone)
								{
									if(comp_num(current->group,f->group,f->c_group)!=0)
									{
										a=current;
										current=current->next;
										delete_current( a );
									}
									else
										current=current->next;
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
									if(comp_num(current->group,f->group,f->c_group)!=0)
									{
										a=current;
										current=current->next;
										delete_current( a );
									}
									else
										current=current->next;
								}
								else
									current=current->next;
							}
							break;
						}
						case GE:
						{
							for (current=head; current != NULL; )
							{
								if (current->phone >= f->phone)
								{
									if(comp_num(current->group,f->group,f->c_group)!=0)
									{
										a=current;
										current=current->next;
										delete_current( a );
									}
									else
										current=current->next;
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
					
					for (current=head; current != NULL; )
					{
						if(comp_num(current->group,f->group,f->c_group)==0)
						{
							a=current;
							current=current->next;
							delete_current( a );
						}
						else
							current=current->next;
					}	
				}
				break;
			}
			case 1:
			{
		        for (current=head; current != NULL; )
				{
					if (comp_num(current->group,f->group,f->c_group)==0)
					{
						a=current;
		                current=current->next;
						delete_current( a );
					}
                    else {
                        current=current->next;
                    }
				}
				break;
			}
			case 0://group
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
}*/

/*int list::liker(char *b, char ** words, char * buf, int * kol)
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
	
	for(i=i;a[i];i++)
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
		while (buf[j]==0)
			j++;
	
	}
	*kol=k;
	return param;
}

int list::comp_like(char * comm, char ** words, int param, int am)
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

char * list::strlast(char * a, char * b)
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

*/

