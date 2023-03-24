package com.huangjian.www.dao;

import com.huangjian.www.Util.MyDataSource;
import com.huangjian.www.Util.UpdateUtil;

public class DeleteDao<T> {

    private final Class<T> aClass;
    private final String table ;

    public DeleteDao(T t) {
        this.aClass =(Class<T>) t.getClass() ;
        String[] strings = this.aClass.getTypeName().split("\\.");
        int len = strings.length;
        this.table = strings[len - 1] ;
    }


    /*
     * 删除方法
     * @param mds  数据库连接池
     * @param id   删除数据的id值
     * */
    public void delete(MyDataSource mds , String condition){
        //sql = delete from (table) where id = ?
        //拼接sql语句
        StringBuilder sb = new StringBuilder("delete from ");
        //拆分条件
        String[] s = condition.split(" ");
        sb.append(getTable()).append(" where ").append(s[0]).append(" ").append(s[1]).append("?");
        //调用工具类的update方法
        UpdateUtil.update(mds,sb.toString(),s[2]);

    }


    public String getTable() {
        return table;
    }
}
