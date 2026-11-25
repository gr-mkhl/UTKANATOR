#ifndef _TREE_STRUCT_H_
#define _TREE_STRUST_H_

typedef char* data_t;
#define os "s"

struct leaf_t
{
    leaf_t* left;
    leaf_t* right;
    data_t data;
};

#endif
