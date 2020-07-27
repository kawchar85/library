#include<iostream>
using namespace std;

///copy from come on code on
/**
    C(n,r) mod m
    Using Matrix Exponentiation
    Time Complexity: O((r^3)*log(n))
    Space Complexity: O(r*r)
*/

long long MOD;

template< class T >
class Matrix
{
    public:
        int m,n;
        T *data;

        Matrix( int m, int n );
        Matrix( const Matrix< T > &matrix );

        const Matrix< T > &operator=( const Matrix< T > &A );
        const Matrix< T > operator*( const Matrix< T > &A );
        const Matrix< T > operator^( int P );

        ~Matrix();
};

template< class T >
Matrix< T >::Matrix( int m, int n )
{
    this->m = m;
    this->n = n;
    data = new T[m*n];
}

template< class T >
Matrix< T >::Matrix( const Matrix< T > &A )
{
    this->m = A.m;
    this->n = A.n;
    data = new T[m*n];
    for( int i = 0; i < m * n; i++ )
        data[i] = A.data[i];
}

template< class T >
Matrix< T >::~Matrix()
{
    delete [] data;
}

template< class T >
const Matrix< T > &Matrix< T >::operator=( const Matrix< T > &A )
{
    if( &A != this )
    {
        delete [] data;
        m = A.m;
        n = A.n;
        data = new T[m*n];
        for( int i = 0; i < m * n; i++ )
            data[i] = A.data[i];
    }
    return *this;
}

template< class T >
const Matrix< T > Matrix< T >::operator*( const Matrix< T > &A )
{
    Matrix C( m, A.n );
    for( int i = 0; i < m; ++i )
        for( int j = 0; j < A.n; ++j )
        {
            C.data[i*C.n+j]=0;
            for( int k = 0; k < n; ++k )
                C.data[i*C.n+j] = (C.data[i*C.n+j] + (data[i*n+k]*A.data[k*A.n+j])%MOD)%MOD;
        }
    return C;
}

template< class T >
const Matrix< T > Matrix< T >::operator^( int P )
{
    if( P == 1 ) return (*this);
    if( P & 1 ) return (*this) * ((*this) ^ (P-1));
    Matrix B = (*this) ^ (P/2);
    return B*B;
}

long long C(int n, int r)
{
    Matrix<long long> M(r+1,r+1);
    for (int i=0;i<(r+1)*(r+1);i++)
        M.data[i]=0;
    M.data[0]=1;
    for (int i=1;i<r+1;i++)
    {
        M.data[i*(r+1)+i-1]=1;
        M.data[i*(r+1)+i]=1;
    }
    return (M^n).data[r*(r+1)];
}

int main()
{
    int n,r;
    while (~scanf("%d%d%lld",&n,&r,&MOD))
    {
        printf("%lld\n",C(n, r));
    }
}
