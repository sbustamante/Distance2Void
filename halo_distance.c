#include <allvars.h>

//Usage ./Halo_Distance.out <halos_filename> <voids_filename> <output_filename>
int main( int argc, char *argv[] )
{   
    //Individual halos
    struct halo *halos;
    halos = (struct halo *)calloc( MAXHALOS, sizeof( struct halo ) );
    //Void Matrix
    struct void_cell *void_matrix;
    void_matrix = (struct void_cell *)calloc( MAXCELLS, sizeof( struct void_cell ) );
    
    char filename[NMAX1];
    float p[NMAX1];

    printf( "\n\n************************ HALO DISTANCE CATALOG ***********************\n" );
    //Load Configuration-----------------------------------------------------------------------
    read_parameters( p, "parameters.conf" );
    
    //Loading halos datafile-------------------------------------------------------------------
    p[NDAT] = data_in_halos( halos, argv[1] );

    //Loading voids datafile-------------------------------------------------------------------
    data_in_voids( void_matrix, argv[2], p[NBOX] );
    
    //Calculating discrete positions of halos--------------------------------------------------
    halo_position( halos, p );
    
    //Calculating catalog of distances to void regions-----------------------------------------
    distances( halos, void_matrix, p );

    //Calculating catalog of distances to void regions-----------------------------------------
    data_out( halos, argv[3], p );
    
    return 0;
}