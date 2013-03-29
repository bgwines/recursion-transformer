//
//  fib.h
//  recursion_optimizer
//
//  Created by Brett Wines on 3/26/13.
//  Copyright (c) 2013 Brett Wines. All rights reserved.
//

#ifndef recursion_optimizer_fib_h
#define recursion_optimizer_fib_h

#include "state.h"

class fib_locals
{
};

class fib_parameters
{
public:
    int n;
    
    fib_parameters(int n)
    : n(n)
    {}
    
    fib_parameters()
    : n(0)
    {}
    
    void init(int n)
    {
        this->n = n;
    }
};

class fib_state : public state<int, fib_parameters, fib_locals>
{
public:
    fib_state(fib_parameters params)
    : state(params)
    {}
    
    bool should_still_recurse()
    {
        return n_rec_calls_made < 2;
    }
    
    void set_up_next_rec_call(fib_parameters& rec_params)
    {
        if (n_rec_calls_made == 0)
            rec_params.n = params.n - 1;
        else
            rec_params.n = params.n - 2;
    }
    
    Maybe<int> calc_return_value()
    {
        if (is_base_case())
            return Maybe<int>(1);
        else
        {
            return Maybe<int>(returned_values[0].stored_elem
                            + returned_values[1].stored_elem);
        }
    }
    
    bool is_base_case()
    {
        return params.n <= 1;
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

class fib_type_bundle
{
public:
    typedef fib_state state_type;
    typedef fib_parameters parameter_type;
    typedef int return_type;
};

int fibonacci(int n)
{
    if (n <= 1)
        return 1;
    
    return fibonacci(n-1) + fibonacci(n-2);
}

#endif
