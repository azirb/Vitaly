#include <stdio.h>      // printf, scanf, puts, NULL 
#include <stdlib.h>     // srand, rand 
#include <time.h>       // time
#include <math.h>       // sqrt, log
#include <conio.h>       // getch ()

int GetIndexByMax (double * _v, int _n) // ����� � ������� ������� ������������� ��������
{int i, imax=0;
 for (i=1;i<_n;i++) if (_v[imax]<_v[i]) imax = i;  
 return imax;
}

void main ()
{const int n = 10; // ����� ���������  
 int m = 1000; //���������� ���� ���
 int k; // ���������� ����������� ���
 int ik; // ����� �������� � ������� � ������� ����� ������
 double Rik; // ������� ik �������� - ��������� ��������
 double Q[n]; // ������ ������ ��������� ��������
 int i; //�������
 double eps = 0.01; // ����������� �������� �� ������ �������
 double RSum=0; // ������ ����� ��������
 
 FILE * fw = fopen ("res.csv","w");
 
 if (fw == NULL) 
  {printf ("Can't open file");
   exit (EXIT_FAILURE);
  }
  
 for (i=0;i<n; i++) Q[i]=0.0; // ��������� �������
 
 srand ((unsigned int) time(NULL)); // initialize random seed
 
 for (k=1;k<=m;k++)
  {ik= GetIndexByMax (Q,n); // �������� ����� ��������, � ������� ����� ������
   if ((double) rand()/RAND_MAX < eps  ) // ������������� - ������ �������
    {do 
      {i= (int) ((double) rand()/RAND_MAX*n); 
      } 
     while (i == ik);
     
     ik = i;    
    }    
   Rik = (double) rand()/RAND_MAX; // �������� ������� generate value between 0 and 1
   RSum += Rik; // ���������� ��������
   
   Q[ik]=Q[ik]+(Rik-Q[ik])/k; // CHAPTER 2. BANDIT PROBLEMS page 32 , (2.3) 
   printf ("%d) %d %lf\n",k,ik,Q[ik]);  // �����  � �������
   fprintf (fw,"%d;%lf\n",k,RSum/k); // ����� ������ ���� � ��������
   
   //if (getch () == 27) break; // �������� ������� ������� �� ����������
  } 
  
 fclose (fw);
}



