/*
  Murat Kaçmaz
  150140052
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>
#include <sys/sem.h>

#define SEMAPHORE_1 500
#define SEMAPHORE_2 550
#define SEMAPHORE_3 600
int sem1,sem2,sem3;
	int N,M,K,T;
void mysignal(void) {}

void sem_signal(int semid, int val) {
	struct sembuf semafor;
	semafor.sem_num = 0;
	semafor.sem_op = val;
	semafor.sem_flg = 1;
	semop(semid, &semafor, 1);
}

void sem_wait(int semid, int val) {
	struct sembuf semafor;
	semafor.sem_num = 0;
	semafor.sem_op = (-1 * val);
	semafor.sem_flg = 1;
	semop(semid, &semafor, 1);
}

void mysigset(int num) {
	struct sigaction mysigaction;
	mysigaction.sa_handler = (void*)mysignal;
	mysigaction.sa_flags = 0;
	sigaction(num, &mysigaction, NULL);
}
void asansor_cagir(int simdiki_kat)
{

}


void person()
{
	srand(time(NULL));

	while (true) {
		int sure =  rand()%30 + 1; // bir katta geçirilecek süreyi hesapla
		bekle(sure);
		int hedef_kat = random() %N+1; // hedef kat no belirle
		asansor_cagir(simdiki_kat);
		asansor_git(hedef_kat);
	}
}



void prosesCreation(int K)
{
	int f,i;
	int mevcutKat;
	for(i = 1 ; i<= K ; i++)
	{
		f = fork();
		if(f==-1)
		{
			printf("error \n");
			exit(1);
		}
		if(f==0)  // childelar
		{
			person();
		}
	}
	if(f>0)
	{
		//asansor
	}



}



int main(int argc, char ** argv)
{
  // 5 4 3 30
	N = atoi(argv[1]);
	M = atoi(argv[2]);
	K = atoi(argv[3]);
	T = atoi(argv[4]);

	printf("Binanin sahip oldugu kat sayisi : %d \n",N);
	printf("Asansor kapasitesi : %d \n",M);
	printf("Binada yer alan maksimum kisi sayisi : %d \n",K);
	printf("Tum kisiler icin maksimum dolasma suresi: %d \n",T);

	printf("Baslangic durumu: asansor 1. katta \n");
	int shm_id;
	int* mainArray;  // main Array
	//char* my_shm_ptr;

	shm_id = shmget(IPC_PRIVATE, 2*K, IPC_CREAT | 0x1C0);  //get function

	if(shm_id == -1) {
		printf("Shared memory creation failed\n");
		exit(0);
	}

	mainArray = (int *) shmat(shm_id, 0, 0);  // attachemment
	if(mainArray == (int *) -1) {
		printf("Shared memory attach failed\n");
		exit(0);
	}

	prosesCreation(K)

	return 0 ;
}
/*

*/
