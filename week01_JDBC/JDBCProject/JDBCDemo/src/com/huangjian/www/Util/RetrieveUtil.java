package com.huangjian.www.Util;

import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;


public class RetrieveUtil {



    /*
     * 该方法用于查询数据库中表的指定字段的所有满足条件的数据的操作,不需要的字段对应的成员变量设为null
     *@param mds  数据库连接池
     *@param sql  sql语句
     *@param t     提供类对象
     *@param params  字段列表
     */
    public static<T> ArrayList<T> query(MyDataSource mds, String sql,T t,Object...params){
        //获取类对象
        Class<T> aClass = (Class<T>) t.getClass();
        //该集合用于存放返回的封装对象
        ArrayList<T> arrayList = new ArrayList<>();
        Constructor<T> constructor = null;
        try {
            //获取空参构造方法
            constructor = aClass.getConstructor();
        } catch (NoSuchMethodException e) {
            e.printStackTrace();
        }
        //获取成员变量
        Field[] fields = aClass.getDeclaredFields();
        try {
            //获取连接
            Connection conn = mds.getConnection();
            //获取执行对象
            PreparedStatement pstmt = conn.prepareStatement(sql);
            //设置占位符
            if(params != null)
                for (int i = 0; i < params.length; i++)
                    pstmt.setObject(i + 1, params[i]);
            //执行sql
            ResultSet rs = pstmt.executeQuery();
            //收集结果集的数据
            while(rs.next()){
                //封装对象
                T tt = null;
                if (constructor != null) {
                    //构造对象
                    constructor.setAccessible(true);
                    tt = constructor.newInstance();
                }
                //封装对象
                for (int i = 0;i < fields.length;i++) {
                    Field field = fields[i];
                    field.setAccessible(true);
                    Object value = rs.getObject(i+1);
                    field.set(tt,value);
                }
                //添加对象
                arrayList.add(tt);
            }
            //关闭资源
            JDBCUtil.close(mds,conn,pstmt,rs);
        } catch (SQLException | InstantiationException | IllegalAccessException | InvocationTargetException e) {
            e.printStackTrace();
        }
        //返回查询的对象集合
        return arrayList ;
    }


}