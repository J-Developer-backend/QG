package com.Huangjian.mapper;


import com.Huangjian.pojo.User;



public interface UserMapper {
    User selectUser(User user);
    User findUser(String username);
    void addUser(User user);
}
