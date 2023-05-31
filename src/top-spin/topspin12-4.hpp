/*
MIRA PEDRO, PROMETI NO TOCAR NI EL .H NI EL .C, PERO
NO PROMETI NO CREAR UN .HPP. NO ME PUEDES RECLAMAR MAGDITO.

Por como estoy trabajando, necesito una forma de diferenciar entre
las operaciones del objeto y las operaciones del topspin, por eso necesito
el namespace :'v.
*/

#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <inttypes.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

namespace top_spin
{
  
#define __STDC_FORMAT_MACROS
#define __STDC_LIMIT_MACROS

#define psvn2c_PSVN_API

#define HAVE_FWD_MOVE_PRUNING
#define HAVE_BWD_MOVES
#define HAVE_BWD_MOVE_PRUNING
#define HAVE_ABSTRACTION


/* number of variables in a state */
#define NUMVARS 12


typedef int8_t var_t;
#define PRI_VAR PRId8
#define SCN_VAR SCNd8

#define NUMDOMAINS 1
static var_t domain_sizes[ NUMDOMAINS ] = { 12 };
static const char *name_of_domain[ NUMDOMAINS ] = { "12N" };
static int var_domains[ NUMVARS ] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static const char *domain_0[ 12 ] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12" };
static const char **domain_to_domain_names[ NUMDOMAINS ] = { domain_0 };
static const char **var_domain_names[ NUMVARS ] = { domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0 };

typedef struct {
 var_t vars[ NUMVARS ];
} state_t;

typedef int (*funcptr)( const state_t *, void * );
typedef void (*actfuncptr)( const state_t *, state_t * );

typedef struct {
 const state_t *my_state;
 funcptr my_funcptr;
} ruleid_iterator_t;

#define num_fwd_rules 12
#define num_bwd_rules 12
static const char *fwd_rule_name[ 12 ] = { "rule_1", "rule_2", "rule_3", "rule_4", "rule_5", "rule_6", "rule_7", "rule_8", "rule_9", "rule_10", "rule_11", "rule_12" };
#define get_fwd_rule_label( ruleid ) (fwd_rule_name[(ruleid)]) 
static const char *bwd_rule_name[ 12 ] = { "rule_1", "rule_2", "rule_3", "rule_4", "rule_5", "rule_6", "rule_7", "rule_8", "rule_9", "rule_10", "rule_11", "rule_12" };
#define get_bwd_rule_label( ruleid ) (bwd_rule_name[(ruleid)]) 
#define cost_of_cheapest_fwd_rule 1
#define cost_of_costliest_fwd_rule 12
static const int fwd_rule_cost[ 12 ] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
#define get_fwd_rule_cost( ruleid ) (fwd_rule_cost[(ruleid)]) 
#define cost_of_cheapest_bwd_rule 1
#define cost_of_costliest_bwd_rule 12
static const int bwd_rule_cost[ 12 ] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
#define get_bwd_rule_cost( ruleid ) (bwd_rule_cost[(ruleid)]) 

static int fwd_rule_label_sets[144] = {0,1,2,3,4,5,6,7,8,9,10,11,0,1,2,3,4,5,6,7,8,9,10,11,0,1,2,3,4,5,6,7,8,9,10,11,0,1,2,3,4,5,6,7,8,9,10,11,0,1,2,3,4,5,6,7,8,9,10,11,0,1,2,3,4,5,6,7,8,9,10,11,0,1,2,3,4,5,6,7,8,9,10,11,0,1,2,3,4,5,6,7,8,9,10,11,0,1,2,3,4,5,6,7,8,9,10,11,0,1,2,3,4,5,6,7,8,9,10,11,0,1,2,3,4,5,6,7,8,9,10,11,0,1,2,3,4,5,6,7,8,9,10,11};

static int bwd_rule_label_sets[144] = {0,1,2,3,4,5,6,7,8,9,10,11,0,1,2,3,4,5,6,7,8,9,10,11,0,1,2,3,4,5,6,7,8,9,10,11,0,1,2,3,4,5,6,7,8,9,10,11,0,1,2,3,4,5,6,7,8,9,10,11,0,1,2,3,4,5,6,7,8,9,10,11,0,1,2,3,4,5,6,7,8,9,10,11,0,1,2,3,4,5,6,7,8,9,10,11,0,1,2,3,4,5,6,7,8,9,10,11,0,1,2,3,4,5,6,7,8,9,10,11,0,1,2,3,4,5,6,7,8,9,10,11,0,1,2,3,4,5,6,7,8,9,10,11};

static int fwd_prune_table[ 156 ] = { 12, 24, 36, 48, 60, 72, 84, 96, 108, 120, 132, 144, 0, 24, 36, 48, 60, 72, 84, 96, 108, 120, 132, 144, 12, 24, 36, 48, 60, 72, 84, 96, 108, 120, 132, 144, 12, 24, 36, 48, 60, 72, 84, 96, 108, 120, 132, 144, 12, 24, 36, 48, 60, 72, 84, 96, 108, 120, 132, 144, 12, 24, 36, 48, 60, 72, 84, 96, 108, 120, 132, 144, 12, 24, 36, 48, 60, 72, 84, 96, 108, 120, 132, 144, 12, 24, 36, 48, 60, 72, 84, 96, 108, 120, 132, 144, 12, 24, 36, 48, 60, 72, 84, 96, 108, 120, 132, 144, 12, 24, 36, 48, 60, 72, 84, 96, 108, 120, 132, 144, 12, 24, 36, 48, 60, 72, 84, 96, 108, 120, 132, 144, 12, 24, 36, 48, 60, 72, 84, 96, 108, 120, 132, 144, 12, 24, 36, 48, 60, 72, 84, 96, 108, 120, 132, 144 };

static void fwdrule1( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 3 ];
  child_state->vars[ 1 ] = state->vars[ 2 ];
  child_state->vars[ 2 ] = state->vars[ 1 ];
  child_state->vars[ 3 ] = state->vars[ 0 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
}

static void fwdrule2( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 4 ];
  child_state->vars[ 1 ] = state->vars[ 3 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 1 ];
  child_state->vars[ 4 ] = state->vars[ 5 ];
  child_state->vars[ 5 ] = state->vars[ 6 ];
  child_state->vars[ 6 ] = state->vars[ 7 ];
  child_state->vars[ 7 ] = state->vars[ 8 ];
  child_state->vars[ 8 ] = state->vars[ 9 ];
  child_state->vars[ 9 ] = state->vars[ 10 ];
  child_state->vars[ 10 ] = state->vars[ 11 ];
  child_state->vars[ 11 ] = state->vars[ 0 ];
}

