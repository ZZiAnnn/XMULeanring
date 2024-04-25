import numpy as np


class Particle:
    def __init__(self, num_cities):
        self.num_cities = num_cities
        self.position = np.random.permutation(num_cities)
        self.velocity = np.random.permutation(num_cities)
        self.best_position = self.position.copy()
        self.best_fitness = float('inf')


class PSO_TSP:
    def __init__(self, num_cities,  distance_matrix, num_particles = 50, max_iter = 40, c1 = 2, c2 = 2, vmax = 5):
        self.num_cities = num_cities
        self.num_particles = num_particles
        self.max_iter = max_iter
        self.c1 = c1
        self.c2 = c2
        self.vmax = vmax
        self.particles = [Particle(num_cities) for _ in range(num_particles)]
        self.global_best_position = np.zeros(num_cities)
        self.global_best_fitness = float('inf')
        self.distance_matrix = distance_matrix

    def evaluate_fitness(self, particle):
        fitness = 0
        for i in range(self.num_cities - 1):
            fitness += self.distance_matrix[particle.position[i]][particle.position[i + 1]]
        fitness += self.distance_matrix[particle.position[-1]][particle.position[0]]  # 回到起点
        return fitness

    # 定义速度更新函数
    def update_velocity(self, x_best, position, c):
        velocity = []
        for i in range(len(position)):
            if position[i] != x_best[i]:
                j = np.where(position == x_best[i])[0][0]
                so = (i, j, c)  # 得到交换子
                velocity.append(so)
                position[i], position[j] = position[j], position[i]  # 执行交换操作
        return velocity

    # 定义位置更新函数
    def update_position(self, position, ss):
        for i, j, r in ss:
            rand = np.random.random()
            if rand <= r:
                position[i], position[j] = position[j], position[i]
        return position

    def update_particle(self, particle):

        # 计算交换序列，即 v = r1(pbest-xi) + r2(gbest-xi)
        ss1 = self.update_velocity(particle.best_position, particle.position, self.c1)
        ss2 = self.update_velocity(self.global_best_position, particle.position, self.c2)
        new_velocity = ss1 + ss2
        new_position = self.update_position(particle.position, new_velocity)

        particle.position = new_position
        particle.velocity = new_velocity


    def optimize(self):
        for iter in range(self.max_iter):
            for particle in self.particles:
                self.update_particle(particle)

            for particle in self.particles:
                fitness = self.evaluate_fitness(particle)
                if fitness < particle.best_fitness:
                    particle.best_fitness = fitness
                    particle.best_position = particle.position.copy()
                if fitness < self.global_best_fitness:
                    self.global_best_fitness = fitness
                    self.global_best_position = particle.position.copy()

# if __name__ == '__main__':
#     num_cities = 5
#     INF = 1000
#     distance_matrix = [[0, 3, INF, 8, 9],
#                        [3, 0, 3, 10, 5],
#                        [INF, 3, 0, 4, 3],
#                        [8, 10, 4, 0, 20],
#                        [9, 5, 3, 20, 0]]
#
#     pso_tsp = PSO_TSP(num_cities, distance_matrix)
#     pso_tsp.optimize()
#
#     print("最优路径：", pso_tsp.global_best_position)
#     print("最短路径长度：", pso_tsp.global_best_fitness)

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

    pso_tsp = PSO_TSP(dimension, distances, 100, 1000, 2, 2)
    pso_tsp.optimize()

    print("最优路径：", pso_tsp.global_best_position)
    print("最短路径长度：", pso_tsp.global_best_fitness)