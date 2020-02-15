
#define MAXINPUTLENGTH 2000
#define TOKENLENGTH 30 //number of max input -1
#define MAXCOMMANDS 2	

struct ProcessGroup {
	int startIndex;
	int size;
	int type;
	struct ProcessGroup *next;

};
typedef struct ProcessGroup groups;
