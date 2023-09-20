import java.sql.*;
import java.util.ArrayList;

public class dataOperate {
    private final dbLink dbLinker;
    private final Statement statement;
    public dataOperate() throws dataOperateException{
        try{
            this.dbLinker = new dbLink();
            this.statement = this.dbLinker.getConnection().createStatement();
        }catch (SQLException e){
            throw new dataOperateException("Create statement failed"+e);
        }
    }
    public String[][] inquireDataBySql(String sql, String ...columns) throws dataOperateException{
        try{
            ArrayList<String[]> resultList = new ArrayList<>();
            ResultSet res = statement.executeQuery(sql);
            while (res.next()){
                String[] temp = new String[columns.length];
                for(int i = 0; i < columns.length; i += 1){
                    temp[i] = res.getString(columns[i]);
                }
                resultList.add(temp);
            }
            try {
                res.close();
            } catch (SQLException e) {
                throw new dataOperateException("Close inquire result set failed" + e);
            }

            return resultList.toArray(new String[resultList.size()][]);
        }catch (SQLException e){
            throw new dataOperateException("Inquire and split data to string array failed: "+e);
        }
    }
    public boolean operateDbBySql(String sql) throws dataOperateException{
        try {
            int count = statement.executeUpdate(sql);
            return count > 0;
        }catch (SQLException e){
            throw new dataOperateException("operate db by sql failed: "+sql+e);
        }
    }
    public void closeDataOperator() throws dataOperateException{
        if(this.statement != null){
            try{
                this.statement.close();
            }catch (SQLException e){
                throw new dataOperateException("Close data operator failed"+e);
            }
        }
        if(this.dbLinker != null){
            try{
                this.dbLinker.closeDbLink();
            }catch (dbLinkException e){
                throw new dataOperateException("Close data operator failed"+e);
            }
        }
    }
}
