import os
pid = os.fork()
if pid == 0:
    print( 'Parent says, "HELLO!"')
else:
    print( 'Child says, "hello!"')
