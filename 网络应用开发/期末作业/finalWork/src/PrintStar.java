public class PrintStar {
    public static void printStar(int number) throws PrintStarException{
        if(number <= 0){
            throw new PrintStarException("Number should > 0");
        }
        for (int i = 1; i <= number; i += 1){
            if(i == number){
                System.out.println("*".repeat(2*number-1));
                return;
            }
            if(i == 1){
                System.out.println(" ".repeat(number-1) + "*");
                continue;
            }
            String s = " ".repeat(number - i) + "*" + " ".repeat(2*(i-1)-1) + "*";
            System.out.println(s);
        }
    }
}
class demo_0{
    public static void main(String[] args) throws PrintStarException {
        PrintStar.printStar(-10);
    }
}