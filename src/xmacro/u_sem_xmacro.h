#ifdef DEFINE_U_VARIABLES
#define U_EXTERN /* nothing */
#else
#define U_EXTERN extern
#endif /* DEFINE_VARIABLES */


#define SEM_EXPAND_AS_VARIABLES(a,b) U_EXTERN u_sem a;
U_SEM_TABLE(SEM_EXPAND_AS_VARIABLES);

#define SEM_EXPAND_AS_STRUCT(a,b) u08 a;


/*  declare a struct with a 1-byte field for every entry */ 
typedef struct{
    U_SEM_TABLE(SEM_EXPAND_AS_STRUCT)
} sem_size_struct_t;


#define U_NUM_SEM  sizeof(sem_size_struct_t)

// #define SEM_EXPAND_AS_ENUMERATION(a,b) a, 
/* declare an enumeration */ 
//enum{
//    U_SEM_TABLE(SEM_EXPAND_AS_ENUMERATION)
//}







