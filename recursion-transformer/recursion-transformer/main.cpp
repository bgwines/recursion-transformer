//
//  main.cpp
//  recursion-transformer
//
//  Created by Brett Wines on 3/28/13.
//  Copyright (c) 2013 Brett Wines. All rights reserved.
//

#include <iostream>
#include <stack>
#include <vector>

#include "BST.h"
#include "fib.h"
#include "fact.h"
#include "permute.h"
#include "state.h"

using namespace std;

template<typename state_type,
typename parameters_type,
typename return_type>
Maybe<return_type> nonrec_wrapped(parameters_type params, bool return_type_is_void)
{
	//to pass info  up  between stackframes / rec calls / iterations
	Maybe<return_type> return_value;
    if (return_type_is_void)
        return_value.Nothing = true;//TODO: deal with this in constructor (with a parameter)
    
    stack<state_type> stackframes;
    stackframes.push(state_type(parameters_type(params))); //top stackframe
    
    //each iteration corresponds to a stackframe -- either a new recursive call,
    //or a previous one after it's performed one a recursive call.
	while (stackframes.size() != 0)
	{
		state_type curr_state = stackframes.top();
        stackframes.pop();
        
		//base cases
		if (curr_state.is_base_case())
		{
            curr_state.perform_base_case_operations();
			return_value = curr_state.calc_return_value();
			continue; //return
		}
        
		//recursive calls
        
        //deal with returnvalue
        if (curr_state.has_recursed_before())
        {
            curr_state.accept_return_value(return_value);
            curr_state.perform_post_rec_call_operations();
        }
        
        //recurse if necessary
		if (curr_state.should_still_recurse())
		{
            curr_state.perform_pre_rec_call_operations();
            
			//set up stackframe for recursive call
			parameters_type rec_params;
            curr_state.set_up_next_rec_call(rec_params);
			curr_state.note_rec_call_made();
            
            //push stackframe back on after modification
            stackframes.push(curr_state);
            
			stackframes.push(state_type(rec_params));
			continue; //recurse
		}
		else //no more recursive calls to make
		{
            curr_state.perform_post_rec_operations();
			return_value = curr_state.calc_return_value();
			continue; //return
		}
	}
    
    return Maybe<return_type>(return_value);
}

//--------------

template<typename type_bundle>
typename type_bundle::return_type nonrec(typename type_bundle::parameter_type params, bool return_type_is_void)
{
    Maybe<typename type_bundle::return_type> return_value
    = nonrec_wrapped<typename type_bundle::state_type,
    typename type_bundle::parameter_type,
    typename type_bundle::return_type>
    (params, return_type_is_void);
    
    if (!return_value.Nothing)
        return return_value.stored_elem;
}

void BST_test()
{
    cout << "\nBST_test";
    
    BST bst;
    bst.insert(4);
    bst.insert(2);
    bst.insert(1);
    bst.insert(3);
    bst.insert(6);
    bst.insert(5);
    bst.insert(7);
    
    bool failed = false;
    for (int i=-2; i<10; i++)
    {
        BST::BST_type_bundle::parameter_type params(i, bst.get_head());
        if (nonrec<BST::BST_type_bundle>(params, false) != bst.find(i))
        {
            failed = true;
            break;
        }
    }
    if (failed)
        cout << "\n\tFAILURE\n";
    else
        cout << "\n\tSUCCESS\n";
}

void fact_test()
{
    cout << "\nfact_test";
    bool failed = false;
    for (int i=0; i<7; i++)
    {
        fact_type_bundle::parameter_type params(i);
        fact_type_bundle::return_type fact = nonrec<fact_type_bundle>(params, false);
        if (fact != factorial(i))
        {
            failed = true;
            break;
        }
    }
    if (failed)
        cout << "\n\tFAILURE\n";
    else
        cout << "\n\tSUCCESS\n";
}

void fib_test()
{
    cout << "\nfib_test";
    bool failed = false;
    for (int i=0; i<7; i++)
    {
        fib_type_bundle::parameter_type params(i);
        int fib = nonrec<fib_type_bundle>(params, false);
        if (fib != fibonacci(i))
        {
            failed = true;
            break;
        }
    }
    if (failed)
        cout << "\n\tFAILURE\n";
    else
        cout << "\n\tSUCCESS\n";
}

void permute_test()
{
    cout << "\npermute_test\nnonrec:";
    permute_type_bundle::parameter_type params("abc", "");
    nonrec<permute_type_bundle>(params, true);
    cout << "\nrec:";
    permute("abc", "");
}

struct _is_void
{
    bool status = true;
    
    _is_void()
    : status(true)
    {}
};
struct _is_not_void
{
    bool status = false;
    
    _is_not_void()
    : status(false)
    {}
};

template <typename T>
class maybe {
public:
    typedef _is_not_void am_i_void;
    
    T stored_elem;
};

template <>
class maybe<void> {
public:
	typedef _is_void am_i_void;
    
    int stored_elem;
};

void test()
{
    BST_test();
    fact_test();
    fib_test();
    permute_test();
}

template <typename T>
void t(int i) {
    maybe<T> m;
    //    if (!maybe<T>::am_i_void::status)
    //        m.stored_elem = i;
    
    if (!maybe<T>::am_i_void::status)
        cout << "m is not void";
    else
        cout << "m is void";
}

int main(int argc, const char * argv[])
{
    //t<int>(142857);
    
    //test();
    
    return 0;
}

