
"""
Question 1
"""
print("QUESTION 1")

import numpy as np
from sympy import *
from sympy.polys.domains import *
from sympy.polys.galoistools import *


"""
Part 1
"""

print("PART 1")

degree = []
others = []

# checking irreducibility using inbuilt library function
def check(i):
    if gf_irreducible_p(ZZ.map(i), 2, ZZ):
        return 1
    return 0

# generating vectors for all polynomials with degree <= deg
def generate(deg,p):    
    for i in range(0,2**(deg+1)):
        temp = [int(x) for x in list('{0:0b}'.format(i))]
        if i < 2**deg:
            others.append(temp)
        else:
            degree.append(temp)


# generating all irreducible polynomials
# brute force method - checking divisibility with all polynomials
irreducibles = []
def get_irreducible(deg,p):
    for i in degree:
        cnt = 0
        for j in others[2:]:
            if gf_rem(ZZ.map(i), ZZ.map(j), 2, ZZ) != []:
                cnt += 1
        if cnt == 2**deg-2:
            irreducibles.append(i)
                
                


generate(8,2)
print("Generating all irreducible polynomials...")
get_irreducible(8,2)
print("Generated all irreducible polynomials!")

irr = irreducibles[np.random.randint(len(irreducibles))]

print("Randomly choosing one irreducible polynomial from the generated list of irreducible polynomials.")


print()
print("The vector form of the randomly chosen irreducible polynomial is: ")
print(ZZ.map(irr))
print()

print("Checking using inbuilt library function...")
print()

if check(irr) == 1:
    print("The above given polynomial is an irreducible polynomial.")
else:
    print("The above given polynomial is not an irreducible polynomial.")

print()


"""
Part 2
"""
"""
The finite field (F_{2^8}, p = 2, m = 8) defined 
using the above irreducuble polynomial will be a
set of all polynomials with  degree less than or
equal to 7.
"""

print("PART 2")

# generating all primitive elements
# brute force method - checking if powers of any polynomial result in the entire field
primitives = []
def get_primitive(p,irr,deg):
    for i in others[2:]:
        mp = {}
        ok = True
        cnt = 0
        for j in range(1,2**deg-1):
            power = gf_pow_mod(ZZ.map(i),j,ZZ.map(irr),2,ZZ)
            if power == []:
                power = '0'
            else:
                power = ''.join([str(elem) for elem in power])
            power = int(power,2) 
            if mp.get(power) == None:
                mp[power] = 1
                cnt += 1
            else:
                ok = False
                break
        if ok == True:
            primitives.append(i)

print("Generating all primitive elements...")
print()
get_primitive(2,irr,8)
print("Generated all primitive elements!")


print("Randomly choosing one primitive element from the generated list of primitive elements.")


print()



primitive = primitives[np.random.randint(len(primitives))]
print("The vector form of the randomly chosen primitive element (B) is: ")
print(primitive)
print()

f = gf_pow_mod(ZZ.map(primitive),34,ZZ.map(irr),2,ZZ)
g = gf_pow_mod(ZZ.map(primitive),20,ZZ.map(irr),2,ZZ)
fg = gf_mul(f,g,2,ZZ)
fg = gf_rem(fg,irr,2,ZZ)
h = gf_pow_mod(ZZ.map(primitive),54,ZZ.map(irr),2,ZZ)

print("B^34 is:")
print(f)
print()

print("B^20 is:")
print(g)
print()

print("The product of the above two polynomials is:")
print(fg)
print()

print("B^54 is:")
print(h)
print()
"""
Question 2
"""
print("QUESTION 2")
print()

