/* File : namespace.h */
/* Manajemen selektor ADT */

/* ********** GLOBAL ********** */
#define Neff(X)     (X).Neff
#define Array(X)    (X).T
#define Elmt(X,i)   (X).T[(i)]

/* *** String *** */
#define MaxEl(S)    (S).MaxEl

/* *** Point *** */
#define Absis(P) (P).X
#define Ordinat(P) (P).Y

/* *** Matrix *** */
#define NRowEff(M)      (M).NRowEff
#define NColEff(M)      (M).NColEff
#define ElmtMx(M,i,j)  (M).Mem[(i)][(j)]

/* *** String Stack *** */
#define Top(S)      (S).TOP
#define InfoTop(S)  (S).T[(S).TOP]
