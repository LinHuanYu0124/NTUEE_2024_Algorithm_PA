#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
#include<iomanip>
#include<vector>
#include<fstream>
using namespace std;
bool front  = true;
bool back   = false;

typedef pair<int, int> set;

void ReadFile(char const *FileName, int *NET,int *Order, int size)
{
    bool flag = 1;
    int null;
    fstream fin(FileName);
    if (!fin.is_open())
    {
        cout << "Wrong File's Name!!" << endl;
    }
    
    else
    {
        for (int i = -1; i < size/2; i++)
        {
            if (flag)
            {
                fin >> null;
                flag = 0;
            }
            else
            {
                //cout << "i = " << i << endl;   
                int begin, end;
                fin >> begin;
                fin >> end;
                NET[begin]   = end;
                NET[end]     = begin;
                Order[begin] = front;
                Order[end]   = back;   
            }
        }
    }
}

bool FindMAX(int a, int b)
{
    return (a > b) ? true : false;
}

//SORTING
//  Merge
void Merge(vector<set> &data, int low, int middle, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int n_1 = middle - low + 1;
    int n_2 = high - middle;
    //int size = high - low + 1;

    vector<set> L(n_1 + 1);
    vector<set> R(n_2 + 1);

    L[n_1] = set(100000000,100000000);
    R[n_2] = set(100000000,100000000);

    for (int i = 0; i < n_1; i++) {
        L[i] = data[low + i];
    }

    for (int i = 0; i < n_2; i++) {
        R[i] = data[middle + i + 1];
    }

    int l = 0, r = 0;
    for (int i = low; i <= high; i++) {
        if (L[l].first <= R[r].first) {
            data[i] = L[l];
            l++;
        } else {
            data[i] = R[r];
            r++;
        }
    }
}

// Sort subvector (Merge sort)
void MergeSortSubVector(vector<set> &data, int low, int high) 
{
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is neededif(begin < end)
    if(low < high)
    {
        int mid;
        mid = (low + high)/2;
        MergeSortSubVector(data, low, mid);
        MergeSortSubVector(data, mid + 1, high);
        Merge(data, low, mid, high);
    }
}

void MergeSort(vector<set> &data, int size){
    MergeSortSubVector(data, 0, size-1);
}

void FindMPS(int **MPS, int **COM, int *NET, int size)
{       
    
    for (int diff = 1; diff < size; diff++)
    {   
        //cout << diff << endl;
        for (int begin = 0; begin + diff < size; begin++)
        {   
            int end = begin + diff;
            if (MPS[begin][end] == -1){
                
                //  Default Value
                int max         = MPS[begin][end-1];
                COM[begin][end] = COM[begin][end-1];
                int mid         = NET[end];

                //cout << "begin = " << setw(2) << begin << ", mid = " << setw(2) << mid << ", end = " << setw(2) << end << endl;

                if (mid < begin || mid > end)
                {
                    max = MPS[begin][end - 1];
                }

                else if (mid == begin)
                {   
                    // COM[begin][end] = begin;
                    if (diff == 1)
                    {
                        max             = 1;
                        COM[begin][end] = begin;
                    }
                    else
                    {
                        if(FindMAX(1 + MPS[begin+1][end-1], max))
                        {
                            max             = 1 + MPS[begin+1][end-1];
                            COM[begin][end] = begin;
                        }
                    }
                }

                else
                {
                    if(end == mid+1)
                    {
                        if(FindMAX(1 + MPS[begin][mid-1], max))
                        {   
                            max             = 1 + MPS[begin][mid-1];
                            COM[begin][end] = mid;    
                        }
                    }
                    else
                    {
                        if (FindMAX(1 + MPS[begin][mid-1] + MPS[mid+1][end-1], max))
                        {
                            max             = 1 + MPS[begin][mid-1] + MPS[mid+1][end-1];
                            COM[begin][end] = mid;    
                        }
                    }
                }

                MPS[begin][end] = max;
            }
            
        }
        
    }    

}

// int FindLine(int begin, int end, int **MPS, int **COM, int *NET, int *Order, vector<set> Line)
// {
//     if (COM[begin][end] == -1)
//     {
//         return 1;     
//     }

