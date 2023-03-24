package com.huangjian.www.Util;


import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.sql.*;
import java.util.Properties;

public class JDBCUtil {

    private static final String driver ;
    private static final String url ;
    private static final String user ;
    private static final String password ;

    //加载驱动
    static {
        InputStream is ;
        try {
            is = new FileInputStream("D:\\GDUTLearning\\JavaProject\\QG\\week01_JDBC\\" +
                    "JDBCProject\\JDBCDemo\\src\\jdbc.properties");
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }
        Properties properties = new Properties();
        try {
            properties.load(is);
        } catch (IOException e) {
            e.printStackTrace();
        }
        driver =  properties.getProperty("driver");
        url = properties.getProperty("url");
        user = properties.getProperty("user");
        password = properties.getProperty("password");
        try {
            Class.forName(driver);
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }
    //获取连接
    public static Connection getConnection(){
        try {
            Class.forName(driver);
        } catch (ClassNotFoundException e) {
            throw new RuntimeException(e);
        }
        try {
            return DriverManager.getConnection(url,user,password);
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }


    //关闭资源
    public static void close(MyDataSource mds,Connection conn , PreparedStatement pstmt, ResultSet rs) throws SQLException {
        //归还连接
        if(mds!=null && conn!=null )
            mds.returnConnection(conn);
        if(pstmt !=null)
            pstmt.close();
        if(rs!=null)
            rs.close();
    }


}