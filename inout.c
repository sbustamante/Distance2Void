#include <allvars.h>

/**************************************************************************************************
 NAME:	     conf2dump
 FUNCTION:   To convert a data file text in plain text 
 INPUTS:     name of configuration file
 RETURN:     0
**************************************************************************************************/
int conf2dump( char filename[] )
{
    char cmd[NMAX1];
    sprintf( cmd, "grep -v \"#\" %s | grep -v \"^$\" | gawk -F\"=\" '{print $2}' > %s.dump", 
	     filename, filename );
    system( cmd );

    return 0;
}


/**************************************************************************************************
 NAME:       in2dump
 FUNCTION:   To convert a data file text in plain text 
 INPUTS:     name of configuration file
 RETURN:     0
**************************************************************************************************/
int in2dump( char filename[] )
{
    char cmd[NMAX1];
    sprintf( cmd, "grep -v \"#\" %s > %s.dump", 
	     filename, filename );
    system( cmd );
    return 0;
}


/**************************************************************************************************
 NAME:       read_parameters
 FUNCTION:   read the file with given name and load information of array given
 INPUTS:     array where it returns reading data and file name 
	     with configuration file
 RETURN:     0 if file read ok
	     1 if file dont exist
**************************************************************************************************/
int read_parameters( float parameters[],
		     char filename[] )
{
    char cmd[NMAX1], filenamedump[NMAX1];
    int i=0;
    FILE *file;

    //Load of File
    file = fopen( filename, "r" );
    if( file==NULL ){
	printf( "  * The file '%s' don't exist!\n", filename );
	return 1;}
    fclose(file);
    
    //Converting to plain text
    conf2dump( filename );
    sprintf( filenamedump, "%s.dump", filename );
    file = fopen( filenamedump, "r" );
    
    //Reading
    while( getc( file ) != EOF ){
	fscanf( file, "%f", &parameters[i] );
	i++;}
    
    fclose( file );
    
    printf( "  * The file '%s' has been loaded!\n", filename );

    sprintf( cmd, "rm -rf %s.dump", filename );
    system( cmd );
    
    return 0;
}


/**************************************************************************************************
 NAME:       data_in_halos
 FUNCTION:   read input file with masses, positions, velocities, id, ...
 INPUTS:     'halo' structure, input file name.
 RETURN:     Number of data (rows)
**************************************************************************************************/
int data_in_halos( struct halo halos[],
		   char filename[])
{
    int i=0, j=0, Ndats;
    char cmd[NMAX1], filenamedump[NMAX1];
    FILE *file;
    float tmp;
    

    //File Detection
    file = fopen( filename, "r" );
    if( file==NULL ){
	printf( "  * The file '%s' don't exist!\n", filename );}
    fclose(file);

    //Conversed to plain text
    in2dump( filename );
    sprintf( filenamedump, "%s.dump", filename );
    file = fopen( filenamedump, "r" );
    
    //Read data
    while( getc( file ) != EOF ){
	fscanf( file,"%d %f %f %f %f %f %f %f %f %f %f %f %f %f", 
		&halos[i].id_or, 
		&halos[i].r[X], &halos[i].r[Y], &halos[i].r[Z],
		&halos[i].v[X], &halos[i].v[Y], &halos[i].v[Z],
		&tmp, 	&halos[i].Mass, &tmp, &tmp, &tmp, &tmp, &tmp );
	halos[i].id = i;
	i++;}

    //Number of rows in datafile
    Ndats = i-1;
    j = 0;
	  
    fclose( file );

    printf( "  * The file '%s' has been loaded!\n", filename );
    
    sprintf( cmd, "rm -rf %s.dump", filename );
    system( cmd );

    return Ndats;
}


/**************************************************************************************************
 NAME:       data_in_voids
 FUNCTION:   read input of matrix of voids
 INPUTS:     'matrix' array, input file name, N axe
 RETURN:     Number of data (cells)
**************************************************************************************************/
long long int data_in_voids( struct void_cell void_matrix[],
			     char filename[], int N )
{
    int i=0,j=0,k=0;
    long long int n=0, m=0;
    FILE *file;    

    //File Detection
    file = fopen( filename, "r" );
    if( file==NULL ){
	printf( "  * The file '%s' don't exist!\n", filename );}
    
    //Read data
    for( m=0; m<N*N*N; m++ ){
	fscanf( file,"%d", &void_matrix[n].id_reg);
	//Setting the matrix coordinates (axes)
	void_matrix[n].id[X] = i;
	void_matrix[n].id[Y] = j;
	void_matrix[n].id[Z] = k;

	k++;
	if( k == N ){
	    k = 0;
	    j ++;}
	if( j == N ){
	    j = 0;
	    i ++;}
	//  z y x  !
 	n = k + N*(j + N*i);
	if( i == N )
	    break;}
	  
    fclose( file );

    printf( "  * The file '%s' has been loaded! %lld cells\n", filename, n );
    return n;
}


/**************************************************************************************************
 NAME:       data_out
 FUNCTION:   store a file with distance and id void catalog according to the loaded halos
 INPUTS:     'halo' structure, input file name, parameters file.
 RETURN:     0
**************************************************************************************************/
int data_out( struct halo halos[],
	      char filename[],
	      float p[] )
{
    long int n;
    int i;
    FILE *file;
    
    file = fopen( filename, "w" );
    for( n=0;n<p[NDAT];n++ ){
	for( i=0;i<p[NNEI];i++ )
	    fprintf( file, "%1.6e\t%d\t", halos[n].distance[i], halos[n].id_voids[i] );
	fprintf( file, "\n" );
    }
    
    fclose( file );
   
    return 0;
}