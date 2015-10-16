#
# Constraint - disks can only be moved from or to the 2nd peg
#

def hanoi(n, source, auxillary, target):
    
    if n > 0:
        global invokes
        invokes = invokes + 1

        # Move tower of size n - 1 to target:
        hanoi(n - 1, source, auxillary, target)
        
        # Move disk from source peg to auxillary peg
        if source:
            auxillary.append(source.pop())
        
        # Move tower of size n-1 from target to source
        hanoi(n - 1, target, auxillary, source)

        # Move disk from auxillary to target peg
        if auxillary:
            target.append(auxillary.pop())

        # Move tower of size n-1 from source to target
        hanoi(n - 1, source, auxillary, target)



invokes = 0
        
source = [3, 2, 1]
target = []
auxillary = []

# print source, auxillary, target

hanoi(len(source),source,auxillary,target)

print source, auxillary, target
print 'Invokes : ' + str(invokes)
