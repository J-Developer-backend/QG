package com.Huangjian.servlet;

import com.Huangjian.util.JDBCUtil;
import com.Huangjian.util.ServletUtil;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;



@WebServlet("/Login")
public class Login extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        resp.setContentType("text/html");
        resp.setCharacterEncoding("utf-8");
        PrintWriter writer = resp.getWriter();
        String[] params = ServletUtil.getParams(req, resp);
        params[0] = new String(params[0].getBytes("ISO-8859-1"),"UTF-8");
        params[1] = new String(params[1].getBytes("ISO-8859-1"),"UTF-8");
        if(params[0] == null || params [1]== null){
            resp.setStatus(400);
            return ;
        }
        if (JDBCUtil.findUser(params[0],params[1])){
            resp.setStatus(200);
            writer.write("<h1>Welcome</h1>");
            writer.write("username:"+params[0]+"\npassword:" + params[1]);
        }else
            resp.setStatus(400);
        writer.flush();
        System.out.println("状态码:"+resp.getStatus());
        System.out.println("----------------------------------------------------");
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        this.doGet(req,resp);
    }
}
