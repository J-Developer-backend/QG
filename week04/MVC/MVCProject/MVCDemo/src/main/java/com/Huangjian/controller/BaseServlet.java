package com.Huangjian.controller;

import com.Huangjian.Service.LoginService;
import com.Huangjian.Service.RegisterService;
import com.Huangjian.Service.impl.LoginServiceImpl;
import com.Huangjian.Service.impl.RegisterImpl;
import com.Huangjian.po.User;
import com.Huangjian.util.ResultUtil;
import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.JSONObject;

import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;
import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

@WebServlet("/base")
public class BaseServlet extends HttpServlet {

    JSONObject jsonObject ;

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.setCharacterEncoding("UTF-8");
        response.setCharacterEncoding("UTF-8");
        String line = request.getReader().readLine();
        jsonObject = JSON.parseObject(line);
        String method = jsonObject.getString("method");
        Class<? extends BaseServlet> clazz = this.getClass();
        try {
            Method login = clazz.getMethod(method, HttpServletRequest.class, HttpServletResponse.class);
            login.invoke(this,request,response);
        } catch (NoSuchMethodException | IllegalAccessException | InvocationTargetException e) {
            e.printStackTrace();
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        this.doGet(request, response);
    }

    public void loginServlet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        LoginService loginService = new LoginServiceImpl();
        User user = loginService.login(request,response,jsonObject);
        int code = 1;
        String msg ;
        if(user == null) {
            msg = "登录失败";
            code = 0;
        }
        else
            msg = "登录成功";
        response.getWriter().write(ResultUtil.result(user,code,msg));
    }

    public void registerServlet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        RegisterService registerService = new RegisterImpl();
        User user = registerService.register(request, response, jsonObject);
        int code = 1;
        String msg ;
        if(user != null){
            msg = "注册成功";
        }else{
            msg = "注册失败";
            code = 0;
        }
        response.getWriter().write(ResultUtil.result(user,code,msg));
    }

    public  void forgetServlet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        LoginService loginService = new LoginServiceImpl();
        User user = loginService.forget(request, response, jsonObject);
        int code = 1;
        String msg ;
        if(user == null) {
            msg = "用户名错误";
            code = 0;
        }
        else
            msg ="密码:" + user.getPassword();
        response.getWriter().write(ResultUtil.result(user,code,msg));
    }
}