//     int mid = COM[begin][end];
//     if(Order[mid])
//     {
//         Line.push_back(set(mid, NET[mid]));
//     }
//     else
//     {
//         Line.push_back(set(NET[mid], mid));
//     }
//     if (mid-1 >= begin)
//         FindLine(begin, mid-1, MPS, COM, NET, Order, Line);
//     if (mid+1 < NET[mid]-1)
//         FindLine(mid+1, NET[mid]-1, MPS, COM, NET, Order, Line);
//     if (NET[mid]+1 <= end)
//         FindLine(NET[mid]+1, end, MPS, COM, NET, Order, Line);
//     return 0;
// }
//======================================================================
int FindLine(int begin, int end, int **MPS, int **COM, int *NET, int *Order, vector<set> &Line)
{
    if (COM[begin][end] == -1) return 1;
    int mid = COM[begin][end];

    if(!Order[mid])
    {
        Line.push_back(set(NET[mid], mid));
    }
        
    else
    {
        Line.push_back(set(mid, NET[mid]));
    }

    FindLine(begin, mid-1, MPS, COM, NET, Order, Line);
    FindLine(mid+1, NET[mid]-1, MPS, COM, NET, Order, Line);
    FindLine(NET[mid]+1, end, MPS, COM, NET, Order, Line);
    return 0;
}
//======================================================================

void OutputMPSTable(int **MPS , int side)
{
    cout << setw(4)<< "\\" << "  ";
    for (int j = 0; j < side; j++)
        cout << setw(4)<< j << "  ";
    cout << endl;
    for (int i = 0; i < side; i++)
    {
        cout << setw(4)<< i << "  ";
        for (int j = 0; j < side; j++)
            cout << setw(4)<< MPS[i][j] << "  ";
        cout << endl;
    }
}

void WriteFile(char const *FileName, int max, vector<set> &Line,int *NET)
{
    ofstream outfile;
    outfile.open(FileName, ios::out);
    outfile << max << "\n";
    int i = 0;
    while (i < max)
    {
        outfile << Line[i].first << " " << Line[i].second << endl;
        i++;
    }

    outfile.close();
}

int main(int argc, char* argv[]){

    if (argc < 3)
    {
        cerr << "Error: The command format should be "
             << "\"./maxPSubset <input-file.in> <output-file>\"" << endl;
        return 1;
    }

    int  size;

    //  READ FILE
    fstream fin(argv[1]);
    if (!fin.is_open())
    {
        cout << "Wrong File's Name!!" << endl;
    }
    fin >> size;
    int **MPS       = new int *[size];
    int **COM       = new int *[size];
    int  *NET       = new int  [size];
    int  *Order     = new int  [size];
    int  *LineSet   = new int  [size];

    vector<set> Line;

    ReadFile(argv[1], NET, Order, size);

    //  Initialization
    for (int i = 0; i < size; i++)
    {
        MPS[i] = new int[size];
        memset(MPS[i], -1, sizeof(int) * size);
        MPS[i][i] = 0;
        COM[i] = new int[size];
        memset(COM[i], -1, sizeof(int) * size);
        LineSet[i] = -1;
    }

    FindMPS(MPS, COM, NET, size);

    FindLine(0, size - 1, MPS, COM, NET, Order, Line);

    int max = MPS[0][size-1];

    MergeSort(Line, max);

    WriteFile(argv[2], MPS[0][size - 1], Line, NET);
    

    

    // for (int i = 0; i < size; i++)
    // {   
    //     cout << LineSet[i] << ", ";
    // }
    // cout << endl;
    


    
    // cout << "Size = " << size << endl;
    // cout << "NET = " ;
    // for (int i = 0; i < size; i++)
    // {
    //     cout << NET[i] << ", ";
    // }
    
    

    // for (int i = 0; i < size; i++)
    // {   
    //     cout << COM[0][i] << ", ";
    // }
    // cout << endl;
    
    // for(int diff = 1; diff < size; diff++)
    // {
    //     for (int begin = 0; begin < size; begin++)
    //     {   
    //         int end = begin + diff;
    //         if (end < size)
    //         {
    //             FindMPS(begin, diff, MPS, COM, data);
    //         }            
    //     }
    // }
    

    // cout << "Max Planar Table:" << endl;
    // OutputMPSTable(MPS , size);
    // cout << endl << "Linking Planar Table:" << endl;
    // OutputMPSTable(COM , size);


    // cout << endl << "Tracing Planar Table:" << endl;
    // OutputMPSTable(trace , size);
    

    //  DELETION==========================================
    //  DELETION==========================================
    for (int k = 0; k < size; k++) {
        delete[] MPS[k];
        delete[] COM[k];
    }
    delete[] MPS;
    delete[] COM;
    delete[] NET;
    delete[] Order;
    delete[] LineSet;

    
}