/*
==========================================================================
Created by Suprotik Dey
@2018


This program reads and writes a file of given size to a file
Absolute path may also be given

To run
$ bench -n [FILESIZE] -f [FILE NAME] -b(to turn off buffered i/o) 
-c [CHUNK_SIZE] -t [time in minutes]_[percentage for stress benchmarking]
When t is valid, all other options are invalid other than filename
==========================================================================
*/
#define _GNU_SOURCE

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/time.h>   
#include <sys/resource.h> 

#define MAX_FILE_SIZE 10240 //10GB
#define MIN_FILE_SIZE 1 //1MB
#define _KB(x) ((size_t)(x) << 10) //Bytes to Kilobytes
#define _MB(x) ((size_t)(x) << 20) //Bytes to Megabytes
#define MIN_CHUNK_SIZE 1 //1KB
#define DEFAULT_CHUNK_SIZE 8 //8KB
#define MAX_CHUNK_SIZE 1024 //1MB
#define MAX_FILE_NAME_LEN 1000 //max length of abs or rel file path
#define DEFAULT_FILENAME "bench"
#define MAX_STRESS_TIME 100 //100 minutes
#define MAX_TIME_SLEEP 
#define STRESS_EXTRA_CALC_TIME 100 //microseconds
#define STRESS_MAX_WRITE_SIZE 102400 //in KB
#define STRESS_RATE_THRESH 2048.000 //KB/s
#define STRESS_PUSH_ADDING_FACTOR 1000
#define STRESS_PUSH_MULTIPLYING_FACTOR 20
#define STRESS_PULL_MULTIPLYING_FACTOR 1.0100

//for printing current working directory
void printcwd()
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s", cwd);
}

void default_time_filename(char *buffer)
{
    time_t rawtime;
    time (&rawtime);
    sprintf(buffer,"%s_%s",DEFAULT_FILENAME,ctime(&rawtime) );
    char *p = buffer;
    for (; *p; ++p)
    {
        if (*p == ' '||*p==':'||*p=='\n')
            *p = '_';
    }
}

//for option parsing
void parse_options(int argc, char** argv, char *filename, int *filesize, int *bufferedIO, int *chunk, int *stresstime, int *stresspercent)
{
    int c,index;

    //defaults
    *filesize = 0;
    *bufferedIO=1;
    *chunk=0;
	*stresstime = 0;
	*stresspercent =0;
    char *loc_filename = NULL;
	char temp_str[MAX_FILE_NAME_LEN], *ttstr;
    opterr = 0;

    while ((c = getopt (argc, argv, "f:n:hbc:t:")) != -1)
    {
        switch (c)
        {
			case 't':
				strcpy(temp_str,optarg);
				ttstr = strdup(temp_str);
				*stresstime=-1;
				*stresstime = atoi(strsep(&ttstr,"_"));
				*stresspercent = atoi(ttstr);
				break;
            case 'n':
                *filesize = atoi(optarg);
                break;
            case 'c':
                *chunk = atoi(optarg);
                break;
            case 'f':
                if(strlen(optarg)>=MAX_FILE_NAME_LEN)
                {
                    printf("Filename too long.. Aborting");
                    exit(0);
                }
                loc_filename = optarg;
                break;
            case 'b':
                *bufferedIO=0;
                break;
            case 'h':
                printf("To run:\n\n[program_name] bench -n [FILESIZE] -f [FILE NAME] -b(to turn off buffered I/O)\n-c [CHUNK_SIZE] -t [time in minutes]_[percentage for stress benchmarking]\nWhen t is valid, all other options are invalid other than filename\n");
                exit(0);
                break;
            case '?':
                if (optopt == 'n' || optopt == 'f'|| optopt == 'c')
                    fprintf (stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint (optopt))
                    fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
                printf("Aborted..\n");
                exit(0);
            default:
				printf("Aborted..\n");
                exit(0);
        }
    }

    for (index = optind; index < argc; index++)
	{
        printf ("Non-option argument %s\n", argv[index]);
		printf("Aborted..\n");
                exit(0);
	}


    //checking filename
    if(loc_filename == NULL)
    {
        default_time_filename(filename);
        printf("No Filename given. Switching to default.\n");
    }
    else
    {
        strcpy(filename,loc_filename);
    }

	//stress options checking
	if(*stresstime!=0)
	{
		if(*stresstime<0 || *stresstime> MAX_STRESS_TIME || *stresspercent<=0 || *stresspercent > 100)
		{
			printf("\nStress options are not valid! Aborting..\n");
			exit(0);
		}
		//return if valid stress
		return;

	}

	//checking filesize range
    if(*filesize == 0)
    {
        printf("No File Size given. Switching to minimum.\n");
        *filesize=MIN_FILE_SIZE;
    }
    else if(*filesize < MIN_FILE_SIZE || *filesize >MAX_FILE_SIZE)
    {
        printf("File Size out of bounds! Aborting.\n");
        exit(0);
    }

	//checking chunk size range
    if(*chunk == 0)
    {
        printf("No Chunk Size given. Switching to default.\n");
        *chunk=DEFAULT_CHUNK_SIZE;
    }
    else if(*chunk < MIN_CHUNK_SIZE || *chunk >MAX_CHUNK_SIZE)
    {
        printf("Chunk Size out of bounds! Aborting.\n");
        exit(0);
    }
}

