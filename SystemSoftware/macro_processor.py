## One Pass SIC/XE Macro Processor
## Begin Source Code

# Initialize Global Variables
source_program = []
sic_op = []

# Macro Processor Data Structures
nam_tab = {}
def_tab = {}
arg_tab = {}
invocation_count = {}

# Begin substitite Method
def substitute(macro,args):
	# Initialize
	i = 0
	append = 1
	loop_flag = 0
	loop_left = ''
	loop_right = ''
	loop_condition = ''
	loop_line = 0
	array_args = 0

	# Internal Data Structures
	macro_time_var_tab = {}
	keyword_tab = {}
	loop_tab = []
	array_tab = {}

	# Check for Keyword Parameters
	keyword_param = 0
	for arg in arg_tab[macro]:
		if(arg.find('=') != -1):
			left,right = arg.split('=')
			keyword_tab[left] = right
			keyword_param = 1

	if keyword_param:
		for arg in args:
			left,right = arg.split('=')
			left = '&'+left
			keyword_tab[left] = right

			# Check For Arrays passed
			if(right.find('(') != -1):
				right = right[1:-1].split(',')
				array_tab[left] = right
				array_args = 1

	# Check For Arrays passed
	index = 0
	for arg in args:
		if(arg.find('(') != -1):
			vals = arg[1:-1].split(',')
			array_tab[arg_tab[macro][index]] = vals
			array_args = 1
		index += 1

	# Begin Expanding from def_tab
	while i < len(def_tab[macro]):
		# Fetch Line
		line = def_tab[macro][i]

		# Replace Variables
		# 5n Invocations
		# Needs better Tokenizing
		if keyword_param:
			for arg in keyword_tab:
				if array_args and arg in array_tab:
					continue
				line = line.replace(arg+' ',keyword_tab[arg]+' ')
				line = line.replace(arg+'\t',keyword_tab[arg]+'\t')
				line = line.replace(arg+'\'',keyword_tab[arg]+'\'')
				line = line.replace(arg+'\n',keyword_tab[arg]+'\n')
				line = line.replace(arg+',',keyword_tab[arg]+',')
				line = line.replace(arg+'->',keyword_tab[arg]+'')
		else:
			index = 0
			for arg in arg_tab[macro]:
				if array_args and arg in array_tab:
					continue
				line = line.replace(arg+' ',args[index]+' ')
				line = line.replace(arg+'\t',args[index]+'\t')
				line = line.replace(arg+'\'',args[index]+'\'')
				line = line.replace(arg+'\n',args[index]+'\n')
				line = line.replace(arg+',',args[index]+',')
				line = line.replace(arg+'->',args[index]+'')
				index += 1

		# Handle Array Arguements
		index = 0
		if array_args:
			# print array_tab
			for arg in macro_time_var_tab:
				line = line.replace('['+arg+']','['+str(macro_time_var_tab[arg])+']')

			for arg in array_tab:
				for k in range(len(array_tab[arg])):
					# print array_tab[arg][k]
					line = line.replace(arg+'['+str(k)+'] ',array_tab[arg][k]+' ')
					line = line.replace(arg+'['+str(k)+']\t',array_tab[arg][k]+'\t')
					line = line.replace(arg+'['+str(k)+']\'',array_tab[arg][k]+'\'')
					line = line.replace(arg+'['+str(k)+']\n',array_tab[arg][k]+'\n')
					line = line.replace(arg+'['+str(k)+'],',array_tab[arg][k]+',')
					line = line.replace(arg+'['+str(k)+']->',array_tab[arg][k]+'')

			# Handle %NITEMS
			for arg in array_tab:
				line = line.replace('%NITEMS('+arg+')',str(len(array_tab[arg])-1))

		# Split on Whitespaces
		words = line.split()

		# Begin Processing Conditional Statements
		# Begin If Statements
		if(words[0].lower() == 'if'):

			left = words[1][1:]
			condition = words[2]
			right = words[3][:-1]

			# Search macro_time_var_tab
			if(left in macro_time_var_tab):
				left = macro_time_var_tab[left]

			if(right in macro_time_var_tab):
				right = macro_time_var_tab[right]

			# Eliminate Empty Quotes
			left = left.replace('\'','')
			right = right.replace('\'','')

			# Begin Equating
			if(condition.lower() == 'eq'):
				if(left != right):
					append = 0
				else:
					append = 1
					i += 1
					continue

			if(condition.lower() == 'ne'):
				if(left == right):
					append = 0
				else:
					append = 1
					i += 1
					continue
			# End Equating

		if(words[0].lower() == 'else'):
			if(append):
				append = 0
			else:
				append = 1
				i += 1
				continue

		# Stop on endif
		if(words[0].lower() == 'endif'):
			append = 1
			i += 1
			continue
		# End If Statements

		# Begin While Loop
		if append and words[0].lower() == 'while':
			loop_flag = 1
			loop_left = words[1][1:]
			loop_condition = words[2]
			loop_right = words[3][:-1]
			loop_line = i

			i += 1
			continue

		# Stop on endw
		if loop_flag and words[0].lower() == 'endw':
			# Expand Loop
			if loop_left in arg_tab:
				left = arg_tab[loop_left]
			elif loop_left in macro_time_var_tab:
				left = macro_time_var_tab[loop_left]
			elif loop_left in keyword_tab:
				left = keyword_tab[loop_left]
			else:
				left = loop_left

			# print loop_right
			if loop_right in macro_time_var_tab:
				right = macro_time_var_tab[loop_right]
			elif loop_right in arg_tab:
				right = arg_tab[loop_right]
			elif loop_right in keyword_tab:
				right = keyword_tab[loop_right]
			else:
				right = loop_right

			left = int(left)
			right = int(right)

			# Begin Equating
			if loop_condition.lower() == 'eq':
				if left == right:
					i  = loop_line+1
					continue	
			elif loop_condition.lower() == 'ne':
				if left != right:
					i  = loop_line+1
					continue
			elif loop_condition.lower() == 'le':
				if left <= right:
					i  = loop_line+1
					continue
			#End Equating
				
			i += 1
			loop_flag = 0
			continue
		# End While Loop
		# End Conditional Statements

		# Generate Unique Labels
		line = line.replace('$', '$'+chr(invocation_count[macro]/26 + 65)+chr(invocation_count[macro]%26 + 65))

		# Append to Output
		if append:
			# Check For Macro Variable Declaration
			if(len(words)>1 and words[1].lower() == 'set'):
				# Check for Operators
				if(words[2].find('+') != -1):
					argsn = words[2].split('+')
					macro_time_var_tab[argsn[0]] = int(macro_time_var_tab[words[0]]) + int(argsn[1])
					i += 1
					continue

				if(words[2].find('-') != -1):
					argsn = words[2].split('-')
					macro_time_var_tab[argsn[0]] = int(macro_time_var_tab[words[0]]) - int(argsn[1])
					i += 1
					continue

				# Add to macro_time_var_tab
				macro_time_var_tab[str(words[0])] = int(words[2])
				i += 1
				continue

			sic_op.append(line[:-1])

		i += 1
