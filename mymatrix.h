#ifndef MYMATRIX
#define MYMATRIX

#include "mexception.h"

#include <iostream>

template<typename T>
class MyMatrix;

template<typename T>
std::ostream & operator <<(std::ostream &, const MyMatrix<T> &);

template<typename T>
std::istream & operator >>(std::istream &, MyMatrix<T> &);

template<typename T>
class MyMatrix
{
    T** element;
    int _size_i;
    int _size_j;
    int _end_i;
    int _end_j;
public:
    MyMatrix() throw (MyExcept);
    MyMatrix (int,int) throw (MyExcept);
    MyMatrix (const MyMatrix<T>&) throw (MyExcept);
    ~MyMatrix();
    T& get_element(int,int) throw (MyExcept);
    int size_i();
    int size_j();
    void push_i() throw (MyExcept);
    void push_j() throw (MyExcept);
    void pop_i() throw (MyExcept);
    void pop_j() throw (MyExcept);
    T get_det() throw (MyExcept);
    void transpose();
    T& operator =(const MyMatrix<T>&) throw (MyExcept);
    MyMatrix<T>& operator+(const MyMatrix<T>&) throw(MyExcept);
    MyMatrix<T>& operator-(const MyMatrix<T>&) throw (MyExcept);
    bool operator ==(const MyMatrix<T>&) throw(MyExcept);
    bool operator !=(const MyMatrix<T>&) throw(MyExcept);
    MyMatrix<T>& operator *(const MyMatrix<T>&) throw(MyExcept);
    MyMatrix<T>& operator *(const T&);
    T& operator [](int,int) throw (MyExcept);
    friend std::ostream& operator << <T>(std::ostream&,const MyMatrix<T>&);
    friend std::istream& operator >> <T>(std::istream& ,MyMatrix<T>&);


};
template<typename T>
MyMatrix<T>::MyMatrix() throw (MyExcept)
    :_size_i(5),_size_j(5),_end_i(0),_end_j(0)
{
    try
    {
        element=new T*[_size_i];
        for(int i(0);i<_size_i;i++)
        {
            element[i]=new T[_size_j];
        }
    }
    catch(std::bad_alloc &ba)
    {
        throw MyExcept("bad alloc");
    }
}
template<typename T>
MyMatrix<T>::MyMatrix(int i, int j) throw (MyExcept)
    :_end_i(i),_end_j(j),_size_i(_end_i*2),_size_j(_end_j*2)
{
    try
    {
        element=new T*[_size_i];
        for(int i(0);i<_size_i;i++)
        {
            element[i]=new T[_size_j];
        }
    }
    catch(std::bad_alloc &ba)
    {
        throw MyExcept("bad alloc");
    }
}

template<typename T>
MyMatrix<T>::MyMatrix(const MyMatrix<T> &m) throw (MyExcept)
    :_end_i(m._end_i),_end_j(m._end_j),_size_i(m._size_i),_size_j(m._size_j)
{
    try
    {
        element=new T*[_size_i];
        for(int i(0);i<_size_i;i++)
        {
            element[i]=new T[_size_j];
        }
        element=m.element;
    }
    catch(std::bad_alloc &ba)
    {
        throw MyExcept("bad alloc");
    }
}

template<typename T>
MyMatrix<T>::~MyMatrix()
{
    delete [] element;
}

template<typename T>
T& MyMatrix<T>::get_element(int i, int j) throw (MyExcept)
{
    if( (i<_end_i)&&(i>-1)&&(j<_end_j)&&(j>-1))
    {
        return element[i][j];
    }
    else
    {
        throw MyExcept("index error");
    }
}

template<typename T>
int MyMatrix<T>::size_i()
{
    return _end_i;
}

template<typename T>
int MyMatrix<T>::size_j()
{
    return _end_j;
}

template<typename T>
void MyMatrix<T>::push_i() throw (MyExcept)
{
    if(_end_i!=_size_i)
    {
        _end_i++;

    }
    else
    {
        try
        {
            _end_i++;
            _size_i*=2;
            T** ptr=new T*[_size_i];

            for(int i(0);i<_size_i;i++)
            {
                ptr[i]=new T[_size_j];
            }
            delete [] element;
            element=ptr;
            ptr=nullptr;

        }
        catch(std::bad_alloc &ba)
        {
            throw MyExcept("bad alloc");
        }
    }

}

template<typename T>
void MyMatrix<T>::push_j() throw (MyExcept)
{
    if(_end_j!=_size_j)
    {
        _end_j++;

    }
    else
    {
        try
        {
            _end_j++;
            _size_j*=2;
            T** ptr=new T*[_size_i];

            for(int i(0);i<_size_i;i++)
            {
                ptr[i]=new T[_size_j];
            }
            delete [] element;
            element=ptr;
            ptr=nullptr;

        }
        catch(std::bad_alloc &ba)
        {
            throw MyExcept("bad alloc");
        }
    }
}

template<typename T>
void MyMatrix<T>::pop_i() throw (MyExcept)
{
    if(_end_i!=0)
    {
        _end_i--;
    }
    else
    {
        throw MyExcept("index i empty");
    }
}