long double diff_time(struct timespec finish, struct timespec start)
{
    long double difft;
	long seconds,ns;
	seconds = finish.tv_sec - start.tv_sec; 
    ns = finish.tv_nsec - start.tv_nsec; 

	if (start.tv_nsec > finish.tv_nsec)
	{ // clock underflow 
		--seconds; 
		ns += 1000000000; 
    }
    difft = (long double)seconds + (long double)ns/(long double)1000000000;
    return difft;
}

//for printing purposes
void verbose(char *filename, int filesize, int bufferedIO, int chunk)
{
    printf("\nFilename: %s\n",filename);
    printf("\nFile size: %d MB\n",filesize);
    printf("\nChunk size: %d KB\n",chunk);
    if(bufferedIO)
        printf("\nBuffered IO? : Yes\n");
    else
        printf("\nBuffered IO? : No\nNote: This will take time");
    
}


//writing to disk
void disk_write(char *filename, int filesize, int bufferedIO, int chunk)
{
    int outputfile,chunk_B = _KB(chunk);
    if(bufferedIO)
        outputfile = open(filename, O_CREAT | O_WRONLY);
    else
        outputfile = open(filename, O_CREAT | O_WRONLY | O_SYNC | O_DIRECT);//switching to non buffered direct I/O

    if(outputfile<0)
    {
        printf("Error. Could not open file. Possible cause: Drive unmounted or Permission denied\n");
        exit(0);
    }

	char *file_buffer;
    file_buffer = (char*)calloc(chunk_B,sizeof(char));
	unsigned long writes = filesize * _MB(1) / chunk_B;

    printf("\n>> Writing...Please wait.\n");
	while (writes-- > 0)
    {
		if(write(outputfile, file_buffer, chunk_B)<0)
		{
            printf("Error writing..\n");
			exit(0);
		}
    }
	close(outputfile);
    free(file_buffer);
}

//reading from disk
void disk_read(char *filename, int filesize, int bufferedIO, int chunk)
{
    int outputfile,chunk_B = _KB(chunk);
    if(bufferedIO)
        outputfile = open(filename, O_RDONLY);
    else
        outputfile = open(filename, O_RDONLY | O_SYNC | O_DIRECT);//switching to non buffered direct I/O

    if(outputfile<0)
    {
        printf("Error. Could not open file. Possible cause: File Deleted or Drive unmounted or Permission denied\n");
        exit(0);
    }

	char *file_buffer;
    file_buffer = (char*)calloc(chunk_B,sizeof(char));
	unsigned long reads = filesize * _MB(1) / chunk_B;

    printf("\n>> Reading...Please wait.\n");
	while (reads-- > 0)
    {
		if(read(outputfile, file_buffer, chunk_B)<0)
		{
            printf("Error reading..\n");
			exit(0);
		}
    }

	close(outputfile);
    free(file_buffer);
}