static void fwdrule3( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 5 ];
  child_state->vars[ 1 ] = state->vars[ 4 ];
  child_state->vars[ 2 ] = state->vars[ 3 ];
  child_state->vars[ 3 ] = state->vars[ 2 ];
  child_state->vars[ 4 ] = state->vars[ 6 ];
  child_state->vars[ 5 ] = state->vars[ 7 ];
  child_state->vars[ 6 ] = state->vars[ 8 ];
  child_state->vars[ 7 ] = state->vars[ 9 ];
  child_state->vars[ 8 ] = state->vars[ 10 ];
  child_state->vars[ 9 ] = state->vars[ 11 ];
  child_state->vars[ 10 ] = state->vars[ 0 ];
  child_state->vars[ 11 ] = state->vars[ 1 ];
}

static void fwdrule4( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 6 ];
  child_state->vars[ 1 ] = state->vars[ 5 ];
  child_state->vars[ 2 ] = state->vars[ 4 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 7 ];
  child_state->vars[ 5 ] = state->vars[ 8 ];
  child_state->vars[ 6 ] = state->vars[ 9 ];
  child_state->vars[ 7 ] = state->vars[ 10 ];
  child_state->vars[ 8 ] = state->vars[ 11 ];
  child_state->vars[ 9 ] = state->vars[ 0 ];
  child_state->vars[ 10 ] = state->vars[ 1 ];
  child_state->vars[ 11 ] = state->vars[ 2 ];
}

static void fwdrule5( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 7 ];
  child_state->vars[ 1 ] = state->vars[ 6 ];
  child_state->vars[ 2 ] = state->vars[ 5 ];
  child_state->vars[ 3 ] = state->vars[ 4 ];
  child_state->vars[ 4 ] = state->vars[ 8 ];
  child_state->vars[ 5 ] = state->vars[ 9 ];
  child_state->vars[ 6 ] = state->vars[ 10 ];
  child_state->vars[ 7 ] = state->vars[ 11 ];
  child_state->vars[ 8 ] = state->vars[ 0 ];
  child_state->vars[ 9 ] = state->vars[ 1 ];
  child_state->vars[ 10 ] = state->vars[ 2 ];
  child_state->vars[ 11 ] = state->vars[ 3 ];
}

