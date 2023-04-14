package com.Huangjian.po;

import com.Huangjian.Annotation.ColumnAnnotation;

public class User {
    @ColumnAnnotation(columnName = "id",value = "id")
    private Integer id;
    @ColumnAnnotation(columnName = "username",value = "username")
    private String username;
    @ColumnAnnotation(columnName = "password",value = "password")
    private String password;

    public User() {
    }

    public User(String username, String password ,Integer id) {
        this.id = id;
        this.username = username;
        this.password = password;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    @Override
    public String toString() {
        return "User{" +
                "id=" + id +
                ", username='" + username + '\'' +
                ", password='" + password + '\'' +
                '}';
    }
}
