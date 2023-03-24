package com.huangjian.www.dao;

import com.huangjian.www.Util.MyDataSource;
import com.huangjian.www.Util.UpdateUtil;

import java.lang.reflect.Field;
import java.util.*;
import java.util.stream.Collectors;

public class UpdateDao<T> {

    private final Class<T> aClass;
    private final String table ;
    private final List<String> fieldList ;

    public UpdateDao(T t) {
        this.aClass =(Class<T>) t.getClass() ;
        String[] strings = this.aClass.getTypeName().split("\\.");
        int len = strings.length;
        this.table = strings[len - 1] ;
        //获取对应类的成员变量
        Field[] fields = aClass.getDeclaredFields();
        fieldList = Arrays.stream(fields).map(Field::getName)
                .collect(Collectors.toList());
    }
    /*
     * 更新指定id对应的行数据的字段的值到指定的值
     * @param mds  数据库连接池
     * @param id   指定id
     * @param map  key为字段，value要更新为的值
     * */
    public void update(MyDataSource mds, String condition , HashMap<String,String> map){
        //sql = update (table) set column = value , ... where id = ?
        //拼接sql语句
        String sb = " update " + getTable() + " set ";
        if(map.isEmpty()){
            System.out.println("not thing to update");
            return ;
        }
        Set<Map.Entry<String, String>> entries = map.entrySet();
        StringJoiner sj = new StringJoiner(","," "," ");
        ArrayList<Object> objects = new ArrayList<>();
        for (Map.Entry<String, String> entry : entries) {
            sj.add(entry.getKey() + "= ?" );
            objects.add(entry.getValue());
        }
        //拆分条件
        String[] s = condition.split(" ");
        //形成sql语句
        String sql = sb + sj + "where " + s[0] + " " + s[1] + "?";
        //添加条件
        objects.add(s[2]);
        //调用工具类的update方法
        UpdateUtil.update(mds,sql,objects.toArray());
    }

    /*
     *输入要更新的字段和更新成为的数据
     *@param sc 文本扫描器
     *@return  返回装载着字段和数据的map集合
     * */
    public HashMap<String,String> setUpdateData(Scanner sc){
        HashMap<String ,String> map = new HashMap<>() ;
        String key;
        String value;
        //用于检查单字段的重复输入
        ArrayList<String> list = new ArrayList<>(fieldList);
        System.out.println(list);
        int length = list.size();
        while ((length - 1) > 0){
            System.out.println("please input the column(needed to updated) and the data(update to) (input break to exit)");
            System.out.println("the column:");
            key = sc.next();
            if(checkInput(key, list) || key.equals("break"))
                break;
            if(key.equals("is_Choose")){
                System.out.println("cannot update this column ,because it change by add to a paper");
                continue;
            }
            System.out.println("the value:");
            value = sc.next();
            map.put(key,value);
            list.remove(key);
            length-- ;
        }
        return map;
    }


    public boolean checkInput(String key,List<String> list){
        return !list.contains(key);
    }

    public Class<T> getaClass() {
        return aClass;
    }

    public String getTable() {
        return table;
    }
}
