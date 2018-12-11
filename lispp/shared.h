#pragma once

#include <assert.h>

class Shared
{
public:
	Shared() :
		ref_(0)
	{
	}

	Shared(const Shared&) :
		ref_(0)
	{
	}

	virtual ~Shared()
	{
		// Out of line to avoid weak vtable
	}

    Shared& operator=(const Shared&)
    {
        return *this;
    }

    void incRef()
    {
        assert(ref_ >= 0);
        ++ref_;
    }

    void decRef()
    {
        assert(ref_ > 0);
        if(--ref_ == 0)
        {
			delete this;
        }
    }

    int ref() const
    {
        return ref_;
    }

private:
    int ref_;
};

