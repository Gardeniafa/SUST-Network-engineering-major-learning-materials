import java.sql.*;

public class dbLink {
    // 在这配置你自己的数据库信息
    // 若使用本地数据库为false，则将使用下面的远端数据库配置，请在下面填写自己的配置，地址、端口、名称、账密
    private static final boolean useLocalDatabaseForDevelop = false;
    private static final String dbUserName = "远端数据库用户";
    private static final String dbPassword = "远程数据库口令";
    private static final String dbName = "远端数据库名称";
    private static final String dbSpecies = "mysql";
    private static final String dbHost = "你的域名、IP地址";
    private static final String dbHostPort = "你的端口";
    private Connection connection;
    public dbLink() {
        try{
            Class.forName("com.mysql.cj.jdbc.Driver");
            if(useLocalDatabaseForDevelop){
                // 配置本地数据库链接信息，根据jdbc链接自行修改
                // 当使用本地数据库开关为true时生效
                this.connection = DriverManager.getConnection("jdbc:"+"mysql"+"://"+"127.0.0.1"+":"+"3306"+"/"+"数据库名称",
                        "数据库用户", "数据库口令");
            }else {
                this.connection = DriverManager.getConnection("jdbc:"+dbSpecies+"://"+dbHost+":"+dbHostPort+"/"+dbName,
                        dbUserName, dbPassword);
            }
        }catch (SQLException | ClassNotFoundException e){
            System.out.println("create db connection error: "+e);
        }
    }
    public Connection getConnection(){
        return this.connection;
    }
    public void closeDbLink() throws dbLinkException{
        if(this.connection == null){
            return;
        }
        try{
            this.connection.close();
        }catch (SQLException e){
            throw new dbLinkException("close db link failed: sql exception");
        }
    }
}