static void fwdrule6( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 8 ];
  child_state->vars[ 1 ] = state->vars[ 7 ];
  child_state->vars[ 2 ] = state->vars[ 6 ];
  child_state->vars[ 3 ] = state->vars[ 5 ];
  child_state->vars[ 4 ] = state->vars[ 9 ];
  child_state->vars[ 5 ] = state->vars[ 10 ];
  child_state->vars[ 6 ] = state->vars[ 11 ];
  child_state->vars[ 7 ] = state->vars[ 0 ];
  child_state->vars[ 8 ] = state->vars[ 1 ];
  child_state->vars[ 9 ] = state->vars[ 2 ];
  child_state->vars[ 10 ] = state->vars[ 3 ];
  child_state->vars[ 11 ] = state->vars[ 4 ];
}

static void fwdrule7( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 9 ];
  child_state->vars[ 1 ] = state->vars[ 8 ];
  child_state->vars[ 2 ] = state->vars[ 7 ];
  child_state->vars[ 3 ] = state->vars[ 6 ];
  child_state->vars[ 4 ] = state->vars[ 10 ];
  child_state->vars[ 5 ] = state->vars[ 11 ];
  child_state->vars[ 6 ] = state->vars[ 0 ];
  child_state->vars[ 7 ] = state->vars[ 1 ];
  child_state->vars[ 8 ] = state->vars[ 2 ];
  child_state->vars[ 9 ] = state->vars[ 3 ];
  child_state->vars[ 10 ] = state->vars[ 4 ];
  child_state->vars[ 11 ] = state->vars[ 5 ];
}

static void fwdrule8( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 10 ];
  child_state->vars[ 1 ] = state->vars[ 9 ];
  child_state->vars[ 2 ] = state->vars[ 8 ];
  child_state->vars[ 3 ] = state->vars[ 7 ];
  child_state->vars[ 4 ] = state->vars[ 11 ];
  child_state->vars[ 5 ] = state->vars[ 0 ];
  child_state->vars[ 6 ] = state->vars[ 2 ];
  child_state->vars[ 7 ] = state->vars[ 1 ];
  child_state->vars[ 8 ] = state->vars[ 3 ];
  child_state->vars[ 9 ] = state->vars[ 4 ];
  child_state->vars[ 10 ] = state->vars[ 5 ];
  child_state->vars[ 11 ] = state->vars[ 6 ];
}

static void fwdrule9( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 11 ];
  child_state->vars[ 1 ] = state->vars[ 10 ];
  child_state->vars[ 2 ] = state->vars[ 9 ];
  child_state->vars[ 3 ] = state->vars[ 8 ];
  child_state->vars[ 4 ] = state->vars[ 0 ];
  child_state->vars[ 5 ] = state->vars[ 1 ];
  child_state->vars[ 6 ] = state->vars[ 2 ];
  child_state->vars[ 7 ] = state->vars[ 3 ];
  child_state->vars[ 8 ] = state->vars[ 4 ];
  child_state->vars[ 9 ] = state->vars[ 5 ];
  child_state->vars[ 10 ] = state->vars[ 6 ];
  child_state->vars[ 11 ] = state->vars[ 7 ];
}

static void fwdrule10( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 11 ];
  child_state->vars[ 2 ] = state->vars[ 10 ];
  child_state->vars[ 3 ] = state->vars[ 9 ];
  child_state->vars[ 4 ] = state->vars[ 1 ];
  child_state->vars[ 5 ] = state->vars[ 2 ];
  child_state->vars[ 6 ] = state->vars[ 3 ];
  child_state->vars[ 7 ] = state->vars[ 4 ];
  child_state->vars[ 8 ] = state->vars[ 5 ];
  child_state->vars[ 9 ] = state->vars[ 6 ];
  child_state->vars[ 10 ] = state->vars[ 7 ];
  child_state->vars[ 11 ] = state->vars[ 8 ];
}

