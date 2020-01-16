import numpy as np


a1 = np.array([313, 1187, 4356, 15542])
b1 = np.array([208, 767, 2796, 9981])

a2 = np.array([0.016, 0.359, 10.723, 368.332])
b2 = np.array([0.021, 0.487, 15.352, 459.978])

x = np.array([25, 50, 100, 200])

# Mflop/s
# for i in range(4):
#     print("(%d,%f)" % (x[i], (x[i] ** 3) * a1[i] * 7 / (a2[i] * 1000000)))

# print("\n")

# for i in range(4):
#     print("(%d,%f)" % (x[i], (x[i] ** 3) * b1[i] * 7 / (b2[i] * 1000000)))


# iterations/s
for i in range(4):
    print("(%d,%f)" % (x[i], a1[i] / (a2[i])))

print("\n")

for i in range(4):
    print("(%d,%f)" % (x[i], b1[i] / (b2[i])))
