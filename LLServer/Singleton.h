/**
* Copyright (C) 2017-2050
* All rights reserved.
*
* @file       Singleton.h
* @brief
* @version    v1.0
* @author     WPP
* @date       2017/09/13
*
* Describe    单件模块
*/

#pragma once
#include <assert.h>

/**
* @class      CSingleton
* @brief      单件模板
*
* Describe
*/
template <typename T>
class CSingleton
{
protected:
	static T* ms_Singleton;
public:
	CSingleton(void)
	{
		assert(!ms_Singleton);
		ms_Singleton = static_cast<T*>(this);
	}
	virtual ~CSingleton(void)
	{
		assert(ms_Singleton);
		ms_Singleton = nullptr;
	}
	static T& getSingleton(void)
	{
		assert(ms_Singleton);
		return (*ms_Singleton);
	}
	static T* getSingletonPtr(void)
	{
		return (ms_Singleton);
	}

private:
	CSingleton& operator=(const CSingleton&)
	{
		return *this;
	}
	CSingleton(const CSingleton&){}
};