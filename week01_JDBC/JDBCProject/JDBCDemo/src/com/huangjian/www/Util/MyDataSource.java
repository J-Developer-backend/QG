package com.huangjian.www.Util;

import javax.sql.DataSource;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.SQLException;
import java.sql.SQLFeatureNotSupportedException;
import java.util.ArrayList;
import java.util.logging.Logger;

//自定义数据库连接池
public class MyDataSource implements DataSource {

    private ArrayList<Connection> connList = null;

    public MyDataSource() {
        connList = new ArrayList<>();
        //初始化数据库连接池的3个连接
        for (int i = 0; i < 3; i++)
            connList.add(JDBCUtil.getConnection());
    }

    //归还连接
    public void returnConnection(Connection conn){
        connList.add(conn);
    }


    //获取连接
    @Override
    public Connection getConnection() throws SQLException {
        //返回已经定义好的连接
        return connList.remove(0);
    }

    @Override
    public Connection getConnection(String username, String password) throws SQLException {
        return null;
    }

    @Override
    public <T> T unwrap(Class<T> iface) throws SQLException {
        return null;
    }

    @Override
    public boolean isWrapperFor(Class<?> iface) throws SQLException {
        return false;
    }

    @Override
    public PrintWriter getLogWriter() throws SQLException {
        return null;
    }

    @Override
    public void setLogWriter(PrintWriter out) throws SQLException {

    }

    @Override
    public void setLoginTimeout(int seconds) throws SQLException {

    }

    @Override
    public int getLoginTimeout() throws SQLException {
        return 0;
    }

    @Override
    public Logger getParentLogger() throws SQLFeatureNotSupportedException {
        return null;
    }
}