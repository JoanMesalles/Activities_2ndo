#include <iostream>
#include <unistd.h>
#include <wait.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <random>
#include <sys/sem.h>


struct ShmMem
{
    int val;
};

ShmMem* shm;

void Incremento(int max)
{
    for (size_t i = 0; i < max; i++)
    {
        shm->val++;
    }

}

int main()
{
    int shmID = shmget(IPC_PRIVATE, sizeof(ShmMem), IPC_CREAT | 0666);
    shm = (ShmMem*)shmat(shmID, NULL, 0);
    shm->val = 0;

    pid_t pid1 = fork();
    if (pid1 == 0)
    {
        Incremento(10000000);
        shmdt(shm);
        exit(0);
    }

    pid_t pid2 = fork();
    if (pid2 == 0)
    {
        Incremento(10000000);
        shmdt(shm);
        exit(0);
    }

    Incremento(10000000);
    int status;
    wait(&status);
    wait(&status);
    std::cout << "val : " << shm->val << std::endl;

    shmdt(shm);
    shmctl(shmID, IPC_RMID, NULL);

}