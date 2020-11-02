import copy

# for given n variables print their disjunctive normal form
# input n number 
# output string 

"""
    Example
    n == 2
    (a0 & a1) | (a0 & ~a1) | (~a0 & a1) | (~a0 & ~a1)


"""

variable = "{}a{}"
statement = "({} & {})"

p = variable.format("",0)

# q = variable.format("", 1)
# s = statement.format(p,q)

# print(s)

def print_disjunctive_form(n):

    var_list = []
    statements = []
    
    for i in range(n):
        var_list.append(["a{}".format(i), "~a{}".format(i)])
    
    helper(var_list, 0, statements, [])
    
    fun = lambda x: " & ".join(x)
    fun2 = lambda x: "({})".format(x)
    statements = map(fun, statements)
    statements = map(fun2, statements)
    return " | ".join(statements)




    

# Do we want 0 or 1

def helper(v_list, i, statements, statement):

    if i == len(v_list):
        t = copy.copy(statement)
        statements.append(t)
        return
    
    statement.append(v_list[i][0])
    helper(v_list, i+1, statements, statement)
    statement.pop()
    statement.append(v_list[i][1])
    helper(v_list, i+1, statements, statement)
    statement.pop()


print(print_disjunctive_form(5))


def print_truth_table(n):
    values = []
    helper_2(n, 0, values, [])
    return values


def helper_2(limit, i, statements, statement):

    if i == limit:
        t = copy.copy(statement)
        t.append("\n")
        statements.append(t)
        return

    statement.append("0")
    helper_2(limit, i+1, statements, statement)
    statement.pop()
    statement.append("1")
    helper_2(limit, i+1, statements, statement)
    statement.pop()



