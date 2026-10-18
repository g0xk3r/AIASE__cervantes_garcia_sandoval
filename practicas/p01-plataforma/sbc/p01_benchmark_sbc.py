#Práctica 1 · El mismo cálculo en la SBC: Python puro vs NumPy
import random
import time
import numpy as np
N, REPS = 1024, 1000
w = [random.uniform(-1, 1) for _ in range(N)]
x = [random.uniform(-1, 1) for _ in range(N)]
def ns_por_mac(segundos):
    return 1e9 * segundos / (N * REPS)
t0 = time.perf_counter()
for _ in range(REPS):
    acc = 0.0
    for i in range(N):
        acc += w[i] * x[i]
t_py = time.perf_counter() - t0

wn, xn = np.array(w, dtype=np.float32), np.array(x, dtype=np.float32)
t0 = time.perf_counter()
for _ in range(REPS):
    acc = float(np.dot(wn, xn))
t_np = time.perf_counter() - t0

wq = np.random.randint(-128, 128, N).astype(np.int32) # valores int8, acumulador int32
xq = np.random.randint(-128, 128, N).astype(np.int32)
t0 = time.perf_counter()
for _ in range(REPS):
    acc = int(np.dot(wq, xq))
t_nq = time.perf_counter() - t0

print(f"Python puro (float) : {ns_por_mac(t_py):8.2f} ns/MAC")
print(f"NumPy float32 : {ns_por_mac(t_np):8.2f} ns/MAC")
print(f"NumPy int8 -> int32 : {ns_por_mac(t_nq):8.2f} ns/MAC")