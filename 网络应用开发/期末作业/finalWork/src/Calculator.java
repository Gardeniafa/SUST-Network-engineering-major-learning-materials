public class Calculator {
    public static int sum(int x, int y){
        return x+y;
    }
    public static int sub(int x, int y){
        return x-y;
    }
    public static int mult(int x, int y){
        return x*y;
    }
    public static int div(int x, int y){
        return x/y;
    }

    public static float add(float x, float y){
        return x+y;
    }
    public static float sub(float x, float y){
        return x-y;
    }
    public static float mult(float x, float y){
        return x*y;
    }
    public static float div(float x, float y){
        return x/y;
    }
}
class demo_02{
    public static void main(String[] args) {
        System.out.println(Calculator.add(1, 2));
        System.out.println(Calculator.add(1.1f, 2.2f));
    }
}
