#!python2.5
# fixed 2013-02-27.
import numpy as np;
import pdb;
 
def mcm_dynamic(seq):
    (mc, r, s, print_opt) = MatrixChain(seq);
    mc(0,len(seq)-1)
    cost = r();
    print cost;
    opt = s()
    print opt;
    #pdb.set_trace();
    print print_opt(0,len(seq)-1);
 
# closures
def MatrixChain(seq):
    m = np.zeros((len(seq),len(seq)));
    seq = seq;
    s = np.zeros((len(seq),len(seq)));
    opt ='';

    def recursive(i,j):
        # print i,j;
        if i==j:
            return 0;
        m[i,j] = np.Inf;
        for k in range(i,j):
            # print i,j,k;
            cost = recursive(i,k)+recursive(k+1,j);
            cost = cost+seq[i][0]*seq[k][1]*seq[j][1];
            if cost < m[i,j]:
                m[i,j] = cost;
                s[i,j] = k;
        return m[i,j] # memoize this?

    recursive = Memoize(recursive);

    def getm():
        return m;
    def gets():
        return s;
    def print_opt(i,j):
        if i==j:
            return  'A%s'%(int(i+1));
        if (j-i)<=1:
            return '(A%s,A%s)'%(int(i+1),int(j+1)) ;
        return '('+print_opt(i,s[i,j]) + print_opt(s[i,j]+1, j)+')';

    return (recursive, getm, gets, print_opt);
 
class Memoize:
    def __init__(self,fn):
        self.mem = {}
        self.fn = fn;
    def __call__(self, *args):
        #pdb.set_trace();
        if self.mem.has_key((args[0], args[1])):
            #print('Fetching: ', args)
            return self.mem[(args[0], args[1])];
        else:
            #print ('putting', args);
            self.mem[args] = self.fn(args[0], args[1]);
            return self.mem[args];
 
if '__main__' == __name__:
    seq = [[30,35],[35,15],[15,5],[5,10],[10,20],[20,25]];
    mcm_dynamic(seq);
