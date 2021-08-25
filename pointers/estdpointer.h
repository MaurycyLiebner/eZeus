// enve - 2D animations software
// Copyright (C) 2016-2020 Maurycy Liebner

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef ESTDPOINTER_H
#define ESTDPOINTER_H

#include "estdselfref.h"

template <class T>
class eStdPointer {
    std::weak_ptr<eStdSelfRef> wp;
    eStdSelfRef* rp = nullptr;

    void updateRawPtr() {
        if(wp.expired()) {
            rp = nullptr;
        } else {
            const std::shared_ptr<eStdSelfRef> sp = wp.lock();
            rp = sp.get();
        }
    }
public:
    inline eStdPointer() {
        static_assert(std::is_base_of<eStdSelfRef, T>::value,
                      "eStdPointer can be used only for eStdSelfRef derived classes");
    }
    inline eStdPointer(T * const p) : rp(p) {
        static_assert(std::is_base_of<eStdSelfRef, T>::value,
                      "eStdPointer can be used only for eStdSelfRef derived classes");
        if(p) wp = p->template weakRef<T>();
    }
    inline eStdPointer(const stdsptr<T>& p) : rp(p.get()) {
        static_assert(std::is_base_of<eStdSelfRef, T>::value,
                      "eStdPointer can be used only for eStdSelfRef derived classes");
        if(p) wp = p->template weakRef<T>();
    }

    inline void swap(eStdPointer &other) {
        wp.swap(other.wp);
        updateRawPtr();
        other.updateRawPtr();
    }

    inline eStdPointer<T> &operator=(T* const p) {
        rp = p;
        if(!p) wp.reset();
        else wp = static_cast<eStdSelfRef*>(p)->weakRef<eStdSelfRef>();
        return *this;
    }

    inline T* data() const {
        if(wp.expired()) return nullptr;
        return static_cast<T*>(rp);
    }

    inline T* get() const { return data(); }

    inline T* operator->() const
    { return data(); }
    inline T& operator*() const
    { return *data(); }
    inline operator T*() const
    { return data(); }

    inline bool isNull() const
    { return wp.expired(); }

    inline void clear() {
        wp.reset();
        rp = nullptr;
    }
};

template <class T>
inline bool operator==(const T *o, const eStdPointer<T> &p)
{ return o == p.operator->(); }

template<class T>
inline bool operator==(const eStdPointer<T> &p, const T *o)
{ return p.operator->() == o; }

template <class T>
inline bool operator==(T *o, const eStdPointer<T> &p)
{ return o == p.operator->(); }

template<class T>
inline bool operator==(const eStdPointer<T> &p, T *o)
{ return p.operator->() == o; }

template<class T>
inline bool operator==(const eStdPointer<T> &p1, const eStdPointer<T> &p2)
{ return p1.operator->() == p2.operator->(); }

template<class T1, class T2>
inline bool operator==(const eStdPointer<T1> &p1, const eStdPointer<T2> &p2)
{ return p1.operator->() == p2.operator->(); }

template <class T>
inline bool operator!=(const T *o, const eStdPointer<T> &p)
{ return o != p.operator->(); }

template<class T>
inline bool operator!= (const eStdPointer<T> &p, const T *o)
{ return p.operator->() != o; }

template <class T>
inline bool operator!=(T *o, const eStdPointer<T> &p)
{ return o != p.operator->(); }

template<class T>
inline bool operator!= (const eStdPointer<T> &p, T *o)
{ return p.operator->() != o; }

template<class T>
inline bool operator!= (const eStdPointer<T> &p1, const eStdPointer<T> &p2)
{ return p1.operator->() != p2.operator->() ; }


#endif // ESTDPOINTER_H
