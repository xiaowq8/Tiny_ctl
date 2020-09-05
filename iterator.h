//
// Created by xjs on 2020/9/1.
//

#ifndef TINY_CTL_ITERATOR_H
#define TINY_CTL_ITERATOR_H
#include "tctl_object.h"

/*
 * 迭代器规则
 * 1、对用户所见的都应该是type**类型
 * 2、使用迭代器的对象应该在结构体中加入__iterator_obj_func成员
 * 3、容器应该存储自己的begin和end迭代器，并且返回迭代器的函数应该为iter_ptr，及使用指向指针的指针去指向type*，
 * */
typedef struct {
    void *(*iter_increment)(void *);
    void *(*iter_decrement)(void *);
    void *(*iter_add)(void *, int);
    void *(*iter_sub)(void *, int);
} __iterator_obj_func;

typedef struct {
    void *obj_this;
    __iterator_obj_func *obj_iter_func;
} __private_iterator;

typedef struct {
    void *ptr;
    void *(*increment)(void);
    void *(*decrement)(void);
    void *(*front_increment)(void);
    void *(*front_decrement)(void);
    void *(*add)(int);void *(*sub)(int);
    byte OBJECT_PRIVATE[sizeof(__private_iterator)];
} iterator;

typedef void* iter_ptr;
#define ITER(p) THIS(container_of((p), iterator, ptr))
#define ITER_TYPE(type) autofree(__destructor_iter) type**
#define NEW_ITER(p) (void*)(&(__constructor_iter((iterator*)p))->ptr)

iterator init_iter(void *obj_ptr, void *p, __iterator_obj_func *func);
iterator *__constructor_iter(iterator *iter);
void __destructor_iter(void *p);
#endif //TINY_CTL_ITERATOR_H
