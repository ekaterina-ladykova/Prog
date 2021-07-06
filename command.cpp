# include "command.h"
# include "list.h"
# include "list_node.h"
# include "groupm.h"
# define LEN 1234



int command::work(groupm * a)
{
	switch ( type )
	{
		case QUIT:
		{
			//printf("QUIT\n");
			return 0;
		}
		case INSERT:
		{
			
           // printf("Insert\n");
			a->insert(this->name.get(),this->phone,this->group,a->mod);
			//a->print_list();
			//printf("\n");
			return 1;
		}
		case SELECT:
		{
           //printf("Select\n");
			a->select(this);
			//printf("\n");
			return 2;
		}
		case DELETE:
		{
           //printf("Delete_%d\n",oper);
            a->delete_n(this);
			//a->print_mas();
			//printf("\n");
			return 4;
		}
        case CMD_NONE:
        {
            break;
        }
        case STOP:
        {
            return 0;

        }

	}
	return 1;
}

cond_type command::sign(char * s)
{
	if ( strcmp(s,"=")==0 ) { return EQ; }
	else
	{
		if ( strcmp(s,"<>")==0 ) { return NE; }
		else
		{
			if ( strcmp(s,"<")==0 ) { return LT; }  
			else
			{
				if ( strcmp(s,">")==0 ) { return GT; }
				else
				{
					if (strcmp(s,"<=") ==0) { return LE; }
					else
					{
						if (strcmp(s,">=")==0) { return GE; }
						else
						{
							if (strcmp(s,"like")==0) { return LIKE; }
						}
					}
				}
			}
		}
        }
        return COND_NONE;
}