static void fwdrule11( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 1 ];
  child_state->vars[ 1 ] = state->vars[ 0 ];
  child_state->vars[ 2 ] = state->vars[ 11 ];
  child_state->vars[ 3 ] = state->vars[ 10 ];
  child_state->vars[ 4 ] = state->vars[ 2 ];
  child_state->vars[ 5 ] = state->vars[ 3 ];
  child_state->vars[ 6 ] = state->vars[ 4 ];
  child_state->vars[ 7 ] = state->vars[ 5 ];
  child_state->vars[ 8 ] = state->vars[ 6 ];
  child_state->vars[ 9 ] = state->vars[ 7 ];
  child_state->vars[ 10 ] = state->vars[ 8 ];
  child_state->vars[ 11 ] = state->vars[ 9 ];
}

static void fwdrule12( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 2 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 0 ];
  child_state->vars[ 3 ] = state->vars[ 11 ];
  child_state->vars[ 4 ] = state->vars[ 3 ];
  child_state->vars[ 5 ] = state->vars[ 4 ];
  child_state->vars[ 6 ] = state->vars[ 5 ];
  child_state->vars[ 7 ] = state->vars[ 6 ];
  child_state->vars[ 8 ] = state->vars[ 7 ];
  child_state->vars[ 9 ] = state->vars[ 8 ];
  child_state->vars[ 10 ] = state->vars[ 9 ];
  child_state->vars[ 11 ] = state->vars[ 10 ];
}

static actfuncptr fwd_rules[ 12 ] = { fwdrule1, fwdrule2, fwdrule3, fwdrule4, fwdrule5, fwdrule6, fwdrule7, fwdrule8, fwdrule9, fwdrule10, fwdrule11, fwdrule12 };

static int fwdfn0_r11( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = NULL;
  return 11;
}

static int fwdfn0_r10( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn0_r11;
  return 10;
}

static int fwdfn0_r9( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn0_r10;
  return 9;
}

static int fwdfn0_r8( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn0_r9;
  return 8;
}

static int fwdfn0_r7( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn0_r8;
  return 7;
}

static int fwdfn0_r6( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn0_r7;
  return 6;
}

static int fwdfn0_r5( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn0_r6;
  return 5;
}

static int fwdfn0_r4( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn0_r5;
  return 4;
}

static int fwdfn0_r3( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn0_r4;
  return 3;
}

static int fwdfn0_r2( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn0_r3;
  return 2;
}

static int fwdfn0_r1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn0_r2;
  return 1;
}

static int fwdfn0_r0( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn0_r1;
  return 0;
}

static int bwd_prune_table[ 156 ] = { 12, 24, 36, 48, 60, 72, 84, 96, 108, 120, 132, 144, 0, 24, 36, 48, 60, 72, 84, 96, 108, 120, 132, 144, 12, 24, 36, 48, 60, 72, 84, 96, 108, 120, 132, 144, 12, 24, 36, 48, 60, 72, 84, 96, 108, 120, 132, 144, 12, 24, 36, 48, 60, 72, 84, 96, 108, 120, 132, 144, 12, 24, 36, 48, 60, 72, 84, 96, 108, 120, 132, 144, 12, 24, 36, 48, 60, 72, 84, 96, 108, 120, 132, 144, 12, 24, 36, 48, 60, 72, 84, 96, 108, 120, 132, 144, 12, 24, 36, 48, 60, 72, 84, 96, 108, 120, 132, 144, 12, 24, 36, 48, 60, 72, 84, 96, 108, 120, 132, 144, 12, 24, 36, 48, 60, 72, 84, 96, 108, 120, 132, 144, 12, 24, 36, 48, 60, 72, 84, 96, 108, 120, 132, 144, 12, 24, 36, 48, 60, 72, 84, 96, 108, 120, 132, 144 };

static void bwdrule1( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 3 ];
  child_state->vars[ 1 ] = state->vars[ 2 ];
  child_state->vars[ 2 ] = state->vars[ 1 ];
  child_state->vars[ 3 ] = state->vars[ 0 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
}

