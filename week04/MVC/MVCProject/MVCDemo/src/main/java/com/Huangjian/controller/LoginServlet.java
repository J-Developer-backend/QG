package com.Huangjian.controller;


import com.Huangjian.Service.LoginService;
import com.Huangjian.Service.impl.LoginServiceImpl;
import com.Huangjian.po.User;
import com.Huangjian.util.ResultUtil;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;


@WebServlet("/LoginServlet")
public class LoginServlet extends BaseServlet {

    private LoginService loginService = new LoginServiceImpl();

     public void login(HttpServletRequest request, HttpServletResponse response) throws IOException {
        User user = loginService.login(request,response,super.jsonObject);
        int code = 200;
        String msg ;
        if(user == null)
            msg = "登录失败";
        else
            msg = "登录成功";
        response.getWriter().write(ResultUtil.result(user,code,msg));
    }
}
