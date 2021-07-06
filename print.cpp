# include "command.h"

void command::print_cmd(FILE * fp, int param)
{
    if (param==0)
    {
        fprintf(fp,"   %-10s| ", "name");
        fprintf(fp,"%-10s| ", "phone");
        fprintf(fp,"%-10s| ", "group");
        fprintf(fp,"%-10s  |","cmd");
        fprintf(fp,"%-5s |","c_name");
        fprintf(fp,"%-5s |","c_phone");
        fprintf(fp,"%-5s |","c_group");
        fprintf(fp,"%-5s","oper");
        fprintf(fp,"\n");
        fprintf(fp,"\n");
    }

    fprintf(fp,"   %-10s| ",name.get());
    fprintf(fp,"%-10d| ", phone);
    fprintf(fp,"%-10d| ", group);

    this->print_cmd_type(fp);
    printf("  |");
    this->print_c(fp,c_name);
    printf("  |");
    this->print_c(fp,c_phone);
    printf("   |");
    this->print_c(fp,c_group);
    printf("   |");
    this->print_op(fp);
}

void command::print(FILE * fp , int param)
{
    switch( type )
	{
		case QUIT:
		{
			fprintf(fp,"quit;\n");
            break;
		}
		case INSERT:
		{
			fprintf(fp,"insert ");
			fprintf(fp,"(");
			fprintf(fp,"%s",name.get());
			fprintf(fp,",");
			fprintf(fp," ");
			fprintf(fp,"%d",phone);
			fprintf(fp,",");
			fprintf(fp," ");
			fprintf(fp,"%d",group);
			fprintf(fp,")");
			fprintf(fp,";\n");
            break;
		}
		case STOP:
		{
			fprintf(fp,"stop;\n");
           	break;
		}
		case SELECT:
		{
			fprintf(fp,"select ");
            fprintf(fp,"*");
            
            if (name != 0)
            {
            	fprintf(fp," where");
            	if (param==0)
            	{
            		fprintf(fp," ");
		        	fprintf(fp,"name");
		        	fprintf(fp," ");
		        	print_c_file(fp,c_name);
		        	fprintf(fp," ");
		        	fprintf(fp,"%s",name.get());
		        	if ( oper!=OP_NONE)
		        	{
		        		fprintf(fp," ");
		        		print_op(fp);
		        		fprintf(fp," ");
		        		if (phone!=-1)
						{
							fprintf(fp,"phone");
							fprintf(fp," ");
		                    print_c_file(fp,c_phone);
		                    fprintf(fp," ");
							fprintf(fp,"%d",phone);
						}
						if (group!=-1)
						{
							fprintf(fp,"group");
							fprintf(fp," ");
		                    print_c_file(fp,c_group);
		                    fprintf(fp," ");
							fprintf(fp,"%d",group);
						}
		        		
		        	}
            	}
            	else
            	{
            		fprintf(fp," ");
            		if (phone!=-1)
					{
						fprintf(fp,"phone");
						fprintf(fp," ");
	                    print_c_file(fp,c_phone);
	                    fprintf(fp," ");
						fprintf(fp,"%d",phone);
					}
					if (group!=-1)
					{
						fprintf(fp,"group");
						fprintf(fp," ");
	                    print_c_file(fp,c_group);
	                    fprintf(fp," ");
						fprintf(fp,"%d",group);
					}
					fprintf(fp," ");
		        	print_op(fp);
					fprintf(fp," ");
		        	fprintf(fp,"name");
		        	fprintf(fp," ");
		        	print_c_file(fp,c_name);
		        	fprintf(fp," ");
		        	fprintf(fp,"%s",name.get());
            	}
            	
            	fprintf(fp,";\n");
            }
            else
            {
            	if (phone != -1)
            	{
            		fprintf(fp," where");
            		if (param==0)
            		{
            			fprintf(fp," ");
						fprintf(fp,"phone");
						fprintf(fp," ");
                        print_c_file(fp,c_phone);
                        fprintf(fp," ");
                        fprintf(fp,"%d",phone);

                       	if ( oper!=OP_NONE)
						{
                            fprintf(fp," ");
                            print_op(fp);
                            fprintf(fp," ");
							fprintf(fp,"group");
							fprintf(fp," ");
                            print_c_file(fp,c_group);
                            fprintf(fp," ");
							fprintf(fp,"%d",group);
						}
						fprintf(fp,";\n");
            		}
            		else
            		{
            			fprintf(fp," ");
						fprintf(fp,"group");
						fprintf(fp," ");
                        print_c_file(fp,c_group);
                        fprintf(fp," ");
						fprintf(fp,"%d",group);
						fprintf(fp," ");
                        print_op(fp);
                        fprintf(fp," ");
						fprintf(fp,"phone");
						fprintf(fp," ");
                        print_c_file(fp,c_phone);
                        fprintf(fp," ");
                        fprintf(fp,"%d",phone);
                        fprintf(fp,";\n");
            		}
            	}
            	else
            	{
            		if (group!=-1)
            		{
            			fprintf(fp," where");
            			fprintf(fp," ");
						fprintf(fp,"group");
						fprintf(fp," ");
                        print_c_file(fp,c_group);
                        fprintf(fp," ");
						fprintf(fp,"%d",group);
						fprintf(fp,";\n");
            		}
            		else
            		{
            			fprintf(fp,";\n");
            		}
            	}
            }
            break;
		}
		case DELETE:
		{
			fprintf(fp,"delete");
            if (name != 0)
            {
            	fprintf(fp," where");
            	if (param==0)
            	{
            		fprintf(fp," ");
		        	fprintf(fp,"name");
		        	fprintf(fp," ");
		        	print_c_file(fp,c_name);
		        	fprintf(fp," ");
		        	fprintf(fp,"%s",name.get());
		        	if ( oper!=OP_NONE)
		        	{
		        		fprintf(fp," ");
		        		print_op(fp);
		        		fprintf(fp," ");
		        		if (phone!=-1)
						{
							fprintf(fp,"phone");
							fprintf(fp," ");
		                    print_c_file(fp,c_phone);
		                    fprintf(fp," ");
							fprintf(fp,"%d",phone);
						}
						if (group!=-1)
						{
							fprintf(fp,"group");
							fprintf(fp," ");
		                    print_c_file(fp,c_group);
		                    fprintf(fp," ");
							fprintf(fp,"%d",group);
						}
		        		
		        	}
            	}
            	else
            	{
            		fprintf(fp," ");
            		if (phone!=-1)
					{
						fprintf(fp,"phone");
						fprintf(fp," ");
	                    print_c_file(fp,c_phone);
	                    fprintf(fp," ");
						fprintf(fp,"%d",phone);
					}
					if (group!=-1)
					{
						fprintf(fp,"group");
						fprintf(fp," ");
	                    print_c_file(fp,c_group);
	                    fprintf(fp," ");
						fprintf(fp,"%d",group);
					}
					fprintf(fp," ");
		        	print_op(fp);
					fprintf(fp," ");
		        	fprintf(fp,"name");
		        	fprintf(fp," ");
		        	print_c_file(fp,c_name);
		        	fprintf(fp," ");
		        	fprintf(fp,"%s",name.get());
            	}
            	
            	fprintf(fp,";\n");
            }
            else
            {
            	if (phone != -1)
            	{
            		fprintf(fp," where");
            		if (param==0)
            		{
            			fprintf(fp," ");
						fprintf(fp,"phone");
						fprintf(fp," ");
                        print_c_file(fp,c_phone);
                        fprintf(fp," ");
                        fprintf(fp,"%d",phone);

                       	if ( oper!=OP_NONE)
						{
                            fprintf(fp," ");
                            print_op(fp);
                            fprintf(fp," ");
							fprintf(fp,"group");
							fprintf(fp," ");
                            print_c_file(fp,c_group);
                            fprintf(fp," ");
							fprintf(fp,"%d",group);
						}
						fprintf(fp,";\n");
            		}
            		else
            		{
            			fprintf(fp," ");
						fprintf(fp,"group");
						fprintf(fp," ");
                        print_c_file(fp,c_group);
                        fprintf(fp," ");
						fprintf(fp,"%d",group);
						fprintf(fp," ");
                        print_op(fp);
                        fprintf(fp," ");
						fprintf(fp,"phone");
						fprintf(fp," ");
                        print_c_file(fp,c_phone);
                        fprintf(fp," ");
                        fprintf(fp,"%d",phone);
                        fprintf(fp,";\n");
            		}
            	}
            	else
            	{
            		if (group!=-1)
            		{
            			fprintf(fp," where");
            			fprintf(fp," ");
						fprintf(fp,"group");
						fprintf(fp," ");
                        print_c_file(fp,c_group);
                        fprintf(fp," ");
						fprintf(fp,"%d",group);
						fprintf(fp,";\n");
            		}
            		else
            		{
            			fprintf(fp,";\n");
            		}
            	}
            }
            break;
		}
		case CMD_NONE:
		{
			fprintf(fp,"none\n");
            break;
		}
	}
}

