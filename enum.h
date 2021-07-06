# ifndef ENUM_H
# define ENUM_H


enum cmd_type { CMD_NONE, QUIT, STOP, SELECT, INSERT, DELETE };
enum cond_type { COND_NONE, EQ, NE, LT, GT, LE, GE, LIKE };
enum op_type { OP_NONE, AND, OR };

# endif