static void bwdrule2( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 11 ];
  child_state->vars[ 1 ] = state->vars[ 3 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 1 ];
  child_state->vars[ 4 ] = state->vars[ 0 ];
  child_state->vars[ 5 ] = state->vars[ 4 ];
  child_state->vars[ 6 ] = state->vars[ 5 ];
  child_state->vars[ 7 ] = state->vars[ 6 ];
  child_state->vars[ 8 ] = state->vars[ 7 ];
  child_state->vars[ 9 ] = state->vars[ 8 ];
  child_state->vars[ 10 ] = state->vars[ 9 ];
  child_state->vars[ 11 ] = state->vars[ 10 ];
}

static void bwdrule3( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 10 ];
  child_state->vars[ 1 ] = state->vars[ 11 ];
  child_state->vars[ 2 ] = state->vars[ 3 ];
  child_state->vars[ 3 ] = state->vars[ 2 ];
  child_state->vars[ 4 ] = state->vars[ 1 ];
  child_state->vars[ 5 ] = state->vars[ 0 ];
  child_state->vars[ 6 ] = state->vars[ 4 ];
  child_state->vars[ 7 ] = state->vars[ 5 ];
  child_state->vars[ 8 ] = state->vars[ 6 ];
  child_state->vars[ 9 ] = state->vars[ 7 ];
  child_state->vars[ 10 ] = state->vars[ 8 ];
  child_state->vars[ 11 ] = state->vars[ 9 ];
}

static void bwdrule4( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 9 ];
  child_state->vars[ 1 ] = state->vars[ 10 ];
  child_state->vars[ 2 ] = state->vars[ 11 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 2 ];
  child_state->vars[ 5 ] = state->vars[ 1 ];
  child_state->vars[ 6 ] = state->vars[ 0 ];
  child_state->vars[ 7 ] = state->vars[ 4 ];
  child_state->vars[ 8 ] = state->vars[ 5 ];
  child_state->vars[ 9 ] = state->vars[ 6 ];
  child_state->vars[ 10 ] = state->vars[ 7 ];
  child_state->vars[ 11 ] = state->vars[ 8 ];
}

static void bwdrule5( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 8 ];
  child_state->vars[ 1 ] = state->vars[ 9 ];
  child_state->vars[ 2 ] = state->vars[ 10 ];
  child_state->vars[ 3 ] = state->vars[ 11 ];
  child_state->vars[ 4 ] = state->vars[ 3 ];
  child_state->vars[ 5 ] = state->vars[ 2 ];
  child_state->vars[ 6 ] = state->vars[ 1 ];
  child_state->vars[ 7 ] = state->vars[ 0 ];
  child_state->vars[ 8 ] = state->vars[ 4 ];
  child_state->vars[ 9 ] = state->vars[ 5 ];
  child_state->vars[ 10 ] = state->vars[ 6 ];
  child_state->vars[ 11 ] = state->vars[ 7 ];
}

static void bwdrule6( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 7 ];
  child_state->vars[ 1 ] = state->vars[ 8 ];
  child_state->vars[ 2 ] = state->vars[ 9 ];
  child_state->vars[ 3 ] = state->vars[ 10 ];
  child_state->vars[ 4 ] = state->vars[ 11 ];
  child_state->vars[ 5 ] = state->vars[ 3 ];
  child_state->vars[ 6 ] = state->vars[ 2 ];
  child_state->vars[ 7 ] = state->vars[ 1 ];
  child_state->vars[ 8 ] = state->vars[ 0 ];
  child_state->vars[ 9 ] = state->vars[ 4 ];
  child_state->vars[ 10 ] = state->vars[ 5 ];
  child_state->vars[ 11 ] = state->vars[ 6 ];
}

static void bwdrule7( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 6 ];
  child_state->vars[ 1 ] = state->vars[ 7 ];
  child_state->vars[ 2 ] = state->vars[ 8 ];
  child_state->vars[ 3 ] = state->vars[ 9 ];
  child_state->vars[ 4 ] = state->vars[ 10 ];
  child_state->vars[ 5 ] = state->vars[ 11 ];
  child_state->vars[ 6 ] = state->vars[ 3 ];
  child_state->vars[ 7 ] = state->vars[ 2 ];
  child_state->vars[ 8 ] = state->vars[ 1 ];
  child_state->vars[ 9 ] = state->vars[ 0 ];
  child_state->vars[ 10 ] = state->vars[ 4 ];
  child_state->vars[ 11 ] = state->vars[ 5 ];
}

