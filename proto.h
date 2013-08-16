// Data Module
int conf2dump( char * );
int in2dump( char * );
int read_parameters( float *, char * );
int data_in_halos( struct halo *, char *);
long long int data_in_voids( struct void_cell *, char *, int );
int data_out( struct halo *, char *, float * );

// Distance Module
float halos_void_dist( float *,int *, float * );
int halo_position( struct halo *, float * );
int distances( struct halo *, struct void_cell *, float * );