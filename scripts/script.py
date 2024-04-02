import argparse
from scipy.interpolate import LinearNDInterpolator
import numpy as np
import matplotlib.pyplot as plt

def read_csv_file(file_name):
    temp = []
    x = []
    y = []
    
    with open(file_name) as file:
        for line in file:
            splt = line.split(",")
            temp.append(float(splt[0]))
            x.append(float(splt[1]))
            y.append(float(splt[2]))
    
    return temp, x, y

def cal_ref(k0, k1, q):
    x0 = np.linspace(0, 0.5)
    x1 = np.linspace(0.5, 1)
    
    A = 0.5*q/k0
    c0 = q/k1
    c1 = 0.25*q*(1/k0 - (3.0/2.0)/k1)
    
    y0 = [A*x for x in x0]
    y1 = [-0.5*(q/k0)*x**2 + c0*x + c1 for x in x1]
    
    return (x0, y0, x1, y1)

if __name__ == '__main__':
    parser = argparse.ArgumentParser(prog='HAMT Processing Script')
    parser.add_argument('file_name')  
    
    args = parser.parse_args()
    temp, x, y = read_csv_file(args.file_name)
    
    # interpolation
    X, Y = np.meshgrid(np.zeros(100), np.linspace(min(y), max(y), 100))
    interp = LinearNDInterpolator(list(zip(x, y)), temp)
    Z = interp(X, Y)
    
    y0 = [val[0] for val in Y]
    z0 = [val[0] for val in Z]
    
    # ref value
    k0 = 1.0
    k1 = 1.0
    q = 1.0
    ref = cal_ref(k0, k1, q)
    
    plt.plot(y0, z0)
    plt.plot(ref[0], ref[1])
    plt.plot(ref[2], ref[3])
    plt.show()
    
    print(ref[3][-1], z0[-1])
    
    print("done")