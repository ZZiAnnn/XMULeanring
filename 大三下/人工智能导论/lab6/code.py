import numpy as np
from matplotlib import pyplot as plt
from sklearn.model_selection import train_test_split


def sigmoid(x):
    return 1 / (1 + np.exp(-x))


def sigmoid_derivative(x):
    return sigmoid(x) * (1 - sigmoid(x))


def cross_entropy_loss(y_true, y_pred):
    epsilon = 1e-12
    n = len(y_true)
    loss = - np.sum(y_true * np.log(y_pred) + epsilon)
    return loss / n


def softmax(x):
    exp_x = np.exp(x - np.max(x, axis=-1, keepdims=True))
    return exp_x / np.sum(exp_x, axis=-1, keepdims=True)


class NeuralNetwork:
    def __init__(self, input_size, hidden_size, output_size):
        self.input_size = input_size
        self.hidden_size = hidden_size
        self.output_size = output_size

        self.weights_input_hidden = np.random.randn(input_size, hidden_size)
        self.weights_hidden_output = np.random.randn(hidden_size, output_size)

        self.bias_hidden = np.zeros(hidden_size)
        self.bias_output = np.zeros(output_size)

    def forward(self, X):
        self.hidden_input = np.dot(X, self.weights_input_hidden) + self.bias_hidden
        self.hidden_output = sigmoid(self.hidden_input)
        self.output = np.dot(self.hidden_output, self.weights_hidden_output) + self.bias_output
        self.output = softmax(self.output)
        return self.output

    def backward(self, X, y, learning_rate):
        error = self.output - y
        n = X.shape[0]
        # 更新输出层的权重和偏置
        self.weights_hidden_output -= learning_rate * np.dot(self.hidden_output.T, error) / n
        self.bias_output -= learning_rate * np.sum(error, axis=0) / n

        # 计算隐藏层的误差
        error_hidden = np.dot(error, self.weights_hidden_output.T)
        delta_hidden = error_hidden * sigmoid_derivative(self.hidden_input)

        # 更新隐藏层的权重和偏置
        self.weights_input_hidden -= learning_rate * np.dot(X.T, delta_hidden) / n
        self.bias_hidden -= learning_rate * np.sum(delta_hidden, axis=0) / n

    def train(self, X, y, epochs, learning_rate):
        y_one_hot = np.eye(self.output_size)[y.astype(int) - 1]
        losses = []
        for epoch in range(epochs):
            output = self.forward(X)
            self.backward(X, y_one_hot, learning_rate)
            loss = cross_entropy_loss(y_one_hot, output)
            losses.append(loss)
            if epoch % 100 == 0:
                print(f'Epoch {epoch:4}, Loss: {loss}')

        plt.plot(losses)
        plt.xlabel('Epoch')
        plt.ylabel('Loss')
        plt.title('Loss over epochs')
        plt.show()

    def predict(self, X):
        output = self.forward(X)
        return np.argmax(output, axis=1) + 1


def read_data(file_name):
    with open(file_name, 'r') as file:
        data = []
        label = {'Iris-setosa': 1, 'Iris-versicolor': 2, 'Iris-virginica': 3}
        for line in file:
            line = line.strip()
            if line:
                features = line.split(',')
                features[:-1] = [float(feature) for feature in features[:-1]]
                features[-1] = label.get(features[-1], features[-1])
                data.append(features)
        return np.array(data)


if __name__ == '__main__':
    iris = read_data('Iris.txt')

    X = iris[:, :-1]
    y = iris[:, -1]

    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=75, stratify=y, random_state=42)

    np.savetxt('Iris-train.txt', np.column_stack((X_train, y_train)), delimiter=',')
    np.savetxt('Iris-test.txt', np.column_stack((X_test, y_test)), delimiter=',')

    train_data = np.loadtxt('Iris-train.txt', delimiter=',')
    X_train = train_data[:, :-1]
    y_train = train_data[:, -1]

    input_size = 4
    hidden_size = 10
    output_size = 3
    learning_rate = 0.2
    epochs = 1500

    nn = NeuralNetwork(input_size, hidden_size, output_size)

    nn.train(X_train, y_train, epochs, learning_rate)

    test_data = np.loadtxt('Iris-test.txt', delimiter=',')
    X_test = test_data[:, :-1]
    y_test = test_data[:, -1]

    predictions = nn.predict(X_test)

    accuracy = np.mean(predictions == y_test.flatten())
    print("准确率:", accuracy)

    accuracies = []
    for _ in range(10):
        model = NeuralNetwork(input_size, hidden_size, output_size)
        model.train(X_train, y_train, epochs, learning_rate)
        predictions = nn.predict(X_test)
        accuracy = np.mean(predictions == y_test.flatten())
        accuracies.append(accuracy)

    print("独立运行10次的准确率:", np.round(accuracies, 4))
    print("平均准确率:", np.mean(accuracies))
    print("准确率标准差:", np.std(accuracies))
