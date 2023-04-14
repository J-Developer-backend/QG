package com.Huangjian.util;

import com.Huangjian.Annotation.ColumnAnnotation;

import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.sql.*;
import java.util.HashMap;
import java.util.Set;

public class QueryUtil {

    public static<T> T query(Class<T> clazz, HashMap<String,String> params){
        Connection conn = JDBCUtil.getConnection();
        String[] split = clazz.getName().split("\\.");
        String table = split[split.length-1];
        String sql = "select * from " + table + " where ";
        Set<String> TFields = params.keySet();
        try {
            for (String s : TFields) {
                Field field = clazz.getDeclaredField(s);
                String columnName = field.getAnnotation(ColumnAnnotation.class).columnName();
                sql = sql + columnName + "= ? and ";
            }
            sql = sql + " 1 = 1";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            int i = 1;
            for (String s : TFields) {
                String value = params.get(s);
                pstmt.setObject(i, value);
                i++;
            }
            ResultSet rs = pstmt.executeQuery();
            ResultSetMetaData metaData = rs.getMetaData();
            int count =metaData.getColumnCount();
            i = 1;
            Constructor clazzConstructor = clazz.getConstructor();
            clazzConstructor.setAccessible(true);
            T t = (T)clazzConstructor.newInstance();
            Field[] fields = clazz.getDeclaredFields();
            while(rs.next()){
                for (int j = 0; j < count; j++) {
                    String columnName = metaData.getColumnName(j + 1);
                    for (Field field : fields) {
                        if(field.getAnnotation(ColumnAnnotation.class).columnName().equals(columnName)){
                            field.setAccessible(true);
                            field.set(t,rs.getObject(j+1));
                        }
                    }
                }
            }
            rs.close();
            pstmt.close();
            JDBCUtil.returnConnection(conn);
            return t;
        } catch (SQLException | NoSuchMethodException | InvocationTargetException
                 | InstantiationException | IllegalAccessException |
                 NoSuchFieldException e) {
            e.printStackTrace();
        }
        return null;
    }

}
