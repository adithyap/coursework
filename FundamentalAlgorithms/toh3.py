#
# Constraint: Cyclic, only moves legal are 1->2, 2->3, 3->1
#

# Moves N disks from source to target
def Hanoi(n, source, auxiliary, target):
    if n > 0:
        global invokes
        invokes = invokes + 1

        # Move N disks from source to auxiliary
        SingleMove(n, source, auxiliary, target)

        # Move N disks from auxiliary to target
        SingleMove(n, auxiliary, target, source)

# Moves N disks by one peg
def SingleMove(n, source, target, auxiliary):

    if n > 0:
        global invokes
        invokes = invokes + 1

        # Move n-1 disks from source to auxiliary
        DoubleMove(n-1, source, auxiliary, target)

        # Move disk from source to target (which is shifted in perspective in this call)
        if source:
            target.append(source.pop())

        # Move n-1 disks from auxiliary to target
        DoubleMove(n-1, auxiliary, target, source)

# Moves N disks by two pegs
def DoubleMove(n, source, target, auxiliary):

    if n > 0:
        global invokes
        invokes = invokes + 1

        # Move n-1 disks from source to target
        DoubleMove(n-1, source, target, auxiliary)

        # Move disk from source to auxiliary
        if source:
            auxiliary.append(source.pop())

        # Move n-1 disks from target to source
        SingleMove(n-1, target, source, auxiliary)

        # Move disk from auxiliary to target
        if auxiliary:
            target.append(auxiliary.pop())

        # Move n-1 disks from source to target
        DoubleMove(n-1, source, target, auxiliary)

invokes = 0
        
source = [6,5,4,3,2,1]
target = []
auxiliary = []

# print source, auxiliary, target

Hanoi(len(source),source,auxiliary,target)

# hanoi(len(source),source,auxiliary,target)

print source, auxiliary, target
print 'Invokes : ' + str(invokes) + ', complexity estimate = ' + str((1+3**0.5)**(len(target)))
