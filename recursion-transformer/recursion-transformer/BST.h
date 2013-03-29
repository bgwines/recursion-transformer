//
//  BST.h
//  recursion_optimizer
//
//  Created by Brett Wines on 3/26/13.
//  Copyright (c) 2013 Brett Wines. All rights reserved.
//

#ifndef recursion_optimizer_BST_h
#define recursion_optimizer_BST_h

#include "state.h"

class BST {
private:
    struct node
    {
        node* left;
        node* right;
        int elem;
        
        node()
        : left(NULL)
        , right(NULL)
        {}
        
        node(int elem)
        : left(NULL)
        , right(NULL)
        , elem(elem)
        {}
    };
    
    node* head;
    
    void insert_rec(int elem, node*& curr)
    {
        if (curr == NULL)
        {
            curr = new node(elem);
            return;
        }
        
        if (elem < curr->elem)
            insert_rec(elem, curr->left);
        else
            insert_rec(elem, curr->right);
    }
    
    bool find_rec(int elem, node* curr)
    {
        if (curr == NULL)
            return false;
        if (curr->elem == elem)
            return true;
        
        if (elem < curr->elem)
            return find_rec(elem, curr->left);
        else
            return find_rec(elem, curr->right);
    }
    
public:
    BST()
    : head(NULL)
    {
        
    }
    
    void insert(int elem)
    {
        insert_rec(elem, head);
    }
    
    bool find(int elem)
    {
        return find_rec(elem, head);
    }
    
    node* get_head()
    {
        return head;
    }
    
    class BST_find_locals
    {
    };
    
    class BST_find_parameters
    {
    public:
        int elem;
        node* curr;
        
        BST_find_parameters(int elem, node* curr)
        : elem(elem)
        , curr(curr)
        {}
        
        BST_find_parameters(int elem)
        : elem(elem)
        , curr(NULL)
        {}
        
        BST_find_parameters()
        : elem(0)
        , curr(NULL)
        {}
    };
    
    class BST_find_state : public state<bool, BST_find_parameters, BST_find_locals>
    {
    public:
        BST_find_state(BST_find_parameters params)
        : state(params)
        {}
        
        bool should_still_recurse()
        {
            return n_rec_calls_made < 1;
        }
        
        void set_up_next_rec_call(BST_find_parameters& rec_params)
        {
            rec_params.elem = params.elem;
            if (params.elem < params.curr->elem)
                rec_params.curr = params.curr->left;
            else
                rec_params.curr = params.curr->right;
        }
        
        Maybe<bool> calc_return_value()
        {
            if (is_base_case())
            {
                if (params.curr == NULL)
                    return Maybe<bool>(false);
                else //always true in this case: (params.curr->elem == params.elem)
                    return Maybe<bool>(true);
            }
            else
            {
                return Maybe<bool>(returned_values[0]);
            }
        }
        
        bool is_base_case()
        {
            return params.curr == NULL || params.curr->elem == params.elem;
        }
        
        void perform_post_rec_operations()
        {}
        
        void perform_base_case_operations()
        {}
        
        virtual void perform_pre_rec_call_operations()
        {}
        
        virtual void perform_post_rec_call_operations()
        {}

    private:
    };
    
    class BST_type_bundle
    {
    public:
        typedef BST_find_state state_type;
        typedef BST_find_parameters parameter_type;
        typedef bool return_type;

    };
};

#endif
