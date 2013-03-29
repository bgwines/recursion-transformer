//
//  state.h
//  recursion_optimizer
//
//  Created by Brett Wines on 3/26/13.
//  Copyright (c) 2013 Brett Wines. All rights reserved.
//

#ifndef __recursion_optimizer__state__
#define __recursion_optimizer__state__

#include <vector>

template<class stored_class>
struct Maybe
{
    stored_class stored_elem;
    bool Nothing;
    
    Maybe(const Maybe<stored_class> &maybe)
    : stored_elem(maybe.stored_elem)
    , Nothing(maybe.Nothing)
    {}
    
    Maybe(stored_class stored_elem)
    : stored_elem(stored_elem)
    , Nothing(false)
    {}
    
    Maybe()
    : Nothing(true)
    {}
    
    void operator= (const Maybe<stored_class>& other)
    {
        stored_elem = other.stored_elem;
        Nothing = other.Nothing;
    }
};

template <typename return_type, typename parameters_type, typename locals_type>
class state
{
public:
    state(parameters_type params)
    : params(params)
    , n_rec_calls_made(0)
    {}
    
    bool has_recursed_before()
    {
        return n_rec_calls_made > 0;
    }
    
    void accept_return_value(Maybe<return_type> return_value)
    {
        if (!return_value.Nothing)
        {
            returned_values.push_back(return_value.stored_elem);
        }
    }
    
    void note_rec_call_made()
    {
        n_rec_calls_made++;
    }
    
    virtual bool should_still_recurse() = 0;
    
    virtual void set_up_next_rec_call(parameters_type &rec_params) = 0;
    
    virtual Maybe<return_type> calc_return_value() = 0;
    
    virtual bool is_base_case() = 0;
    
    virtual void perform_post_rec_operations() = 0;
    
    virtual void perform_base_case_operations() = 0;
    
    virtual void perform_pre_rec_call_operations() = 0;
    
    virtual void perform_post_rec_call_operations() = 0;
    
protected:
    std::vector< Maybe<return_type> > returned_values;
    
    parameters_type params;
    
    locals_type locals;
    
    size_t n_rec_calls_made;
};


#endif /* defined(__recursion_optimizer__state__) */
