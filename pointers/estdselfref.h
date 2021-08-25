#ifndef ESTDSELFREF_H
#define ESTDSELFREF_H

#include <memory>

template <class T> class eStdPointer;
template <class T> using stdsptr = std::shared_ptr<T>;
template <class T> using stdptr = eStdPointer<T>;

class eStdSelfRef {
    template <class T> friend class eStdPointer;
public:
    virtual ~eStdSelfRef();

    template <class T, typename... Args>
    static inline std::shared_ptr<T> make_shared(Args && ...args) {
        return (new T(std::forward<Args>(args)...))->template iniRef<T>();
    }

    template<class T>
    inline std::shared_ptr<T> ref() const {
        return std::static_pointer_cast<T>(
                    std::shared_ptr<eStdSelfRef>(mThisWeak));
    }
private:
    template<class T>
    inline std::weak_ptr<T> weakRef() const {
        if(mThisWeak.expired()) return std::weak_ptr<T>();
        return ref<T>();
    }

    template<class T>
    std::shared_ptr<T> iniRef() {
        std::shared_ptr<T> thisRef = std::shared_ptr<T>(static_cast<T*>(this));
        this->mThisWeak = std::static_pointer_cast<eStdSelfRef>(thisRef);
        return thisRef;
    }
private:
    std::weak_ptr<eStdSelfRef> mThisWeak;
};

namespace e {
    template <class T, typename... Args>
    inline std::shared_ptr<T> make_shared(Args && ...args) {
        return T::template make_shared<T>(std::forward<Args>(args)...);
    }
}

#endif // ESTDSELFREF_H