"""
Part a
[n = 10, k = 4] code, message polynomial M(X) = 1 + B**5X
"""
print("Part A")
print()
print("Given [n = 10, k = 4] code, message polynomial M(X) = 1 + B**5X")
print("Taking field size to be 16 (m = 4)")
print("Taking the degree of irreducible polynomial to be 4")
n = 10
k = 4
degree = []
others = []
irreducibles = []
generate(4,2)
print("Generating all irreducible polynomials...")
get_irreducible(4,2)
print("Generated all irreducible polynomials!")
irr1 = irreducibles[np.random.randint(len(irreducibles))]
print("Randomly choosing one irreducible polynomial from the generated list of irreducible polynomials.")
print()
print("The vector form of the randomly chosen irreducible polynomial is: ")
print(ZZ.map(irr1))
print()

primitives = []
print("Generating all primitive elements using the above given irreducible polynomial...")
print()
get_primitive(2,irr1,4)
print("Generated all primitive elements!")
print("Randomly choosing one primitive element from the generated list of primitive elements.")
print()
primitive1 = primitives[np.random.randint(len(primitives))]
print("The vector form of the randomly chosen primitive element (B) is: ")
print(primitive1)
print()

# M(X) = 1 + B**5X
# storing powers of primitive element at the non-zero monomial indices
msg = [np.array([0],dtype=int) for i in range(k)]
msg[0] = gf_pow_mod(ZZ.map(primitive1),0,ZZ.map(irr1),2,ZZ)
msg[1] = gf_pow_mod(ZZ.map(primitive1),2,ZZ.map(irr1),2,ZZ)

def print_codeword(msg):
    ret = []
    for i in msg:
        if np.sum(i) == 0:
            ret.append([0])
        else:
            ret.append(i)
    return ret

print("The message polynomial M(X) = 1 + B**5X will be: ")
print(print_codeword(msg))
print()
print("The evalauation points are:")
# evaluation points will be just powers of the primitive element
eval_pts1 = []
for i in range(0,n):
    eval_pts1.append(gf_pow_mod(ZZ.map(primitive1),i+1,ZZ.map(irr1),2,ZZ))
    print(eval_pts1[i])

codeword1 = [np.array([0],dtype=int) for i in range(n)]

# vector matrix multiplication
# multiplication of m[x] with the generator matrix that contains powers of n evaluation points
for i in range(0,n):
    for j in range(0,k):
        eval_ij = gf_pow_mod(ZZ.map(eval_pts1[i]),j+1,ZZ.map(irr1),2,ZZ)
        mul = gf_mul(ZZ.map(msg[j]),ZZ.map(eval_ij),2,ZZ)
        rem = gf_rem(ZZ.map(mul),ZZ.map(irr1),2,ZZ)
        codeword1[i] = gf_add(codeword1[i],rem,2,ZZ)
        codeword1[i] = gf_rem(ZZ.map(codeword1[i]),ZZ.map(irr1),2,ZZ)

print("The encoded vectors corresponding to the given RS code are:")
print(print_codeword(codeword1))
print()





"""
Part b
[n = 20, k = 10] code, message polynomial M(X) = B**4 + B**5X**3 + B**10X**9
"""

print("Part B")
print()
print("Given [n = 20, k = 10] code, message polynomial M(X) = B**4 + B**5X**3 + B**10X**9")
print("Taking field size to be 32 (m = 5)")
print("Taking the degree of irreducible polynomial to be 5")
n = 20
k = 10
degree = []
others = []
irreducibles = []
generate(5,2)
print("Generating all irreducible polynomials...")
get_irreducible(5,2)
print("Generated all irreducible polynomials!")
irr = irreducibles[np.random.randint(len(irreducibles))]
print("Randomly choosing one irreducible polynomial from the generated list of irreducible polynomials.")
print()
print("The vector form of the randomly chosen irreducible polynomial is: ")
print(ZZ.map(irr))
print()

primitives = []
print("Generating all primitive elements using the above given irreducible polynomial...")
print()
get_primitive(2,irr,5)
print("Generated all primitive elements!")
print("Randomly choosing one primitive element from the generated list of primitive elements.")
print()
primitive = primitives[np.random.randint(len(primitives))]
print("The vector form of the randomly chosen primitive element (B) is: ")
print(primitive)
print()


