import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.Arrays;

public class test {
    public static void main(String[] args) {
//        ArrayList<String[]> tp = new ArrayList<>();
//        tp.add(new String[]{"z", "y", "x"});
//        tp.add(new String[]{"x", "y", "z"});
//        tp.add(new String[]{"j", "k", "l"});
//        System.out.println(Arrays.deepToString(tp.toArray(new String[0][])));
//        String[][] tpq = new String[][]{
//                {"1", "2", "3"},
//                {"4", "5", "6"},
//                {"7", "8", "9"}
//        };
//        System.out.println(Arrays.deepToString(tpq));
//        int[] a = new int[]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
//        int[] b = new int[5];
////        System.arraycopy(a, 8, b, 0, 3);
//        System.out.println(Arrays.toString(b));
//        int[][] c = new int[3][];
//        c[0] = new int[]{1, 2, 3, 2};
//        c[1] = new int[]{1, 2, 3};
//        c[2] = new int[]{1, 2, 3};
//        System.out.println(Arrays.deepToString(c));
        JFrame frame = new JFrame();
        frame.setLayout(null);
        frame.setSize(600, 360);
        frame.setLocationRelativeTo(null);
        String[] head = new String[]{"ID", "用户", "性别"};
        String[][] data = new String[][]{
                new String[]{"1", "vwx", "1"},
                new String[]{"1", "vwx", "1"},
                new String[]{"1", "vwx", "1"}
        };
        JTable tb = new JTable(data, head);
        tb.setBounds(0, 30, 600, 230);
        frame.add(tb.getTableHeader(), BorderLayout.NORTH);
        frame.add(tb, BorderLayout.CENTER);
        JButton btn = new JButton("打印");
        btn.setBounds(30, 300, 36, 20);
        frame.add(btn);
        btn.addActionListener(e -> System.out.println(Arrays.deepToString(data)));
        frame.setVisible(true);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
}
