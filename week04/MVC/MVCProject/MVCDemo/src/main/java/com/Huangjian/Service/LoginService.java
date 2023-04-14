package com.Huangjian.Service;

import com.Huangjian.po.User;
import com.alibaba.fastjson.JSONObject;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public interface LoginService {
    User login(HttpServletRequest request, HttpServletResponse response, JSONObject jsonObject) throws IOException;
    User forget(HttpServletRequest request, HttpServletResponse response,JSONObject jsonObject);
}
