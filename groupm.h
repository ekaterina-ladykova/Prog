# ifndef GROUPM_H
# define GROUPM_H
# include "record.h"
# include "enum.h"
# include "command.h"
# define RAZN 57
#define RAZMNAME 188500
class groupm;
class list;

class groupm
{
    private:
        list ** mas=0;
		list_node ** hash_phone=0;
		list_node ** hash_name=0;
		list_node * head=0;
		int mod = 0;
    public:
		friend class command;
    	groupm(int g)
		{
			mas=new list*[900];
			for(int i=0;i<900;i++)mas[i]=0;
			
			mod =g;
			hash_name= new list_node*[RAZMNAME];
			for(int i=0; i<RAZMNAME;i++) hash_name[i]=0;

			hash_phone= new list_node*[mod];
			for(int i=0;i<mod;i++)hash_phone[i]=0;
		}
		~groupm()
		{
			for(int i=0;i<900;i++)
			{
				if(mas[i])
				{
					delete []mas[i]->hash_name;
					delete []mas[i]->hash_phone;
					delete mas[i];
				}
			}
			
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
			delete []mas;
		}
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
		void print_list_mas()
		{
			list_node *a=head;
			int i=0;
			while(a!=NULL)
			{
				printf("%s %d %d\n",a->name.get(),a->phone,a->group);
				i++;
				a=a->down_group;
				if (i>10) break;
			}
		}
		int read_mas(const char*name, int num);
		void insert(char*name,int phone,int group,int num);
		void print_mas();
		void read_file(FILE * fp, FILE * bf);
		int *make_alfavit(char * t, int * alf);
		void select(command * );
		void delete_n(command * f);
		int liker(char *b, char ** words, char * buf,int * );
        int comp_like(char * comm, char ** words, int param,int);
        char * strlast(char * a, char * b);
		list_node* insert(char * name, int phone, int group );
		int cmp(list_node * a,command * f);
		int comp_name(list_node*a, char * b, cond_type c_name );
		int comp_num(int a, int b, cond_type r);
		void delete_current(list_node *a);
		void perest(list_node*a);
		int poiskvmasphone(list_node*a);
		void printmasphone();
		void perestphone(list_node*a);
		void perestgroup(list_node*a);
		
		
		int masname(list_node*a);
		int poiskvmasname(list_node*a);
		void masphone(list_node*a);
		int poiskvmasphoneinsert(list_node*a);
		void perest_name_global(list_node*a);
		void perest_phone_global(list_node*a);
		int poiskvmasname(command*a);
		int poiskvmasphoneinsert(command*a);
};

#  endif

