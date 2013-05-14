#ifndef __O_H__
#define __O_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
    
#if UINTPTR_MAX == 0xffffffff
#define OMAX_UTIL_GET_LEN_AND_PTR \
if(argc != 3){\
    error("%s: expected 2 arguments but got %d", __func__, argc);\
    return;\
}\
if(argv->a_type != A_FLOAT){\
    error("%s: argument 1 should be a float", __func__);\
    return;\
}\
if(argv[1].a_type != A_FLOAT){\
    error("%s: argument 2 should be a symbol", __func__);\
    return;\
}\
if(argv[2].a_type != A_FLOAT){\
    error("%s: argument 2 should be a symbol", __func__);\
    return;\
}\
float ff = atom_getfloat(&argv[0]);\
long len = (long)*((uint32_t *)&ff);\
ff = atom_getfloat(&argv[1]);\
uint64_t l1 = *((uint64_t *)&ff);\
l1 <<= 32;\
ff = atom_getfloat(&argv[2]);\
uint64_t l2 = *((uint64_t *)&ff);\
char *ptr = (char *)(l1 | l2);
    
#elif UINTPTR_MAX == 0xffffffffffffffff
#define OMAX_UTIL_GET_LEN_AND_PTR \
if(argc != 2){\
object_error((t_object *)x, "%s: expected 2 arguments but got %d", __func__, argc);\
return;\
}\
if(atom_gettype(argv) != A_LONG){\
object_error((t_object *)x, "%s: argument 1 should be an int", __func__);\
return;\
}\
if(atom_gettype(argv + 1) != A_LONG){\
object_error((t_object *)x, "%s: argument 2 should be an int", __func__);\
return;\
}\
long len = atom_getlong(argv);\
long ptr = (long)(argv[1].a_w.w_symbol);
#else
#warning wtf
#endif
// that stupid macro above used to be defined in osc.h.  I moved it here but
// was too lazy to change all the files that used it, so we have this #define below.
// As I visit each of the files, I'll change it and then this can be removed...
#define OSC_GET_LEN_AND_PTR OMAX_UTIL_GET_LEN_AND_PTR

#ifdef OMAX_PD_VERSION
#include "m_pd.h"
#include "string.h"
#define proxy_getinlet(x) (0)  //<<< TEMPORORY

#define critical_enter(x)
#define critical_exit(x)
#define critical_free(x)
#define critical_new(x)
#define t_critical void*
#define object_post(x, st, ...) post(st, ##__VA_ARGS__)
#define object_error(x, st, ...) error(st, ##__VA_ARGS__)

#define A_SYM   A_SYMBOL
#define A_LONG  A_CANT
#define OMAX_DICT_DICTIONARY(o, x, st)

#define object_alloc(class) pd_new(class)

void atom_setfloat(t_atom *atom, t_float f)
{
    SETFLOAT(atom, f);
}

void atom_setlong(t_atom *atom, long l)
{
    SETFLOAT(atom, (float)l);
}

void atom_setsym(t_atom *atom, t_symbol *s)
{
    SETSYMBOL(atom, s);
}

t_int atom_getlong(t_atom *atom)
{
    return atom_getint(atom);
}

t_symbol *atom_getsym(t_atom *atom)
{
    return atom_getsymbol(atom);
}

t_atomtype atom_gettype(t_atom *atom)
{
    return atom->a_type;
}
    
void outlet_atoms(void *out, short argc, t_atom *argv)
{
    if (argc == 1) {
        if (argv->a_type == A_FLOAT)
            outlet_float((t_outlet *)out,argv->a_w.w_float);
        else if (argv->a_type == A_SYM)
            outlet_anything((t_outlet *)out,argv->a_w.w_symbol,0,0);
    } else {
        if (argv->a_type == A_FLOAT)
            outlet_list((t_outlet *)out,&s_list, argc, argv);
        else if (argv->a_type == A_SYM)
            outlet_anything((t_outlet *)out,argv->a_w.w_symbol,argc-1,argv+1);
    }
}

void outlet_int(void *outlet, int i)
{
    outlet_float((t_outlet *)outlet, (float)i);
}    
#endif
#endif