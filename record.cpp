# include "record.h"
# define LEN 1234
using namespace std;

int record::init (const char *n, int p, int g)
{
    phone=p;
    group=g;
    if (n)
    {
        name=std::unique_ptr<char []>( new char[strlen(n)+1]);
        if (!this->get_name()) return -1;
        strcpy (name.get(),n);
    }
    else
        name=0;
    return 0;
}

void record::destroy ()
{
    name=0;
    phone =0;
    group=0;
}

/*void record::copy(const record & x )
{
    name=std::move(x.name);
    phone=x.phone;
    group=x.group;
}*/

record::record(const record &x)
{
    init(x.get_name(),x.get_phone(),x.get_group());
}

/*record::record(record &&x)
{
    phone=x.phone;
    group=x.group;
    name=std::move(x.name);
    x.group=0;
    x.phone=0;
    x.name=nullptr;
}*/

/*record & record::operator=(const record &x)
{
    destroy();
    init(x.get_name(),x.get_phone(),x.get_group());
    return (*this);
}

record & record::operator=(record &&x)
{
    destroy();
    phone=x.phone;
    group=x.group;
    name=std::move(x.name);
    x.phone=0;
    x.group=0;
    x.name=nullptr;
    return (*this);
}*/

int record::read(FILE *fp)
{
    char buf[LEN];
    int t=0;
    destroy();
    if ((t=fscanf(fp,"%s%d%d",buf, &phone, &group))!=3)
    {
        if (feof(fp)) return 1;
        return -1;
    }
    if (init(buf,phone,group))
        return -2;
    return 0;
}

void record::print(FILE *fp)
{
	//printf("_____");
    //if (name,get()!=NULL)
        fprintf(fp,"%s %d %d\n",name.get(),phone,group);
   /* else {
        printf("_____Empty name, %d %d\n",phone,group);
    }*/
}
/*
// 0 or 1
int student::operator<(const student &x)
{
    if (!name && !x.name)
        return value<x.value;
    if (!name) return 1;
    if (!x.name) return 0;
    int res=strcmp(name,x.name);
    if (res<0) return 1;
    if (res>0) return 0;
    return value<x.value;
}

int student::operator>(const student &x)
{
    if (!(this->get_name() )&& !x.name)
        return value>x.value;
    if (!(this->get_name())) return 0;
    if (!x.name) return 1;
    int res=strcmp((this->get_name()),x.name);
    if (res<0) return 0;
    if (res>0) return 1;
    return value>x.value;
}

int student::operator==(const student &x)
{
    if ( (!name && !x.name)&& (value==x.value) )
        return 1;
    int res=strcmp(this->get_name(),x.name);
    if ( (res==0)&&(value==x.value) )
        return 1;
    return 0;
}

int student::cmp(const student &x)
{
	if (!(this->get_name()) && !x.name)
        return value<x.value;
    if (!(this->get_name())) return 1;
    if (!x.name) return 0;
    int res=strcmp((this->get_name() ),x.name);
    if (res<0) return 1;
    if (res>0) return 0;
    return value<x.value;
     if (!name && !x.name)
        return value>x.value;
    if (!name) return 0;
    if (!x.name) return 1;
    int res=strcmp(name,x.name);
    if (res<0) return 0;
    if (res>0) return 1;
    return value>x.value;
}*/
