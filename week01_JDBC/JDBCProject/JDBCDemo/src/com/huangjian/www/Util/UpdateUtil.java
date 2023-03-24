package com.huangjian.www.Util;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class UpdateUtil {

    /*
     * 该方法可用于增删改数据库的操作
     *@param mds  数据库连接池
     *@param sql  sql语句
     * @param params  字段列表
     */
    public static void update(MyDataSource mds ,String sql,Object...params){

        try {
            //获取连接
            Connection conn = mds.getConnection();
            //获取执行对象
            PreparedStatement pstmt = conn.prepareStatement(sql);
            //设置占位符
            if(params!=null) {
                for (int i = 0; i < params.length; i++)
                    pstmt.setObject(i + 1, params[i]);
            }
            //执行sql
            int n = pstmt.executeUpdate();
            System.out.println(n+" line changed");
            //关闭资源
            JDBCUtil.close(mds,conn,pstmt,null);
        } catch (SQLException e) {
            //异常处理
            e.printStackTrace();
        }
    }

}