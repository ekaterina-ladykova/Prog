# ifndef COMMAND_H
# define COMMAND_H
# include "record.h"
# include "enum.h"
# include "list.h"
# include <memory>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# define LEN 1234
class command;
class list;
class groupm;

class command: public record
{
	private:
		cmd_type type=CMD_NONE;
		cond_type c_name=COND_NONE;
		cond_type c_phone=COND_NONE;
		cond_type c_group=COND_NONE;
		op_type oper=OP_NONE;
		int order=0;
	public:
		friend class list;
		friend class groupm;
		int parse(char * s, char ** word, int * alf);
		void print(FILE * fp , int param);
        void print_c_file(FILE * fp, cond_type y);
		int print_cmd (FILE * out);
        void print_cmd_type_file(FILE * fp);
        char ** division(char * s, int * alf, char ** word);
        void print_cmd_type(FILE * fp);
        void print_c(FILE * fp, cond_type y);
        void print_op(FILE * fp);
        void print_cmd(FILE * fp, int param);
        cond_type sign(char * s);
        int division(char * s, char *t, char ** words);
        int parse(char * s, char ** words, int * alf,char * t);
        //int * make_alfavit(char * t, int * alf);
        //void read_file (FILE * fp, FILE * bf);
        int work(groupm * a );
        void select();
        int comp_name(char * a);
        int comp_ot(int a, int ind);
        void insert(list * a);
        int cmp(list_node * a);
        int get_phone()
        {
        	return phone;
        }
        int get_group()
        {
        	return group;
        }
};

#endif 





