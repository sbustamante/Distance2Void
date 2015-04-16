/**************************************************************************************************
			      MACROS
**************************************************************************************************/
//General Macros
#define MAXHALOS	500000
#define MAXCELLS	17000000
#define MAXNEIGH	10

#define NMAX1		1000

//Macros for Parameters
#define NBOX		0
#define LBOX		1
#define LREG		2
#define NNEI		3
#define NDAT		4

#define X		0
#define Y		1
#define Z		2

/**************************************************************************************************
			      STRUCTURES
**************************************************************************************************/   
struct halo{
    //Positions
    float r[3];
    //Velocities
    float v[3];
    //Mass
    float Mass;
    //Id
    int id;
    //Id of original file
    int id_or;

    //Cell occupied
    int i_cell[3];
    
    //The nearest cell of the nearest void
    int i_void[MAXNEIGH][3];
    
    //Distance to the three closer voids
    float distance[MAXNEIGH];
    //Id of closer voids
    int id_voids[MAXNEIGH];
    };
    
struct void_cell{
    //Id of this cell
    int id[3];
    //Id of whole region
    int id_reg;
    };
    
/**************************************************************************************************
			      HEADERS
**************************************************************************************************/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <proto.h>