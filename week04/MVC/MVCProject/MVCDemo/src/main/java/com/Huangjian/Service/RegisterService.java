package com.Huangjian.Service;

import com.Huangjian.po.User;
import com.alibaba.fastjson.JSONObject;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public interface RegisterService {
    User register(HttpServletRequest request, HttpServletResponse response, JSONObject jsonObject);
}
