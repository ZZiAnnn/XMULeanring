package Decorator;

import Decorator.Shape;

public class Circle extends Shape {
    @Override
    public void draw() {
        System.out.println("Drawing Circle");
    }
}