void command::print_cmd_type_file(FILE * fp)
{
        switch( type )
        {
                case QUIT:
                {
                        fprintf(fp,"quit");
                        break;
                }
                case INSERT:
                {
                        fprintf(fp,"insert");
                        break;
                }
                case STOP:
                {
                        fprintf(fp,"stop");
                        break;
                }
                case SELECT:
                {
                        fprintf(fp,"select");
                        break;
                }
                case DELETE:
                {
                        fprintf(fp,"delete");
                        break;
                }
                case CMD_NONE:
                {
                        fprintf(fp,"none");
                        break;
                }
        }
}

void command::print_c_file(FILE * fp, cond_type y)
{
        switch(y)
        {
                case EQ:
                {
                        fprintf(fp,"=");
                        break;
                }
                case NE:
                {
                        fprintf(fp,"<>");
                        break;
                }
                case LT:
                {
                        fprintf(fp,"<");
                        break;
                }
                case GT:
                {
                        fprintf(fp,">");
                        break;
                }
                case LE:
                {
                        fprintf(fp,"<=");
                        break;
                }
                case GE:
                {
                        fprintf(fp,">=");
                        break;
                }
                case LIKE:
                {
                        fprintf(fp,"like");
                        break;
                }
                case COND_NONE:
                {
                        fprintf(fp,"none");
                        break;
                }
        }
}


