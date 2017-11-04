#include <omp.h> 
#include <stdio.h> 
#include <locale.h> 
#include <string.h>

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "Russian");

#ifdef _OPENMP 
	printf("OpenMP поддерживается!\n\n");
#endif 
	printf("<<<<< Последовательная область 1 >>>>>\n");

	int NumOfThreads;
#pragma omp parallel 
	{
		int ThreadId;
		ThreadId = omp_get_thread_num();
		NumOfThreads = omp_get_num_threads();
		if (ThreadId == 0) // main thread
		{
			printf("Нить - мастер: Общее количество нитей = %d\n", NumOfThreads);
		}
		else 
		{
			printf("Нить %d из %d\n", ThreadId, NumOfThreads);
		}
	}
	printf("\n<<<<< Последовательная область 2 >>>>>\n");

	printf("------------------------------\n");
#pragma omp parallel 
	{
		int ThreadId;
		ThreadId = omp_get_thread_num();
		NumOfThreads = omp_get_num_threads(); 
		printf("Параллельный регион 2. Нить %d из %d\n", ThreadId, NumOfThreads);
	}
	printf("------------------------------\n");
	omp_set_num_threads(3);
#pragma omp parallel 
	{
		int ThreadId;
		ThreadId = omp_get_thread_num();
		NumOfThreads = omp_get_num_threads();
		printf("Параллельный регион 3. Нить %d из %d\n", ThreadId, NumOfThreads);
	}
	printf("------------------------------\n");
#pragma omp parallel num_threads(4)
	{
		int ThreadId;
		ThreadId = omp_get_thread_num();
		NumOfThreads = omp_get_num_threads();
		printf("Параллельный регион 4. Нить %d из %d\n", ThreadId, NumOfThreads);
	}
	printf("------------------------------\n");

	printf("==============================\n");
	printf("128 нитей  OMP_DYNAMIC=false \n");
	omp_set_dynamic(0);
#pragma omp parallel num_threads(128)
	{
		int ThreadId;
		ThreadId = omp_get_thread_num();
		NumOfThreads = omp_get_num_threads();
		printf("Параллельный регион 5. Нить %d из %d\n", ThreadId, NumOfThreads);
	}
	printf("==============================\n");
	printf("128 нитей  OMP_DYNAMIC=true \n");
	omp_set_dynamic(1);
#pragma omp parallel num_threads(128)
	{
		int ThreadId;
		ThreadId = omp_get_thread_num();
		NumOfThreads = omp_get_num_threads();
		printf("Параллельный регион 6. Нить %d из %d\n", ThreadId, NumOfThreads);
	}
	printf("==============================\n");

	bool omp_mode = false;
	if (argc > 1 && !strcmp(argv[1], "parallel" ))
		omp_mode = true;

	printf("###############################\n");
	printf("Если задан параметр приложени parallel, то запускаем в параллельном режиме:\n");
#pragma omp parallel if (omp_mode)
	{
		int ThreadId;
		ThreadId = omp_get_thread_num();
		NumOfThreads = omp_get_num_threads();
		if (ThreadId == 0) // main thread
		{
			printf("Нить - мастер: Общее количество нитей = %d\n", NumOfThreads);
		}
		else
		{
			printf("Нить %d из %d\n", ThreadId, NumOfThreads);
		}
	}

	printf("Нажмите ENTER для выхода...\n");
	getchar();
}