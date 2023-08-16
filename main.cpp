#include <iostream>
#include <future>

using namespace std;

int make_thread = true;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void merge(int* arr, int l, int m, int r)
{
   int nl = m - l + 1;
   int nr = r - m;

   // создаем временные массивы
   int left[nl], right[nr];

   // копируем данные во временные массивы
   for (int i = 0; i < nl; i++)
       left[i] = arr[l + i];
   for (int j = 0; j < nr; j++)
       right[j] = arr[m + 1 + j];

   int i = 0, j = 0;
   int k = l;  // начало левой части

   while (i < nl && j < nr) {
       // записываем минимальные элементы обратно во входной массив
       if (left[i] <= right[j]) {
           arr[k] = left[i];
           i++;
       }
       else {
           arr[k] = right[j];
           j++;
       }
       k++;
   }
   // записываем оставшиеся элементы левой части
   while (i < nl) {
       arr[k] = left[i];
       i++;
       k++;
   }
   // записываем оставшиеся элементы правой части
   while (j < nr) {
       arr[k] = right[j];
       j++;
       k++;
   }
}

void mergeSort(int* arr, int l, int r){
	if(l >= r) return;
	int m = (l + r - 1) /2;
	if(make_thread && (r - l > 10000)){
		auto f = async(launch::async, [&]() {
	           mergeSort(arr, l, m);
	    });
	    mergeSort(arr, m + 1, r);
	}else{
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);
	}
	mergeSort(arr, m + 1, r);
	merge(arr, l, m, r);
}

int main(int argc, char** argv) {
	const int len = 20000;
	int arr[len];
	for(int i = 0;i < len;i++) arr[i] = rand() % 50;
	mergeSort(arr, 0, len - 1);
	for(int i = 0;i < len;i++) cout << arr[i] << " ";
	
	return 0;
}