void command::print_cmd_type(FILE * fp)
{
        switch( type )
	{
		case QUIT:
		{
                        fprintf(fp,"%-10s","quit");
                        break;
		}
		case INSERT:
		{
                        fprintf(fp,"%-10s","insert");
                        break;
		}
		case STOP:
		{
                        fprintf(fp,"%-10s","stop");
                        break;
		}
		case SELECT:
		{
                        fprintf(fp,"%-10s","select");
                        break;
		}
		case DELETE:
		{
                        fprintf(fp,"%-10s","delete");
                        break;
		}
		case CMD_NONE:
		{
                        fprintf(fp,"%-10s","none");
                        break;
		}
	}
}

void command::print_c(FILE * fp, cond_type y)
{
	switch(y)
	{
		case EQ:
		{
                        fprintf(fp,"%-5s","=");
                        break;
		}
		case NE:
		{
                        fprintf(fp,"%-5s","<>");
                        break;
		}
		case LT:
		{
                        fprintf(fp,"%-5s","<");
                        break;
		}
		case GT:
		{
                        fprintf(fp,"%-5s",">");
                        break;
		}
		case LE:
		{
                        fprintf(fp,"%-5s","<=");
                        break;
		}
		case GE:
		{
                        fprintf(fp,"%-5s",">=");
                        break;
		}
		case LIKE:
		{
                        fprintf(fp,"%-5s","like");
                        break;
		}
                case COND_NONE:
		{
                        fprintf(fp,"%-5s","none");
                        break;
		}
	}
}

void command::print_op(FILE * fp)
{
        switch( oper )
	{
		case AND:
		{
			fprintf(fp,"and");
                        break;
		}
		case OR:
		{
			fprintf(fp,"or");
                        break;
		}
		case OP_NONE:
		{
			fprintf(fp,"none");
                        break;
		}
	}
}