static void bwdrule8( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 5 ];
  child_state->vars[ 1 ] = state->vars[ 7 ];
  child_state->vars[ 2 ] = state->vars[ 6 ];
  child_state->vars[ 3 ] = state->vars[ 8 ];
  child_state->vars[ 4 ] = state->vars[ 9 ];
  child_state->vars[ 5 ] = state->vars[ 10 ];
  child_state->vars[ 6 ] = state->vars[ 11 ];
  child_state->vars[ 7 ] = state->vars[ 3 ];
  child_state->vars[ 8 ] = state->vars[ 2 ];
  child_state->vars[ 9 ] = state->vars[ 1 ];
  child_state->vars[ 10 ] = state->vars[ 0 ];
  child_state->vars[ 11 ] = state->vars[ 4 ];
}

static void bwdrule9( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 4 ];
  child_state->vars[ 1 ] = state->vars[ 5 ];
  child_state->vars[ 2 ] = state->vars[ 6 ];
  child_state->vars[ 3 ] = state->vars[ 7 ];
  child_state->vars[ 4 ] = state->vars[ 8 ];
  child_state->vars[ 5 ] = state->vars[ 9 ];
  child_state->vars[ 6 ] = state->vars[ 10 ];
  child_state->vars[ 7 ] = state->vars[ 11 ];
  child_state->vars[ 8 ] = state->vars[ 3 ];
  child_state->vars[ 9 ] = state->vars[ 2 ];
  child_state->vars[ 10 ] = state->vars[ 1 ];
  child_state->vars[ 11 ] = state->vars[ 0 ];
}

static void bwdrule10( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 4 ];
  child_state->vars[ 2 ] = state->vars[ 5 ];
  child_state->vars[ 3 ] = state->vars[ 6 ];
  child_state->vars[ 4 ] = state->vars[ 7 ];
  child_state->vars[ 5 ] = state->vars[ 8 ];
  child_state->vars[ 6 ] = state->vars[ 9 ];
  child_state->vars[ 7 ] = state->vars[ 10 ];
  child_state->vars[ 8 ] = state->vars[ 11 ];
  child_state->vars[ 9 ] = state->vars[ 3 ];
  child_state->vars[ 10 ] = state->vars[ 2 ];
  child_state->vars[ 11 ] = state->vars[ 1 ];
}

static void bwdrule11( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 1 ];
  child_state->vars[ 1 ] = state->vars[ 0 ];
  child_state->vars[ 2 ] = state->vars[ 4 ];
  child_state->vars[ 3 ] = state->vars[ 5 ];
  child_state->vars[ 4 ] = state->vars[ 6 ];
  child_state->vars[ 5 ] = state->vars[ 7 ];
  child_state->vars[ 6 ] = state->vars[ 8 ];
  child_state->vars[ 7 ] = state->vars[ 9 ];
  child_state->vars[ 8 ] = state->vars[ 10 ];
  child_state->vars[ 9 ] = state->vars[ 11 ];
  child_state->vars[ 10 ] = state->vars[ 3 ];
  child_state->vars[ 11 ] = state->vars[ 2 ];
}

static void bwdrule12( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 2 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 0 ];
  child_state->vars[ 3 ] = state->vars[ 4 ];
  child_state->vars[ 4 ] = state->vars[ 5 ];
  child_state->vars[ 5 ] = state->vars[ 6 ];
  child_state->vars[ 6 ] = state->vars[ 7 ];
  child_state->vars[ 7 ] = state->vars[ 8 ];
  child_state->vars[ 8 ] = state->vars[ 9 ];
  child_state->vars[ 9 ] = state->vars[ 10 ];
  child_state->vars[ 10 ] = state->vars[ 11 ];
  child_state->vars[ 11 ] = state->vars[ 3 ];
}

static actfuncptr bwd_rules[ 12 ] = { bwdrule1, bwdrule2, bwdrule3, bwdrule4, bwdrule5, bwdrule6, bwdrule7, bwdrule8, bwdrule9, bwdrule10, bwdrule11, bwdrule12 };

static int bwdfn0_r11( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = NULL;
  return 11;
}

static int bwdfn0_r10( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn0_r11;
  return 10;
}

static int bwdfn0_r9( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn0_r10;
  return 9;
}

static int bwdfn0_r8( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn0_r9;
  return 8;
}

