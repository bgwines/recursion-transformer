#int fibonacci(int n)
#{
#    if (n <= 1)
#        return 1;
#    
#    return fibonacci(n-1) + fibonacci(n-2);
#}

#def helper(function):
#	first_space_index = function.find(' ')
#	return_type = function[0 : first_space_index]
#
#	param_start_index = function.find('(')
#	function_name = function[first_space_index+1 : param_start_index-1]
#
#	param_end_index = function.find(')')
#	parameters = function[param_start_index+1 : param_end_index-1]

def transform(function): #(param in string form)
	# divide function into parts
		# get returntype
		# get function name
		# get list of parameter types and names
		# get base cases
		# get recursive calls

	# store all above in object
	# convert object to string form of C++ state object

	# make new file, insert nonrec<>() and state object into code

def main():
	#fileread
	#transform()