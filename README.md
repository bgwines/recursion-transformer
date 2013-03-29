Thi program transforms most recursive functions into iterative functions that have 
identical functionality.

The following is the general recursive format, the domain of the transformation:

	return_type rec(state.params)
	{
	    if (is_base_case())
	    {
			perform_base_case_operations();
	        return calc_return_value();
	    }
	    
	    //state.locals initialized
	    while (should_still_recurse())
	    {
	    	perform_pre_rec_call_operations();

	        set_up_next_rec_call();
	        note_rec_call_made();
	        rec();
	        if (has_recursed_before())
	        	accept_return_value();

	        perform_post_rec_call_operations();
	    }

	    perform_post_rec_operations();

	    return calc_return_value();
	}
