#ifndef OOP_LAB6_7_TEMPLATEVECTORDINAMIC_H
#define OOP_LAB6_7_TEMPLATEVECTORDINAMIC_H
template <typename ElemType>
class IteratorVector;

template <typename ElemType>
class MyVector
{
private:
    int lungime;
    int capacitate;
    ElemType* elemente;

    /*Face resize*/
    void resize();
public:
    /*Constructor*/
    MyVector();

    /*Constructor de copiere*/
    MyVector(const MyVector& other);

    /*Destructor*/
    ~MyVector();

    /*Operator assignment
     * elibereaza obiectul curent
     * aloca spatiu pentru elemente si le copiaza din other in this
     */
    void operator=(const MyVector& other);

    /*Move constructor*/
    MyVector(MyVector&& other);

    /*Move assignment*/
    MyVector& operator=(MyVector&& other);

    /*Operator de indexare*/
    const ElemType& operator[](int index) const;
    ElemType& operator[](int index);

    /*Adaug in vector un element*/
    void add(const ElemType& e);

    /*Sterg elementul de pe o pozitie data*/
    void erase(IteratorVector<ElemType> poz);

    /*Returneaza elementul de pe pozitia data*/
    ElemType& get(int poz) const;

    /*Pun un element dat pe o pozitie data*/
    void set(int poz, const ElemType& e);

    /*Returnez lungimea vectorului*/
    int size() const noexcept;


    friend class IteratorVector<ElemType>;
    IteratorVector<ElemType> begin() const;
    IteratorVector<ElemType> end() const;

};



template<typename ElemType>
MyVector<ElemType>::MyVector(): elemente{ new ElemType[5]}, capacitate{5},lungime{0}{}

template<typename ElemType>
MyVector<ElemType>::MyVector(const MyVector<ElemType> &other)
{
    elemente = new ElemType[other.capacitate];
    lungime = other.lungime;
    capacitate = other.capacitate;
    for(int i=0; i<other.lungime; i++)
        elemente[i] = other.elemente[i];

}

template<typename ElemType>
ElemType& MyVector<ElemType>::operator[](int index)
{
    return elemente[index];
}

template<typename ElemType>
const ElemType& MyVector<ElemType>::operator[](int index) const
{
    return elemente[index];
}
template<typename ElemType>
void MyVector<ElemType>::erase(IteratorVector<ElemType> poz)
{
    int pozitie = poz.getPoz();
    for(int i= pozitie;i<lungime-1;i++)
        elemente[i]=elemente[i+1];
    lungime--;

}

template<typename ElemType>
void MyVector<ElemType>::operator=(const MyVector<ElemType> &other)
{
    if(this == &other)
        return ;
    delete[] elemente;
    elemente = new ElemType[other.capacitate];
    for(int i=0; i<lungime; i++)
        elemente[i] = other.elemente[i];
    lungime = other.lungime;
    capacitate = other.capacitate;
    return ;
}

template<typename ElemType>
MyVector<ElemType>::~MyVector()
{
    delete[] elemente;
}

template<typename ElemType>
ElemType &MyVector<ElemType>::get(int poz) const
{
    return this->elemente[poz];
}

template<typename ElemType>
int MyVector<ElemType>::size() const noexcept
{
    return this->lungime;
}

template<typename ElemType>
void MyVector<ElemType>::set(int poz, const ElemType &e)
{
    this->elemente[poz] = e;
}

template<typename ElemType>
MyVector<ElemType>::MyVector(MyVector&& other)
{
    elemente = other.elemente;
    lungime = other.lungime;
    capacitate = other.capacitate;

    other.elemente = nullptr;
    other.lungime = 0;
    other.capacitate = 0;
}

template<typename ElemType>
MyVector<ElemType>& MyVector<ElemType>::operator=(MyVector<ElemType>&& other){
    if (this == &other)
    {
        return *this;
    }
    delete[] elemente;

    elemente = other.elemente;
    lungime = other.lungime;
    capacitate = other.capacitate;

    other.elemente = nullptr;
    other.lungime = 0;
    other.capacitate = 0;
    return *this;
}


template<typename ElemType>
void MyVector<ElemType>::resize()
{
    if(this->lungime >= this->capacitate)
    {
        this->capacitate *= 2;
        ElemType* aux = new ElemType[this->capacitate];
        for(int i=0; i<this->lungime;i++)
            aux[i]= this->elemente[i];

        delete[] elemente;
        elemente = aux;
    }
}

template<typename ElemType>
void MyVector<ElemType>::add(const ElemType &e)
{
    resize();
    this->elemente[lungime++] = e;
}

template<typename ElemType>
IteratorVector<ElemType> MyVector<ElemType>::begin() const
{
    return IteratorVector<ElemType>(*this);
}

template<typename ElemType>
IteratorVector<ElemType> MyVector<ElemType>::end() const
{
    return IteratorVector<ElemType>(*this,lungime);
}

template <typename ElemType>
class IteratorVector
{
private:
    const MyVector<ElemType>& v;
    int poz = 0;
public:
    IteratorVector(const MyVector<ElemType>& v) noexcept;
    IteratorVector(const MyVector<ElemType>&v,int poz) noexcept;
    bool valid() const;
    ElemType& element() const;
    void next();
    ElemType& operator*();
    IteratorVector& operator++();
    bool operator==(const IteratorVector& other) noexcept;
    bool operator!=(const IteratorVector& other) noexcept;
    int getPoz(){return this->poz;};
};

template<typename ElemType>
IteratorVector<ElemType>::IteratorVector(const MyVector<ElemType>& v) noexcept:v{ v } {}

template<typename ElemType>
IteratorVector<ElemType>::IteratorVector(const MyVector<ElemType>& v, int poz)noexcept : v{ v }, poz{ poz } {}

template<typename ElemType>
bool IteratorVector<ElemType>::valid()const {
    return poz < v.lungime;
}

template<typename ElemType>
ElemType& IteratorVector<ElemType>::element() const {
    return v.elemente[poz];
}

template<typename ElemType>
void IteratorVector<ElemType>::next() {
    poz++;
}

template<typename ElemType>
ElemType& IteratorVector<ElemType>::operator*() {
    return element();
}

template<typename ElemType>
IteratorVector<ElemType>& IteratorVector<ElemType>::operator++() {
    next();
    return *this;
}

template<typename ElemType>
bool IteratorVector<ElemType>::operator==(const IteratorVector<ElemType>& other) noexcept {
    return poz == other.poz;
}

template<typename ElemType>
bool IteratorVector<ElemType>::operator!=(const IteratorVector<ElemType>& other)noexcept {
    return !(*this == other);
    //return *this != other;
}



#endif //OOP_LAB6_7_TEMPLATEVECTORDINAMIC_H
