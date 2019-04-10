

struct BSTNODE;

typedef struct valueobject
{
    char *type;
    
    int ival;
    double rval;
    char *sval;
    struct BSTNODE *bstValue;
} value;

typedef struct BSTNODE {
    int value;
    struct BSTNODE *nextNode;
    struct BSTNODE *previousNode;
    int weight;
    int level;
    struct BSTNODE *child;
} BSTNode;

extern value *newBSTNodeValue(BSTNode *v);
extern value *newIntegerValue(int);
extern value *newRealValue(double);
extern value *newStringValue(char *);
extern value *newVariableValue(char *);
extern value *newOperatorValue(char *);
extern value *newSemicolonValue(void);
extern void displayValue(FILE *,value *);

extern char *INTEGER;
extern char *REAL;
extern char *STRING;
extern char *VARIABLE;
extern char *OPERATOR;
extern char *SEMICOLON;
extern char *BSTNODE;
