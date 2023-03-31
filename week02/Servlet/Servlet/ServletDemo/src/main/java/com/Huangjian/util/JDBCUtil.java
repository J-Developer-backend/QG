package com.Huangjian.util;

import java.io.IOException;
import java.io.InputStream;
import java.net.URL;
import java.sql.*;
import java.util.ArrayList;
import java.util.Properties;

public class JDBCUtil {
    private static String driver;
    private static String url;
    private static String username;
    private static String password;
    private static final ArrayList<Connection> connList ;

    static {
        ClassLoader classLoader = JDBCUtil.class.getClassLoader();
        URL resource = classLoader.getResource("jdbc.properties");
        try {
            InputStream inputStream = resource.openStream();
            Properties properties = new Properties();
            properties.load(inputStream);
            driver = properties.getProperty("drive");
            url = properties.getProperty("url");
            username = properties.getProperty("username");
            password = properties.getProperty("password");
        } catch (IOException e) {
            e.printStackTrace();
        }
        connList = new ArrayList<>();
        for(int i=0;i<3;i++){
            Connection conn = null;
            try {
                Class.forName(driver);
                conn = DriverManager.getConnection(url,username,password);
            } catch (ClassNotFoundException | SQLException e) {
                e.printStackTrace();
            }
            if(conn!=null)
                connList.add(conn);
        }

    }

    public static Connection getConnection(){
        if(connList.size() == 0) {
            for (int i = 0; i < 3; i++) {
                Connection conn = null;
                try {
                    Class.forName(driver);
                    conn = DriverManager.getConnection(url, username, password);
                } catch (ClassNotFoundException | SQLException e) {
                    e.printStackTrace();
                }
                if (conn != null)
                    connList.add(conn);
            }
        }
        return connList.remove(0);
    }

    public static void close(Connection conn,PreparedStatement pstmt) {
        if(conn!=null)
            connList.add(conn);
        if(pstmt!=null) {
            try {
                pstmt.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }

    public static boolean addUser(String username ,String password)  {
        if(findOneUser(username))
            return false;
        if(username == null || password == null)
                return false;
        String sql = "INSERT INTO user VALUES (?, ?);";
        Connection conn = JDBCUtil.getConnection();
        PreparedStatement pstmt = null;
        try {
            pstmt  = conn.prepareStatement(sql);
            pstmt.setObject(1,username);
            pstmt.setObject(2,password);
            int i = pstmt.executeUpdate();
            if(i == 0)
                return false;
        } catch (SQLException e) {
            e.printStackTrace();
        }finally {
            JDBCUtil.close(conn,pstmt);
        }
        return true;
    }

    public static boolean findUser(String username ,String password)  {
        String sql = "SELECT * FROM user WHERE username = ? and password = ?;";
        Connection conn = JDBCUtil.getConnection();
        PreparedStatement pstmt = null;
        try {
            pstmt  = conn.prepareStatement(sql);
            pstmt.setObject(1,username);
            pstmt.setObject(2,password);
            ResultSet rs = pstmt.executeQuery();
            if ( rs.next())
               return true;
        } catch (SQLException e) {
            e.printStackTrace();
        }finally {
            JDBCUtil.close(conn,pstmt);
        }
        return false;
    }


    public static boolean findOneUser(String username)  {
        String sql = "SELECT * FROM user WHERE username = ? ;";
        Connection conn = JDBCUtil.getConnection();
        PreparedStatement pstmt = null;
        try {
            pstmt  = conn.prepareStatement(sql);
            pstmt.setObject(1,username);
            ResultSet rs = pstmt.executeQuery();
            if ( rs.next())
                return true;
        } catch (SQLException e) {
            e.printStackTrace();
        }finally {
            JDBCUtil.close(conn,pstmt);
        }
        return false;
    }


}
