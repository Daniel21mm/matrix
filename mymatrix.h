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
    int _end_i;
    int _end_j;
    int _size_i;
    int _size_j;

    T scalar_result(T* a, T **b, int _size, int index);
    T det_minor(T**,int);
    T** get_minor(T**,int,int);
    int steper(int,int);
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
    MyMatrix<T> transpose();
    MyMatrix<T>& operator =(const MyMatrix<T>&) throw (MyExcept);
    MyMatrix<T>& operator+(const MyMatrix<T>&) throw(MyExcept);
    MyMatrix<T>& operator-(const MyMatrix<T>&) throw (MyExcept);
    bool operator ==(const MyMatrix<T>&) throw(MyExcept);
    bool operator !=(const MyMatrix<T>&) throw(MyExcept);
    MyMatrix<T> operator *(const MyMatrix<T>&) throw(MyExcept);
    MyMatrix<T>& operator *(const T&);
    T* operator [](int) throw (MyExcept);
    friend std::ostream& operator << <T>(std::ostream&,const MyMatrix<T>&);
    friend std::istream& operator >> <T>(std::istream& ,MyMatrix<T>&);


};

template<typename T>
T MyMatrix<T>::scalar_result(T *a, T** b, int _size, int index)
{
    T result=a[0]*b[0][index];
    for(int i(1);i<_size;i++)
    {
        result+=a[i]*b[i][index];
    }
    return result;

}

template<typename T>
T** MyMatrix<T>::get_minor(T **m, int index, int size)
{
    T** tmp =new T*[size-1];
    for(int i(0);i<size-1;i++)
        tmp[i]=new T[size-1];

    for(int i(1);i<size;i++)
    {
        for(int j(0),in(0);j<size;j++)
        {
            if(j!=index)
            {

                tmp[i-1][in]=m[i][j];
                in++;
            }

        }
    }

    return tmp;
    for(int i(0);i<size-1;i++)
        delete [] tmp[size-1];

}

template<typename T>
int MyMatrix<T>::steper(int base, int index)
{
    int step=base;
    for(int i(0);i<index;i++)
    {
        step*=base;
    }
    return step;

}

template<typename T>
T MyMatrix<T>::det_minor(T **m, int size)
{
    T result=static_cast<T>(0);
    if(size==2)
    {
        return m[0][0]*m[1][1]-m[0][1]*m[1][0];
    }
    else
    {
        result=m[0][0]*det_minor(get_minor(m,0,size),size-1);

        for(int i(1);i<size;i++)
        {
            result+=m[0][i]*steper(-1,i+1)*det_minor(get_minor(m,i,size),size-1);
        }
        return result;
    }

}



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
    for(int i(0);i<_size_i;i++)
    {
        delete [] element[i];
    }
    element=nullptr;
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
            for(int i(0);i<_size_i/2;i++)
            {
                delete [] element[i];
            }
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
            for(int i(0);i<_size_i;i++)
            {
                delete [] element[i];
            }
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

        return det_minor(element,_end_i);
    }


}

template<typename T>
MyMatrix<T> MyMatrix<T>::transpose()
{

    MyMatrix<T> tmp(_end_j,_end_i);

    for(int i(0);i<_end_i;i++)
    {
        for(int j(0);j<_end_j;j++)
        {
            tmp.element[j][i]=element[i][j];
        }
    }
    return tmp;

}

template<typename T>
MyMatrix<T>& MyMatrix<T>::operator =(const MyMatrix<T> &m) throw (MyExcept)
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
        for(int i(0);i<_size_i;i++)
        {
            delete [] element[i];
        }
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
            for(int j(0);j<_end_j;j++)
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
            for(int j(0);j<_end_j;j++)
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
            for(int j(0);j<_end_j;j++)
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
            for(int j(0);j<_end_j;j++)
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
MyMatrix<T> MyMatrix<T>::operator *(const MyMatrix<T> &m) throw (MyExcept)
{
    MyMatrix<T> tmp(_end_i,m._end_j);
    if(_end_j!=m._end_i)
    {
        throw MyExcept("different sizes matrixs") ;
    }
    else
    {

        for(int i(0);i<_end_i;i++)
        {
            for(int j(0);j<m._end_j;j++)
            {
                tmp.element[i][j]=scalar_result(element[i],m.element,_end_j,j);
            }
        }

        return tmp;

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
T* MyMatrix<T>::operator [](int i) throw(MyExcept)
{
    if( (i<_end_i)&&(i>-1))
    {
        return element[i];
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
        os << "\n";
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

