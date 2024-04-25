import random
import numpy as np

# 旅行商问题的目标函数：总路径长度
def total_distance(path, distances):
    total = 0
    for i in range(len(path) - 1):
        total += distances[path[i]][path[i + 1]]
    total += distances[path[-1]][path[0]]  # 回到起点
    return total


# 初始化种群
def initialize_population(num_cities, population_size):
    population = []
    for _ in range(population_size):
        individual = list(range(num_cities))
        random.shuffle(individual)
        population.append(individual)
    return population


# 适应度函数
def fitness(individual, distances):
    return 1 / total_distance(individual, distances)


# 选择函数：轮盘赌法
def selection(population, distances):
    fitness_values = [fitness(individual, distances) for individual in population]
    total_fitness = sum(fitness_values)
    probabilities = [f / total_fitness for f in fitness_values]
    selected = random.choices(population, probabilities, k=len(population))
    return selected


# 交叉函数：部分映射交叉
def crossover(parent1, parent2):
    size = min(len(parent1), len(parent2))
    start = random.randint(0, size - 1)
    end = random.randint(start + 1, size)
    child1 = [None] * size
    child2 = [None] * size
    for i in range(start, end):
        child1[i] = parent2[i]
        child2[i] = parent1[i]
    for i in range(size):
        if parent1[i] not in child1:
            for j in range(size):
                if child1[j] is None:
                    child1[j] = parent1[i]
                    break
        if parent2[i] not in child2:
            for j in range(size):
                if child2[j] is None:
                    child2[j] = parent2[i]
                    break
    return child1, child2


# 变异函数：随机交换
def mutate(individual):
    index1, index2 = random.sample(range(len(individual)), 2)
    individual[index1], individual[index2] = individual[index2], individual[index1]
    return individual


# 主函数
def genetic_algorithm(num_cities, distances, population_size=500, generations=1000):
    population = initialize_population(num_cities, population_size)
    for _ in range(generations):
        population = selection(population, distances)
        next_population = []
        for i in range(0, len(population), 2):
            parent1, parent2 = population[i], population[i + 1]
            child1, child2 = crossover(parent1, parent2)
            child1 = mutate(child1)
            child2 = mutate(child2)
            next_population.extend([child1, child2])
        population = next_population
    best_individual = max(population, key=lambda x: fitness(x, distances))
    return best_individual, total_distance(best_individual, distances)


# if __name__ == "__main__":
#     # INF = 1e7
#     # num_cities = 5
#     # distances = [[0, 3, INF, 8, 9],
#     #              [3, 0, 3, 10, 5],
#     #              [INF, 3, 0, 4, 3],
#     #              [8, 10, 4, 0, 20],
#     #              [9, 5, 3, 20, 0]]
#
#     best_path, shortest_distance = genetic_algorithm(num_cities, distances)
#     print("最佳路径:", best_path)
#     print("最短距离:", shortest_distance)


# 读取数据集
def read_tsp(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()
        node_coord_start = None
        dimension = None
        node_coords = []

        for i, line in enumerate(lines):
            if line.startswith("DIMENSION"):
                dimension = int(line.split(":")[1])
            elif line.startswith("NODE_COORD_SECTION"):
                node_coord_start = i + 1
            elif node_coord_start and i >= node_coord_start:
                if line.strip() == "EOF":
                    break
                parts = line.strip().split()
                node_coords.append((float(parts[1]), float(parts[2])))

        return dimension, node_coords


def calculate_distance(coord1, coord2):
    x1, y1 = coord1
    x2, y2 = coord2
    return ((x1 - x2) ** 2 + (y1 - y2) ** 2) ** 0.5


def create_adjacency_matrix(node_coords):
    dimension = len(node_coords)
    adjacency_matrix = [[0] * dimension for _ in range(dimension)]

    for i in range(dimension):
        for j in range(i + 1, dimension):
            distance = calculate_distance(node_coords[i], node_coords[j])
            adjacency_matrix[i][j] = distance
            adjacency_matrix[j][i] = distance

    return adjacency_matrix


if __name__ == "__main__":

    tsp_file = "st70.tsp"
    # 读取数据集
    dimension, node_coords = read_tsp(tsp_file)
    distances = create_adjacency_matrix(node_coords)
    print(dimension)
    best_path, shortest_distance = genetic_algorithm(dimension, distances)
    print("最佳路径:", best_path)
    print("最短距离:", shortest_distance)