package com.huangjian.www.dao;

import com.huangjian.www.Util.MyDataSource;
import com.huangjian.www.Util.UpdateUtil;

import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.util.Arrays;
import java.util.List;
import java.util.StringJoiner;
import java.util.stream.Collectors;

public class InsertDao<T> {

    private final Class<T> aClass ;
    private final String table ;


    public InsertDao(T t){
        this.aClass = (Class<T>) t.getClass();
        String[] strings = this.aClass.getTypeName().split("\\.");
        int len = strings.length;
        this.table = strings[len - 1] ;
    }


    /*
     *插入方法
     * @param mds  数据库连接池
     * @param ts   插入对象数组
     * */
    public void insert (MyDataSource mds, T... ts){
        for (T t : ts) {
            //  sql = "insert into (table) (columns) values (params)"
            StringJoiner columns = new StringJoiner(",", "(", ")");
            StringJoiner values = new StringJoiner(",", "(", ")");
            //获取T类的成员变量
            Field[] fields = aClass.getDeclaredFields();
            //id自增，不需要插入
            Object[] params = new Object[fields.length - 1];
            //过滤get方法，获取对应bean类的所有get方法的methods对象到List集合中
            List<Method> methodList = Arrays.stream(aClass.getDeclaredMethods())
                    .filter(method -> {
                        String[] s = method.getName().split("\\.");
                        return s[s.length - 1].startsWith("get");
                    })
                    .collect(Collectors.toList());
            //id自增，不需要插入
            try {
                for (int j = 1; j < fields.length; j++) {
                    //获取成员变量名，拼接成字段列表
                    String fieldName = fields[j].getName();
                    columns.add(fieldName);
                    //寻找相应的get方法
                    for (Method method : methodList) {
                        String[] split = method.getName().split("\\.");
                        int len = split.length;
                        //找到对应成员变量的get方法
                        if (split[len - 1].split("get")[1].equalsIgnoreCase(fieldName)) {
                            //调用get方法
                            Object o = method.invoke(t);
                            //存贮到params数组中
                            params[j - 1] = o;
                            //加入一个占位符
                            values.add("?");
                            //移除该方法
                            methodList.remove(method);
                            break;
                        }
                    }
                }
            } catch (Exception e) {
                throw new RuntimeException(e);
            }
            //行成sql语句
            String sql = "insert into " + getTable() + columns + " values " + values;
            UpdateUtil.update(mds, sql, params);
        }
    }
    public Class<T> getaClass() {
        return aClass;
    }

    public String getTable() {
        return table;
    }



}
