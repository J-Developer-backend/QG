package com.Huangjian.Servlet;


import com.Huangjian.Util.JsonStr;
import com.Huangjian.Util.MybatisUtil;
import com.Huangjian.mapper.UserMapper;
import com.Huangjian.pojo.User;
import com.alibaba.fastjson.JSON;
import org.apache.ibatis.session.SqlSession;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.BufferedReader;
import java.io.IOException;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {


    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        BufferedReader reader = req.getReader();
        String jsonStr = reader.readLine();
        if(jsonStr==null){
            JsonStr ok = new JsonStr(null, 200, "empty commit");
            resp.getWriter().write(JSON.toJSONString(ok));
            return;
        }
        jsonStr = new String(jsonStr.getBytes("ISO-8859-1"),"UTF-8");
        System.out.println("请求json:"+jsonStr);
        User user = JSON.parseObject(jsonStr, User.class);
        SqlSession session = MybatisUtil.getSession();
        UserMapper mapper = session.getMapper(UserMapper.class);
        User selectUser = mapper.selectUser(user);
        System.out.println("selectUser:"+selectUser);
        JsonStr ok = new JsonStr(selectUser, 200, "OK");
        resp.getWriter().write(JSON.toJSONString(ok));


    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        this.doGet(req,resp);
    }
}
