#include "test.h"

// template <class T>
// class sign{
//     public:
//         sign(T);
//         T check();
//     private:
//         T status;
// };

template <class T>
sign<T>::sign(T s){status = s;}

template <class T>
T sign<T>::check(){return status;}

template class sign<int>;
