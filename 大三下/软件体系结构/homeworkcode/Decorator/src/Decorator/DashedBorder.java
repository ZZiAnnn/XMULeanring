package Decorator;

public class DashedBorder extends Decorator{
    private Shape shape;

    public DashedBorder(Shape shape) {
        this.shape = shape;
    }

    @Override
    public void draw() {
        System.out.println("Drawing Dashed Border");
        shape.draw();
    }
    @Override
    public void setBorderColor(String color) {
        System.out.println("Setting border color to " + color);
    }
}