int command::parse(char * s, char ** words, int * alf,char * t)
{
    int param=0;
    (void)alf;
    int k=0;
    k=division(s,t,words);
    if (k==0) return -1;
	
    if ( strcmp(words[0],"quit")==0 )
	{
		type=QUIT;
		c_name=COND_NONE;
        c_phone=COND_NONE;
        c_group=COND_NONE;
        oper=OP_NONE;
        init(0,-1,-1);
		
	}
	else
	{
		if ( strcmp(words[0],"stop")==0 )
		{
			type=STOP;
			c_name=COND_NONE;
            c_phone=COND_NONE;
            c_group=COND_NONE;
            oper=OP_NONE;
            init(0,-1,-1);
		}
		else
		{
			if ( strcmp(words[0],"select")==0 )
			{//select
				type=SELECT;
                if (k<3) 
                {
                	c_name=COND_NONE;
                    c_phone=COND_NONE;
                    c_group=COND_NONE;
                    oper=OP_NONE;
                    init(0,-1,-1);
                    order = 0;
                	return 0;
                }
                if ( (strcmp( words[1], "*" ) == 0 )&&( strcmp(words[2], "where")==0 ) )
				{
					if ( strcmp(words[3],"name")==0 )
					{//name
                        c_name=sign(words[4]); ///!!!!
                        init(words[5],-1,-1);
                        c_phone=COND_NONE;
                        c_group=COND_NONE;
                        oper=OP_NONE;
						param=0;
						order=100;
                    	if (k<7) return 0;
                        if (words[6]!=NULL)
						{
                            if ( strcmp(words[6],"and")==0 ) { oper =AND; }
                            else { if ( strcmp(words[6], "or")==0 ) { oper =OR; } }
							
                            if ( strcmp(words[7],"phone")==0 )
							{
                                c_phone=sign(words[8]);///!!!!!
                                c_group=COND_NONE;
                                init(words[5],atoi(words[9]),-1);
                                order=110;
							}
							else
							{
                                if ( strcmp(words[7],"group")==0 )
								{
                                    c_group=sign(words[8]);//||||
                                    c_phone=COND_NONE;
                                    init(words[5],-1,atoi(words[9]));
                                    order=101;
								}
								else return -1;
							}
						}
						
					}//name
					else
					{//else not name
						if ( strcmp(words[3],"phone")==0 )
						{//phone
                            c_phone=sign(words[4]); ///!!!!
							init(0,atoi(words[5]),-1);
                            c_name=COND_NONE;
                            c_group=COND_NONE;
                            oper=OP_NONE;
							order=10;
							param=0;
                            if (k<7) return 0;
                            if (words[6]!=NULL)
							{
		                        if ( strcmp(words[6],"and")==0 ) { oper =AND; }
		                        else { if ( strcmp(words[6],"or")==0 ) { oper =OR; } }
		                        if ( strcmp(words[7],"name")==0 )
								{
		                            c_name=sign(words[8]); ///!!!!!
		                            c_group=COND_NONE;
									init(words[9],atoi(words[5]),-1);
									param=1;
									order=110;
								}
								else
								{
                                    if ( strcmp(words[7],"group")==0 )
									{
                                        c_group=sign(words[8]);//||||
                                        c_name=COND_NONE;
										init(0,atoi(words[5]),atoi(words[9]));
										param=0;
										order=11;
									}
									else return -1;
								}
							}
						}//phone
						else
						{//else not name, not phone
							if ( strcmp(words[3],"group")==0 )
							{//group
                                c_group=sign(words[4]);  ///!!!!
								init(0,-1,atoi(words[5]));
                                c_name=COND_NONE;
                                c_phone=COND_NONE;
                                oper=OP_NONE;
								order=1;
								param=0;
                                if (k<7) return 0;
                                if (words[6]!=NULL)
								{
                                    if ( strcmp(words[6],"and")==0 ) { oper=AND; }
                                    else { if ( strcmp(words[6],"or")==0 ) { oper=OR; } }
                                    if ( strcmp(words[7],"name")==0 )
									{
                                        c_name=sign(words[8]);///!!!!!
                                        c_phone=COND_NONE;
										init(words[9],-1,atoi(words[5]));
										order=101;
									}
									else
									{
		                                if ( strcmp(words[7],"phone")==0 )
										{
		                                    c_phone=sign(words[8]);//||||
		                                    c_name=COND_NONE;
		                                    init(0,atoi(words[9]),atoi(words[5]));
		                                    order=11;
										}
										else
										{
											return -1;
										}
											
									}
									param=1;
								}
							}//group
							else
							{
								return -1;
							}
						}//else not name, not phone
					}//else not name
				}
				else
				{
					return -1;
				}
			}//select
			else
			{
				if ( strcmp(words[0],"insert")==0 )
				{
					type=INSERT;
                    init(words[1],atoi(words[2]),atoi(words[3]));
                    c_name=COND_NONE;
                    c_phone=COND_NONE;
                    c_group=COND_NONE;
                    oper=OP_NONE;
				}
				else
				{
					if ( strcmp(words[0],"delete")==0 )
					{//delete
                        //printf("*\n");
						type=DELETE;
                        if (k<2)
                        {
                            //printf("LOL\n");
                            c_name=COND_NONE;
                            c_phone=COND_NONE;
                            c_group=COND_NONE;
                            oper=OP_NONE;
                            init(0,-1,-1);
                            order=0;
                            return 0;
                        }
						if (strcmp(words[1], "where")==0 )
						{
                            // printf("2\n");
							if ( strcmp(words[2],"name")==0 )
							{//name
                               // printf("1\n");
                                c_name=sign(words[3]); ///!!!!
                                init(words[4],-1,-1);
                                c_phone=COND_NONE;
                                c_group=COND_NONE;
                                oper =OP_NONE;
								order=100;
								param=0;
                                if(k<6) return 0;
                                if (words[5]!=NULL)
								{
                                    if ( strcmp(words[5],"and")==0 ) { oper =AND; }
                                    else { if ( strcmp(words[5], "or")==0 ) { oper =OR; } }
									
                                    if ( strcmp(words[6],"phone")==0 )
									{
                                        c_phone=sign(words[7]);///!!!!!
                                        c_group=COND_NONE;
                                        init(words[4],atoi(words[8]),-1);
                                        order=110;
									}
									else
									{
                                        if ( strcmp(words[6],"group")==0 )
										{
                                            c_group=sign(words[7]);//||||
                                            c_phone=COND_NONE;
                                            init(words[4],-1,atoi(words[8]));
                                            order=101;
										}
										else return -1;
									}
									param=0;
								}
							}//name
							else
							{//else not name
								if ( strcmp(words[2],"phone")==0 )
								{//phone
                                	//printf("3\n");
                                    c_phone=sign(words[3]); ///!!!!
									init(0,atoi(words[4]),-1);
                                    c_name=COND_NONE;
                                    c_group=COND_NONE;
                                    oper =OP_NONE;
									order=10;
									param=0;
                                    if(k<6) return 0;
                                    if (words[5]!=NULL)
									{
		                                //printf("88\n");
		                                if ( strcmp(words[5],"and")==0 ) { oper =AND; }
		                                else { if ( strcmp(words[5],"or")==0 ) { oper=OR; } }
		                                if ( strcmp(words[6],"name")==0 )
										{
                                            c_name=sign(words[7]); ///!!!!!
                                            c_group=COND_NONE;
											init(words[8],atoi(words[4]),-1);
											param=1;
											order=110;
										}
										else
										{
                                            if ( strcmp(words[6],"group")==0 )
											{
                                                c_group=sign(words[7]);//||||
                                                c_name=COND_NONE;
												init(0,atoi(words[4]),atoi(words[8]));
												param=0;
												order=11;
											}
											else return -1;
										}
									}
								}//phone
								else
								{//else not name, not phone
									if ( strcmp(words[2],"group")==0 )
									{//group
                                        c_group=sign(words[3]);  ///!!!!
										init(0,-1,atoi(words[4]));
                                        c_name=COND_NONE;
                                        c_phone=COND_NONE;
                                        oper =OP_NONE;
										order=1;
										param=0;
                                        if(k<6) return 0;
                                        if (words[5]!=NULL)
										{
                                            if ( strcmp(words[5],"and")==0 ) { oper =AND; }
                                            else { if ( strcmp(words[5],"or")==0 ) { oper =OR; } }
                                            if ( strcmp(words[6],"name")==0 )
											{
                                                c_name=sign(words[7]);///!!!!!
                                                c_phone=COND_NONE;
												init(words[8],-1,atoi(words[4]));
												order=101;
											}
											else
											{
                                                if ( strcmp(words[6],"phone")==0 )
												{
                                                    c_phone=sign(words[7]);//||||
                                                    c_name=COND_NONE;
													init(0,atoi(words[8]),atoi(words[4]));
													order=11;
												}
												else return -1;
											}
											param=1;
										}
									}//group
								}//else not name, not phone
							}//else not name
						}
						else
						{
							return -1;
						}
					}//delete
				}
			}
		}
	}
        return param;
}


int command::division(char * s, char *t, char ** word)
{
        int i=0;
        char *q=strtok(s,t);
        word[i]=q;

        while (q!=NULL)
        {
                i++;
                q=strtok(NULL,t);
                word[i]=q;
        }
        return i;
}









