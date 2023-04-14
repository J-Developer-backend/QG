package com.Huangjian.util;

import com.Huangjian.Annotation.ColumnAnnotation;

import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.HashMap;
import java.util.Set;
import java.util.StringJoiner;

public class InsertUtil {
    public static<T> T insert(Class<T> clazz, HashMap<String ,String > params){
        Connection conn = JDBCUtil.getConnection();
        String[] split = clazz.getName().split("\\.");
        String table = split[split.length-1];
        String sql = "insert into " + table ;
        StringJoiner sj1 = new StringJoiner(","," ( "," ) ");
        StringJoiner sj2 = new StringJoiner("," ," ( "," ) ");
        Set<String> TFields = params.keySet();
        for (String field : TFields) {
            try {
                Field clazzField = clazz.getDeclaredField(field);
                String columnName = clazzField.getAnnotation(ColumnAnnotation.class).columnName();
                sj1.add(columnName);
                sj2.add(" ? ");
            } catch (NoSuchFieldException e) {
                e.printStackTrace();
            }
        }
        sql = sql + sj1 + " values " + sj2;
        PreparedStatement pstmt ;
        try {
            pstmt = conn.prepareStatement(sql);
            int i = 1;
            for (String s : TFields) {
                String value = params.get(s);
                pstmt.setObject(i, value);
                i++;
            }
            int line = pstmt.executeUpdate();
            if(line != 0){
                Constructor<T> constructor = clazz.getDeclaredConstructor();
                constructor.setAccessible(true);
                T t = constructor.newInstance();
                for (String field : TFields) {
                    Field clazzField = clazz.getDeclaredField(field);
                    clazzField.setAccessible(true);
                    clazzField.set(t,params.get(field));
                }
                pstmt.close();
                return t;
            }
        } catch (SQLException | NoSuchMethodException | IllegalAccessException | InstantiationException |
                 InvocationTargetException | NoSuchFieldException e) {
            e.printStackTrace();
        }finally {
            JDBCUtil.returnConnection(conn);
        }
        return null;
    }
}
