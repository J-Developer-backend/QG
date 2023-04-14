package com.Huangjian.Service.impl;

import com.Huangjian.Service.LoginService;
import com.Huangjian.dao.UserDao;
import com.Huangjian.dao.impl.UserDaoImpl;
import com.Huangjian.po.User;
import com.alibaba.fastjson.JSONObject;


import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;


public class LoginServiceImpl implements LoginService {
    private UserDao userDao = new UserDaoImpl();
    @Override
    public User login(HttpServletRequest request, HttpServletResponse response ,JSONObject jsonObject) {
        String username = jsonObject.getString("username");
        String password = jsonObject.getString("password");
        if(username.length() == 0)
            return null;
        return userDao.queryUser(username,password);

    }

    @Override
    public User forget(HttpServletRequest request, HttpServletResponse response, JSONObject jsonObject) {
        String username = jsonObject.getString("username");
        if(username.length() == 0)
            return null;
        return userDao.queryUser(username);
    }
}