# M(X) = B**4 + B**5X**3 + B**10X**9
# storing powers of primitive element at the non-zero monomial indices
msg = [np.array([0],dtype=int) for i in range(k)]
msg[0] = gf_pow_mod(ZZ.map(primitive),4,ZZ.map(irr),2,ZZ)
msg[3] = gf_pow_mod(ZZ.map(primitive),5,ZZ.map(irr),2,ZZ)
msg[9] = gf_pow_mod(ZZ.map(primitive),10,ZZ.map(irr),2,ZZ)

def print_codeword(msg):
    ret = []
    for i in msg:
        if np.sum(i) == 0:
            ret.append([0])
        else:
            ret.append(i)
    return ret

print("The message polynomial M(X) = B**4 + B**5X**3 + B**10X**9 will be: ")
print(print_codeword(msg))
print()
print("The evalauation points are:")
eval_pts = []
# evaluation points will be just powers of the primitive element
for i in range(0,n):
    eval_pts.append(gf_pow_mod(ZZ.map(primitive),i+1,ZZ.map(irr),2,ZZ))
    print(eval_pts[i])

codeword2 = [np.array([0],dtype=int) for i in range(n)]

# vector matrix multiplication
# multiplication of m[x] with the generator matrix that contains powers of n evaluation points
for i in range(0,n):
    for j in range(0,k):
        eval_ij = gf_pow_mod(ZZ.map(eval_pts[i]),j+1,ZZ.map(irr),2,ZZ)
        mul = gf_mul(ZZ.map(msg[j]),ZZ.map(eval_ij),2,ZZ)
        rem = gf_rem(ZZ.map(mul),ZZ.map(irr),2,ZZ)
        codeword2[i] = gf_add(codeword2[i],rem,2,ZZ)
        codeword2[i] = gf_rem(ZZ.map(codeword2[i]),ZZ.map(irr),2,ZZ)

print("The encoded vectors corresponding to the given RS code are:")
print(print_codeword(codeword2))
print()



"""
Part c
[n = 50, k = 25] code, message polynomial 
M(X) = B**20 + B**4X**8 + B**44X**12 + B**30X**14 + B**15X**18 + B**3X**23

"""
print("Part C")
print()
# Let m = 4, so the field size is 16
print("Given [n = 50, k = 25] code, message polynomial M(X) = B**20 + B**4X**8 + B**44X**12 + B**30X**14 + B**15X**18 + B**3X**23")
print("Taking field size to be 64 (m = 6)")
print("Taking the degree of irreducible polynomial to be 6")
n = 50
k = 25
degree = []
others = []
irreducibles = []
generate(6,2)
print("Generating all irreducible polynomials...")
get_irreducible(6,2)
print("Generated all irreducible polynomials!")
irr = irreducibles[np.random.randint(len(irreducibles))]
print("Randomly choosing one irreducible polynomial from the generated list of irreducible polynomials.")
print()
print("The vector form of the randomly chosen irreducible polynomial is: ")
print(ZZ.map(irr))
print()

primitives = []
print("Generating all primitive elements using the above given irreducible polynomial...")
print()
get_primitive(2,irr,6)
print("Generated all primitive elements!")
print("Randomly choosing one primitive element from the generated list of primitive elements.")
print()
primitive = primitives[np.random.randint(len(primitives))]
print("The vector form of the randomly chosen primitive element (B) is: ")
print(primitive)
print()

# M(X) = B**20 + B**4X**8 + B**44X**12 + B**30X**14 + B**15X**18 + B**3X**23
# storing powers of primitive element at the non-zero monomial indices
msg = [np.array([0],dtype=int) for i in range(k)]
msg[0] = gf_pow_mod(ZZ.map(primitive),20,ZZ.map(irr),2,ZZ)
msg[8] = gf_pow_mod(ZZ.map(primitive),4,ZZ.map(irr),2,ZZ)
msg[12] = gf_pow_mod(ZZ.map(primitive),44,ZZ.map(irr),2,ZZ)
msg[14] = gf_pow_mod(ZZ.map(primitive),30,ZZ.map(irr),2,ZZ)
msg[18] = gf_pow_mod(ZZ.map(primitive),15,ZZ.map(irr),2,ZZ)
msg[23] = gf_pow_mod(ZZ.map(primitive),3,ZZ.map(irr),2,ZZ)

