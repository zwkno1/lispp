#pragma once

#include <algorithm>

//
// "Handle" or "smart pointer" class for classes derived from Shared
//

template<typename T>
class HandleBase
{
public:

    typedef T element_type;

    T* get() const
    {
        return ptr_;
    }

    T* operator->() const
    {
        return ptr_;
    }

    T& operator*() const
    {
        return *ptr_;
    }

    operator bool() const
    {
        return ptr_ ? true : false;
    }

    void swap(HandleBase& other)
    {
        std::swap(ptr_, other.ptr_);
    }

    T* ptr_;

};

template<typename T, typename U>
inline bool operator==(const HandleBase<T>& lhs, const HandleBase<U>& rhs)
{
    T* l = lhs.get();
    U* r = rhs.get();
    if(l && r)
    {
        return *l == *r;
    }

    // Note: don't use if { } else { }. This causes lots warnings when
    // compiling with GCC and optimization enabled. See bug 2330.
    return !l && !r;
}

template<typename T, typename U>
inline bool operator!=(const HandleBase<T>& lhs, const HandleBase<U>& rhs)
{
    return !operator==(lhs, rhs);
}

template<typename T, typename U>
inline bool operator<(const HandleBase<T>& lhs, const HandleBase<U>& rhs)
{
    T* l = lhs.get();
    U* r = rhs.get();
    if(l && r)
    {
        return *l < *r;
    }

    // Note: don't use if { } else { }. This causes lots warnings when
    // compiling with GCC and optimization enabled. See bug 2330.
    return !l && r;
}

template<typename T, typename U>
inline bool operator<=(const HandleBase<T>& lhs, const HandleBase<U>& rhs)
{
    return lhs < rhs || lhs == rhs;
}

template<typename T, typename U>
inline bool operator>(const HandleBase<T>& lhs, const HandleBase<U>& rhs)
{
    return !(lhs < rhs || lhs == rhs);
}

template<typename T, typename U>
inline bool operator>=(const HandleBase<T>& lhs, const HandleBase<U>& rhs)
{
    return !(lhs < rhs);
}

template<typename T>
class Handle : public HandleBase<T>
{
public:

    Handle(T* p = 0)
    {
        this->ptr_ = p;

        if(this->ptr_)
        {
            this->ptr_->incRef();
        }
    }

    template<typename Y>
    Handle(const Handle<Y>& r)
    {
        this->ptr_ = r.ptr_;

        if(this->ptr_)
        {
            this->ptr_->incRef();
        }
    }

    Handle(const Handle& r)
    {
        this->ptr_ = r.ptr_;

        if(this->ptr_)
        {
            this->ptr_->incRef();
        }
    }

    ~Handle()
    {
        if(this->ptr_)
        {
            this->ptr_->decRef();
        }
    }

    Handle& operator=(T* p)
    {
        if(this->ptr_ != p)
        {
            if(p)
            {
                p->incRef();
            }

            T* ptr = this->ptr_;
            this->ptr_ = p;

            if(ptr)
            {
                ptr->decRef();
            }
        }
        return *this;
    }

    template<typename Y>
    Handle& operator=(const Handle<Y>& r)
    {
        if(this->ptr_ != r.ptr_)
        {
            if(r.ptr_)
            {
                r.ptr_->incRef();
            }

            T* ptr = this->ptr_;
            this->ptr_ = r.ptr_;

            if(ptr)
            {
                ptr->decRef();
            }
        }
        return *this;
    }

    Handle& operator=(const Handle& r)
    {
        if(this->ptr_ != r.ptr_)
        {
            if(r.ptr_)
            {
                r.ptr_->incRef();
            }

            T* ptr = this->ptr_;
            this->ptr_ = r.ptr_;

            if(ptr)
            {
                ptr->decRef();
            }
        }
        return *this;
    }

    template<class Y>
    static Handle dynamicCast(const HandleBase<Y>& r)
    {
        return Handle(dynamic_cast<T*>(r.ptr_));
    }

    template<class Y>
    static Handle dynamicCast(Y* p)
    {
        return Handle(dynamic_cast<T*>(p));
    }
};

