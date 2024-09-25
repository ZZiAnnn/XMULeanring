import Decorator.*;

public class Main {
    public static void main(String[] args) {
        Shape circle = new Circle();
        Decorator decoratedCircle = new DashedBorder(circle);
        decoratedCircle.draw();
        decoratedCircle.setBorderColor("red");
    }
}