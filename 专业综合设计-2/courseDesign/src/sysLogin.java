import javax.swing.*;

import java.util.Arrays;


public class sysLogin {
    private dataOperate dataOperator;
    private final JFrame loginFrame;
    private final JTextField nameInput = new JTextField();
    private final JTextField passwordInput = new JPasswordField();
    private LoginUser user = null;
    public sysLogin() throws sysLoginException{
        loginFrame = new JFrame();
        loginFrame.setLocationRelativeTo(null);
        loginFrame.setSize(333, 169);
        loginFrame.setLayout(null);
        loginFrame.setResizable(false);
        JLabel userNameLabel = new JLabel("UserName");
        userNameLabel.setBounds(27, 21, 69, 18);
        loginFrame.add(userNameLabel);
        this.nameInput.setBounds(101, 19, 193, 22);
        loginFrame.add(this.nameInput);
        JLabel passwordJlabel = new JLabel("Password");
        passwordJlabel.setBounds(27, 55, 69, 18);
        loginFrame.add(passwordJlabel);
        this.passwordInput.setBounds(101, 53, 193, 22);
        loginFrame.add(this.passwordInput);
        JButton loginBtn = new JButton("Login");
        loginBtn.setBounds(105, 106, 78, 22);
        loginFrame.add(loginBtn);
        JButton cancelBtn = new JButton("Cancel");
        cancelBtn.setBounds(196, 106, 78, 22);
        loginFrame.add(cancelBtn);
        JLabel wrongReportLabel = new JLabel("");
        wrongReportLabel.setBounds(69, 83, 289, 15);
        loginFrame.add(wrongReportLabel);
        loginFrame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        loginFrame.setIconImage(new ImageIcon("C:\\Data\\coding\\JAVA\\webApplicationDevelopment\\courseDesign\\src\\a-yonghuxinxiyonghu.png").getImage());
        loginFrame.setLocationRelativeTo(null);
        loginFrame.setVisible(true);
        cancelBtn.addActionListener(e -> {
            try {
                this.closeFrame();
            } catch (sysLoginException ex) {
                try {
                    throw ex;
                } catch (sysLoginException ignored) {
                }
            }
        });
        loginBtn.addActionListener(e -> {
            String userName = this.nameInput.getText();
            String password = this.passwordInput.getText();
            try {
                this.dataOperator = new dataOperate();
            } catch (dataOperateException ex) {
                try {
                    throw new sysLoginException("init data operator error: "+ex);
                } catch (sysLoginException ignored) {
                }
            }
            try{
                String[][] res = dataOperator.inquireDataBySql("select * from `system` where id='"+userName+
                        "' or name='"+userName+"'", "id", "name", "permission", "password");
                System.out.println("Inquired data: "+ Arrays.deepToString(res));
                for (String[] re : res) {
                    if (userName.equals(re[0]) || userName.equals(re[1])) {
                        if (password.equals(re[3])) {
                            System.out.println("Login success!");
                            this.user = new LoginUser(re[0], re[1], re[2], re[3]);
                            wrongReportLabel.setText("<html><body><p style='color: rgba(0, 255, 0, 0.8);" +
                                    "font-size: 1.1em; font-weight: bolder;'>Login success!</p></body></html>");
                            return;
                        }else {
                            System.out.printf("check for id: %s, userName or id found, but password is not correct...\n", re[0]);
                        }
                    }
                }
                System.out.println("userName not found...");
                wrongReportLabel.setText("<html><body><p style='color: rgba(255, 0, 0, 0.8);font-size: 1.1em; " +
                        "font-weight: bolder;'>Incorrect password or user name!</p></body></html>");
            }catch (dataOperateException exception){
                try {
                    throw new sysLoginException("inquire data by sql failed: "+exception);
                } catch (sysLoginException ignored) {
                }
            }
        });
    }
    public boolean getLoginStatus(){
        return this.user != null;
    }
    public void closeFrame() throws sysLoginException {
        if(dataOperator == null){
            System.exit(0);
        }
        try {
            this.dataOperator.closeDataOperator();
        }catch (dataOperateException e){
            throw new sysLoginException("When close login frame, exception occur:"+e);
        }
        if(!this.getLoginStatus()){
            System.exit(0);
        }
        this.loginFrame.dispose();
    }
    public LoginUser getLoginUser(){
        return this.user;
    }
}
