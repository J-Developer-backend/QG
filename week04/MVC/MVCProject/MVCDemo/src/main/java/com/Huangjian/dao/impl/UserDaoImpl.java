package com.Huangjian.dao.impl;

import com.Huangjian.dao.UserDao;
import com.Huangjian.po.User;
import com.Huangjian.util.InsertUtil;
import com.Huangjian.util.QueryUtil;

import java.util.HashMap;

public class UserDaoImpl implements UserDao {


    @Override
    public User queryUser(String username, String password) {
        HashMap<String,String> map = new HashMap<>();
        map.put("username",username);
        map.put("password",password);
        User user = QueryUtil.query(User.class, map);
        if(user == null)
            return null;
        else if (user.getUsername() == null)
            return null;
        else
            return user;
    }

    @Override
    public User queryUser(String username) {
        HashMap<String,String> map = new HashMap<>();
        map.put("username",username);
        User user = QueryUtil.query(User.class, map);
        if(user == null)
            return null;
        else if (user.getUsername() == null)
            return null;
        else
            return user;
    }

    @Override
    public User addUser(String username, String password) {
        User user = this.queryUser(username);
        if(user == null) {
            HashMap<String,String> map = new HashMap<>();
            map.put("username",username);
            map.put("password",password);
            user = InsertUtil.insert(User.class, map);
            return user;
        }else {
            return null;
        }
    }
}
