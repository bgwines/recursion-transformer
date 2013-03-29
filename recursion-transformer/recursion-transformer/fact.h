//
//  fact.h
//  recursion_optimizer
//
//  Created by Brett Wines on 3/26/13.
//  Copyright (c) 2013 Brett Wines. All rights reserved.
//

#ifndef recursion_optimizer_fact_h
#define recursion_optimizer_fact_h

#include "state.h"

class fact_locals
{
};

class fact_parameters
{
public:
    int n;
    
    fact_parameters(int n)
    : n(n)
    {}
    
    fact_parameters()
    : n(0)
    {}
    
    void init(int n)
    {
        this->n = n;
    }
};

class fact_state : public state<int, fact_parameters, fact_locals>
{
public:
    fact_state(fact_parameters params)
    : state(params)
    {}
    
    bool should_still_recurse()
    {
        return n_rec_calls_made < 1;
    }
    
    void set_up_next_rec_call(fact_parameters &rec_params)
    {
        rec_params.n = params.n - 1;
    }
    
    Maybe<int> calc_return_value()
    {
        if (is_base_case())
            return Maybe<int>(params.n);
        else
        {
            return Maybe<int>(params.n * returned_values[0].stored_elem);
        }
    }
    
    bool is_base_case()
    {
        return params.n <= 2;
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

class fact_type_bundle
{
public:
    typedef fact_state state_type;
    typedef fact_parameters parameter_type;
    typedef int return_type;
};

int factorial(int n)
{
    if (n <= 2)
        return n;
    
    return n * factorial(n-1);
}


#endif
