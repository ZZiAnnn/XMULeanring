import numpy as np
import matplotlib.pyplot as plt


# 定义函数 f(x)
def f(x):
    return 11 * np.sin(6 * x) + 7 * np.cos(5 * x)


# 模拟退火算法
def simulated_annealing(f, x_min, x_max, T_max, T_min, cooling_rate, max_iter, epsilon):
    x_best = 3.5
    f_best = f(x_best)

    x_current = x_best
    f_current = f_best

    x_hist = [x_best]
    f_hist = [f_best]

    T = T_max
    while T > T_min:
        for _ in range(max_iter):
            x_new = x_current + np.random.uniform(-epsilon, epsilon)
            x_new = max(min(x_new, x_max), x_min)  # 确保 x_new 在 [x_min, x_max] 范围内
            f_new = f(x_new)
            delta_f = f_new - f_current
            if delta_f < 0 or np.random.rand() < np.exp(-delta_f / T):
                x_current = x_new
                f_current = f_new
                if f_current < f_best:
                    x_best = x_current
                    f_best = f_current
            x_hist.append(x_best)
            f_hist.append(f_best)
        T *= cooling_rate
    return x_best, f_best, x_hist, f_hist

if __name__ == '__main__':

    # 冷却参数表
    x_min = 0
    x_max = 2 * np.pi
    T_max = 100
    T_min = 0.1
    cooling_rate = 0.95
    max_iter = 100
    epsilon = 0.1  # 马尔科夫迭代步长

    x_best, f_best, x_hist, f_hist = simulated_annealing(f, x_min, x_max, T_max, T_min, cooling_rate, max_iter, epsilon)

    print("最优解 x:", x_best)
    print("最小值 f(x):", f_best)

    # 可视化搜索过程
    plt.figure(figsize=(10, 6))
    plt.plot(np.linspace(x_min, x_max, 1000), f(np.linspace(x_min, x_max, 1000)), 'r-', label='f(x)')
    plt.plot(x_hist, f_hist, 'bo-', markersize=2, label='Search Path')
    plt.scatter(x_hist[0], f_hist[0], color='green', label='Start Point')
    plt.scatter(x_best, f_best, color='red', label='End Point')

    plt.xlabel('x')
    plt.ylabel('f(x)')
    plt.title('Simulated Annealing Search for Minimum of f(x)')
    plt.legend()
    plt.grid(True)
    plt.show()