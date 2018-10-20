//
// Created by andry on 20.10.2018.
//

#ifndef EXEM_OPTIONAL_H
#define EXEM_OPTIONAL_H

#include <type_traits>
#include <assert.h>

template <typename T>
class optional
{
private:
    bool to_null;
    typename std::aligned_storage<sizeof(T), alignof(T)>::type data_;

public:
    optional(): to_null(true) {}

    optional(T const& other): to_null(false)
    {
        new(reinterpret_cast<T *>(&data_)) T(other);
    }


    optional(optional const& other): to_null(other.to_null)
    {
        if (!to_null)
        {
            new(reinterpret_cast<T *>(&data_)) T(*other);
        }
    }

    ~optional() { clear(); }

    optional& operator=(optional const &other)
    {
        optional<T> helper = other;
        this->swap(helper);
        return *this;
    }

    void clear()
    {
        if (!to_null)
        {
            reinterpret_cast<const T*>(&data_)->~T();
        }
        to_null = true;
    }

    explicit operator bool() const { return !to_null;}

    T& operator*()
    {
        assert(!to_null);
        return *reinterpret_cast<T *>(&data_);
    }

    T const& operator*() const
    {
        assert(!to_null);
        return *reinterpret_cast<T const *>(&data_);
    }

    T* operator ->()
    {
        assert(!to_null);
        return reinterpret_cast<T *>(&data_);
    }

    T const* operator ->() const
    {
        assert(!to_null);
        return reinterpret_cast<T const *>(&data_);
    }

    void swap(optional<T> &other)
    {
        if (!to_null)
        {
            if (!other.to_null)
            {
                std::swap(*reinterpret_cast<T *>(&data_), *reinterpret_cast<T *>(&other.data_));
            }
            else
            {
                new(reinterpret_cast<T *>(&other.data_)) T(**this);
                this->clear();
                other.to_null = false;
            }
        }
        else if (!other.to_null)
        {
            new(reinterpret_cast<T *>(&data_)) T(*other);
            other.clear();
            to_null = false;
        }
    }

    template <typename U>
    bool operator==(optional<U> &other)
    {
        if (this->to_null && !other)
            return true;
        if (!this->to_null && other)
            return reinterpret_cast<T&>(data_) == reinterpret_cast<U&>(*other);
       return false;
    }

    template <typename U>
    bool operator!=(optional<U> &other)
    {
        return !(*this == other);
    }

    template <typename U>
    bool operator<(optional<U> &other)
    {
        if (this->to_null && !other)
            return false;
        if (!this->to_null && other)
            return reinterpret_cast<T&>(data_) < reinterpret_cast<U&>(*other);
        if (this->to_null)
            return true;
        return false;
    }

    template <typename U>
    bool operator>(optional<U> &other)
    {
        return other < *this;
    }

    template <typename U>
    bool operator<=(optional<U> &other)
    {
        return !(*this > other);
    }

    template <typename U>
    bool operator>=(optional<U> &other)
    {
        return !(*this < other);
    }
};

template <typename T>
void swap(optional<T> &left, optional<T> &right)
{
    left.swap(right);
}

#endif //EXEM_OPTIONAL_H
