import java.util.Date;
import java.text.SimpleDateFormat;


public class orderNumberGeneration {
    public String orderBuilder(){
        SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMddHHmmss");
        Date date = new Date();
        return "D" + sdf.format(date) + System.getenv().get("USERNAME");
    }
}
class demo_05{
    public static void main(String[] args) {
        orderNumberGeneration ong = new orderNumberGeneration();
        System.out.println(ong.orderBuilder());
    }
}