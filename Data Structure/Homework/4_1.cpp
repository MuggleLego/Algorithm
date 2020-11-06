//date:2020.11.06
//given a sparse matrix,output its transpose by the method of fast transpose

#include <iostream>
#include<assert.h>
using namespace std;

struct Triple
{
    int col, row;
    double value;
    Triple& operator= (Triple& x){
        col=x.col;
        row=x.row;
        value=x.value;
        return *this;
    }
};

class SparseMatrix
{
    friend ostream &operator<<(ostream &out, SparseMatrix &M);
    friend istream &operator>>(istream &in, SparseMatrix &M);

private:
    int Cols, Rows, Terms;
    Triple *array;
    int maxTerms;

public:
    SparseMatrix(int size):maxTerms(size)
    {
        if(size <1){
            cerr<<"initializaition error!"<<endl;
            exit(1);
        }
        array = new Triple[size];
        assert(array);
        Rows = Cols = Terms = 0;
    };
    ~SparseMatrix(){delete []array;};
    SparseMatrix& operator= (SparseMatrix& M){
        Rows=M.Rows;
        Cols=M.Cols;
        Terms=M.Terms;
        maxTerms=M.maxTerms;
        for (int i=0;i<Terms;i++){
            array[i]=M.array[i];
        }
        return *this;
    }
    SparseMatrix FastTranspose(){
        int *rowSize=new int[Cols];
        int *rowStart=new int[Cols];
        SparseMatrix res(maxTerms);
        res.Rows=Rows;
        res.Cols=Cols;
        res.Terms=Terms;
        if (Terms>0){
            for (int i=0;i<Cols;i++) rowSize[i]=0;
            for (int i=0;i<Terms;i++) rowSize[array[i].col]++;//to see how many elements in a column i
            rowStart[0]=0;
            for(int i=1;i<Cols;i++) rowStart[i]=rowStart[i-1]+rowSize[i-1];
            int j;
            for (int i=0;i<Terms;i++){
                j=rowStart[array[i].col-1];//position of the ith nonzero element in res
                res.array[j].row=array[i].col;
                res.array[j].col=array[i].row;
                res.array[j].value=array[i].value;
                rowStart[array[i].col]++;
            }
        }
        delete []rowSize;
        delete []rowStart;
        return res;
    }
};


ostream &operator<<(ostream &out,SparseMatrix &M)
{

    out << "rows:" << M.Rows << endl;
    out << "columns:" << M.Cols << endl;
    out << "the number of nonzero terms:" << M.Terms << endl;
    for (int i = 0; i < M.Terms; i++)
    {
        out << "M(" << M.array[i].row << "," << M.array[i].col << ")=" << M.array[i].value << endl;
    }
    return out;
};


istream &operator>>(istream &in,SparseMatrix &M)
{
    cout << "Enter number of rows,columns,and terms:" << endl;
    in >> M.Rows >> M.Cols >> M.Terms;
    if (M.Terms > M.maxTerms)
    {
        cerr << "number of terms overflows!" << endl;
        exit(1);
    }
    for (int i = 0; i < M.Terms; i++)
    {
        cout << "Enter position and value of term:" << i + 1 << endl;
        cin >> M.array[i].row >> M.array[i].col >> M.array[i].value;
    }
    return in;
};

int main()
{
    SparseMatrix a(100);
    cin >> a;
    cout << a;
    SparseMatrix b=a.FastTranspose();
    cout<<endl<<endl;
    cout<<"the transpose:"<<endl;
    cout<<b;
    return 0;
}
