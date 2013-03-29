//
//  permute.h
//  recursion_optimizer
//
//  Created by Brett Wines on 3/26/13.
//  Copyright (c) 2013 Brett Wines. All rights reserved.
//

#ifndef recursion_optimizer_permute_h
#define recursion_optimizer_permute_h

#include "state.h"

using namespace std;

class permute_parameters
{
public:
    string src;
    string so_far;
    
    permute_parameters(string src, string so_far)
    : src(src)
    , so_far(so_far)
    {}
    
    permute_parameters()
    : src("")
    , so_far("")
    {}
    
    void init(string src, string so_far)
    {
        this->src = src;
        this->so_far = so_far;
    }
};

class permute_locals
{
public:
    permute_locals()
    : i(0)
    {}
    
    int i;
};

typedef void attempt;

class permute_state : public state<attempt, permute_parameters, permute_locals>
{
public:
    permute_state(permute_parameters params)
    : state(params)
    {}
    
    bool should_still_recurse()
    {
        return locals.i < params.src.length();
    }
    
    void set_up_next_rec_call(permute_parameters& rec_params)
    {
        rec_params.src = params.src.substr(0, locals.i)
                       + params.src.substr(locals.i+1);
        
        rec_params.so_far = params.so_far + params.src[locals.i];
    }
    
    Maybe<attempt> calc_return_value()
    {
        return Maybe<attempt>();
    }
    
    bool is_base_case()
    {
        return params.src == "";
    }
    
    void perform_post_rec_operations()
    {}
    
    void perform_base_case_operations()
    {
        std::cout << "\n\t" << params.so_far;
    }
    
    virtual void perform_pre_rec_call_operations()
    {}
    
    virtual void perform_post_rec_call_operations()
    {
        locals.i++;
    }
    
private:
    
};

class permute_type_bundle
{
public:
    typedef permute_state state_type;
    typedef permute_parameters parameter_type;
    typedef attempt return_type;
    
};

void permute(string src, string so_far)
{
    if (src == "")
    {
        cout << "\n\t" << so_far;
        return;
    }
    
    for (int i=0; i<src.length(); i++)
    {
        string so_far_copy = so_far + src[i];
        
        string src_copy = src.substr(0,i) + src.substr(i+1);
        
        permute(src_copy, so_far_copy);
    }
}


#endif