static int bwdfn0_r7( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn0_r8;
  return 7;
}

static int bwdfn0_r6( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn0_r7;
  return 6;
}

static int bwdfn0_r5( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn0_r6;
  return 5;
}

static int bwdfn0_r4( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn0_r5;
  return 4;
}

static int bwdfn0_r3( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn0_r4;
  return 3;
}

static int bwdfn0_r2( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn0_r3;
  return 2;
}

static int bwdfn0_r1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn0_r2;
  return 1;
}

static int bwdfn0_r0( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn0_r1;
  return 0;
}


#define init_history 0

#define max_fwd_children 12

/* NOTE: FOR ALL OF THE MOVE ITERATOR DEFINITIONS funcptr
   MUST BE A VARIABLE. */

/* initialise a forward move iterator */
#define init_fwd_iter( ruleid_iter, state ) { \
  (*ruleid_iter).my_funcptr = fwdfn0_r0 ; \
  (*ruleid_iter).my_state = state; \
}

/* use iterator to generate next applicable rule to apply 
   returns rule to use, -1 if there are no more rules to apply */
#define next_ruleid( ruleid_iter ) (((*ruleid_iter).my_funcptr)?((*ruleid_iter).my_funcptr)((*ruleid_iter).my_state,&((*ruleid_iter).my_funcptr)):-1)

/* apply a rule to a state */
#define apply_fwd_rule( rule, state, result ) fwd_rules[(rule)](state,result)
/* returns 0 if the rule is pruned, non-zero otherwise */
#define fwd_rule_valid_for_history( history, rule_used ) (fwd_prune_table[(history)+(rule_used)])
/* generate the next history from the current history and a rule */
#define next_fwd_history( history, rule_used ) (fwd_prune_table[(history)+(rule_used)])


static const int bw_max_children = 12;
#define max_bwd_children 12

/* initialise a backwards move iterator */
#define init_bwd_iter( ruleid_iter, state ) { \
  (*ruleid_iter).my_funcptr = bwdfn0_r0 ; \
  (*ruleid_iter).my_state = state; \
}

/* apply a rule to a state */
#define apply_bwd_rule( rule, state, result ) bwd_rules[(rule)](state,result)
/* returns 0 if the rule is pruned, non-zero otherwise */
#define bwd_rule_valid_for_history( history, rule_used ) (bwd_prune_table[(history)+(rule_used)])
/* generate the next history from the current history and a rule */
#define next_bwd_history( history, rule_used ) (bwd_prune_table[(history)+(rule_used)])


/* returns 1 if state is a goal state, 0 otherwise */
static int is_goal( const state_t *state )
{
  if( state->vars[ 0 ] == 0 && state->vars[ 1 ] == 1 && state->vars[ 2 ] == 2 && state->vars[ 3 ] == 3 && state->vars[ 4 ] == 4 && state->vars[ 5 ] == 5 && state->vars[ 6 ] == 6 && state->vars[ 7 ] == 7 && state->vars[ 8 ] == 8 && state->vars[ 9 ] == 9 && state->vars[ 10 ] == 10 && state->vars[ 11 ] == 11 ) {
    return 1;
  }
  return 0;
}

static void init_goal_state( state_t *state, int goal_rule )
{
  switch( goal_rule ) {
  case 0:
    state->vars[ 0 ] = 0;
    state->vars[ 1 ] = 1;
    state->vars[ 2 ] = 2;
    state->vars[ 3 ] = 3;
    state->vars[ 4 ] = 4;
    state->vars[ 5 ] = 5;
    state->vars[ 6 ] = 6;
    state->vars[ 7 ] = 7;
    state->vars[ 8 ] = 8;
    state->vars[ 9 ] = 9;
    state->vars[ 10 ] = 10;
    state->vars[ 11 ] = 11;
    break;
  }
}

/* get the first goal state and initialise iterator */
#define first_goal_state( state_ptr, int_ptr_goal_iter ) init_goal_state(state_ptr,*(int_ptr_goal_iter)=0)

/* get the next goal state
   returns 1 if there is another goal state, 0 otherwise */
static int8_t next_goal_state( state_t *state, int *goal_iter )
{
  switch( *goal_iter ) {
  case 0:
    return 0;
  }
  return 0;
}

}