#include <iostream>
#include <locale.h>
#include <time.h>
#include <Windows.h>
#include <stdlib.h>

using namespace std;

int szukaj_lidera(int tab[], int n)
{
    int lider = tab[0], do_pary = 1;

    //wykreœlanie par o ró¿nych wartoœciach
    for (int i = 1; i < n; i++) {
        if (do_pary > 0)
            if (tab[i] == lider)
                ++do_pary;
            else
                --do_pary;
        else
        {
            ++do_pary;
            lider = tab[i];
        }
    }

    if (do_pary == 0)
        return -1; //zwrócenie -1 oznacza, ¿e zbiór nie posiada lidera

    int ile = 0; //zmienna zliczaj¹ca wyst¹pieñia potencjalnego lidera

    for (int i = 0; i < n; i++)  //zliczamy wyst¹pienia lidera
        if (tab[i] == lider)
            ++ile;

    if (ile > n / 2) //sprawdzamy, czy potencjalny lider wystêpuje oczekiwan¹ iloœæ razy
        return lider;

    return -1;

}
void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void heapify(int arr[], int N, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < N && arr[left] > arr[largest])
        largest = left;
    if (right < N && arr[right] > arr[largest])
        largest = right;
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, N, largest);
    }
}
void heapSort(int arr[], int N)
{
    for (int i = N / 2 - 1; i >= 0; i--)
        heapify(arr, N, i);
    for (int i = N - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}
int szukaj_lidera2(int tab[], int n)
{
    heapSort(tab, n);
    int lider = tab[0];
    int liczniknajw = 1;
    int licznikzw = 1;

    for (int i = 0; i < n; i++) {
        if (tab[i] == tab[i + 1]) {
            licznikzw++;
            if (licznikzw > liczniknajw) {
                liczniknajw = licznikzw;
                lider = tab[i];
            }
        }
        else {
            licznikzw = 1;
        }
        if (liczniknajw > n / 2) {
            return lider;
        }
    }
     return -1;
}
int szykaj_lidera_silowo(int tab[], int n) {
    float ilosc=0;
    float pol = n / 2;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (tab[i] == tab[j]) {
                ilosc++;
            }
        }
        if (ilosc > pol) {
            return tab[i];
        }
        ilosc = 0;
    }
    return -1;
}

void wypisz(int tab[], int n) {
    for (int i = 0; i < n; i++) {
        cout << tab[i] << " ";
    }
}
int * menu_wyboru(int n) {

    int * tab;

    tab = new int[n];

    for (int i = 0; i < n; i++) {
        cout << "Wpisz " << i + 1 << " liczbe: ";
        cin >> tab[i];
    }

    return tab;
}

void check_if_lider(int lider) {

    if (lider == -1)
        cout << "Zbiór nie posiada lidera" << endl;
    else
        cout << "Liderem zbioru jest " << lider << endl;

}
int* rand_tabl(int n) { //jeżeli zbiór ma posiadać lidera (do opcji 3)
    int* tablica = new int[n];
    int x;
    cout << "Jaka liczba ma być liderem?: ";
    cin >> x;
    for (int i = 0; i < (n/2); i++) {
        tablica[i] = rand() % n;
    }
    for (int i = (n / 2); i < n; i++) {
        tablica[i] = x;
    }
    return tablica;
}
int* rand_tabl2(int n) { //jeżeli zbiór nie ma posiadać lidera (case 3)
    int* tablica = new int[n];

    for (int i = 0; i < n; i++) {
        tablica[i] = rand() % n;
    }
    return tablica;
}


void porownanie(int *tab, int n) {
    clock_t t1, t2, t3;
    cout << "Algorytm 1:" << endl;
    t1 = clock();
    int lider = szukaj_lidera(tab, n);
    check_if_lider(lider);
    t1 = clock() - t1;
    long double time_taken = ((long double)t1) / CLOCKS_PER_SEC;
    cout << "Czas działania algorytmu pierwszego: " << time_taken << " s" << endl;
    srand(time(NULL));
    cout << endl << "Algorytm 2:" << endl;
    t2 = clock();
    int lider2 = szukaj_lidera2(tab, n);
    check_if_lider(lider2);
    t2 = clock() - t2;
    long double time_taken2 = ((long double)t2) / CLOCKS_PER_SEC;
    cout << "Czas działania algorytmu drugiego: " << time_taken2 << " s" << endl;
    srand(time(NULL));
    cout << endl << "Algorytm 3:" << endl;
    t3 = clock();
    int lider3 = szykaj_lidera_silowo(tab, n);
    check_if_lider(lider3);
    t3 = clock() - t3;
    long double time_taken3 = ((long double)t3) / CLOCKS_PER_SEC;
    cout << "Czas działania algorytmu trzeciego: " << time_taken3 << " s" << endl;
}

int main()
{
    setlocale(LC_CTYPE, "Polish");
    srand(time(NULL));
    int wybor = 0;
    while (wybor != 6) {
        cout << "Program do wyszukiwania lidera w zadanym zbiorze" << endl;
        cout << "Wybierz jedną z dostępnych opcji" << endl;
        cout << "1. Algorytm wyszukiwania wykorzystujący właściwości lidera" << endl;
        cout << "2. Algorytm wyszukiwania wykorzystujący sortowanie" << endl;
        cout << "3. Algorytm wyszukiwania O(n^2)" << endl;
        cout << "4. Porównanie algorytmów (zbiór posiada ldiera)" << endl;
        cout << "5. Porównanie algorytmów (zbiór nie posiada lidera)" << endl;
        cout << "6. Wyjście" << endl;
        cout << "Którą opcję chcesz wybrać?: ";
        cin >> wybor;

        cout << endl;
        int n;
        if (wybor > 0 && wybor < 7 && wybor != 6)
        {
            cout << "Ile liczb chcesz wczytać? ";
            cin >> n;
        }
        cout << endl;

        switch (wybor) {
        case 1: {

            int* tab = menu_wyboru(n);

            int lider = szukaj_lidera(tab, n);

            check_if_lider(lider);

            delete[] tab;
            break;
        }
        case 2: {

            int* tab = menu_wyboru(n);

            int lider = szukaj_lidera2(tab, n);

            check_if_lider(lider);

            delete[] tab;
            break;
        }
        case 3: {
            int* tab = menu_wyboru(n);

            int lider = szykaj_lidera_silowo(tab, n);

            check_if_lider(lider);

            delete[] tab;

            break;
        }
        case 4: {
            int* tab = rand_tabl(n);
            porownanie(tab, n);
            delete[] tab;

            break;
        }
        case 5: {
            int* tab = rand_tabl2(n);
            porownanie(tab, n);
            delete[] tab;
            break;
        }
        case 6: {
            cout << "Wyjście";
            break;
        }
        default: {
            cout << "Niepoprawna liczba";
            break;
        }
        }

        cout << endl;
        system("pause");
        if (getchar() == '\n') {
            system("CLS");
        }

    }

    return 0;
}