def print_codeword(msg):
    ret = []
    for i in msg:
        if np.sum(i) == 0:
            ret.append([0])
        else:
            ret.append(i)
    return ret

print("The message polynomial M(X) = B**20 + B**4X**8 + B**44X**12 + B**30X**14 + B**15X**18 + B**3X**23 will be: ")
print(print_codeword(msg))
print()
print("The evalauation points are:")
eval_pts = []
# evaluation points will be just powers of the primitive element
for i in range(0,n):
    eval_pts.append(gf_pow_mod(ZZ.map(primitive),i+1,ZZ.map(irr),2,ZZ))
    print(eval_pts[i])

codeword3 = [np.array([0],dtype=int) for i in range(n)]

# vector matrix multiplication
# multiplication of m[x] with the generator matrix that contains powers of n evaluation points
for i in range(0,n):
    for j in range(0,k):
        eval_ij = gf_pow_mod(ZZ.map(eval_pts[i]),j+1,ZZ.map(irr),2,ZZ)
        mul = gf_mul(ZZ.map(msg[j]),ZZ.map(eval_ij),2,ZZ)
        rem = gf_rem(ZZ.map(mul),ZZ.map(irr),2,ZZ)
        codeword3[i] = gf_add(codeword3[i],rem,2,ZZ)
        codeword3[i] = gf_rem(ZZ.map(codeword3[i]),ZZ.map(irr),2,ZZ)

print("The encoded vectors corresponding to the given RS code are:")
print(print_codeword(codeword3))
print()

"""
Question 3
"""

print("QUESTION 3")
print()

print("Part A")
print()
print("Given [n = 10, k = 4] code")
print("Taking field size to be 16 (m = 4)")
n = 10
k = 4
deg = 4
sz = 16
msg = []

# for i in range(0,k):
#     row = []
#     for j in range(0,deg):
#         print("Enter the coefficient for X^%d at index %d: "%(j,i))
#         c = int(input())
#         row.append(c)
#     msg.append(row)

print("The transmitted vectors are:")
print(codeword1)


rec = [ [ 0 for i in range(deg) ] for j in range(n) ]

for i in range(0,len(codeword1)):
    for j in range(0,len(codeword1[i])):
        rec[i][j]=codeword1[i][j]

print("Enter the number of errors: ")
e = int(input())
alpha_idx = []
for i in range(0,e):
    print("Enter the index at which you want an error: ")
    idx = int(input())
    alpha_idx.append(idx)
    row = []
    for j in range(0,deg):
        print("Enter the coefficient for X^%d at index %d: "%(j,idx))
        c = int(input())
        rec[idx][j]=c

print()
print("The received vectors are:")
print(rec)
print()

# Mapping powers of the primitive element from 0 to size(field)-1
mp = {}
mp1 = {}
mp['0']=0
mp1['0']=[0]
for i in range(1,sz):
    power = gf_pow_mod(ZZ.map(primitive1),i,ZZ.map(irr1),2,ZZ)
    power_str = ''.join([str(elem) for elem in power])
    mp[power_str] = i
    mp1[power_str] = power


    

print("printing the mapping of powers of the primitive element from 0 to size(field)-1")

print(mp)
print()

print("Performing Gaussian Elimination...")
print()
print("Constructing the augmented matrix")
print()

