# include <stdio.h>
# include <utmp.h>
# include <unistd.h>
# include <fcntl.h>
# include <time.h>
# include <stdlib.h>
#include <string.h>

int countPrint = 0;

void showtime(long timeval){
	char *cp;
	cp = ctime(&timeval);
	printf("%-16.16s " ,cp);
}

void show_info(struct utmp *utbufp){
	if(strcmp(utbufp->ut_name, "runlevel") == 0){
		return;
	}
	countPrint++;
	printf("%-8.8s " , utbufp->ut_user);
	if(strcmp(utbufp->ut_line, "~") == 0){
		printf("%-12.12s " , "system boot");
	}
	else{
		printf("%-12.12s " , utbufp->ut_line);
	}
	printf(" %-18.18s " , utbufp->ut_host);
	showtime(utbufp->ut_time);
	#ifdef SHOWHOST
	if(utbufp->ut_host[0] != '0'){
		printf("(%-8.8d) " , utbufp->ut_time);
	}
	#endif
	printf("\n");
}



int main(int argc, char *argv[]){
	int num_rec = atoi(argv[1]);
	struct utmp cur_record;
	int utmpfd, reclen = sizeof(cur_record);
	if((utmpfd = open("/var/log/wtmp", O_RDONLY)) == -1){
		perror(UTMP_FILE);
		exit(1);
	}
	lseek(utmpfd, -(reclen), SEEK_END);
	int i = 1;
	while( countPrint < num_rec && read(utmpfd, &cur_record, reclen) == reclen){
		i++;
		show_info(&cur_record);
		lseek(utmpfd, -(reclen * i), SEEK_END);
	}
	close(utmpfd);
	return 0;	
}
