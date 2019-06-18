template < typename T, int N >
class Array
{
	private:
    T m_array[N];
	public:
    int length();
    bool set(int index, T value);
    bool get(int index, T& value);
    T& operator[] (int index);
    T operator[] (int index) const;
    virtual ~Array();                 // Array 类可能被继承，析构函数声明为虚函数
};

template < typename T, int N >
int Array<T, N>::length()
{
    return N;
}

template < typename T, int N >
bool Array<T, N>::set(int index, T value)
{
    bool ret = (index >=0) && (index < N);
    
    if( ret )
    {
	        m_array[index] = value;
	    }
	    
	    return ret;
}

template < typename T, int N >
bool Array<T, N>::get(int index, T& value)
{
    bool ret = (index >=0) && (index < N);
    
    if( ret )
    {
	        value = m_array[index];
	    }
	    
	    return ret;
}

template < typename T, int N >
T& Array<T, N>::operator[] (int index)
{
    return m_array[index];
}

template  < typename T, int N >
T Array<T, N>::operator[] (int index) const
{
    return m_array[index];    
}

template < typename T, int N >
Array<T, N>::~Array()
{
}