template<typename T>
void MyMatrix<T>::pop_j() throw (MyExcept)
{
    if(_end_j!=0)
    {
        _end_j--;
    }
    else
    {
        throw MyExcept("index i empty");
    }
}

template<typename T>
T MyMatrix<T>::get_det() throw(MyExcept)
{
    if(_end_i!=_end_j)
    {
        throw MyExcept("Matrix is not square");
    }
    else
    {
        //написать отдельную функцию для подсчета
    }


}

template<typename T>
void MyMatrix<T>::transpose()
{
    T tmp[_end_i][_end_j];

    for(int i(0);i<_end_i;i++)
    {
        for(int j(0);j<_end_j;j++)
        {
            tmp[i][j]=element[i][j];
        }
    }
    for(int i(0);i<_end_i;i++)
    {
        for(int j(0);j<_end_j;j++)
        {
            element[i][j]=tmp[j][i];
        }
    }
}

template<typename T>
T& MyMatrix<T>::operator =(const MyMatrix<T> &m) throw (MyExcept)
{
    _end_i=m._end_i;
    _end_j=m._end_j;
    _size_i=m._size_i;
    _size_j=m._size_j;
    try
    {
        T**tmp=new T*[_size_i];
        for(int i(0);i<_size_i;i++)
        {
            tmp[i]=new T[_size_j];
        }
        delete [] element;

        for(int i(0);i<_end_i;i++)
        {
            for(int j(0);j<_end_j;j++)
            {
                tmp[i][j]=m.element[i][j];
            }
        }
        element =tmp;
        tmp=nullptr;
        return *this;

    }
    catch(std::bad_alloc &ba)
    {
        throw MyExcept("bad alloc");
    }

}

template<typename T>
MyMatrix<T>& MyMatrix<T>::operator+(const MyMatrix<T> & m) throw (MyExcept)
{
    if((_end_i==m._end_i)&&(_end_j==m._end_j))
    {
        for(int i(0);i<_end_i;i++)
        {
            for(int j(0);i<_end_j;j++)
            {
                element[i][j]+=m.element[i][j];
            }
        }
        return *this;
    }
    else
    {
        throw MyExcept("different sizes matrixs");
    }
}

template<typename T>
MyMatrix<T>& MyMatrix<T>::operator-(const MyMatrix<T> & m) throw (MyExcept)
{
    if((_end_i==m._end_i)&&(_end_j==m._end_j))
    {
        for(int i(0);i<_end_i;i++)
        {
            for(int j(0);i<_end_j;j++)
            {
                element[i][j]-=m.element[i][j];
            }
        }
        return *this;
    }
    else
    {
        throw MyExcept("different sizes matrixs");
    }
}

template<typename T>
bool MyMatrix<T>::operator ==(const MyMatrix<T> & m) throw (MyExcept)
{
    if((_end_i==m._end_i)&&(_end_j==m._end_j))
    {
        for(int i(0);i<_end_i;i++)
        {
            for(int j(0);i<_end_j;j++)
            {
                if(element[i][j]!=m.element[i][j])
                {
                    return false;
                }
            }
        }
        return true;
    }
    else
    {
        throw MyExcept("different sizes matrixs");
    }
}

template<typename T>
bool MyMatrix<T>::operator !=(const MyMatrix<T> & m) throw (MyExcept)
{
    if((_end_i==m._end_i)&&(_end_j==m._end_j))
    {
        for(int i(0);i<_end_i;i++)
        {
            for(int j(0);i<_end_j;j++)
            {
                if(element[i][j]!=m.element[i][j])
                {
                    return true;
                }
            }
        }
        return false;
    }
    else
    {
        throw MyExcept("different sizes matrixs");
    }
}

template<typename T>
MyMatrix<T> &MyMatrix<T>::operator *(const MyMatrix<T> &m) throw (MyExcept)
{
    if(_end_j!=_end_i)
    {
        throw MyExcept("different sizes matrixs") ;
    }
    else
    {
        T tmp[_end_i][_end_j];
    }
}

template<typename T>
MyMatrix<T> &MyMatrix<T>::operator *(const T &c)
{

        for(int i(0);i<_end_i;i++)
        {
            for(int j(0);j<_end_j;j++)
            {
                element[i][j]*=c;
            }
        }
        return *this;


}

template<typename T>
T &MyMatrix<T>::operator [](int i, int j)
{
    if( (i<_end_i)&&(i>-1)&&(j<_end_j)&&(j>-1))
    {
        return element[i][j];
    }
    else
    {
        throw MyExcept("index error");
    }
}

template<class T>
std::ostream& operator <<(std::ostream& os,const MyMatrix<T>& m)
{

    for(int i(0);i<m._end_i;i++)
    {
        for(int j(0);j<m._end_j;j++)
        {
        os << m.element[i][j] << " ";
        }
    }
    return os;
}

template<class T>
std::istream& operator >> (std::istream& is ,MyMatrix<T>& m)
{
    for(int i(0);i<m._end_i;i++)
    {
        for(int j(0);j<m._end_j;j++)
        {
        is >> m.element[i][j];
        }
    }
    return is;
}


#endif // MYMATRIX

