#pragma once

#include <cstdint>

#include "shared.h"
#include "handle.h"

enum ObjectType : std::uint8_t
{
	OBJECT_NUMBER,
	OBJECT_LIST,
	OBJECT_FUNCTION,
};

class Object : public Shared
{
protected:
	Object(std::uint8_t t)
		: type_(t)
	{
	}

public:
	inline std::uint8_t type() const
	{
		return type_;
	}

private:
	std::uint8_t type_;
};

typedef Handle<Object> ObjectPtr;

class Number : public Object
{
public:
	Number(int v = 0)
		: Object(OBJECT_NUMBER)
		, value_(v)
	{
	}

	inline int value()
	{
		return value_;
	}

private:
	int value_;
};
typedef Handle<Number> NumberPtr;

class List : public Object
{
public:
	List()
		: Object(OBJECT_LIST)
	{
	}

	inline ObjectPtr car()
	{
		return car_;
	}

	inline ObjectPtr cdr()
	{
		return cdr_;
	}

private:
	ObjectPtr car_;
	ObjectPtr cdr_;
};

typedef Handle<List> ListPtr;

class Function : public Object
{
public:
	Function()
		: Object(OBJECT_FUNCTION)
	{
	}

};

typedef Handle<Function> FunctionPtr;