//main benchmark function
void disk_bench(char *filename, int filesize, int bufferedIO, int chunk)
{
    long double difft;
    long double diskrate;
    struct timespec start, finish;
    
    //write speed-----------------
    printf("\n-----------------------------------------------------\n");
    clock_gettime(CLOCK_REALTIME, &start); 
	disk_write(filename,filesize,bufferedIO,chunk);
    clock_gettime(CLOCK_REALTIME, &finish); 


    difft = diff_time(finish, start);

    diskrate = (long double)filesize/difft;
     
    printf("\nThe time required to write is: %Lf s.\n",difft);
    printf("The Disk Write I/O rate: %LfMB/s.\n",diskrate);
    printf("\n-----------------------------------------------------\n");

    //read speed-----------------

    clock_gettime(CLOCK_REALTIME, &start); 
	disk_read(filename,filesize,bufferedIO,chunk);
    clock_gettime(CLOCK_REALTIME, &finish);

	difft = diff_time(finish, start);

    diskrate = (long double)filesize/difft;

    printf("\nThe time required read is: %Lf s.\n",difft);
    printf("The Disk Read I/O rate: %LfMB/s.\n",diskrate);
    printf("\n-----------------------------------------------------\n");
    
}

//greet
void init()
{
    printf("\n--------------------------------------------------------\n");
    printf("\t=============DISK BENCHMARK=============");
    printf("\n--------------------------------------------------------\n");
    printf("\n\nCurrent Directory: ");
    printcwd();
    printf("\n\n");
}

//file remover
void removeFile(char *filename)
{
    if (remove(filename) == 0)
        printf("\nTest File Deleted successfully..\n");
    else
        printf("\nUnable to delete the file!\n");
}

void stress_write(int outputfile, long int filesize, char *file_buffer)
{
    //filesize is in KB
    int chunk_B = _KB(MAX_CHUNK_SIZE);
    if(filesize<MAX_CHUNK_SIZE)
        chunk_B = _KB(MIN_CHUNK_SIZE);
	unsigned long int writes = filesize * _KB(1) / chunk_B;
	while (writes-- > 0)
    {
		if(write(outputfile, file_buffer, chunk_B)<0)
		{
            printf("Error writing.. Possibly File deleted, disk overflow or permission denied. Aborting\n");
			exit(0);
		}
    }
	fsync(outputfile);
}


//calculate optimum write size and if required, sleep
long int calc_wt_size_sleep(long double reqd_diskrate, long double curr_diskrate, long int curr_write_size)
{
	long double slack = reqd_diskrate - curr_diskrate;
	if(slack > -STRESS_RATE_THRESH && slack < STRESS_RATE_THRESH)
	{
		return curr_write_size;
	}


	long int time_sleep_micro=0;
	struct timespec finish;
	if(reqd_diskrate < curr_diskrate)
	{
		//calc sleep time, decrease write size
		time_sleep_micro = (long int)(((curr_diskrate/reqd_diskrate)-1.000000000)*1000000.0) - STRESS_EXTRA_CALC_TIME;

		if(time_sleep_micro>0)
			usleep(time_sleep_micro);
		curr_write_size = curr_write_size*1.0 /((curr_diskrate/reqd_diskrate)*STRESS_PULL_MULTIPLYING_FACTOR);
		if(curr_write_size<MIN_CHUNK_SIZE)
			curr_write_size = MIN_CHUNK_SIZE;
		//printf("\nLower: %ld",curr_write_size);
		return curr_write_size;		
	}
	else
	{
		if(curr_write_size != STRESS_MAX_WRITE_SIZE)
		{
			//increase write size
			curr_write_size = curr_write_size+(STRESS_PUSH_ADDING_FACTOR*1.00*STRESS_PUSH_MULTIPLYING_FACTOR*(1.0-(curr_diskrate/reqd_diskrate)));
			if(curr_write_size > STRESS_MAX_WRITE_SIZE)
				curr_write_size = STRESS_MAX_WRITE_SIZE;
			//printf("\nIncrease: %ld",curr_write_size);
		}
		return curr_write_size;
	}

    
}

