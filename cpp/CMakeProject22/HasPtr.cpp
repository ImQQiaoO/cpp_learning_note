#include "HasPtr.h"

HasPtr &HasPtr::operator=(const HasPtr &rhs) {
    if (this == &rhs)	// 自赋值，什么也不做
        return *this;
    ++*rhs.use;		    // 递增右侧运算对象的引用计数
    if (--*use == 0) {	// 然后递减本对象的引用计数
        delete ps;		// 如果没有其他用户
        delete use;		// 释放本对象分配的成员
    }
    ps = rhs.ps;		// 将数据从rhs拷贝到本对象
    i = rhs.i;
    use = rhs.use;
    return *this;		// 返回本对象
}

HasPtr::~HasPtr() {
    if (--*use == 0) {	// 如果引用计数变为0
        delete ps;		// 释放string内存
        delete use;		// 释放计数器内存
    }
}