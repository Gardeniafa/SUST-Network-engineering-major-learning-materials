public class multiplicationTable {
    public void printMultTable(int len){
        for(int i = 1; i <= len; i += 1){
            for(int j = 1; j <= i; j += 1){
                System.out.printf("%2d*%2d = %2d\t", j, i, i*j);
            }
            System.out.println();
        }
    }
}
class demo_01{
    public static void main(String[] args) {
        multiplicationTable mtb = new multiplicationTable();
        mtb.printMultTable(9);
    }
}