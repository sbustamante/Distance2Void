#include <allvars.h>

/**************************************************************************************************
 NAME:       halos_void_dist
 FUNCTION:   this function calculates the comoving distance between a specified halo and a close
	     void
 INPUTS:     halo position, void discrete position.
 RETURN:     0
**************************************************************************************************/
float halos_void_dist( float rh[3],
		       int iv[3],
		       float p[] )
{
    int i, i_t;
    float distance[3];
    
    for( i=0;i<3;i++ ){
	distance[i] = fabs( p[LBOX]*(iv[i]+0.5)/p[NBOX] - rh[i]);
	if( distance[i] >= p[LBOX]/2.0 )
	    distance[i] = p[LBOX] - distance[i];}
	    
    return pow( distance[0]*distance[0] + distance[1]*distance[1] + distance[2]*distance[2], 0.5 );
}


/**************************************************************************************************
 NAME:       halo_position
 FUNCTION:   this function calculates the discrete position in the grid occupied by each halo
 INPUTS:     'halo' structure,  parameters.
 RETURN:     0
**************************************************************************************************/
int halo_position( struct halo halos[],
		   float p[] )
{
    long int i;
    int j;
    
    for( i=0;i<p[NDAT];i++ )
	for( j=0;j<3;j++ )
	    halos[i].i_cell[j] = (int)(halos[i].r[j]/p[LBOX]*p[NBOX]);
    return 0;
}


/**************************************************************************************************
 NAME:       distances
 FUNCTION:   this function calculates the distance between each halo and its three closer neighbor
	     void regions
 INPUTS:     'halo' structure, 'void_cell', parameters.
 RETURN:     0
**************************************************************************************************/
int distances( struct halo halos[],
	       struct void_cell void_matrix[],
	       float p[] )
{
    long int nh;
    int i, j, k, nn, nnp, N;
    N = (int)p[NBOX];
    float distance;
    int it, jt, kt, ic, jc, kc;
    int pass;
    long long int nv;

    //Sweeping halos of the general catalog
    for( nh=0;nh<p[NDAT];nh++ ){
	#ifdef PRINT
 	if( nh%10000==0 ) printf("In halo %ld\n", nh);
	#endif
	//nn-esim closer neighbor
	for( nn=0;nn<p[NNEI];nn++ ){
	    //Initializing the current distance
	    halos[nh].distance[nn] = p[LBOX];
	    //Sweeping all the neighbor cells
	    for( ic=-p[LREG];ic<=p[LREG];ic++ )
	    for( jc=-p[LREG];jc<=p[LREG];jc++ )
	    for( kc=-p[LREG];kc<=p[LREG];kc++ ){
		i = halos[nh].i_cell[X];
		j = halos[nh].i_cell[Y];
		k = halos[nh].i_cell[Z];
		//Effective Indexes
		it = i + ic; jt = j + jc; kt = k + kc;
		//Neighbor out of limits (Periodic boundary conditions) (X direction)
		if( i+ic>=N )		it = i+ic-N;
		if( i+ic<0 )		it = N+(i+ic);
		//Neighbor out of limits (Periodic boundary conditions) (Y direction)
		if( j+jc>=N )		jt = j+jc-N;
		if( j+jc<0 )		jt = N+(j+jc);
		//Neighbor out of limits (Periodic boundary conditions) (Z direction)
		if( k+kc>=N )		kt = k+kc-N;
		if( k+kc<0 )		kt = N+(k+kc);
	
		//Index of current void cell
		nv = it + N*(jt + N*kt);
		//Distance between the current dark halo and the void cell
		if( void_matrix[nv].id_reg != 0 ){
		    pass = 0;
		    for( nnp=0;nnp<nn;nnp++ ){
			//Verifying current void regions is different to previous ones
			if( void_matrix[nv].id_reg == halos[nh].id_voids[nnp] ){
			    pass = 1;
			    break;}}
		    if( pass == 0 ){
			//Distance to current void cell
			distance = halos_void_dist( halos[nh].r, void_matrix[nv].id, p );
			if( distance < halos[nh].distance[nn] ){
			    halos[nh].distance[nn] = distance;
			    halos[nh].id_voids[nn] = void_matrix[nv].id_reg;
			    halos[nh].i_void[nn][X] = it;
			    halos[nh].i_void[nn][Y] = jt;
			    halos[nh].i_void[nn][Z] = kt;}}}
		 }
	    }
    }

    return 0;
}