void P_stress(char *filename,long double stress_s,long double reqd_diskrate)//diskrate in KB/s
{
	int outputfile = open(filename, O_CREAT | O_WRONLY);
	int lit_count=0;
    if(outputfile<0)
    {
        printf("Error. Could not open file. Possible cause: Drive unmounted or Permission denied\n");
        exit(0);
    }
    long double difft;
    long double curr_diskrate;
    struct timespec start, finish;
    long int curr_write_size=MIN_CHUNK_SIZE; // in KB
    long int tot_file_written=0; // in KB
    char *file_buffer;
	long int curr_difft;

    file_buffer = (char*)calloc(_KB(MAX_CHUNK_SIZE),sizeof(char));

	printf("\nStressing....\n");
    //start timer
    clock_gettime(CLOCK_REALTIME, &start);
	while(1)
	{
		//write out
        stress_write(outputfile, curr_write_size, file_buffer);
        //add total filesize
        tot_file_written = tot_file_written + curr_write_size;
        //measure timer
        clock_gettime(CLOCK_REALTIME, &finish);
        difft = diff_time(finish, start);
		//if file overflow exit
		if(tot_file_written>(MAX_FILE_SIZE*_KB(1)))
        {
            printf("File Overflow! Abort..\n");
            exit(0);
        }
        //if timer overflow, break
        if(difft>stress_s)
            break;
        
        //calculate current diskrate
        curr_diskrate = (long double)tot_file_written / difft;
		
        //update with the difference, the filesize
        curr_write_size = calc_wt_size_sleep(reqd_diskrate,curr_diskrate,curr_write_size);
	}

	close(outputfile);
    free(file_buffer);
}


//stress by percentage and time
void stress_start(char *filename, int stresstime, int stresspercent)
{
	printf("\nFilename : %s",filename);
	printf("\nTotal Run time: %d mins.\n",stresstime);
	long double difft;
    long double max_diskrate,reqd_diskrate;
    struct timespec start, finish;
	int filesize=500;	

	//getting max bandwidth
	printf("Getting Max Write speed..\n");
	clock_gettime(CLOCK_REALTIME, &start); 
	disk_write(filename, filesize, 1, 1000);//huge chunk with caching
	clock_gettime(CLOCK_REALTIME, &finish); 
	difft = diff_time(finish, start);
    max_diskrate = (long double)filesize/difft;
	

	//calculating required bandwidth and details
	reqd_diskrate = max_diskrate*(stresspercent*1.0/100.0);
	printf("\nMax Disk Rate:%LfMB/s.",max_diskrate);
	printf("\nPercentage required:%d%%",stresspercent);
	printf("\nTarget Disk Rate:%LfMB/s\n",reqd_diskrate);
	
	P_stress(filename, stresstime*60.0,reqd_diskrate*1024.0);
}

int main(int argc, char** argv)
{
    char bench_filename[MAX_FILE_NAME_LEN];
    int bench_filesize;
    int bufIOflag, chunkSize;
	int stresstime, stresspercent;
    init();
    parse_options(argc,argv,bench_filename,&bench_filesize,&bufIOflag,&chunkSize,&stresstime,&stresspercent);
	if(stresstime>0 && stresspercent>0)
	{
		printf("\n\t===Entering stress Mode===\n");
		stress_start(bench_filename,stresstime,stresspercent);
		removeFile(bench_filename);
		return 0;
	}
    verbose(bench_filename,bench_filesize,bufIOflag,chunkSize);
    disk_bench(bench_filename,bench_filesize,bufIOflag,chunkSize);
    removeFile(bench_filename);
    return 0;
}
