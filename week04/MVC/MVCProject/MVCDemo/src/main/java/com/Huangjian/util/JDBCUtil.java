package com.Huangjian.util;


import java.io.IOException;
import java.io.InputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Properties;

public class JDBCUtil {
    private static String driver;
    private static String url;
    private static String username;
    private static String password;
    private static ArrayList<Connection> connList = new ArrayList<>();

    static {
        Properties properties = new Properties();
        try {
            InputStream is = JDBCUtil.class.getClassLoader().getResource("jdbc.properties").openStream();
            properties.load(is);
        } catch (IOException e) {
            e.printStackTrace();
        }
        driver = properties.getProperty("driver");
        url = properties.getProperty("url");
        username = properties.getProperty("username");
        password = properties.getProperty("password");
        for (int i = 0; i < 5; i++) {
            Connection connection = getConnections();
            connList.add(connection);
        }
    }

    private static Connection getConnections() {
        Connection conn = null;
        try {
            Class.forName(driver);
            conn = DriverManager.getConnection(url,username,password);
        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
        }
        return conn;
    }

    public static Connection getConnection(){
        return connList.remove(0);
    }

    public static void returnConnection(Connection conn){
        connList.add(conn);
    }

}






