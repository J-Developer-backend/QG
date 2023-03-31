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

@WebServlet("/Register")
public class Register extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        resp.setContentType("text/html");
        PrintWriter writer = resp.getWriter();
        String[] params = ServletUtil.getParams(req, resp);
        boolean b = JDBCUtil.addUser(params[0], params[1]);
        if(b){
            resp.setStatus(200);
            writer.write("register succeed");
        }else
            resp.setStatus(400);
        writer.flush();
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        this.doGet(req, resp);
    }
}
