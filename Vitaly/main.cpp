#include <stdio.h>      // printf, scanf, puts, NULL 
#include <stdlib.h>     // srand, rand 
#include <time.h>       // time
#include <math.h>       // sqrt, log
#include <conio.h>       // getch ()

int GetIndexByMax (double * _v, int _n) // поиск в массиве индекса максимального значения
{int i, imax=0;
 for (i=1;i<_n;i++) if (_v[imax]<_v[i]) imax = i;  
 return imax;
}

void main ()
{const int n = 10; // число автоматов  
 int m = 1000; //количество всех игр
 int k; // количество проведенных игр
 int ik; // номер автомата с которым в текущее время играем
 double Rik; // награда ik автомата - случайная величина
 double Q[n]; // вектор оценки случайной величины
 int i; //счетчик
 double eps = 0.01; // вероятность перехода на другой автомат
 double RSum=0; // общаяя сумма выйгрыша
 
 FILE * fw = fopen ("res.csv","w");
 
 if (fw == NULL) 
  {printf ("Can't open file");
   exit (EXIT_FAILURE);
  }
  
 for (i=0;i<n; i++) Q[i]=0.0; // обнуление вектора
 
 srand ((unsigned int) time(NULL)); // initialize random seed
 
 for (k=1;k<=m;k++)
  {ik= GetIndexByMax (Q,n); // выбираем номер автомата, с которым будем играть
   if ((double) rand()/RAND_MAX < eps  ) // перескакиваем - меняем автомат
    {do 
      {i= (int) ((double) rand()/RAND_MAX*n); 
      } 
     while (i == ik);
     
     ik = i;    
    }    
   Rik = (double) rand()/RAND_MAX; // получаем выйгрыш generate value between 0 and 1
   RSum += Rik; // накопление выйгрыша
   
   Q[ik]=Q[ik]+(Rik-Q[ik])/k; // CHAPTER 2. BANDIT PROBLEMS page 32 , (2.3) 
   printf ("%d) %d %lf\n",k,ik,Q[ik]);  // вывод  в консоль
   fprintf (fw,"%d;%lf\n",k,RSum/k); // вывод номера шага и среднего
   
   //if (getch () == 27) break; // ожидание нажатия клавиши на клавиатуре
  } 
  
 fclose (fw);
}



