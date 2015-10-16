# Basic tower of Hanoi

def hanoi(n, source, helper, target):
    if n > 0:
        global invokes
        invokes = invokes + 1

        # move tower of size n - 1 to helper:
        hanoi(n - 1, source, target, helper)
        # move disk from source peg to target peg
        if source:
            target.append(source.pop())
        # move tower of size n-1 from helper to target
        hanoi(n - 1, helper, source, target)
        
invokes = 0

source = [3,2,1]
target = []
helper = []
hanoi(len(source),source,helper,target)

print source, helper, target
print 'Invokes : ' + str(invokes)
