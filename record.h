# ifndef RECORD_H
# define RECORD_H
# include <memory>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>

class record
{
	private:
		std::unique_ptr<char []> name=NULL;
		int phone=0;
		int group=0;
	public:
		friend class command;
		friend class list;
		friend class groupm;
		record() = default;
		~record() { destroy(); };
		const char  * get_name () const
		{
		    return name.get();
		}
		int get_phone() const
		{
		    return phone;
		}
		int get_group() const
		{
		    return group;
		}
		int init (const char *n, int p, int g);
        record(const record &x);
        void print(FILE *fp);
		void destroy ();
        int read(FILE *fp);
		/*int read (FILE *);
		void delete_student();
		void copy(const student & x );
		void print (FILE * fp);
		int operator<=(const student &x);
		int operator<(const student &x);
		int operator>(const student &x);
		int operator==(const student &x);*/
		
};

# endif
