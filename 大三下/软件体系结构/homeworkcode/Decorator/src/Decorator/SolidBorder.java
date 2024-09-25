package Decorator;

public class SolidBorder extends Decorator {
    private Shape shape;

    public SolidBorder(Shape shape) {
        this.shape = shape;
    }

    @Override
    public void draw() {
        System.out.println("Drawing Solid Border");
        shape.draw();
    }
    @Override
    public void setBorderColor(String color) {
        System.out.println("Setting border color to " + color);
    }
}