# Constructing the augmented matrix
A = []
for i in range(n):
    eval_pt = eval_pts1[i]
    row = []
    for j in range(e):
        power = gf_pow_mod(ZZ.map(eval_pt),j,ZZ.map(irr1),2,ZZ)
        mul = gf_mul(ZZ.map(rec[i]),ZZ.map(power),2,ZZ)
        rem = gf_rem(ZZ.map(mul),ZZ.map(irr1),2,ZZ)
        row.append(rem)
    for j in range(n-e):
        power = gf_pow_mod(ZZ.map(eval_pt),j,ZZ.map(irr1),2,ZZ)
        row.append(power)
    A.append(row)

print("The augmented matrix is:")
print(A)
print()



A_mp = [ [ 0 for i in range(n) ] for j in range(n) ]
print("The augmented matrix containing the mapping of elements of A is:")
for i in range(n):
    for j in range(len(A[i])):
        vec = A[i][j]
        vec = ''.join([str(elem) for elem in vec])
        A_mp[i][j] = mp[vec]

print("The mapped augmented matrix is:")
print(A_mp)
print()

def divide(a,b,q):
    ret = a - b
    while ret > q - 1:
        ret -= (q-1)
    while ret <= 0:
        ret += (q-1)
    return ret

def multiply(a,b,q):
    ret = a + b
    while ret > q - 1:
        ret -= (q-1)
    while ret <= 0:
        ret += (q-1)
    return ret

# Gaussian elimination
for i in range(n):
    for j in range(n-1,i,-1):
        quo = divide(A_mp[j][i],A_mp[i][i],sz)
        for k in range(n+1):
            a = A_mp[j][k]
            b = multiply(quo,A_mp[i][k],sz)
            key_a =''
            for key,val in mp.items():
                if a == val:
                    key_a = key
                    break
            list_a = mp1[key_a]
            key_ab =''
            for key,val in mp.items():
                if b == val:
                    key_b = key
                    break
            list_b = mp1[key_b]
            l = max(len(list_a),len(list_b))
            coeff = np.zeros(l,dtype=int)
            for i in range(l):
                if i<len(list_a):
                    coeff[i] = (coeff[i] + list_a[i])%2            
                if i<len(list_b):
                    coeff[i] = (coeff[i] + list_b[i])%2
            coeff = ''.join([str(elem) for elem in coeff])
            idx = mp[coeff]

print("The mapped augmented matrix after Gaussian elimination is:")
print(A_mp)
print()


soln = [np.array([0],dtype=int) for i in range(n)]
soln[n-1] = divide(A_mp[n-1][n],A_mp[n-1][n-1],sz)

for i in range(n-2,-1,-1):
    soln[i] = A_mp[i][n]
    if A_mp[i][i] == 0:
        soln[i] = 1
        continue
    
    for j in range(i+1,n):
        a = soln[i]
        b = multiply(A_mp[i][j],soln[j],sz)
        key_a =''
        for key,val in mp.items():
            if a == val:
                key_a = key
                break
        list_a = mp1[key_a]
        key_ab =''
        for key,val in mp.items():
            if b == val:
                key_b = key
                break
        list_b = mp1[key_b]
        l = max(len(list_a),len(list_b))
        coeff = np.zeros(l,dtype=int)
        for i in range(l):
            if i<len(list_a):
                coeff[i] = (coeff[i] + list_a[i])%2            
            if i<len(list_b):
                coeff[i] = (coeff[i] + list_b[i])%2
        coeff = ''.join([str(elem) for elem in coeff])
        idx = mp[coeff]
        soln[i] = idx
    soln[i] = divide(soln[i],A_mp[i][j],sz)

    list_soln = []
    for i in soln:
        a = i
        key_a =''
        for key,val in mp.items():
            if a == val:
                key_a = key
                break
        list_a = mp1[key_a]
        list_soln.append(list_a)
    

E = []
N = []

for i in range(n):
    if i < e:
        E.append(list_soln[i])
    else:
        N.append(list_soln[i])

print("The error locator polynomial is:")
print(E)
print()

print("The polynomial N(x) is:")
print(N)
print()
