package com.Huangjian.dao;

import com.Huangjian.po.User;

public interface UserDao {
    User queryUser(String username, String password);
    User queryUser(String username);
    User addUser(String username,String password);
}
