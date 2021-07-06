# ifndef LIST_NODE_H
# include "record.h"
# define LIST_NODE_H

class list_node: public record
{
    private:
        list_node * next=0;
        list_node * prev=0;
		///внутри группы
		list_node * down_group=0;
		list_node * up_group = 0;
		list_node * down_name2=0;
		list_node * up_name2=0;
		list_node * down_phone=0;
		list_node * up_phone=0;
		//во всем
		list_node * down_n=0;
		list_node * up_n=0;
		list_node * down_p=0;
		list_node * up_p=0;
		int modphone=0;
		int place=0;
    public: 
    	friend class list;
		friend class groupm;
		
};
#  endif
