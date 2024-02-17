#include <iostream>
#include <exception>

struct IntDynArrayStruct{
    int size;
    int ptr;
    int* data;
};

IntDynArrayStruct initArray(int size){
    IntDynArrayStruct obj;
    obj.data = new int[size]();
    obj.size = size;
    obj.ptr = 0;
    return obj;
}

void deleteObj(IntDynArrayStruct& obj)
{
    delete[] obj.data;
}

struct Temp{
    Temp() { std::cout << "Created Temp\n"; }
    Temp(int x) { std::cout << "Created N Temp\n"; }
};

int GLOBALX = 42;

class IntDynArray{
private:
    int shitty_var;
    int m_size;
    int m_ptr;
    int* m_data;
    void init(int size);
    Temp t;
    int& ref;
    const int const_val;
    //inline static int static_val = 5;
    static int static_val;

public:
    // constructor
    IntDynArray(int size);

    // default constructor
    IntDynArray();
    //IntDynArray() = default;

    ~IntDynArray();

    int& getElem(int idx);
    bool at(int idx, int& val);
    int getSize() const;
    void print() const;

    inline static void staticMethod(){
        std::cout << "Static method\n";
    }
};

int IntDynArray::static_val = 5;

IntDynArray::~IntDynArray(){
    delete[] m_data;
    m_data = nullptr;
    m_size = 0;
    m_ptr = 0;
    std::cout << "Object destroyed\n";
   //IntDynArray();
   --static_val;
}

IntDynArray::IntDynArray() :    ref(GLOBALX), 
                                m_size(1), 
                                shitty_var(m_size),
                                const_val(42)
{
    ++static_val;
    std::cout << shitty_var << '\n';
    init(1);
    std::cout << "Default object created\n";
    
    //IntDynArray::~IntDynArray();
}

IntDynArray::IntDynArray(int size) :ref(GLOBALX), t(5), const_val(42) {
    std::cout << "Sized object created\n";
    init(size);
}

void IntDynArray::init(int size){
    m_data = new int[size]();
    m_size = size;
    m_ptr = 0;
}

int& IntDynArray::getElem(int idx){
    if (idx < 0 || idx >= m_size)
        throw std::range_error("idx out of range");
    return m_data[idx];
}

bool IntDynArray::at(int idx, int& val){
    if (idx < 0 || idx >= m_size)
        return false;
    val = m_data[idx];
    return true;
}

int IntDynArray::getSize() const{
    //m_ptr = 2; // CE
    int x = 2;
    m_data[2] = 5;
    *(m_data + 2) = 5;
    std::cout << m_ptr << '\n';
    return m_size;
}

void IntDynArray::print() const{
    for (int i = 0; i < m_size; ++i)
        std::cout << m_data[i] << ' ';
    std::cout << '\n';
}

int main()
{
    IntDynArray* obj_ptr;
    {
        IntDynArray obj(5);
        *(int*)&obj = 4;
        std::cout << *(int*)&obj <<'\n';
        obj.getElem(1);
        obj.print();
        obj.staticMethod();
        obj_ptr = &obj;
    }

    const IntDynArray const_obj;
    const_obj.getSize();

    IntDynArray::staticMethod();
    const_obj.staticMethod();
   // obj_ptr->getElem(5);
   // delete obj_ptr;
    return 0;
}