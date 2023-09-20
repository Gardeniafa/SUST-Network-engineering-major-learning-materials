import java.util.concurrent.TimeUnit;

public class sysEntry {
    public static void main(String[] args){
        sysLogin login;
        try{
            login = new sysLogin();
        }catch (sysLoginException e){
            System.out.println("Create login window failed:");
            e.printStackTrace();
            return;
        }
        LoginUser user;
        while (true){
            try{
                TimeUnit.MILLISECONDS.sleep(300);
            }catch (InterruptedException e){
                System.out.println("Time sleep interrupted with");
                e.printStackTrace();
            }
            if(login.getLoginStatus()){
                user = login.getLoginUser();
                System.out.println("entry: login success as: " + user.permission());
                try {
                    login.closeFrame();
                }catch (sysLoginException e){
                    System.out.println("Login occurs error:");
                    e.printStackTrace();
                }
                break;
            }
        }
        System.out.println("Login success, do other things...");
        try {
            new sysManager(user);
        }catch (sysManagerException e){
            e.printStackTrace();
        }

    }
}
