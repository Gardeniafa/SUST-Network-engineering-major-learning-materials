public abstract class Shape {
    public abstract double getArea();
    public abstract double getCircumference();
}
class Circle extends Shape{
    private double radius;
    public Circle(double radius){
        super();
        if(radius > 0){
            this.radius = radius;
        }else {
            System.out.println("radius should > 0");
        }
    }

    @Override
    public double getArea() {
        return Math.PI*radius*radius;
    }

    @Override
    public double getCircumference() {
        return 2*Math.PI*radius;
    }
}
class Rectangle extends Shape{
    private double width, height;
    public Rectangle(double width, double height){
        super();
        if(width > 0 && height > 0){
            this.height = height;
            this.width = width;
        }else {
            System.out.println("width and height should > 0");
        }
    }

    @Override
    public double getArea() {
        return this.width * this.height;
    }

    @Override
    public double getCircumference() {
        return 2 * (this.width + this.height);
    }
}

class demo_03{
    public static void main(String[] args) {
        Shape circle = new Circle(10);
        Shape rectangle = new Rectangle(3, 4);
        System.out.printf("circle area = %f, circumference = %f\n", circle.getArea(), circle.getCircumference());
        System.out.printf("rectangle area = %f, circumference = %f\n", rectangle.getArea(), rectangle.getCircumference());
    }
}