# End substitute

# Begin Main Program
fin = open('large.sic','r')

line_count = 1
level = 0
current_macro = ''

# Read Line By line
for line in fin:

	print line

	# Append each line to source_program
	source_program.append(line)

	# Skip on Empty Line
	if(line[0] == '\n'):
		line_count += 1
		continue

	# Split on whitespaces
	words = line.split()

	# Skip line if Commented
	if len(words) > 0 and len(words[0]) > 0 and words[0][0] == '.':
		line_count += 1
		continue

	# Check for Macro Definition
	if(len(words)>1 and words[1].lower() == 'macro'):
		# Append to nam_tab
		# Data Structure: {Macro Name : Start Line, End Line}
		nam_tab[words[0]] = [line_count, 0]
		# Initialize def_tab
		def_tab[words[0]] = []
		# Append to arg_tab
		arg_tab[words[0]] = words[2].split(',')
		# Store Current Macro name
		current_macro = words[0]
		line_count += 1
		level += 1
		continue

	# If inside Macro Definition, append to def_tab
	if(level):
		if(words[0].lower() == 'mend'):
			nam_tab[current_macro][1] = line_count
			level -= 1
		else:
			def_tab[current_macro].append(line)
		line_count += 1
		continue

	# Check for Macro Invocation
	macro_invoked = 0

	for macro_name in nam_tab:
		index = 0
		# If Line contains Label
		if(len(words)>1 and macro_name.lower() == words[1].lower()):
			index = 2
			# Append Label to Output
			sic_op.append(words[0])
			# Flag macro_invoked
			macro_invoked = 1

		# If Line contains No Label
		if len(words) > 0 and macro_name.lower() == words[0].lower():
			index = 1
			# Flag macro_invoked
			macro_invoked = 1

		if macro_invoked:
			# Split Arguements
			if words[index].find('(') == -1:
				args = words[index].split(',')
			else:
				args = []
				s = ''
				# Remove Spaces
				words[index].replace(' ','')
				# Split Args
				b_flag = 0
				for i in range(len(words[index])):
					if words[index][i] == '(':
						b_flag = 1

					if b_flag and words[index][i]==')':
							s += words[index][i]
							b_flag = 0
					elif not b_flag and words[index][i] == ',':
							args.append(s)
							s = ''
					else:
						s += words[index][i]
				args.append(s)
			# Comment Invocation
			sic_op.append('.' + line)
			# Increase invocation_count
			if(macro_name in invocation_count):
				invocation_count[macro_name] += 1
			else:
				invocation_count[macro_name] = 0
			# Invoke substitite Method
			substitute(macro_name,args)
			break

	if not macro_invoked:
		sic_op.append(line[:-1])

	line_count += 1

# End Main Program

# Print Expanded Source Program
for line in sic_op:
	print line

## End of Source Code