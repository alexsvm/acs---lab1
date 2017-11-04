#include <omp.h> 
#include <stdio.h> 
#include <locale.h> 
#include <string.h>

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "Russian");

#ifdef _OPENMP 
	printf("OpenMP ��������������!\n\n");
#endif 
	printf("<<<<< ���������������� ������� 1 >>>>>\n");

	int NumOfThreads;
#pragma omp parallel 
	{
		int ThreadId;
		ThreadId = omp_get_thread_num();
		NumOfThreads = omp_get_num_threads();
		if (ThreadId == 0) // main thread
		{
			printf("���� - ������: ����� ���������� ����� = %d\n", NumOfThreads);
		}
		else 
		{
			printf("���� %d �� %d\n", ThreadId, NumOfThreads);
		}
	}
	printf("\n<<<<< ���������������� ������� 2 >>>>>\n");

	printf("------------------------------\n");
#pragma omp parallel 
	{
		int ThreadId;
		ThreadId = omp_get_thread_num();
		NumOfThreads = omp_get_num_threads(); 
		printf("������������ ������ 2. ���� %d �� %d\n", ThreadId, NumOfThreads);
	}
	printf("------------------------------\n");
	omp_set_num_threads(3);
#pragma omp parallel 
	{
		int ThreadId;
		ThreadId = omp_get_thread_num();
		NumOfThreads = omp_get_num_threads();
		printf("������������ ������ 3. ���� %d �� %d\n", ThreadId, NumOfThreads);
	}
	printf("------------------------------\n");
#pragma omp parallel num_threads(4)
	{
		int ThreadId;
		ThreadId = omp_get_thread_num();
		NumOfThreads = omp_get_num_threads();
		printf("������������ ������ 4. ���� %d �� %d\n", ThreadId, NumOfThreads);
	}
	printf("------------------------------\n");

	printf("==============================\n");
	printf("128 �����  OMP_DYNAMIC=false \n");
	omp_set_dynamic(0);
#pragma omp parallel num_threads(128)
	{
		int ThreadId;
		ThreadId = omp_get_thread_num();
		NumOfThreads = omp_get_num_threads();
		printf("������������ ������ 5. ���� %d �� %d\n", ThreadId, NumOfThreads);
	}
	printf("==============================\n");
	printf("128 �����  OMP_DYNAMIC=true \n");
	omp_set_dynamic(1);
#pragma omp parallel num_threads(128)
	{
		int ThreadId;
		ThreadId = omp_get_thread_num();
		NumOfThreads = omp_get_num_threads();
		printf("������������ ������ 6. ���� %d �� %d\n", ThreadId, NumOfThreads);
	}
	printf("==============================\n");

	bool omp_mode = false;
	if (argc > 1 && !strcmp(argv[1], "parallel" ))
		omp_mode = true;

	printf("###############################\n");
	printf("���� ����� �������� ��������� parallel, �� ��������� � ������������ ������:\n");
#pragma omp parallel if (omp_mode)
	{
		int ThreadId;
		ThreadId = omp_get_thread_num();
		NumOfThreads = omp_get_num_threads();
		if (ThreadId == 0) // main thread
		{
			printf("���� - ������: ����� ���������� ����� = %d\n", NumOfThreads);
		}
		else
		{
			printf("���� %d �� %d\n", ThreadId, NumOfThreads);
		}
	}

	printf("������� ENTER ��� ������...\n");
	getchar();
}