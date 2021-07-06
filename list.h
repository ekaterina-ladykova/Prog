# ifndef LIST_H
# define LIST_H
# include "record.h"
# include "list_node.h"
# include "enum.h"
# include "command.h"

class list;
class command;

class list
{
    private:
        list_node * head=0;//
        list_node * current=0;////
		list_node **hash_name=0;
		list_node **hash_phone=0;
		int mod=0;
    public:
    	friend class command;
		friend class groupm;
		int read_list(const char * name,int num);
		void delete_list();
		list_node * get_head()
		{
			return head;
		}
		//void read_file(FILE * fp, FILE * bf);
		int liker(char *b, char ** words, char * buf,int * );
        int comp_like(char * comm, char ** words, int param,int);
        char * strlast(char * a, char * b);
		//int * make_alfavit(char * t, int * alf);
		list_node* insert(char * name, int phone, int group );
		int cmp(list_node * a,command * f);
		//void select(command * );
		int comp_name(list_node*a, char * b, cond_type c_name );
		int comp_num(int a, int b, cond_type r);
		void delete_current(list_node *a);
		//void delete_n(command * f);
		void print_list()
		{
			list_node *a=head;
			int i=0;
			while(a!=NULL)
			{
				printf("%s %d %d\n",a->name.get(),a->phone,a->group);
				i++;
				a=a->next;
				if (i>10) break;
			}
		}
		int mas(list_node*a);
		int poiskvmas(list_node*a);
		void printmas();
		//void perest(list_node*a);
		void masphone(list_node*a);
		int poiskvmasphone(list_node*a);
		void printmasphone();
		//void perestphone(list_node*a);
		void print_list_mas()
		{
			list_node *a=head;
			int i=0;
			printf("           group \n");
			while(a!=NULL)
			{
				printf("%s %d %d %d\n",a->name.get(),a->phone,a->group, a->place);
				i++;
				a=a->down_group;
				if (i>10) break;
			}
			/*printf("           phone\n");
			printmasphone();
			printf("           name\n");
			printmas();*/
		}
};

#  endif

