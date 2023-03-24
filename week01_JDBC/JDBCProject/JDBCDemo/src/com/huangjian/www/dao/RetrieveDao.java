package com.huangjian.www.dao;

import com.huangjian.www.Util.MyDataSource;
import com.huangjian.www.Util.RetrieveUtil;

import java.lang.reflect.Field;
import java.util.ArrayList;
import java.util.StringJoiner;

public class RetrieveDao <T>{

    private final Class<T> aClass ;
    private final String table ;


    public RetrieveDao(T t) {
        this.aClass =(Class<T>) t.getClass() ;
        String[] strings = this.aClass.getTypeName().split("\\.");
        int len = strings.length;
        this.table = strings[len - 1] ;
    }


    /*
     * 该方法用于查询数据库中表的指定字段的所有满足条件的数据的操作
     *@param mds        数据库连接池
     *@param t          提供类对象
     *@param condition  查询条件
     *@param params     字段列表
     */
    public ArrayList<T>  retrieve(MyDataSource mds ,T t , String condition, Object...params){
        // sql = select ?,?,...(columns) from (table) where () () (?)
        //拼接sql语句
        StringBuilder sql = new StringBuilder("select ");
        StringJoiner sj = new StringJoiner(","," "," ");
        //存放占位符的值
        ArrayList<Object> objects = new ArrayList<>();
        //拆分条件,条件以固定形式传入(空格隔开),(字段 符号 值)
        String[] conditions = condition.split(" ");
        //设置字段
        if(params[0].equals("*")) {
            Field[] fields = getaClass().getDeclaredFields();
            for (Field field : fields)
                sj.add(field.getName());
        }else {
            for (Object param : params)
                sj.add(param.toString());
        }
        //添加条件参数
        objects.add(conditions[2]);
        //形成sql语句
        sql.append(sj).append(" from ").append(getTable()).append(" where ").append(conditions[0] + conditions[1]).append(" ?");
        return RetrieveUtil.query(mds, sql.toString(), t ,objects.toArray());
    }

    public Class<T> getaClass() {
        return aClass;
    }

    public String getTable() {
        return table;
    }


}